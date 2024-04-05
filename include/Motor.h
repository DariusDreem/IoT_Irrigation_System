#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

class Motor
{
public:
    Motor(int motorPin);
    ~Motor();

    void turnOn(int ms);
    void turnOff();
};

#endif // Motor.h