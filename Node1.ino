//IoT Course Project - Wireless Sensor Network for Remote Temperature Monitoring
#include <ESP8266WiFi.h>//NodeMCU header file
String apiKey = "1M8H86BEC47ZBZFA";//Thingspeak API key
const char* ssid     = "Jon.AP";//WiFi ssid
const char* password = "JOHNATHAN";//WiFi Password
const char* server = "api.thingspeak.com";//Thingspeak server address
float temp_celsius = 0;//Temperature variable
WiFiClient client;//Establish WiFi client
void setup() //setup function, executed once at startup
{
  WiFiServer server(80);//Initialize WiFi server
  Serial.begin(115200);//Start serial comunications
  WiFi.begin(ssid, password);//Authenticate WiFi network
  server.begin();//Start server
}
void loop() //loop function, executed continously 
{
  temp_celsius = ((analogRead(A0)+ 0.682)/3.09);//Obtain temperature from output voltage reading, formula derived graphically
  if (client.connect(server,80))//If devices establishes connection with server
  {  
	//Send temperature to server, syntax defined by thingspeak. Field 1 used for node 1
    String postStr = apiKey;
    postStr +="&field1=";
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
  client.stop();//Stop client
  delay(10000);//30 sec delay between updates, required by thingspeak
}
