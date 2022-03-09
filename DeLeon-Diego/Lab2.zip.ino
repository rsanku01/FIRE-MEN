int sensorPin = A0;
int ledPin = LED_BUILTIN;
int sensorValue = 0;

void setup()
{
  pinMode(ledPin.OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  sensorValue = analogRead(sensorPin);
  if (sensorValue > 900)
  {
    digitalWrite(ledPin, LOW);
  }
  else
  {
    digitalWrite(ledPin, HIGH);
  }
 Serial.println(sensorValue, DEC); 
}
