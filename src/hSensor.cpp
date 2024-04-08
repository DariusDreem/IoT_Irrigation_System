#include "HSensor.h"

HSensor::HSensor(int sensorPin)
{
    this->sensorPin = sensorPin;
    pinMode(this->sensorPin, INPUT);
}

HSensor::~HSensor()
{
}

int HSensor::getHumidity()
{
    return analogRead(this->sensorPin);
}

bool HSensor::isWet()
{
    return getHumidity() > 500;
}

bool HSensor::isDry()
{
    return !isWet();
}
