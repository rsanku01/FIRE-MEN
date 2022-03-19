#include <ESP8266WiFi.h> //including the necessary libraries

const char* ssid = "Just Don't";          //no worries
const char* password = "cestbien168";     //i've changed the id and pass!

const char* host = "postman-echo.com";  //checking process
WiFiClient client;              //checking process
const int httpPort = 80;        //checking process

void setup() {
  Serial.begin(115200);   //starting the serial
  delay(10);              //small delay

  Serial.println();
  Serial.println();
  Serial.print("connecting to ");   //indication to the user
  Serial.println(ssid);             
  WiFi.begin(ssid, password);       //connecting  
  while (WiFi.status() != WL_CONNECTED) {     //informing the user of the state of the connection
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");       //indicating a proper connection
  Serial.println("IP address: ");         
  Serial.println(WiFi.localIP());       //indicating the ip address

}

void loop() {
  delay(5000);
  Serial.print("connecting to ");
  Serial.println(host);

  if(!client.connect(host, httpPort))         //checking the connection
  {
    Serial.println("connection failed");      //informing if connection failed
    return;
  }

  String url = "/get"; 
  Serial.print("Requesting URL: ");
  Serial.println(url);                        //giving info to the user
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  unsigned long timeout = millis();           
  while(client.available() == 0){             //loop for the connection time
    if(millis() - timeout > 5000){
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

while(client.available()){                      //loop for working connection
  String line = client.readStringUntil('\r');
  Serial.print(line);
}

Serial.println();
Serial.println("closing connection");
}
