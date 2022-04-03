#include "dweetESP8266.h"
#define THIG_NAME "I4ET-Group1-FIREMEN"
#define Flame_Sensor D1

int Class_Variable =0;
int Flame_State = 0;

const char* ssid = "dfa4fe";
const char* password = "271435942";

dweet DweetClient;
 char *key1 = "Flame_Sensor";//this is the name of the parameter sent to Dweet.io
 char *key9 = "Class_Variable";
void setup() {
  Serial.begin(9600);
  pinMode(Flame_Sensor, INPUT);
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
 Flame_State = digitalRead(Flame_Sensor);
  if (Flame_State == 0)    
  {
    Serial.println("No Flame is detected"); //Display the state of the sensors
    delay(2000);
    Class_Variable = 0;
  }
  else 
  {
    Serial.println("Flame is detected"); //Display the state of the sensors
    delay(2000);
    Class_Variable = 1; //Variable to determine the class of fire
  }
//Sending Values to Server
//Flame
itoa(Flame_State, val, 10); //convert an integer value into a char array
  DweetClient.add(key1, val);
  DweetClient.sendAll(THIG_NAME);
//Class_Variable
itoa(Class_Variable, val, 10); //convert an integer value into a char array
  DweetClient.add(key9, val);
  DweetClient.sendAll(THIG_NAME);
}
