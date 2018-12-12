

void SPI_send(byte value) {

  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);

  //  send in the value via SPI:
  SPI.transfer(value);


  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
}
