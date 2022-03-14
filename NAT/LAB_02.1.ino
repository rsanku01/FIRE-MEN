#include "DHT.h"
#define DHTTYPE DHT11
#define dht_dpin D1

DHT dht(dht_dpin, DHTTYPE);

void setup()
{
  dht.begin();
  Serial.begin(9600);
  delay(10);
  Serial.println("initializing the Sensor");
}

void loop()
{
  delay(3000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("THE PRESENT HUMIDITY = ");
  Serial.print(h);
  Serial.print("% ");
  Serial.print("THE PRESENT TEMPERATURE = ");
  Serial.print(t);
  Serial.println("c ");
}
