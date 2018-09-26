#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
 
void setup() {
 
  Serial.begin(115200);                                  //Serial connection
  //WiFi.begin("CSD", "csd@NITK2014");   //WiFi connection
  WiFi.begin("DIR-825", "03760826");

  //WiFi.begin("Redmi", "1234567890");
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
 
}
 
void loop() {
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://10.100.83.152:5000/node");      //Specify request destination
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header

   //String a= String(analogRead(A0));
   //String a='ab';
   //Serial.println(a);
   int httpCode = http.POST("a");   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
 
   Serial.println("Error in WiFi connection");   
 
 }
 
   //delay(500);  //Send a request every 30 seconds
 
}
