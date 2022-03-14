#define redpin D1
#define greenpin D2
#define bluepin D3
#define Buzzer D4

#include "pitches.h"
//int melody[] = {
  //NOTE_C5, NOTE_E5, NOTE_C5};
  

int val;

void setup() {
  // put your setup code here, to run once:
pinMode(redpin, OUTPUT);
pinMode(greenpin, OUTPUT);
pinMode(bluepin, OUTPUT);
pinMode(Buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
for (val=0; val<50; val++)
{
  analogWrite(redpin,val);
  analogWrite(bluepin, 50-val);
  analogWrite(greenpin, 23-val);
  delay(10);
  tone(Buzzer,NOTE_C6 );
}
for (val=0; val<50; val++) 
{
  analogWrite(redpin,val);
  analogWrite(bluepin, 50-val);
  analogWrite(greenpin, 23-val);
  delay(10);
  tone(Buzzer,NOTE_E4 );
}
}
