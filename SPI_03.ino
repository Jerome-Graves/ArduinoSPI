#include <SPI.h>

#define SELECT 3


 byte val = 0;
 bool dir = 0;

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
  // put your setup code here, to run once:
  pinMode(SELECT, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  Serial.begin(9600);

  SPI.begin();

}

void loop() {
  delay(500);
  if (dir == false) {
    val += 1;
  } else {
    val -= 1;
  }

  if (val == 0 || val == 255)
    dir = !dir;

  
 
  // put your main code here, to run repeatedly:

  
  send_SPI(val);
  Serial.println(val);
  
}
