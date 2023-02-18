#include <WiFi.h>
#include <ThingSpeak.h>
#include "DHT.h"
DHT dht(15,DHT11);


char ssid[] = "LG";   // your network SSID (name)
char pass[] = "getjar123";

WiFiClient client;

unsigned long myChannelNumber = 1808024;
const char * myWriteAPIKey = "XS4DKZKDE5V6U7KA";

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  dht.begin();
  Serial.begin(9600);
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
   if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
   
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);    
    }
    Serial.println("\nConnected.");
  }
  float temp=dht.readTemperature();
  float hum=dht.readHumidity();
  Serial.print("TEMPERATURE: ");
  Serial.println(temp);
  Serial.print("HUMIDITY : ");
  Serial.println(hum);
  delay(20000);
  
  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, hum);
  
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(20000);

}
