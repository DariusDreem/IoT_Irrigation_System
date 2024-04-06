#include <Arduino.h>
#include "Motor.h"
#include "HSensor.h"
#include <time.h>

long timeToWait = 0;

void setup()
{
  Serial.begin(9600);
  Motor motor(2);
  HSensor sensor(3);

  // Récupération de l'heure actuelle
  time_t currentTime;
  time(&currentTime);
  Serial.println(ctime(&currentTime));
}

int CalculateTimeToWait()
{
}

void loop()
{
}