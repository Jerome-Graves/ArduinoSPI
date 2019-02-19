#include <SPI.h>

int buff ;

void setup (void)
{
  Serial.begin (9600);
  SPCR |= bit(SPE);         /* Enable SPI */
  pinMode(MISO, OUTPUT);    /* Make MISO pin as OUTPUT */
  SPI.attachInterrupt();    /* Attach SPI interrupt */
}

void loop (void)
{
 
}

// SPI interrupt routine
ISR (SPI_STC_vect)
{

   Serial.println(SPDR);
   
}
