/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

void setup() {
  pinMode(12, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  String a=String('00');
  int b=a.toInt();
  analogWrite(13, b); 
  delay(1000);       
  
}
