int IRsensor = D1;
int led = D4;
int Value;

void setup() {
  // put your setup code here, to run once:
pinMode(D4, OUTPUT);
pinMode(D1, INPUT);
 Serial.begin(9600);
 
}

void loop() {
  // put your main code here, to run repeatedly:
Value = digitalRead(IRsensor);
if (Value == HIGH )
{
  digitalWrite(D4, LOW);
  Serial.println("Flame is Detected");
  delay(2000);
}
else
{
digitalWrite(D4, HIGH);
Serial.println("No Flame Present");
delay(2000);
}

}
