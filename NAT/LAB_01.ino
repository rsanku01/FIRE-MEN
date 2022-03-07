//The code is to activate the builtin LED by pressing the character N
//The code is to deactivate the builtin LED by pressing the character E

void setup() 
{
pinMode(D4, OUTPUT);
digitalWrite(D4, HIGH);

Serial.begin(230400);
}

void loop() 
{
  if (Serial.available() > 0)
  {
  int letter = Serial.read();
  if (letter == 'N')
  {
    Serial.println("The LED is ON/ACTIVATED");
    digitalWrite(D4, LOW);
  }
  else if (letter == 'E')
  {
    Serial.println("The LED is OFF/DEACTIVATED");
    digitalWrite(D4,HIGH);
  }
  }
}
