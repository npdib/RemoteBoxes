#include "timeHandler.h"

ESP32Time rtc;

void setTime(void)
{
    configTzTime(time_zone, ntpServer1, ntpServer2);
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        rtc.setTimeStruct(timeinfo); 
    }
}