#include "Time.h"

#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <ctime>
#include <WiFiUdp.h> // Utilisez cette bibliothèque pour UDP

struct tm
{
    int tm_sec;   // Secondes (0-59)
    int tm_min;   // Minutes (0-59)
    int tm_hour;  // Heures (0-23)
    int tm_mday;  // Jour du mois (1-31)
    int tm_mon;   // Mois (0-11)
    int tm_year;  // Année depuis 1900
    int tm_wday;  // Jour de la semaine (0-6, dimanche = 0)
    int tm_yday;  // Jour de l'année (0-365)
    int tm_isdst; // Indicateur d'heure d'été (0, 1 ou -1)
};

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

long Time::AlarmClock()
{
    struct tm timeStruc = GetTimeNow();
    time_t timeNow = mktime(&timeStruc);

    struct tm targetTimeStruct = heureActuelle;
    targetTimeStruct.tm_hour = targetTime;
    targetTimeStruct.tm_min = 0;
    targetTimeStruct.tm_sec = 0;

    time_t targetTime = mktime(&targetTimeStruct);

    return difftime(targetTime, timeNow);
};

bool Time::isTimeToIrrigate()
{
    struct tm timeinfo = GetTimeNow();
    int currentHour = timeinfo.tm_hour;

    return currentHour == 6 || currentHour == 7 || currentHour == 8;
}

void sleepLightOneHour()
{
    esp_sleep_enable_timer_wakeup(3600 * 1000000ULL); // Wake up after 1 hour
    esp_deep_sleep_start();
}

void sleepDeepSleep()
{
    long timeToSleep = AlarmClock();
    esp_sleep_enable_timer_wakeup(3600 * 1000000ULL); // Wake up after 1 hour
    Serial.println("Going to deep sleep, UwU ^^");
    esp_deep_sleep_start();
}
