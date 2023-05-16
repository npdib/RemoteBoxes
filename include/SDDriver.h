#ifndef SDDRIVER
#define SDDRIVER

#include <SPI.h>
#include <SD.h>


typedef struct {
    std::string SSID = "";
    std::string Username = "";
    std::string Password = "";
} WiFiCredentials;

static constexpr int SD_CS = 7;

void mountSD(void);
void unmountSD(void);
WiFiCredentials readWiFiData(void);


#endif //  SDDRIVER