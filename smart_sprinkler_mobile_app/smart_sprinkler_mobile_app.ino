#include<WiFi.h>
#include <ThingSpeak.h>

int soil=14;
int value1;
int in1=13;
int in2=14;

char ssid[] = "LG";   // your network SSID (name)
char pass[] = "getjar123";

WiFiClient client;

unsigned long myChannelNumber =  1694153;
const char * myWriteAPIKey = "JBJTPW5BW5C2FWSC";
const char * myReadAPIKey = "EJTTT1S8LKVB6WIW";

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  ThingSpeak.begin(client);
  
  pinMode(soil,INPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);

}
void loop(){

    if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
   
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);    
    }
    Serial.println("\nConnected.");
  }
  
  value1=analogRead(soil);
  
  ThingSpeak.setField(1, value1);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(20000);
   
  int a = ThingSpeak.readIntField(myChannelNumber, 1, myReadAPIKey); 
  Serial.println("SOIL MOISTURE");
  Serial.print(a);
  delay(1000);
 
  


   if (a<600){
   digitalWrite(in1,HIGH);
   digitalWrite(in2,LOW);
   Serial.println("LOW MOISTURE , Sprinkler on");
   delay(1000);
   }
    else{
   digitalWrite(in1,LOW);
   digitalWrite(in2,LOW);
   Serial.println("STOP , sprinkler off");
   delay(1000);
   }
   
  
 
}
