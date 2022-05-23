//USED LIBARY 

#include "DHT.h"
#include "PMS.h"
#define DHTPIN 2

// Uncomment whatever type you're using!

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

PMS pms(Serial);
PMS::DATA data;

void setup() {
  Serial.begin(9600);
  dht.begin();
  delay(2000);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  unsigned int pm10 = data.PM_AE_UG_10_0;
  
  unsigned int pm25 = data.PM_AE_UG_2_5;
  
  unsigned int pm1 = data.PM_AE_UG_1_0;
  
  // Check if any reads failed and exit early (to try again).
  
  if (isnan(h) || isnan(t) || isnan(f)) {
    return;
  }
  if ( pm10 == 0 || pm25 == 0 || pm1 == 0 ) {
    return;
  }
}
