#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
#include <DNSServer.h>
#include <Hash.h>

#include <Wire.h>
#include "WEMOS_Motor.h"

#define bit(b) (1UL << (b)) // Taken directly from Arduino.h
#define DEBUGPIN 12
//#define DEBUG_ESP_HTTP_SERVER

/* Set these to your desired credentials. */
const char *ssid = "TigerTank";
//const char *password = "TigerTank";

const char* mdnsName = "tank"; // Domain name for the mDNS responder
const byte captive_portal = 1;
const byte DNS_PORT = 53;
extern const char index_html[];
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

Motor ML(0x30, _MOTOR_A, 1000);
Motor MR(0x30, _MOTOR_B, 1000);

#define L1 4
#define L2 5
#define R1 0
#define R2 14
#define frontled 12
#define backled 13

int PwmFrequency = 20000;
bool active = 0;
bool DBG = false;
unsigned long int lastpacket = 0;
const unsigned long int timeoutms = 50000;

void handleRoot() {
  server.send_P(200, "text/html", index_html);
  Serial.println("handleroot: Client in.");
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      digitalWrite(frontled, LOW);
      Serial.println("WS disconnected");
      break;
    case WStype_CONNECTED: {
        // send message to client
        webSocket.sendTXT(num, "Connected");
        digitalWrite(frontled, HIGH);
        Serial.println("WS connected");
      }
      break;
    case WStype_TEXT: {
        if (payload[0] == 'g' && payload[1] == 'e' && payload[2] == 't') {
          /*            webSocket.sendTXT(num, senddata);
          */
        }
        Serial.println("WS_Text");
      }
      break;
    case WStype_BIN: {
        Serial.println("WS_Bin");
        if (length == 5) {
          active = 1;

          if (payload[0] == 0 && payload[1] == 0)
            ML.setmotor(_STOP);
          else if (payload[0] == 0)
            ML.setmotor(_CCW, payload[1]);
          else
            ML.setmotor(_CW, payload[0]);

          if (payload[2] == 0 && payload[3] == 0)
            MR.setmotor(_STOP);
          else if (payload[2] == 0)
            MR.setmotor(_CW, payload[3]);
          else
            MR.setmotor(_CCW, payload[2]);

          if(payload[4] & 2)
            ;//do nothing, it's handlend on JS side
            
          if(payload[4] & 4){
            //turn on headlights
          }else{
            
          }
          if(payload[4] & 8){
            
          }else{
            
          }
          if(payload[4] & 16){
          }else{
            
          }
          if(payload[4] & 32){
            
          }else{
            
         }
          if(payload[4] & 64){
            
          }else{
            
          }
//          //we have 5 bits of pwmfreq;
//          float pwmfactor = (payload[4] & 0b00111110) >> 1;
//          float newpwmfreq = (20000.0 * pow(0.82, pwmfactor));
//          //Serial.println(pwmfactor);
//          int k = (float) newpwmfreq;
//          if (k != PwmFrequency) {
//            PwmFrequency = k;
//            //analogWriteFreq(PwmFrequency);
//            ML.setfreq(PwmFrequency);
//            MR.setfreq(PwmFrequency);
//            if (DBG) Serial.print("PWM freq=");
//            if (DBG) Serial.println(k);
//          }

          lastpacket = millis();

        } else {
          Serial.print("Binary packet length !=5: ");
          Serial.println(length);
        }
        for (int i = 0; i < length; i++) {
          Serial.print(payload[i]);
        }
        Serial.println(" <-packet");
      }
      break;
  }

}

void setupmotorpins() {
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);

  ML.setfreq(2000);
  MR.setfreq(2000);

  ML.setmotor(_CCW, 50);
  MR.setmotor(_CCW, 50);
  delay(500);
  ML.setmotor(_STOP);
  MR.setmotor(_STOP);
}

void startMDNS() { // Start the mDNS responder
  MDNS.begin(mdnsName);                        // start the multicast domain name server
  Serial.print("mDNS responder started: http://");
  Serial.print(mdnsName);
  Serial.println(".local");
}

void setup() {
  pinMode(DEBUGPIN, OUTPUT);
  setupmotorpins();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, NULL, 2);
  IPAddress myIP = WiFi.softAPIP();


  if (captive_portal) dnsServer.start(DNS_PORT, "*", apIP);
  server.on("/", handleRoot);
  server.begin();

  webSocket.onEvent(webSocketEvent);
  webSocket.begin();
  startMDNS();
  Serial.begin(115200);
  Serial.println("Tank Ready");
  Serial.println(myIP);
}

void loop() {
  webSocket.loop();
  if (captive_portal)
    dnsServer.processNextRequest();
  server.handleClient();
  if ( millis() - lastpacket > timeoutms) {
    if (active) {
      Serial.println("Timeout, stopping");
      digitalWrite(frontled, LOW);
      ML.setmotor(_STOP);
      MR.setmotor(_STOP);
      active = 0;
      lastpacket = millis();
    } else {
      digitalWrite(frontled, !digitalRead(frontled));
      lastpacket = millis();
    }
  }
  yield();
}
