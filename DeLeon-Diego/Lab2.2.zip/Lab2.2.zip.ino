int SensorPin = A0; //analog input pin
int ledPin = LED_BUILTIN; //pin of the onboard LED
int sensorValue = 0; //variable that stores the LDR sensor value

void setup() 
{
  pinMode(ledPin,OUTPUT);
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
