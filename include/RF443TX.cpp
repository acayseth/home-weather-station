#include <ManagerRF443.cpp>

class RF443TX : public ManagerRF443
{
private:
    RH_Place place;

public:
    RF443TX(uint8_t pin, RH_Place place) : ManagerRF443(pin, false)
    {
        place = place;
    }

    bool sent(int8_t temperature, uint8_t humidity, uint32_t pressure, bool low_battery)
    {
        data.place = place;
        data.temperature = temperature;
        data.humidity = humidity;
        data.pressure = pressure;
        data.low_battery = low_battery;

        bool result = rf443.send((uint8_t *)&data, sizeof(Package)) || rf443.waitPacketSent();

        if (rf443.send((uint8_t *)&data, sizeof(Package)) or rf443.waitPacketSent())
        {
            result = true;
        }

        memset(&data, 0, sizeof(Package));

        return result;
    }
};