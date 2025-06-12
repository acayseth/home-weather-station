#include <ManagerWeather.cpp>
#include <ManagerRF443.cpp>
#include <LowPower.h>

#define SENSOR_PLACE OUT_SIDE

#define DHT_PIN 2
#define DHT_TYPE DHT22

#define RF443_PIN 12

ManagerWeather weather(DHT_PIN, DHT_TYPE);
ManagerRF443 rf443(RF443_PIN, SENSOR_PLACE);

void setup()
{
  Serial.begin(9600);
  weather.begin();
  rf443.begin();
}

void loop()
{
  int8_t temperature = weather.readTemperature();
  uint8_t humidity = weather.readHumidity();
  
  bool is_low_battery = false;
  float pressure = 0;

  if (SENSOR_PLACE == OUT_SIDE) {
    pressure = weather.readPressure();
  }

  rf443.transmitter(temperature, humidity, pressure, is_low_battery);

  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
}