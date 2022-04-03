
#include <MQ135.h>

#include "pitches.h"
#include "dweetESP8266.h"
#define THIG_NAME "I4ET-Group1-FIREMEN" //Put here you thing name


#define PIN_MQ135 A0

MQ135 mq135_sensor(PIN_MQ135);
#include <OneWire.h>
#include <DallasTemperature.h>

#define Flame_Sensor D1
#define Temperature_Sensor D2
#define Alarm_LED D3
#define Buzzer D4
#define RED_LED D5
#define GREEN_LED D6
#define BLUE_LED D7
#define Electrical_Connectivity D8

OneWire oneWire(Temperature_Sensor);

DallasTemperature sensors(&oneWire);

const char* ssid = "dfa4fe";
const char* password = "271435942";

dweet DweetClient;
 char *key1 = "Flame_Sensor";//this is the name of the parameter sent to Dweet.io
 char *key2 = "Smoke_Sensor";
 char *key3 = "Temperature_Sensor";
 char *key4 = "Alarm";
 char *key5 = "ABC_Extinguisher";
 char *key6 = "C02_Extinguisher";
 char *key7 = "Water_Sprinkler";
 char *key8 = "Air_Quality";
 char *key9 = "Class_Variable";
 char *key10 = "Extractor_Fan";

//sensors.requestTemperatures();
float temperature = 15;//sensors.getTempCByIndex(0); // Assume current temperature. Recommended to measure with DHT22
float humidity = 58; // Assume current humidity. Recommended to measure with DHT22

int Class_Variable =0;
int Flame_State = 0;
int Electrical= 1;
int water = 0;
int alarm =0;
int Elec =0;
int smoke = 0;
void setup() {
  Serial.begin(9600);
  pinMode(Flame_Sensor, INPUT);
  pinMode(Temperature_Sensor, INPUT);
  pinMode(Alarm_LED, OUTPUT);
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
  }
char val[16]; //it stores a number composed by up to 16 characters


void loop() {
  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);
  
  //for temperature
  Serial.print("Temperature is ");
  Serial.println(temperature);
  delay(500);

//Smoke Sensor
  Serial.print("Corrected PPM: ");
  Serial.print(correctedPPM);
  Serial.println("ppm");
  delay(500);
  int Smoke_Present = correctedPPM;
  if ((Smoke_Present >=300) && (Smoke_Present <=900))
  {
    smoke = 1;
    Serial.println("Smoke is Present");
    delay(500);
  }
  else 
  {
    Serial.println("Smoke is Absent");
    delay(500);
    smoke = 0;
  }
  //Flame Sensor
  Flame_State = digitalRead(Flame_Sensor);
  if (Flame_State == 0)    
  {
    //Serial.println("No Flame is detected"); //Display the state of the sensors
    //delay(2000);
    Class_Variable = 0;
  }
  else 
  {
    Serial.println("Flame is detected"); //Display the state of the sensors
    Class_Variable = 1; //Variable to determine the class of fire
     //Alarm System
    Serial.println("Alarm is triggered"); // Trigger on the Alarm system
    delay(500);
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
    alarm = 1;
  }

Electrical = digitalRead(Electrical_Connectivity);
//Class of Fire
if (Class_Variable == 1)
{
   if (correctedPPM>=2000)
  {
    Serial.println("Class C type of Fire. Gas Fire");
    Serial.println("ABC Fire Extinguisher is released");
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, LOW);
    delay(500);
    }
    else if (Electrical == 0)
    {
     Elec = 1;
     Serial.println("Class E type of Fire. Electrical Fire");
     Serial.println("CO2 Fire Extinguisher is released");
     Serial.println("Seal Area");
     digitalWrite(RED_LED, HIGH);
     delay(500);
     digitalWrite(RED_LED, LOW);
     delay(500); 
    }
    else 
    {
      water = 1;
      Serial.println("Class A type of Fire. Other Fire");
      digitalWrite(BLUE_LED, HIGH);
      delay(500);
      digitalWrite(BLUE_LED, LOW);
      delay(500);
     }
}
 else
 {
  Serial.println("No Flame is detected"); 
  (Electrical = 1);
  Elec = 0;
  water = 0;
  alarm = 0;
 }
    digitalWrite(Buzzer, LOW);
    delay(500);
    digitalWrite(Alarm_LED, LOW);
    delay(500);
    
//Sending Values to Server
//Flame
itoa(Flame_State, val, 10); //convert an integer value into a char array
  DweetClient.add(key1, val);
  DweetClient.sendAll(THIG_NAME);
//Smoke Sensor 
  itoa(smoke, val, 10); //convert an integer value into a char array
  DweetClient.add(key2, val);
  DweetClient.sendAll(THIG_NAME);
//Temperature
  String Temp = String(temperature,2);
  Temp.toCharArray(val,16);
  DweetClient.add(key3, val);
  DweetClient.sendAll(THIG_NAME);
//Alarm
  itoa(alarm, val, 10); //convert an integer value into a char array
  DweetClient.add(key4, val);
  DweetClient.sendAll(THIG_NAME);
  
//ABC_Extinguisher
  itoa((correctedPPM>=2000), val, 10); //convert an integer value into a char array
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
  //PPM
  itoa(correctedPPM, val, 11); //convert an integer value into a char array
  DweetClient.add(key8, val);
  DweetClient.sendAll(THIG_NAME);
}

  










   
