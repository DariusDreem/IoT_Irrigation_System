#include "TimeSys.h"

#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <ctime>
#include <WiFiUdp.h> // Utilisez cette bibliothèque pour UDP
#include <time.h>
#include <RTClib.h>

WiFiUDP udp; // Créez une instance de la classe WiFiUDP

void Time::ConnectToWiFi()
{
    WiFi.begin(this->ssid, this->password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
}

void Time::SyncronizationTime()
{
    // Utilisez les paramètres passés à la fonction plutôt que de les redéfinir
    configTime(3600, 7200, "pool.ntp.org", "time.nist.gov");

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Échec de l'obtention de l'heure");
        return;
    }

    Serial.println("Synchronisation de l'heure réussie ^^");
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

int Time::GetHour()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Échec de l'obtention de l'heure");
        return timeinfo.tm_hour; // Retourne l'heure même si la récupération a échoué
    }
    Serial.println(&timeinfo, "%H");
    return timeinfo.tm_hour;
}

struct tm Time::GetTimeNow()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Échec de l'obtention de l'heure");
        return {};
    }
    Serial.println(&timeinfo, "%H:%M:%S");
    return timeinfo;
}

#include <ctime>

double Time::AlarmClock(int targetTimeValue)
{
    struct tm timeStruc = GetTimeNow();
    time_t timeNow = mktime(&timeStruc);

    struct tm targetTimeStruct;
    targetTimeStruct.tm_hour = targetTimeValue;
    targetTimeStruct.tm_min = 0;
    targetTimeStruct.tm_sec = 0;

    time_t targetTimeSys = mktime(&targetTimeStruct);

    return difftime(targetTimeSys, timeNow);
};

bool Time::isTimeToIrrigate()
{
    struct tm timeinfo = GetTimeNow();
    int currentHour = timeinfo.tm_hour;

    return currentHour == 6 || currentHour == 7 || currentHour == 8;
}

void Time::sleepLightOneHour()
{
    esp_sleep_enable_timer_wakeup(3600 * 1000000ULL); // Wake up after 1 hour
    esp_deep_sleep_start();
}

void Time::sleepDeepSleep(int timeToSleepParam)
{
    long int timeToSleep = timeToSleepParam;
    double sleepTime = AlarmClock(timeToSleepParam);
    uint64_t uint64Value = static_cast<uint64_t>(sleepTime);
    esp_sleep_enable_timer_wakeup(uint64Value * 1000000ULL); // Wake up after 1 hour
    Serial.println("Going to deep sleep, UwU ^^");
    esp_deep_sleep_start();
}
