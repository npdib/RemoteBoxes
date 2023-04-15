#include "SDDriver.h"

void initialiseSD(void)
{
    // setup for the SD card
    Serial.print("Initializing SD card...");

    if(!SD.begin(SD_CS)) 
    {
        Serial.println("initialization failed!");
        return;
    }
}

WiFiCredentials readWiFiData(void)
{
    File wifiFile = SD.open("wifi.txt", FILE_READ);
    uint8_t fileData[128];
    wifiFile.read(fileData, sizeof(fileData));
    WiFiCredentials SDCredentials;
    wifiFile.close();
    SDCredentials.SSID = "NOWQYH9M";
    SDCredentials.Password = "5sqspkg8qTEa";
    return SDCredentials;
}