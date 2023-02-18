#include<WiFi.h>
char ssid[] = "LG"; //wifi name
char pass[] = "getjar123"; //wifi password

WiFiClient client;

void setup(){
   WiFi.mode(WIFI_STA);
   Serial.begin(9600);
  }
void loop(){
  if (WiFi.status()!=WL_CONNECTED){
     Serial.print("ATTEMPTING TO CONNECT");
    }
  while(WiFi.status() != WL_CONNECTED){
     WiFi.begin(ssid,pass);
     Serial.print(".");
     delay(5000);
     
    }
   Serial.println("\nCONNECTED");
  }
  
