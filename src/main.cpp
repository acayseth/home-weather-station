#include "RF443TX.cpp"
#include <LowPower.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>

#define SENSOR_PLACE PLACE_OUT_SIDE
#define DHT_PIN 2
#define DHT_TYPE DHT22
#define RF443_PIN 12

DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_BMP085 bmp;

RF443TX rf443(RF443_PIN, PLACE_OUT_SIDE);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  rf443.begin();
  if (SENSOR_PLACE == PLACE_OUT_SIDE)
  {
    bmp.begin();
  }
}

void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  uint32_t pressure = 0;
  
  if (SENSOR_PLACE == PLACE_OUT_SIDE)
  {
    pressure = bmp.readPressure();
  }

  if (!isnan(temperature) || !isnan(humidity))
  {
    rf443.sent(
      static_cast<int8_t>(round(temperature)),
      static_cast<uint8_t>(round(humidity)),
      pressure,
      false
    );
  }

  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
}