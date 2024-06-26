#ifndef TimeSys
#define TimeSys

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
    double AlarmClock(int targetTime);
    bool isTimeToIrrigate();
    void sleepLightOneHour();
    void sleepLight(int timeToSleep);
    void sleepDeepSleep(int timeToSleep);
};

#endif // TimeSys.h