#include <MQ135.h>
#include "dweetESP8266.h"
#include "DHT.h"
#define DHTTYPE DHT11
#define THIG_NAME "I4ET-Group1-FIREMEN" 

#define dht_dpin D1
#define PIN_MQ135 A0

DHT dht(dht_dpin, DHTTYPE);
MQ135 mq135_sensor(PIN_MQ135);


const char* ssid = "dfa4fe";
const char* password = "271435942";

dweet DweetClient;
 char *key2 = "Smoke_Sensor";
 char *key3 = "Temperature_Sensor";
 char *key8 = "Air_Quality";

 int smoke = 0;

//sensors.requestTemperatures();
 
void setup()
{
  pinMode(dht_dpin, INPUT);
  dht.begin();
  Serial.begin(9600);
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

void loop()
{
 //The MQ_135 Gas Sensor depends on the temperature and humidity of the air to measure the quality of air in PPM
  float temperature = dht.readTemperature();//sensors.getTempCByIndex(0); // Assume current temperature. Recommended to measure with DHT22
  float humidity = dht.readHumidity(); // Assume current humidity. Recommended to measure with DHT22
  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);
  
  delay(2000);
  //Smoke Sensor
  Serial.print("Corrected PPM: ");
  Serial.print(correctedPPM);
  Serial.println("ppm");
  delay(500);
  int Smoke_Present = correctedPPM;
  if ((Smoke_Present >=300) && (Smoke_Present <=900)) //This range is determined by calibrating the sensor at standard condition when smoke was introduced.
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
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("THE PRESENT HUMIDITY = ");
  Serial.print(h);
  Serial.print("% ");
  Serial.print("THE PRESENT TEMPERATURE = ");
  Serial.print(t);
  Serial.println("c ");

  //Sending Values to Server
  //Smoke Sensor 
  itoa(smoke, val, 10); //convert an integer value into a char array
  DweetClient.add(key2, val);
  DweetClient.sendAll(THIG_NAME);
  //Temperature
  String Temp = String(t,2);
  Temp.toCharArray(val,16);
  DweetClient.add(key3, val);
  DweetClient.sendAll(THIG_NAME);
   //PPM
  itoa(correctedPPM, val, 10); //convert an integer value into a char array
  DweetClient.add(key8, val);
  DweetClient.sendAll(THIG_NAME);
}
