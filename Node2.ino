#include <ESP8266WiFi.h>
String apiKey = "1M8H86BEC47ZBZFA";  
const char* ssid     = "Jon.AP"; // Your ssid
const char* password = "JOHNATHAN"; // Your Password
const char* server = "api.thingspeak.com";
float temp_celsius = 0;
WiFiClient client;
void setup() 
{
  WiFiServer server(80);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  server.begin();
}
void loop() 
{
  temp_celsius = (analogRead(A0) * 330.0) / 1023.0;   // To convert analog values to Celsius We have 3.3 V on our board and we know that output voltage of LM35 varies by 10 mV to every degree Celsius rise/fall. So , (A0*3300/10)/1023 = celsius
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  {  
    String postStr = apiKey;
    postStr +="&field2=";
    postStr += String(temp_celsius);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.print("Temperature: ");
    Serial.print(temp_celsius);
    Serial.print(" degrees Celcius");
    Serial.println("%. Send to Thingspeak.");
  }
  client.stop();
  delay(10000);// 30 sec delay between ypdates (minimum 15)
}
