#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
#include <DNSServer.h>
#include <math.h>

#include <Wire.h>
#include "WEMOS_Motor.h"

#define ENABLE_MOT

/*Physical connections*/
#define REVERSE_LIGHT 0       // reverse lights     D3 / GPIO0
#define CONNECT_LED 2             // connection     D4 / GPIO2 -- BUILTIN_LED
#define RIGHT_TURN_SIGNAL 12  // right turn signal  D6 / GPIO 12
#define BRAKE_LIGHT 13        // brake lights       D7 / GPIO13
#define LEFT_TURN_SIGNAL 14   // left turn signal   D5 / GPIO14
#define HEAD_LIGHT 15         // front lights       D8 / GPIO15

/*Tank physical parameters*/
const float b = 1.0;

/*Timing parameters*/
const unsigned long int activeCycle = 10;           // [ms]
const unsigned long int turnSignalLength = 666;     // [ms]
const unsigned long int minBrakeLightLength = 100;  // [ms]
const unsigned long int timeoutms = 1000;          // [ms]
const unsigned long int idleCycle = 30;             // [ms]

/* Network parameters */
const char *ssid = "TigerTank";
const char *password = "";
const char* mdnsName = "tank"; // Domain name for the mDNS responder
const byte DNS_PORT = 53;
extern const char index_html[];
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

/* Motor controllers */
Motor ML(0x30, _MOTOR_A, 1000);
Motor MR(0x30, _MOTOR_B, 1000);
int PwmFrequency = 20000;

/*State variables*/
int v, v_prev, omega, v_L, v_R = 0;
bool emergency_signal_on, headlight_on = 0;
bool active, breaking = 0;
int16_t idleDuty = 0;
int8_t idleDir = 1;
unsigned long int currentMillis = 0;
unsigned long int lastCycle = 0;
unsigned long int lastpacket = 0;
unsigned long int lastTurnSignal = 0;
unsigned long int lastNotBrake = 0;

/*root http response: send html site*/
void handleRoot() {
  /*server.send_P(200, "text/html", index_html);*/
  if(SPIFFS.exists("/index.html")){
    File f = SPIFFS.open("/index.html","r");
    server.streamFile(f, "text/html");
    f.close();
  }else{
    Serial.println("Error: no index.html found");
  }
  Serial.println("handleroot: Client in.");
}

/*redirect to root if page not found*/
void handleNotFound()
{
  server.sendHeader("Location", "/", true); //Redirect to our html web page
  server.send(302, "text/plane", "");
}

/*websocket event handler*/
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      digitalWrite(CONNECT_LED, HIGH);
      Serial.println("WS disconnected");
      break;
    case WStype_CONNECTED: {
        // send message to client
        webSocket.sendTXT(num, "Connected");
        digitalWrite(CONNECT_LED, LOW);
        Serial.println("WS connected");
      }
      break;
    case WStype_BIN: {
        //Serial.println("WS_Bin");
        // payload: v, omega, buttons
        Serial.print("WS msg received: ");
        for (uint8_t i = 0; i < length; i++) {
          Serial.print(payload[i]);
          Serial.print(", \t");
        }
        Serial.println();
        if (length == 3) {
          active = 1;
          v = ((int)payload[0] - 127) * 2;
          omega = ((int)payload[1] - 127) * 2;

          v_L = v - b / 2 * omega;
          v_R = v + b / 2 * omega;

          Serial.printf("%d\t%d\n", v_L, v_R);

          /* Server side */
          //          if (payload[2] & 1)

          headlight_on = payload[2] & 2;
          emergency_signal_on = payload[2] & 4;

          /* RESERVED */
          //          if (payload[2] & 8) {
          //
          //          } else {
          //
          //          }
          //          if (payload[2] & 16) {
          //          } else {
          //
          //          }
          //          if (payload[2] & 32) {
          //
          //          } else {
          //
          //          }

          lastpacket = millis();

        } else {
          Serial.print("Binary packet length !=3: ");
          Serial.println(length);
        }
      }
      break;
    default:
      Serial.print("Unsupported WS message type: ");
      Serial.println(type);
      break;
  }

}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Setup start");

  /*Init lights*/
  pinMode(CONNECT_LED, OUTPUT);
  digitalWrite(CONNECT_LED, HIGH);

  pinMode(REVERSE_LIGHT, OUTPUT);
  digitalWrite(REVERSE_LIGHT, LOW);

  pinMode(LEFT_TURN_SIGNAL, OUTPUT);
  digitalWrite(LEFT_TURN_SIGNAL, LOW);

  pinMode(BRAKE_LIGHT, OUTPUT);
  digitalWrite(BRAKE_LIGHT, LOW);

  pinMode(HEAD_LIGHT, OUTPUT);
  digitalWrite(HEAD_LIGHT, LOW);

  pinMode(RIGHT_TURN_SIGNAL, OUTPUT);
  digitalWrite(RIGHT_TURN_SIGNAL, LOW);

  /*Init motor drivers*/
#ifdef ENABLE_MOT
  ML.setfreq(PwmFrequency);
  MR.setfreq(PwmFrequency);

  ML.setmotor(_CCW, 50);
  MR.setmotor(_CW, 50);
  delay(10);
  ML.setmotor(_STOP);
  MR.setmotor(_STOP);
#endif

  /*Init file system*/
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  /*Init network*/
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); // local_ip, gateway, subnet mask
  WiFi.softAP(ssid, password, 2, false, 1);                   // ssid, pwd, channel, hidden, max conn
  Serial.println(WiFi.softAPIP());

  dnsServer.start(DNS_PORT, "*", apIP);

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();

  webSocket.onEvent(webSocketEvent);
  webSocket.begin();

  MDNS.begin(mdnsName);                        // start the multicast domain name server
  MDNS.addService("http", "tcp", 80);
  Serial.print("mDNS responder started: http://");
  Serial.print(mdnsName);
  Serial.println(".local");

  /*Setup finish*/
  Serial.println("Tank Ready");
}


void loop() {
  // operate web services
  dnsServer.processNextRequest();
  MDNS.update();
  server.handleClient();
  webSocket.loop();

  currentMillis = millis();
  if ( currentMillis  - lastpacket > timeoutms) {
    if (active) {
      Serial.println("Timeout, stopping");
      webSocket.disconnect();
      ML.setmotor(_STOP);
      MR.setmotor(_STOP);
      active = 0;
    }
  }

  if (currentMillis  - lastCycle >= activeCycle && active) {
    /*Handle motor*/
#ifdef ENABLE_MOT
    if (v_L == 0)
      ML.setmotor(_STOP);
    else {
      if (v_L > 0)
        ML.setmotor(_CCW, v_L);
      else
        ML.setmotor(_CW, -v_L);
    }
    if (v_R == 0)
      MR.setmotor(_STOP);
    else {
      if (v_R > 0)
        MR.setmotor(_CW, v_R);
      else
        MR.setmotor(_CCW, -v_R);
    }
#endif

    /*Handle lights*/
    // Headlight
    digitalWrite(HEAD_LIGHT, headlight_on);

    // Reverse light
    if (v < 0) {
      analogWrite(REVERSE_LIGHT, 128);
    } else {
      analogWrite(REVERSE_LIGHT, 0);
    }

    // Brake light
    if (abs(v_prev) > abs(v) || ((currentMillis - lastNotBrake) <= minBrakeLightLength)) {
      if (breaking == 0)
        lastNotBrake = currentMillis;
      breaking = 1;
      analogWrite(BRAKE_LIGHT, 255);
    } else {
      analogWrite(BRAKE_LIGHT, 50);
      breaking = 0;
    }

    // Turn signals
    if (currentMillis - lastTurnSignal >= turnSignalLength) {
      // Left turn signal
      if (v * omega > 0 || emergency_signal_on) {
        digitalWrite(LEFT_TURN_SIGNAL, !digitalRead(LEFT_TURN_SIGNAL));
      } else {
        digitalWrite(LEFT_TURN_SIGNAL, LOW);
      }

      // Right turn signal
      if (v * omega < 0 || emergency_signal_on) {
        digitalWrite(RIGHT_TURN_SIGNAL, !digitalRead(RIGHT_TURN_SIGNAL));
      } else {
        digitalWrite(RIGHT_TURN_SIGNAL, LOW);
      }

      lastTurnSignal = currentMillis;
    }

    v_prev = v;
    lastCycle = currentMillis ;
  }

  if (currentMillis  - lastCycle >= idleCycle && !active) {
    analogWrite(HEAD_LIGHT, idleDuty);
    analogWrite(BRAKE_LIGHT, idleDuty);
    analogWrite(REVERSE_LIGHT, idleDuty);
    analogWrite(LEFT_TURN_SIGNAL, idleDuty);
    analogWrite(RIGHT_TURN_SIGNAL, idleDuty);

    idleDuty += idleDir;

    if (idleDuty == -10 || idleDuty == 200)
      idleDir *= -1;

    lastCycle = currentMillis;
  }
  yield();
}
