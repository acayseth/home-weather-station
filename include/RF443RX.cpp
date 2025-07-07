#include <ManagerRF443.cpp>

class RF443RX : public ManagerRF443
{
public:
    RF443RX(uint8_t pin) : ManagerRF443(pin, false) {}

    Package receive()
    {
        memset(&data, 0, sizeof(Package));

        uint8_t buf[sizeof(Package)];
        uint8_t len = sizeof(buf);

        if (rf443.recv(buf, &len) && len == sizeof(Package))
        {
            memcpy(&data, buf, sizeof(Package));
        }

        return data;
    }
};