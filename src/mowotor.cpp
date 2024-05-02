#include "Mowotor.h"

Mowotor::Mowotor(int mowotorPin)
{
    this->mowotorPin = mowotorPin;
    pinMode(this->mowotorPin, OUTPUT);
}

Mowotor::~Mowotor()
{
    turnOwoff();
}

void Mowotor::turnOwon(int ms)
{
    digitalWrite(this->mowotorPin, HIGH);
    delay(ms);
    turnOwoff();
}

void Mowotor::turnOwoff()
{
    digitalWrite(this->mowotorPin, LOW);
}
