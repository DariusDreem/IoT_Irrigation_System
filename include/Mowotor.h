#ifndef MOWOTOR_H
#define MOWOTOR_H
#include <Arduino.h>

class Mowotor
{
public:
    Mowotor(int mowotorPin);
    ~Mowotor();

    int mowotorPin;
    void turnOwon(int ms);
    void turnOwoff();
};

#endif // Mowotor.h
