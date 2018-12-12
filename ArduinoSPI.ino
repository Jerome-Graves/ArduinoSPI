/*
  SPI test

   digital pin 10  (SS pin)
   digital pin 11 (MOSI pin)
   digital pin 12 (MISO pin)
   digital pin 13 (SCK pin)

   digital pin 4 (encoder switch pin)
   digital pin 2 (encoder phase 1 pin)
   digital pin 3 (encoder phase 2 pin)

*/


#include <SPI.h>

const byte slaveSelectPin = 10;

const byte  encoderSwitchPin = 4;
const byte  encoderPhase1 = 2;
const byte  encoderPhase2 = 3;
      byte eoncoderVal = 0xf0;
      bool aState;
      bool aLastState;

void setup() {
  Serial.begin(9600);
  // set the slaveSelectPin as an output:
  pinMode(slaveSelectPin, OUTPUT);

  // initialize SPI:
  SPI.begin();


  pinMode(encoderSwitchPin, INPUT);
  pinMode(encoderPhase1, INPUT);
  pinMode(encoderPhase2, INPUT);
  aLastState = digitalRead(encoderPhase1);
}

void loop() {

  aState = digitalRead(encoderPhase1); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (aState != aLastState){
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(encoderPhase2) != aState) {
      eoncoderVal ++;
      SPI_send(eoncoderVal);
      Serial.print("Just sent data ");
      Serial.print("Value: ");
      Serial.println(eoncoderVal);
      Serial.print(" ");
    }
    else {
      eoncoderVal --;
      SPI_send(eoncoderVal);
      Serial.print("Just sent data ");
      Serial.print("Value: ");
      Serial.println(eoncoderVal);
      Serial.print(" ");
    }
  }
  aLastState = aState; // Updates the previous state of the outputA with the current state




}
