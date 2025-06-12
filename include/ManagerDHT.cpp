#include <DHT.h>

class ManagerDHT
{
private:
    DHT dht;

    int8_t cast_int(float value) {
        if (isnan(value)) {
            return 255;
        }

        return static_cast<int8_t>(round(value));
    }

    uint8_t cast_uint(float value) {
        if (isnan(value)) {
            return 255;
        }

        return static_cast<uint8_t>(round(value));
    }

public:
    ManagerDHT(uint8_t pin, uint8_t type) : dht(pin, type) {}

    void begin()
    {
        dht.begin();
    }

    int8_t readTemperature()
    {
        return cast_int(dht.readTemperature());
    }

    uint8_t readHumidity()
    {
        return cast_uint(dht.readHumidity());
    }
};