#include "Motor.h"

Motor::Motor(int motorPin)
{
    this->motorPin = motorPin;
    pinMode(this->motorPin, OUTPUT);
}

Motor::~Motor()
{
    turnOff();
}

void Motor::turnOn(int ms)
{
    digitalWrite(this->motorPin, HIGH);
    delay(ms);
    turnOff();
}

void Motor::turnOff()
{
    digitalWrite(this->motorPin, LOW);
}

