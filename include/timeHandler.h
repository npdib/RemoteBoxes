#ifndef TIMEHANDLER
#define TIMEHANDLER

#include "ESP32Time.h"

#define ONE_HOUR 3600000

void configureRTC(void);
void setTime(void);
void reFetchTime(void);
std::string getTime(void);
std::string getDate(void);

#endif