int Led = LED_BUILTIN;
int sensorD0 = D1;
int val;

void setup() 
{
  pinMode(Led,OUTPUT);
  pinMode(sensorD0,INPUT);
}

void loop() {
  val=digitalRead(sensorD0);
  if(val==HIGH)
  {
    digitalWrite(Led,LOW);
  }
  else
  {
    digitalWrite(Led,HIGH);
  }
}
