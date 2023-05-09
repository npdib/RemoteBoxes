#include "timeHandler.h"

ESP32Time rtc;
unsigned long fetch_time_timer = 0;

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

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

std::string getTime(void)
{
    return rtc.getTime().c_str();
}