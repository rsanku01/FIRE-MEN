//This code debugs IR Transmitter code, then power ON RGB 7display LED
#include <IRremote.h> // >v3.0.0
                                           
#define PIN_RECV  D2
#define LED D4

void setup()  
{  
  Serial.begin(9600); //initialize serial connection to print on the Serial Monitor of the Arduino IDE
  IrReceiver.begin(PIN_RECV); // Initializes the IR receiver object
  pinMode(LED, OUTPUT);
}  
                               
void loop()  
{  
  if (IrReceiver.decode()) {
    
    Serial.println("Received Signal...");  
    digitalWrite(LED, HIGH);  
    Serial.println ("LED is ON");
    IrReceiver.resume(); // Important, enables to receive the next IR signal
  }  
  else  
  {
    Serial.println("SIgnal is Lost");
    delay(10000);
    digitalWrite(LED, LOW);
  }
}  
