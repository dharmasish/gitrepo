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
  
  digitalWrite(12, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(1000);                      // Wait for a second
  digitalWrite(12, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(1000);
  digitalWrite(13, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(1000);                      // Wait for a second
  digitalWrite(13, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(1000);
  digitalWrite(14, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(1000);                      // Wait for a second
  digitalWrite(14, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(1000);
  digitalWrite(12, HIGH);  // Turn the LED off by making the voltage HIGH
  digitalWrite(13, HIGH);
  digitalWrite(14, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(1000);                      // Wait for a second
  digitalWrite(12, LOW);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  delay(1000);
}
