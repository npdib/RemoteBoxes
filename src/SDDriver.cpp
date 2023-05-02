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

    File wifiFile = SD.open("/wifi.txt", FILE_READ);
    wifiFile.close();
}

WiFiCredentials readWiFiData(void)
{
    // uint8_t fileData[128];
    // wifiFile.read(fileData, sizeof(fileData));
    WiFiCredentials SDCredentials;
    // wifiFile.close();
    SDCredentials.SSID = "NOWQYH9M";
    SDCredentials.Password = "5sqspkg8qTEa";
    return SDCredentials;
}