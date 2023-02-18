#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "DHT.h"
DHT dht(15,DHT11);


// Wifi network station credentials
#define WIFI_SSID "LG"
#define WIFI_PASSWORD "getjar123"

#define BOT_TOKEN "5588019712:AAGCMlywGrpln5CCxkLgZ5IEcF_6mASxHnc"

#define CHAT_ID "1441821453"

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

String getReadings(){
  float temperature, humidity;
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  String message = "Temperature: " + String(temperature) + " ºC \n";
  message += "Humidity: " + String (humidity) + " % \n";
  return message;
}



void handleNewMessages(int numNewMessages)
{
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following command to get current readings.\n\n";
      welcome += "/readings \n";
      welcome += "/temperature \n";
      welcome += "/humidity \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/readings") {
      String readings = getReadings();
      bot.sendMessage(chat_id, readings, "");
    }  
   

    if (text == "/temperature") {
      float temp=dht.readTemperature();
      String tempMsg= "Temperature: " + String(temp) + " ºC \n";
      bot.sendMessage(CHAT_ID, tempMsg, "");
    }  
    if (text == "/humidity") {
      float hum=dht.readHumidity();
       String humMsg= "Humidity: " + String(hum) + " % \n";
      bot.sendMessage(CHAT_ID, humMsg, "");
    }  
    
  }
    
   
}


void setup()
{
  Serial.begin(115200);
  Serial.println();

  dht.begin();

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(5000);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  float temp=dht.readTemperature();
     if (temp > 30 ){
     bot.sendMessage(CHAT_ID, "ALERT!!TEMPERATURE IS ABOVE 30 ", ""); 
    }
  
  
}
 

void loop()
{ 

  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
