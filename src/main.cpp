#include <Arduino.h>
#include "Motor.h"
#include "HSensor.h"
#include <time.h>
#include <avr/sleep.h>

int timeToWait = 0;
time_t currentTime;

const int motorPin = 2;
const int sensorPin = 3;

void setup()
{
  Serial.begin(9600);
  Motor motor(motorPin);
  HSensor sensor(sensorPin);

  // Récupération de l'heure actuelle
  time(&currentTime);
  Serial.println(ctime(&currentTime));

  timeToWait = CalculateTimeToWait(7);
}

int CalculateTimeToWait(int desiredHour) // A vérifier
{
  // Récupération de l'heure actuelle
  time_t currentTime;
  time(&currentTime);

  // Récupération de l'heure actuelle
  struct tm *timeinfo;
  timeinfo = localtime(&currentTime);

  // Calcul du temps à attendre
  int timeToWait = 0;
  if (timeinfo->tm_hour < desiredHour)
  {
    timeToWait = (desiredHour - timeinfo->tm_hour) * 3600 * 1000;
  }
  else if (timeinfo->tm_hour >= desiredHour && timeinfo->tm_hour < 24)
  {
    timeToWait = ((24 - timeinfo->tm_hour + desiredHour) * 3600 * 1000);
  }
  return timeToWait;
}

bool NeedIrrigation()
{
  // Dis si le sol est sec donc besoin d'irrigation
  return if (analogRead(sensorPin) > 300);
}

void loop()
{
  // Démarrage a 7h (normalement)

  // Si le sol est sec
  if (NeedIrrigation())
  {
    motor.Start();
    delay(5000);
    motor.Stop();
  }

  // Récupération de l'heure actuelle
  time(&currentTime);
  Serial.println(ctime(&currentTime));

  timeToWait = CalculateTimeToWait(7);
}
// vérifier si son interne n'est pas déréglé
}