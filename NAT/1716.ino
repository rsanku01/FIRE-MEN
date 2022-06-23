
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <stdio.h>

float ReadSensorValue;
char data;
char OutputPump;
float DerivedValue, IntegralValue;
float SP = 20;
char GetData[50];
char GetPatameters[50];
int n = 0;
//float PV, CP, T, Kp;
int on_off = 1;
char UpdateParameters[50];
float GetPar = 0;
float N = 20;
float Time = 1;


const char* ssid = "udcdocencia";
const char* password = "Universidade.2022";
WiFiClient espClient;
PubSubClient client(espClient);
const char* mqtt_server = "10.20.30.244";                                //get the ifconfig and change it
const char* plant = "plant3";                                           //check the plant id and change for every plant
const char* topic_update_parameters = "plant3/update_parameters";
const char* topic_get_parameters = "plant3/get_parameters";
const char* topic_on_off = "plant3/on_off";
const char* topic_data = "plant3/data";
const char* topic_parameters = "plant3/parameters";



void setup_wifi() {
  delay(10);
  WiFi.begin ("udcdocencia", "Universidade.2022");            //check if quotes are required for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println ("Wifi connected");
}






float error;
float v;
float x;

class PID
{
  public:
    float c1, c2, c3, N, ts, kp, ti, td, pv, cp, t, integral, derived, error;
    void update_constants (float k_, float ti_, float td_);
    float get_control_action (float error_k);
    PID (float N_, float tc_, float kc_, float ts_)
    {
      error = 0;
      integral = 0;
      derived = 0;
      c1 = 0;
      c2 = 0;
      c3 = 0;
      N = N_;
      ts = ts_;
      kp = 0.6 * kc_;
      ti = tc_ / 2.0;
      td = tc_ / 8.0;
      update_constants(kp, ti, td);
    }
};

float PID::get_control_action(float error_k) {
  integral = (c1 * (error_k + error)) + integral;
  derived = (c2 * (error_k - error)) + (c3 * derived);
  float u = kp * (error_k + integral + derived);
  // Acotar la potencia de 0-100
  if (u > 100) {
    u = 100;
  }
  if (u < 0) {
    u = 0;
  }
  // Actualizacion Variables
  error = error_k;

  return u;
}

void PID::update_constants (float k_, float ti_, float td_)
{
  kp = k_;
  ti = ti_;
  td = td_;

  // Calculo de las constantes intermedias
  c1 = ts / (2 * ti);
  c2 = (2 * td) / (((2 * td) / N) + ts);
  c3 = (((2 * td) / N) - ts) / (((2 * td) / N) + ts);
}

PID nat(10, 20, 5.50, 1);

void callback (char* topic, byte* payload, unsigned int length) {

  if (String(topic) == topic_update_parameters) {
    char inmsg[length + 1];
    for (int i = 0; i < length; i++) {
      inmsg[i] = (char)payload[i];
    }
    inmsg[length] = '\0';
    float New_Kp, New_Ti, New_Td;
    sscanf(inmsg, "%f;%f;%f;%f", &SP, &New_Kp, &New_Ti, &New_Td);
    nat.update_constants(New_Kp, New_Ti, New_Td);
  }

  if (String(topic) == topic_get_parameters) {
    char inmsg2[length + 1];
    for (int i = 0; i < length; i++) {
      inmsg2[i] = (char)payload[i];
    }
    inmsg2[length] = '\0';
    GetPar = inmsg2[0];
    char Send_Parameters[50];
    snprintf(Send_Parameters, 50, "%f;%f;%f;%f;%i", SP, nat.kp, nat.ti, nat.td, on_off);
    client.publish(topic_parameters, Send_Parameters, topic_data);
  }

  if (String(topic) == topic_on_off) {
    char inmsg3[length + 1];



    for (int i = 0; i < length; i++) {
      inmsg3[i] = (char)payload[i];              //check if it works with1 since its either 1 or 0
    }
    inmsg3[length] = '\0';
    char Send_Parameters[50];
    snprintf(Send_Parameters, 50, "%i;%i", 0, 1);
    client.publish(topic_parameters, Send_Parameters, topic_data);
  }
  //  inmsg3[length] = '\0';
  //  on_off = inmsg3[0];
  //  mqtt_in_onoff = String(inmsg3) == "1";
  //  }

  if (String(topic) == topic_data) {
    char inmsg4[length + 1];
    for (int i = 0; i < length; i++) {
      inmsg4[i] = (char)payload[i];
    }
    inmsg4[length] = '\0';

//    float SP,PV, CP, T;
    snprintf(inmsg4, "%f;%f;%f;%f", SP, nat.pv, nat.cp, nat.t);
    client.publish(topic_data);

  }


  if (String(topic) == topic_parameters) {
    char inmsg5[length + 1];
    for (int i = 0; i < length; i++) {
      inmsg[i] = (char)payload[i];
    }
    inmsg5[length] = '\0';
    float Kp, Ti, Td;
    snprintf(inmsg, "%f;%f;%f;%f;%i", &SP, &Kp, &Ti, &Td, &on_off);
    client.publish(topic_parameters);
  }

}

void setup() {
  pinMode(D3, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer("10.20.30.244", 1883);                     //change the mqtt server as required by checking ifconfig
  client.connect(plant);
  client.setCallback(callback);
  //  client.subscribe(data);
  client.loop();
}

void loop() {
  analogRead(A0);
  //analogWriteFreq (40000);
  Serial.println (analogRead(A0));
  delay(500);
  v = analogRead(A0) * 100 / 1023;
  error = 50 - v;
  x = nat.get_control_action(error);
  analogWrite(D3, error * 1023 / 100 * on_off);
  Serial.println();
  delay(500);
}
