
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

#define SELECT 3  //chip select

char ssid[] = "synth-net";          // network SSID (name)
char pass[] = "synth123";           // network password

byte val = 0;




// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
const IPAddress outIp(10,40,10,105);        // remote IP
const unsigned int outPort = 9999;          // remote port
const unsigned int localPort = 8888;        // local port to listen for UDP packets
OSCErrorCode error;
unsigned int ledState = LOW;



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
  digitalWrite(LED_BUILTIN, ledState);    // turn *on* led

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
  //Serial.println(Udp.localPort());
#endif

}





void loop() {

  OSCMessage msg;
  int size = Udp.parsePacket();

  if (size > 0) {
    while (size--) {
      msg.fill(Udp.read());
    }
    if (!msg.hasError()) {
      // Route osc msg to funtion.
      msg.route("/1/slider", slider);

      msg.route("/1/waveType",waveType1);
      msg.route("/1/phase1", phase1);
      msg.route("/1/freq", frequ1);
      msg.route("/1/amp", amp1);

      msg.route("/2/waveType",waveType2);
      msg.route("/2/phase2", phase2);
      msg.route("/2/freq", frequ2);
      msg.route("/2/amp", amp2);
    } else {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}


//slider
void slider(OSCMessage &msg,int addoff) {
  val = (byte)msg.getFloat(0);
  Serial.print("/Slider: ");
  send_SPI(val);
  Serial.println(val);
}


//wave 1 atributes
void waveType1(OSCMessage &msg,int addoff) {
  val = (byte)msg.getFloat(0);
  Serial.print("/waveType1: ");
  send_SPI(val);
  Serial.println(val);
}

void phase1(OSCMessage &msg,int addoff) {
  val = (byte)msg.getFloat(0);
  Serial.print("/pitch1: ");
  send_SPI(val);
  Serial.println(val);
}

void frequ1(OSCMessage &msg,int addoff) {
  val = (byte)msg.getFloat(0);
  Serial.print("/frequ1: ");
  send_SPI(val);
  Serial.println(val);
}

void amp1(OSCMessage &msg,int addoff) {
  val = (byte)msg.getFloat(0);
  Serial.print("/amp1: ");
  send_SPI(val);
  Serial.println(val);
}


//Wave 2 atributes
void waveType2(OSCMessage &msg,int addoff) {
  val = (byte)msg.getFloat(0);
  Serial.print("/waveType2: ");
  send_SPI(val);
  Serial.println(val);
}

void phase2(OSCMessage &msg,int addoff) {
  val = (byte)msg.getFloat(0);
  Serial.print("/pitch2: ");
  send_SPI(val);
  Serial.println(val);
}

void frequ2(OSCMessage &msg,int addoff) {
  val = (byte)msg.getFloat(0);
  Serial.print("/frequ2: ");
  send_SPI(val);
  Serial.println(val);
}

void amp2(OSCMessage &msg,int addoff) {
  val = (byte)msg.getFloat(0);
  Serial.print("/amp2: ");
  send_SPI(val);
  Serial.println(val);
}
