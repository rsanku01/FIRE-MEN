void setup() {
  Serial.begin(230400);

}

void loop() {
  if (Serial.available() > 0) // checking if info from serial port.
  {
    if (Serial.read() == 100) //100 is ASCII code for D.
    {
      digitalWrite(LED_BUILTIN, HIGH);
      }
    if (Serial.read() == 111) //111 is ASCII code for O.
    {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
