#ifndef SENSOR_H
#define SENSOR_H
#include <Arduino.h>

class HSensor
{
public:
    HSensor(int sensorPin);
    ~HSensor();

    int getHumidity();

private:
    int sensorPin;
};

#endif // HumiditySensor.h
