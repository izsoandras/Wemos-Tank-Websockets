#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
#include <DNSServer.h>
#include <Hash.h>


#define DEBUGPIN 12
//#define DEBUG_ESP_HTTP_SERVER

/* Set these to your desired credentials. */
const char *ssid = "TigerTank";
//const char *password = "TigerTank";

const char* mdnsName = "tank"; // Domain name for the mDNS responder
const byte captive_portal=1;
const byte DNS_PORT = 53;
extern const char index_html[];
IPAddress apIP(192, 168, 0, 1);
DNSServer dnsServer;
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

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
const unsigned long int timeoutms = 500;

void handleRoot() {
  server.send_P(200,"text/html", index_html);
  Serial.println("handleroot: Client in.");
  }
  
   
    
void handleTest(){
  if(server.args() == 0)
    return server.send(500, "text/plain", "BAD ARGS");
  String level = server.arg(0);
  String dt = server.arg(1);
  String response = "Testing the motors to level "+level+" interval " + dt;
  server.send(200, "text/plain",  response);
  delay(100);
    for (int i =0; i<strtoi(level);i++){
        digitalWrite(frontled,!digitalRead(frontled));
        analogWrite(L2,0);
        analogWrite(L1,i);
        delay(strtoi(dt));
    }
}
server.on("/test", HTTP_GET, handleTest);    // Send a GET request to <IP>/get?message=<message>
   
 
void handle404() {
  server.send(200,"text/html", "<html><title>NO Tank</title><body>No Tank 404, try connecting to the root of the server.</body></html>");
  Serial.println("handle404");
  }
 
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
			digitalWrite(frontled,LOW);
			Serial.println("WS disconnected");
             break;
        case WStype_CONNECTED: {
            // send message to client
            webSocket.sendTXT(num, "Connected");
			digitalWrite(frontled,HIGH);
			Serial.println("WS connected");
        }
            break;
        case WStype_TEXT: {
            if(payload[0]=='g' && payload[1]=='e' && payload[2]=='t'){
/*            webSocket.sendTXT(num, senddata);
*/            }
			Serial.println("WS_Text");
        }
            break;
        case WStype_BIN: {
			if (length ==5){
				active = 1;
				analogWrite(L2,payload[0]   );
				analogWrite(L1,payload[1]   );
				analogWrite(R2,payload[2]   );
				analogWrite(R1,payload[3]   );
				if (payload[4] & 1) digitalWrite(frontled,HIGH);
				else digitalWrite(frontled,LOW);
				if (payload[4] & 0b10000000) digitalWrite(backledled,HIGH);
				else digitalWrite(backled,LOW);
				
				//we have 5 bits of pwmfreq;
				float pwmfactor = (payload[4] & 0b00111110)>>1;
				float newpwmfreq = (20000.0 * pow(0.82,pwmfactor));
				//Serial.println(pwmfactor);
				int k = (float) newpwmfreq;
				if (k!= PwmFrequency){
					PwmFrequency = k;
					analogWriteFreq(PwmFrequency);
                    if (DBG) Serial.print("PWM freq=");
                    if (DBG) Serial.println(k);
				}
				
				lastpacket = millis();
				
			}else{
				if (DBG) Serial.print("Binary packet length !=5: ");
				if (DBG) Serial.println(length);
			}
			for (int i = 0; i < length; i++){
				if (DBG) Serial.print(payload[i]);
			}
			if (DBG) Serial.println(" <-packet");
        }
        break;
    }

}
void toggletest(int pin){
  for (int i = 0; i<32;i++){
    analogWrite(pin,8*i);
    delay(1);
  }
  analogWrite(pin,0);
  delay(500);
}
void setupmotorpins(){
  analogWriteRange(255);
  analogWriteFreq(PwmFrequency) ;
  // initialise pins
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(frontled,OUTPUT);
  pinMode(backled,OUTPUT);
  digitalWrite(L1,LOW);
  digitalWrite(L2,LOW);
  digitalWrite(R1,LOW);
  digitalWrite(R2,LOW);
  digitalWrite(backled,LOW);
  toggletest(L1);
  toggletest(L2);
  toggletest(R1);
  toggletest(R2);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED,LOW);  
}

void startMDNS() { // Start the mDNS responder
  MDNS.begin(mdnsName);                        // start the multicast domain name server
  Serial.print("mDNS responder started: http://");
  Serial.print(mdnsName);
  Serial.println(".local");
}

void setup() {
	pinMode(DEBUGPIN,OUTPUT);
	setupmotorpins();
	WiFi.softAP(ssid,NULL,2);
	IPAddress myIP = WiFi.softAPIP();

	if(captive_portal) dnsServer.start(DNS_PORT, "*", apIP);
	server.onNotFound(handle404);
	server.on("/", handleRoot);
	server.begin();
    
	webSocket.onEvent(webSocketEvent);
	webSocket.begin();
	startMDNS();
	Serial.begin(115200);
	Serial.println("Tank Ready");
}

void loop() {
  webSocket.loop();
  if(captive_portal)
    dnsServer.processNextRequest();
  server.handleClient();
  if ( millis() - lastpacket>timeoutms){
      if (active){
		Serial.println("Timeout, stopping");
        digitalWrite(frontled,LOW);
		analogWrite(L2,0  );
		analogWrite(L1,0  );
		analogWrite(R2,0  );
		analogWrite(R1,0  );
		active = 0;
        lastpacket = millis();
      }else{
        digitalWrite(frontled,!digitalRead(frontled));   
        lastpacket=millis();
       }
  }
  yield();
}
