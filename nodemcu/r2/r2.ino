/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
//int ledPin = 13;
int adc_value=900;
void setup() {

    USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);
    pinMode(12, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    pinMode(13, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);
    //digitalWrite(ledPin, LOW);
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();
    

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    //WiFiMulti.addAP("CSD", "csd@NITK2014");
    //WiFiMulti.addAP("NITK-NET", "2K16NITK");
    WiFiMulti.addAP("Redmi", "1234567890");

}




void frwd(void)
{
  USE_SERIAL.print("forward");
  digitalWrite(13, HIGH);
  digitalWrite(12,LOW);
  digitalWrite(14,LOW);
  digitalWrite(15,HIGH);
  
}
void bck(void){
  USE_SERIAL.print("back");
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);
  digitalWrite(14,HIGH);
  digitalWrite(15, LOW);
  }
void left(void){
  USE_SERIAL.print("left");
  digitalWrite(14, LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  digitalWrite(15,HIGH);
  }
void right(void){
  USE_SERIAL.print("right");
  digitalWrite(14,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
  digitalWrite(15,LOW);
  }  
void stp(void){
  USE_SERIAL.print("stop");
  digitalWrite(14,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  digitalWrite(15,LOW);
  }

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        
        http.begin("http://dharma.pythonanywhere.com/ad"); 
        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code xyz: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
                adc_value=payload.toInt();
                
                      
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
        
        http.begin("http://dharma.pythonanywhere.com/dt"); //HTTP
        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
            adc_value=909;
            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
                if (payload == "f")  {
                  frwd();
                  }
                if (payload == "b")  {
                  bck();
                  }
                if (payload == "l")  {
                  left();
                  
                  }
                if (payload == "r")  {
                  right();
                  }
                if (payload == "s")  {
                  stp();
                  }        
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(1500);
}

