//The code is to detect the presence of LPG in a compartment then triger the safety system

#define Gas_Sensor D1 //LPG Sensor
#define redpin D3 
#define greenpin D4 
#define bluepin D5 
#define Buzzer D6 

#include "pitches.h"
  
int val;

void setup() {
Serial.begin(230400);
pinMode(Gas_Sensor, INPUT);
pinMode(redpin, OUTPUT);
pinMode(greenpin, OUTPUT);
pinMode(bluepin, OUTPUT);
pinMode(Buzzer, OUTPUT);
}

void loop() {
  boolean state = digitalRead(Gas_Sensor);
  if (state)    
  {
    Serial.println("No Gas is detected"); //Display the state of the sensors
    delay(1000);
    
  }
  else
  {
    Serial.println("Gas is detected"); //Display the state of the sensors
    Serial.println("Gas alarm is triggered"); // Trigger on the Alarm system
    delay(1000);
    //The alarm system produces a Siren Warning Sound (buzzer sound + flashing RGB LED).
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
 
  }
