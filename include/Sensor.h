#ifndef Sensor.h
#define Sensor .h
#include <Arduino.h>

class HumiditySensor
{
public:
    HumiditySensor(int sensorPin);
    ~HumiditySensor();

    int getHumidity();

private:
    int sensorPin;
};

#endif // HumiditySensor.h
