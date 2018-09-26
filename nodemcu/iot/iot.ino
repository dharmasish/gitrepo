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

void setup() {

    USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);
    pinMode(12, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    pinMode(13, OUTPUT);
    pinMode(14, OUTPUT);
    //digitalWrite(ledPin, LOW);
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFiMulti.addAP("CSD", "csd@NITK2014");

}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
        http.begin("http://10.100.80.181:5000/data"); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
                const char* t="1";
                const char* f="0";
                if (payload == "r")  {
                  digitalWrite(14, HIGH);
                  digitalWrite(12,LOW);
                  digitalWrite(13,LOW);
                  }
                if (payload == "g")  {
                  digitalWrite(12, HIGH);
                  digitalWrite(14,LOW);
                  digitalWrite(13,LOW);
                  }
                if (payload == "b")  {
                  digitalWrite(12, HIGH);
                  digitalWrite(14,LOW);
                  digitalWrite(13,LOW);
                  }
                if (payload == "n")  {
                  digitalWrite(12, LOW);
                  digitalWrite(14,LOW);
                  digitalWrite(13,LOW);
                  }      
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(100);
}

