// Encoder interrrupt functions.

void encoder0_Interrupt() {
if (digitalRead(ENCODER0_PIN_A) == digitalRead(ENCODER0_PIN_B)) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  } 
}

void encoder1_Interrupt() {
  if (digitalRead(ENCODER1_PIN_A) == digitalRead(ENCODER1_PIN_B)) {
    encoder1Pos++;
  } else {
    encoder1Pos--;
  }
}
