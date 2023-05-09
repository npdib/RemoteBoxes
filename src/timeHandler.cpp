#include "timeHandler.h"

ESP32Time rtc;
unsigned long fetch_time_timer = 0;

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const char* time_zone = "GMT+0BST-1,M3.5.0/01:00:00,M10.5.0/02:00:00";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

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
    struct tm timeinfo = rtc.getTimeStruct();
	char s[51];
	strftime(s, 50, "%H:%M", &timeinfo);
    return (std::string) s;
}

std::string getDate(void)
{
    return rtc.getDate().c_str();
}