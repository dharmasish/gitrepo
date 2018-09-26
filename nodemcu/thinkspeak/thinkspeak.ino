//#include <ESP8266HTTPClient.h>

#include <ArduinoJson.h>

#include <ESP8266WiFi.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
int val;
int tempPin = A0;
String apiKey = "FNDV89KMCROLBL4K"; //API key from ThingSpeak channel
const char* ssid = "160385"; //SSID of your wifi
const char* password = "kuld@123"; //password of your wifi
int duration=5;//delay between each data measure and uploading
////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* server = "api.thingspeak.com";
WiFiClient client; //Start clinet

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  //Get temperature and humidity data
val = analogRead(tempPin);
float mv = val*4.833; 
float cel = mv/10;
float farh = (cel*9)/5 + 32;
  Serial.print("TEMPRATURE = ");
Serial.print(cel);
Serial.print("*C");
Serial.println();
delay(1000);

Serial.print("TEMPRATURE = ");
Serial.print(farh);
Serial.print("*F");
Serial.println();


  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String('t');
    postStr += "&field2=";
    postStr += String('h');
    postStr += "\r\n\r\n";

    //Uplad the postSting with temperature and Humidity information every
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.print('t');
    Serial.print(" degrees Celcius Humidity: ");
    Serial.print('h');
    Serial.println("% send to Thingspeak");
  }
  client.stop();

  Serial.println("Waitingâ€¦");
  // thingspeak needs minimum 15 sec delay between updates
  delay(duration*1000);
}



