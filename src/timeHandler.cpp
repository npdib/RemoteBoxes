#include "timeHandler.h"

ESP32Time rtc;
unsigned long fetch_time_timer = 0;

void configureRTC(void)
{
    configTzTime(time_zone, ntpServer1, ntpServer2);
}

void setTime(void)
{
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        rtc.setTimeStruct(timeinfo); 
    }
    fetch_time_timer = millis();
}

void reFetchTime(void)
{
    if(millis() - fetch_time_timer > ONE_HOUR)
    {
        setTime();
    }
}