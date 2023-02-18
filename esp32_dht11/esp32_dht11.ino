#include<WiFi.h>
#include "DHT.h"
DHT dht(15,DHT11);

void setup(){
  Serial.begin(9600);
  dht.begin();
  }
void loop(){
  float temp=dht.readTemperature();
  float hum=dht.readHumidity();
  Serial.print("TEMPERATURE: ");
  Serial.println(temp);
  Serial.print("HUMIDITY : ");
  Serial.println(hum);
  delay(1000);
  }
