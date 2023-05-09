#ifndef TIMEHANDLER
#define TIMEHANDLER

#include "ESP32Time.h"

#define ONE_HOUR 3600000

const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

void configureRTC(void);
void setTime(void);
void reFetchTime(void);

#endif