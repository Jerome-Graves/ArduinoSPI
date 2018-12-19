
/*
  SPI test

   digital pin 10  (SS pin)
   digital pin 11 (MOSI pin)
   digital pin 12 (MISO pin)
   digital pin 13 (SCK pin)


*/


#include <SPI.h>
#include <EnableInterrupt.h>

// Pins for encoders.
#define ENCODER0_PIN_A  A8
#define ENCODER0_PIN_B  A9
#define ENCODER1_PIN_A  A10 
#define ENCODER1_PIN_B  A11 


// SPI slave select pin for FPGA
#define SLAVESELECT_PIN 10


// Position stored as byte.
volatile byte encoder0Pos = 0 ;
volatile byte encoder1Pos = 0 ;



void setup() {
  Serial.begin(9600);


  // Set the slaveSelectPin as an output:
  pinMode(SLAVESELECT_PIN, OUTPUT);
  // initialize SPI:
  SPI.begin();


   // Set Encoder pins to Input and enable Pullup resistors.
  pinMode(ENCODER0_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER0_PIN_B, INPUT_PULLUP);
  pinMode(ENCODER1_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER1_PIN_B, INPUT_PULLUP);

  // Enable Interrupts
  enableInterrupt(ENCODER0_PIN_A, encoder0_Interrupt, FALLING);
  enableInterrupt(ENCODER1_PIN_A, encoder1_Interrupt, FALLING);
}

void loop() {
  SPI_send(encoder0Pos);
  SPI_send(encoder1Pos);
  delay(1000);
  disableInterrupt(ENCODER0_PIN_A);
  disableInterrupt(ENCODER1_PIN_A);
  Serial.print("--- sent :");
  Serial.print(encoder0Pos, DEC);
  Serial.print(", ");
  Serial.print(encoder1Pos, DEC);
  Serial.print(" --- ");
  enableInterrupt(ENCODER0_PIN_A, encoder0_Interrupt, FALLING);
  enableInterrupt(ENCODER1_PIN_A, encoder1_Interrupt, FALLING);
  
}
