#ifndef TIME_H
#define TIME_H

class Time
{
private:
    const char *ssid;
    const char *password;
    void ConnectToWiFi();

public:
    Time(const char *ssid, const char *password);
    ~Time();

    void SyncronizationTime();
    int GetHour();
    struct tm GetTimeNow();
    long AlarmClock();

    bool isTimeToIrrigate();
    void sleepLightOneHour();
    void sleepDeepSleep();
    void sleepLight(int timeToSleep);
};

#endif // Time.h