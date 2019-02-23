
//Libraries:
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif // wifi for ESP8266

#include <WiFiUdp.h>     // Datagram Protocol over wifi
#include <OSCMessage.h>  // OSC comunication
#include <OSCBundle.h>
#include <OSCData.h>
#include <SPI.h>        // SPI comunication

//Constants:
#define SELECT 3  //Chip select pin for SPI (CS)

//Control codes For SPI:
#define WAVETYPE  0x01
#define FREQ      0x02
#define PHASE     0x03
#define AMP       0x04

char ssid[] = "synth-net";          // network SSID (name)
char pass[] = "synth123";           // network password

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
const IPAddress outIp(10,40,10,105);        // remote IP
const unsigned int outPort = 9999;          // remote port
const unsigned int localPort = 8888;        // local port to listen for UDP packets
OSCErrorCode error;
unsigned int ledState = LOW;



//

void send_SPI(byte ctrl, byte data)
{
  digitalWrite(LED_BUILTIN, LOW); // debug light on
  delay(1);
  digitalWrite(SELECT, LOW); // CS enable
  SPI.transfer(ctrl); // control byte
  SPI.transfer(data); // send  data byte
  SPI.transfer(0x00); // end byte
  digitalWrite(SELECT, HIGH); // CS disable
  digitalWrite(LED_BUILTIN, HIGH); // debug light off
}

void send_SPI(byte ctrl, long data)
{
  byte buff[3];
  buff [0] =  (byte) data >> 8;
  buff [1] =  (byte) data >> 16;
  buff [2] =  (byte) data >> 24;

  digitalWrite(LED_BUILTIN, LOW);
  delay(1);
  digitalWrite(SELECT, LOW);
  SPI.transfer(ctrl); // control byte
  SPI.transfer(buff, sizeof(buff));

  SPI.transfer(0x00); // end byte
  digitalWrite(SELECT, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
}

void send_SPI(byte ctrl, uint16_t data)
{
  digitalWrite(LED_BUILTIN, LOW);
  delay(1);
  digitalWrite(SELECT, LOW);
  SPI.transfer(ctrl); // control byte
  SPI.transfer16(data);
  SPI.transfer(0x00); // end byte
  digitalWrite(SELECT, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
}




void setup() {
  pinMode(SELECT, OUTPUT); // enable CS pin
  pinMode(LED_BUILTIN, OUTPUT); // enable onboard led
  digitalWrite(LED_BUILTIN, ledState);    // turn on led

  // Set up SPI:
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  SPI.begin();
  //Begin Serial for Debug.
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





void loop() {

  OSCMessage msg; // data type to store OSC packet.
  int size = Udp.parsePacket(); // size recived udp packet

  if (size > 0) {
    while (size--) {
      msg.fill(Udp.read()); // fill msg with udp data
    }
    if (!msg.hasError()) {
      // Route osc msg to funtion.
      msg.route("/1/waveType",waveType1);
      msg.route("/1/phase", phase1);
      msg.route("/1/freq", frequ1);
      msg.route("/1/amp", amp1);

      msg.route("/2/waveType",waveType2);
      msg.route("/2/phase", phase2);
      msg.route("/2/freq", frequ2);
      msg.route("/2/amp", amp2);
    } else {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}



//Functions called when correct OSC message recived.

//wave 1 atributes
void waveType1(OSCMessage &msg,int addoff) {
  byte val = (byte)msg.getFloat(0);
  Serial.print("/waveType1: ");
  send_SPI(WAVETYPE,val);
  Serial.println(val);
}

void phase1(OSCMessage &msg,int addoff) {
  uint16_t  val = (short)msg.getFloat(0);
  Serial.print("/pitch1: ");
  send_SPI(PHASE,val);
  Serial.println(val);
}

void frequ1(OSCMessage &msg,int addoff) {
  long val = (long)msg.getFloat(0);
  Serial.print("/frequ1: ");
  send_SPI(FREQ,val);
  Serial.println(val);
}

void amp1(OSCMessage &msg,int addoff) {
  uint16_t  val = (short)msg.getFloat(0);
  Serial.print("/amp1: ");
  send_SPI(AMP,val);
  Serial.println(val);
}


//Wave 2 atributes
void waveType2(OSCMessage &msg,int addoff) {
  byte val = (byte)msg.getFloat(0);
  Serial.print("/waveType2: ");
  send_SPI(WAVETYPE+0x10,val);
  Serial.println(val);
}

void phase2(OSCMessage &msg,int addoff) {
  uint16_t val = (short)msg.getFloat(0);
  Serial.print("/pitch2: ");
  send_SPI(PHASE+0x10,val);
  Serial.println(val);
}

void frequ2(OSCMessage &msg,int addoff) {
  long val = (long)msg.getFloat(0);
  Serial.print("/frequ2: ");
  send_SPI(FREQ+0x10,val);
  Serial.println(val);
}

void amp2(OSCMessage &msg,int addoff) {
  uint16_t  val = (short)msg.getFloat(0);
  Serial.print("/amp2: ");
  send_SPI(AMP+0x10,val);
  Serial.println(val);
}
