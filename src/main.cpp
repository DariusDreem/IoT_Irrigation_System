#include <WiFi.h>
#include "TimeSys.h"
#include "Mowotor.h"
#include "HSensor.h"
#include <RTClib.h>

RTC_DS3231 rtc;

// Replace with your network credentials
const char *ssid = "your_SSID";
const char *password = "your_PASSWORD";

// Motor and humidity sensor pins
const int mowotorPin = 5;   // Example pin for motor
const int sensorPin = 34; // Example pin for humidity sensor

// Create motor and sensor objects
Mowotor waterPump(mowotorPin);
HSensor soilSensor(sensorPin);

// Time variables
const int wakeHour = 6;      // Wake up at 7 AM
const int sleepHour = 23;    // Go to sleep at 11 PM
const int checkInterval = 1; // Check every hour after 8 AM

// Function prototypes
void setup()
{
  Serial.begin(9600);
  // Serial.begin(115200);
  // configTime(0, 0, "pool.ntp.org"); // GMT offset and daylight offset are set to 0
}

void loop()
{
  // create a new Time object
  Time time(ssid, password);

  time.SyncronizationTime();

  DateTime timeNow = rtc.now();

  if (time.isTimeToIrrigate())
  {
    for (size_t i = time.GetHour(); i < 9; i++)
    {
      Serial.println("Check water of plant");
      if (soilSensor.isDry())
      {
        Serial.println("Watering plant");
        // TODO : IRIGATE
        waterPump.turnOwon(1000);
        // TODO : SLEEP DEEP
      }
      else
      {
        Serial.println("Plant is good");
        time.sleepLightOneHour();
      }
    }
  }

  if (time.GetHour() < 6)
  {
    Serial.println("Sleeping deep until 6AM");

    time.sleepLight(time.AlarmClock(6));
  }
  else if (time.GetHour() > 10)
  {
    if (soilSensor.isDry())
    {
      Serial.println("Watering plant");
      waterPump.turnOwon(1000);
    }
    time.sleepLight(time.AlarmClock(6));
  }
}
