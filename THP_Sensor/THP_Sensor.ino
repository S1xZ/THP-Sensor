//USED LIBARY 
#include "DHT.h"
#include <PMserial.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

//DHT DEF
#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

//FIREBASE WIFI DEF
#define FIREBASE_HOST "https://esp8266-thpsensor-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "ezKzdUZEgykVkbpXbWWzFk9xwbKaWVG3YMkYvAe3"
#define WIFI_SSID "PROJ"
#define WIFI_PASSWORD "test1234"

//SOFTWARE SERIAL
SoftwareSerial StmSerial(13,15); //RX, TX
uint8_t buffer[1];

//PM SERIAL
constexpr auto PMS_RX = 5;
constexpr auto PMS_TX = 4;
SerialPM pms(PMS3003, PMS_RX, PMS_TX);

void setup() {
  Serial.begin(9600);
  StmSerial.begin(9600);
  
  dht.begin();
  pms.init();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  //Read pms value
  pms.read();

  // Read Humidity as Percent
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
     Serial.printf("FAILED\r\n");
    return;
  }
  
  Serial.printf("PM1.0 %2d, PM2.5 %2d, PM10 %2d [ug/m3]\r\n",
                  pms.pm01, pms.pm25, pms.pm10);
  Serial.printf("Humidity: %.2f %% Temperature: %.2f°C  %.2f°F\r\n",
                  h, t, f);

  //Send data through StmSerial
  buffer[0] = pms.pm25;
  StmSerial.write(buffer, sizeof(buffer));

}
