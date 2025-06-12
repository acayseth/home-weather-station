#include <RH_ASK.h>
#include <SPI.h>

enum RH_Place
{
    IN_SIDE = 0,
    OUT_SIDE = 1,
    UNDEFINED = 2,
};

typedef struct CBData
{
    RH_Place place;
    int8_t temperature;
    uint8_t humidity;
    float pressure;
    bool is_low_battery;
} Package;

class ManagerRF443
{
private:
    RH_ASK rf443;
    Package data;
    RH_Place place = UNDEFINED;

    void set_data(int8_t temperature, uint8_t humidity, uint8_t pressure, bool is_low_battery)
    {
        data.place = place;
        data.temperature = temperature;
        data.humidity = humidity;
        data.pressure = pressure;
        data.is_low_battery = is_low_battery;
    }

    Package get_data()
    {
        return data;
    }

public:
    ManagerRF443(uint8_t pin, bool is_transmitter, RH_Place place)
    {
        uint8_t rx_pin = 255;
        uint8_t tx_pin = 255;

        if (place != UNDEFINED)
        {
            this->place = place;
        }

        if (is_transmitter)
            tx_pin = pin;
        else
            rx_pin = pin;

        rf443 = RH_ASK(2000, rx_pin, tx_pin);
    }

    void begin()
    {
        if (!rf443.init())
        {
            Serial.println("RF443 init failed");
        }
    }

    void clean()
    {
        data.place = UNDEFINED;
        data.temperature = 0;
        data.humidity = 0;
        data.pressure = 0;
        data.is_low_battery = false;
    }

    bool transmitter(int8_t temperature, uint8_t humidity, float pressure = 0, bool is_low_battery = false)
    {
        if (place == UNDEFINED)
        {
            clean();
            return false;
        }

        set_data(temperature, humidity, pressure, is_low_battery);

        if (!rf443.send((uint8_t *)&data, sizeof(Package)) or !rf443.waitPacketSent())
        {
            memset(&data, 0, sizeof(Package));
            clean();
            return false;
        }

        clean();

        return true;
    }

    bool receiver()
    {
        uint8_t buf[sizeof(Package)];
        uint8_t len = sizeof(buf);

        if (!rf443.recv(buf, &len) or len != sizeof(Package))
        {
            clean();
            return false;
        }

        memcpy(&data, buf, sizeof(Package));

        return true;
    }
};