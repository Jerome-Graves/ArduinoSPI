
/*
  SPI test

   digital pin 10  (SS pin)
   digital pin 11 (MOSI pin)
   digital pin 12 (MISO pin)
   digital pin 13 (SCK pin)


*/


#include <SPI.h>
#include <EnableInterrupt.h>
#include <LiquidCrystal.h>

// Pins for encoders.
#define ENCODER0_PIN_A  A8
#define ENCODER0_PIN_B  A9
#define ENCODER1_PIN_A  A10
#define ENCODER1_PIN_B  A11

//Pins for LCD.
#define LCD_RS          12
#define LCD_EN          11
#define LCD_D4          5
#define LCD_D5          4
#define LCD_D6          3
#define LCD_D7          2

// SPI slave select pin for FPGA.
#define SLAVESELECT_PIN 10


// Encoder position stored as byte.
volatile byte encoder0Pos = 0 ;
volatile byte encoder1Pos = 0 ;

// Create LCD object.
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  Serial.begin(9600);

  // Set up the LCD's number of columns and rows.
    lcd.begin(16, 2);


  // Set the slaveSelectPin as an output.
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
  delay(100); // debug delay

  // Send over SPI.
  SPI_send(encoder0Pos);
  SPI_send(encoder1Pos);

  // Print to LCD.
  lcd.clear();
  lcd.print(" !!Synthy Boy!!");
  lcd.setCursor(0, 1);
  lcd.print(encoder0Pos, DEC);
  lcd.setCursor(7, 1);
  lcd.print("::");
  lcd.setCursor(13, 1);
  lcd.print(encoder1Pos, DEC);
}
