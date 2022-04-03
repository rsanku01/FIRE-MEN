#include "dweetESP8266.h"
#include "pitches.h"
#define THIG_NAME "I4ET-Group1-FIREMEN"
#define Alarm_LED D1
#define Buzzer D2

int alarm =0;
const char* ssid = "dfa4fe";
const char* password = "271435942";

dweet DweetClient;
 char *key1 = "Flame_Sensor";//this is the name of the parameter sent to Dweet.io
 char *key4 = "Alarm";
 char *key9 = "Class_Variable";
 
void setup() {
  Serial.begin(9600);
  pinMode(Alarm_LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  //Conecting to a WiFi network
   Serial.println();
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(ssid);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  }
char val[16]; //it stores a number composed by up to 16 characters

void loop() {
 String Class_Variable = DweetClient.getDweet(THIG_NAME, key9);
 int Class_Variable_int = Class_Variable.toInt();

 if (Class_Variable_int == 1)
  {
    alarm = 1;
    Serial.println("Alarm is triggered"); // Trigger on the Alarm system
    Serial.println("Alarm System is ON....");
    digitalWrite(Alarm_LED, HIGH);
    //Alarm System
    Serial.println("Alarm is triggered"); // Trigger on the Alarm system
    delay(1000);
    Serial.println("Alarm System is ON....");
    digitalWrite(Alarm_LED, HIGH);
    tone(Buzzer, NOTE_C6);
    delay(500);
    tone(Buzzer, NOTE_E4);
    delay(500);
    tone(Buzzer, NOTE_C6);
    delay(500);
    tone(Buzzer, NOTE_E4);
    delay(500);
  }
  else 
  {
    alarm = 0;
  }
    digitalWrite(Buzzer, LOW);
    digitalWrite(Alarm_LED, LOW);
    delay(500);
 
//Sending Values to Server
//Alarm
  itoa(alarm, val, 10); //convert an integer value into a char array
  DweetClient.add(key4, val);
  DweetClient.sendAll(THIG_NAME);
}
