#include <ManagerDHT.cpp>

#define DHT_PIN 2
#define DHT_TYPE DHT22

ManagerDHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {

  

  delay(2000);
}