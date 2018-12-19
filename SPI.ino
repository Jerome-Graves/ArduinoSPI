

void SPI_send(char value) {

  // take the SS pin low to select the chip:
  digitalWrite(SLAVESELECT_PIN, LOW);

  //  send in the value via SPI:
  SPI.transfer(value);

  // take the SS pin high to de-select the chip:
  digitalWrite(SLAVESELECT_PIN, HIGH);
}
