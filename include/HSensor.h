#ifndef HSENSOR_H
#define HSENSOR_H
#include <Arduino.h>

class HSensor
{
public:
    HSensor(int sensorPin);
    ~HSensor();
    bool isDry();
    bool isWet();

    int getHumidity();

private:
    int sensorPin;
};

#endif // HSensor.h
