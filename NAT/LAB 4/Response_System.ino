#include "dweetESP8266.h"
#include "Servo.h"

#define THIG_NAME "I4ET-Group1-FIREMEN"
#define RED_LED D1
#define GREEN_LED D2
#define BLUE_LED D3
#define Electrical_Connectivity D4
#define servo_pin D5

int ABC=0;
int Electrical= 1;
int water = 0;
int Elec =0;
int Extractor = 0;

Servo myservo;
int angle = 0; 

const char* ssid = "dfa4fe";
const char* password = "271435942";

dweet DweetClient;
 char *key1 = "Flame_Sensor";//this is the name of the parameter sent to Dweet.io
 char *key2 = "Smoke_Sensor";
 char *key5 = "ABC_Extinguisher";
 char *key6 = "C02_Extinguisher";
 char *key7 = "Water_Sprinkler";
 char *key8 = "Air_Quality";
 char *key9 = "Class_Variable";
 char *key10 = "Extractor_Fan";
 
 
void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(Electrical_Connectivity, INPUT);

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
  myservo.attach(servo_pin);
  }
char val[16]; //it stores a number composed by up to 16 characters

void loop() {
 String Class_Variable = DweetClient.getDweet(THIG_NAME, key9);
 int Class_Variable_int = Class_Variable.toInt();
 delay(500);
 String Air_Quality = DweetClient.getDweet(THIG_NAME, key8);
 int Air_Quality_int = Air_Quality.toInt();
 delay(500);
 String Smoke_Sensor = DweetClient.getDweet(THIG_NAME, key2);
 int Smoke_Sensor_int = Smoke_Sensor.toInt();
 delay(500);
 
//Class of Fire
 Electrical = digitalRead(Electrical_Connectivity);
 if (Class_Variable_int == 1)
  {
   if (Air_Quality_int>=2000)
  {
    Serial.println("Class C type of Fire. Gas Fire");
    Serial.println("ABC Fire Extinguisher is released");
    digitalWrite(GREEN_LED, HIGH);
    delay(2000);
    digitalWrite(GREEN_LED, LOW);
    delay(2000);
    ABC = 1;
    }
    else if (Electrical == 0)
    {
     Elec = 1;
     Serial.println("Class E type of Fire. Electrical Fire");
     Serial.println("CO2 Fire Extinguisher is released");
     Serial.println("Seal Area");
     digitalWrite(RED_LED, HIGH);
     delay(2000);
     digitalWrite(RED_LED, LOW);
     delay(2000); 
    }
    else 
    {
      water = 1;
      Serial.println("Class A type of Fire. Other Fire");
      digitalWrite(BLUE_LED, HIGH);
      delay(2000);
      digitalWrite(BLUE_LED, LOW);
      delay(2000);
     }
}
 else
 {
  Serial.println("No Flame is detected"); 
  ABC = 0;
  Electrical = 0;
  Elec = 0;
  water = 0;
 }

//Extractor Fan
if ((Class_Variable_int == 0) && (Smoke_Sensor_int == 1))
{ // move from 0 to 180 degrees with a positive angle of 1
  Extractor = 1;
  Serial.println("Extractor fan is ON");
  for(angle = 0; angle < 180; angle += 1)
  {                          
    myservo.write(angle);
    delay(15);                       
  } 

  delay(1000);
  
  // move from 180 to 0 degrees with a negative angle of 5
  for(angle = 180; angle>=1; angle-=5)
  {                                
    myservo.write(angle);
    delay(5);                       
  } 

    delay(1000);
}
else 
{
  Serial.println("Extractor fan is OFF");
  delay(500);
  digitalWrite(servo_pin, LOW);
  Extractor = 0;
}
//Sending Values to Server
//ABC_Extinguisher
  itoa(ABC, val, 10); //convert an integer value into a char array
  DweetClient.add(key5, val);
  DweetClient.sendAll(THIG_NAME);
//C02_Extinguisher
  itoa(Elec, val, 10); //convert an integer value into a char array
  DweetClient.add(key6, val);
  DweetClient.sendAll(THIG_NAME);
//Water_Sprinkler
  itoa(water, val, 10); //convert an integer value into a char array
  DweetClient.add(key7, val);
  DweetClient.sendAll(THIG_NAME);
//Extractor Fan
  itoa(Extractor, val, 10); //convert an integer value into a char array
  DweetClient.add(key10, val);
  DweetClient.sendAll(THIG_NAME);
}
