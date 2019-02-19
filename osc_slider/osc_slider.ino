/*---------------------------------------------------------------------------------------------
  Open Sound Control (OSC) library for the ESP8266/ESP32
  Example for receiving open sound control (OSC) messages on the ESP8266/ESP32
  Send integers '0' or '1' to the address "/led" to turn on/off the built-in LED of the esp8266.
  This example code is in the public domain.
--------------------------------------------------------------------------------------------- */
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <SPI.h>

#define SELECT 3

char ssid[] = "synth-net";          // your network SSID (name)
char pass[] = "synth123";                    // your network password

 byte val = 0;

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
const IPAddress outIp(10,40,10,105);        // remote IP (not needed for receive)
const unsigned int outPort = 9999;          // remote port (not needed for receive)
const unsigned int localPort = 8888;        // local port to listen for UDP packets (here's where we send the packets)


OSCErrorCode error;
unsigned int ledState = LOW;              // LOW means led is *on*



void send_SPI(byte data)
{

  digitalWrite(LED_BUILTIN, LOW);
  delay(1);
  
  digitalWrite(SELECT, LOW);
  
   SPI.transfer(data);
  digitalWrite(SELECT, HIGH);

  digitalWrite(LED_BUILTIN, HIGH);
  //delay(1);
}






void setup() {
  pinMode(SELECT, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(BUILTIN_LED, ledState);    // turn *on* led

  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  SPI.begin();

  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
#ifdef ESP32
  Serial.println(localPort);
#else
  Serial.println(Udp.localPort());
#endif

}


void slider(OSCMessage &msg,int addoff) {
  val = (byte)msg.getFloat(0);
  //digitalWrite(LED_BUILTIN, ledState);
  Serial.print("/Slider: ");
  send_SPI(val);
  Serial.println(val);
}

void loop() {
  
  OSCMessage msg;
  int size = Udp.parsePacket();

  if (size > 0) {
    while (size--) {
      msg.fill(Udp.read());
    }
    if (!msg.hasError()) {
      msg.route("/1/slider", slider);
    } else {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}
