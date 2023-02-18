#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

int led=D1;

char ssid[] = "Gpcet-B3";   // your network SSID (name)
char pass[] = "gpcet123";

WiFiClient client;

unsigned long myChannelNumber =  1810816;
const char * myReadAPIKey = "IHA7BERZAIM0VGNR";
void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  pinMode(led,OUTPUT);
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
 
  int a = ThingSpeak.readIntField(myChannelNumber, 1, myReadAPIKey); 
  Serial.println("LED STATUS");
  Serial.print(a);
  delay(1000);

 if (a == 1){
    digitalWrite(led,HIGH);
  
  }
 else{
    digitalWrite(led,LOW);
  }
 
 }

 
 
