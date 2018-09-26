#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <ESP8266HTTPClient.h>

//ADXL345
#define BW_RATE 0x2C //Data rate and power mode control
#define POWER_CTL 0x2D //Power Control Register
#define DATA_FORMAT 0x31 //Data format control
#define DATAX0 0x32 //X-Axis Data 0

#define SS D0 //(IO15 -> IO5)

char values[10];
int16_t x, y, z;
float xg, yg, zg;

//const char* ssid = "DIR-825";
//const char* password = "03760826";
const char* ssid = "Redmi";
const char* password = "1234567890";


#include <Hash.h>
#include <WebSocketsServer.h>
WebSocketsServer webSocket = WebSocketsServer(81);


//unsigned long numberOfReconnects;
//unsigned long millisReconnected;


#define NUMBER_OF_SAMPLES 5000  // maximum number of samples taken
int samples[NUMBER_OF_SAMPLES];
int numberOfSamples = 10;//200
unsigned long samplingTime = 1;  // time in us to collect all the numberOfSamples
int samplingPause = 0; // '3'time in ms to pause between continuous sampling

unsigned long totalSamples;
unsigned long millisLastSample;


void analogSample(void)
{
  // do not start sampling before pause time expires
  if (millis() < millisLastSample + samplingPause)
  {
    return;
  }
  samplingTime = micros();
  for (int i = 0; i < numberOfSamples; i++)
  {

    readRegister(DATAX0, 6, values);
    x = ((int16_t)values[1] << 8) | (int16_t)values[0];
    //xg = x * 0.03125;
    xg = x * 3.125;
    Serial.print(xg);
    samples[i] = xg;
    totalSamples++;
    delay(4); // no delay
  }
  samplingTime = micros() - samplingTime;
  millisLastSample = millis();
}
void writeRegister(char registerAddress, char value) {
// SPI
digitalWrite(SS, LOW);
//
SPI.transfer(registerAddress);
//
SPI.transfer(value);
// SPI
digitalWrite(SS, HIGH);
}

void readRegister(char registerAddress, int16_t numBytes, char * values) {
//
char address = 0x80 | registerAddress;
//
if (numBytes > 1)address = address | 0x40;
// SPI
digitalWrite(SS, LOW);
//
SPI.transfer(address);
//
for (int16_t i = 0; i < numBytes; i++) {
values[i] = SPI.transfer(0x00);
}
// SPI CS HIGH
digitalWrite(SS, HIGH);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t lenght)
{
  unsigned long messageNumber;

  switch (type)
  {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      Serial.printf("[%u] Connected from ", num);
      Serial.println(webSocket.remoteIP(num));
      // send message back to client
      webSocket.sendTXT(num, "Connected");
      break;
    case WStype_TEXT:
      
      if (payload[0] == '#')
      {
        char* token = strtok((char*) &payload[2], " ");
        messageNumber = (unsigned long) strtol(token, '\0', 10);

        analogSample();

        // send the analog samples back
        String message = "# " + String(messageNumber) + " ";
        for (int i = 0; i < numberOfSamples; i++)
        {
          message = message + String(samples[i]) + ";";
        }
        message[message.length() - 1] = '\0';
        webSocket.sendTXT(num, message);
      }
      else
      {
        Serial.printf("[%u] received Text: %s\n", num, payload);
      }
      break;
    default:
      Serial.println("Case?");
      break;
  }
}


//
// Monitor Wi-Fi connection if it is alive
// If not alive then wait until it reconnects
//
void isWiFiAlive(void)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Not connected ");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(500);
    }
    Serial.printf(" now connected, my IP: %s\n", WiFi.localIP().toString().c_str());
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    
    String a= WiFi.localIP().toString(); 
    HTTPClient http;
    http.begin("http://dharma.pythonanywhere.com/nodeip");      //Specify request destination
    http.addHeader("Content-Type", "text/plain");
    int httpCode = http.POST(a);   //Send the request
    String payload = http.getString();                  //Get the response payload
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    http.end();

    //totalSamples = 0;
    //numberOfReconnects++;
    //millisReconnected = millis();
    //showStatisticsTimer = millisReconnected;
  }
}


void setup(void)
{
  Serial.begin(115200);
  Serial.println("\nEspScopeA0-Charlie 0.1.2");
  Serial.println("Type h for help");

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("WebSockets started");
  
  
  SPI.begin();
  SPI.setDataMode(SPI_MODE2);
  SPI.setBitOrder(MSBFIRST);
  SPI.setFrequency(100000);
    // SS Hight
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);
  
  // ADXL345
  writeRegister(DATA_FORMAT, 0x03); // ±16g 10bit
  writeRegister(POWER_CTL, 0x08); //
  writeRegister(BW_RATE, 0x0F); //


}


void loop(void)
{
  isWiFiAlive();
  webSocket.loop();
}
