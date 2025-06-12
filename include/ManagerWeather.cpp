#include <DHT.h>
#include <Adafruit_BMP085.h>

class ManagerWeather
{
private:
    DHT dht;
    Adafruit_BMP085 bmp;

    int8_t cast_int(float value)
    {
        if (isnan(value))
        {
            return 255;
        }

        return static_cast<int8_t>(round(value));
    }

    uint8_t cast_uint(float value)
    {
        if (isnan(value))
        {
            return 255;
        }

        return static_cast<uint8_t>(round(value));
    }

public:
    ManagerWeather(uint8_t pin, uint8_t type) : dht(pin, type) {}

    void begin()
    {
        dht.begin();
        bmp.begin();
    }

    int8_t readTemperature()
    {
        return cast_int(dht.readTemperature());
    }

    uint8_t readHumidity()
    {
        return cast_uint(dht.readHumidity());
    }

    float readPressure(uint32_t altitude_meters = 0)
    {
        /**
         *      >   1100   hPa	Vreme stabilă, cer senin sau parțial noros
         *          1050   hPa	Vreme obișnuită, fără schimbări majore
         *      1000–1049   hPa	Posibilă vreme instabilă, nori, ploi ușoare
         *      <   1000   hPa   Mare probabilitate de ploi, vânt, furtuni
         *      <    990   hPa	Furtuni puternice, ciclon, front rece activ
         */

        float value = bmp.readPressure();

        if (isnan(value))
        {
            return 255;
        }

        return value;
    }
};