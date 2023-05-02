#include "SDDriver.h"

void mountSD(void)
{
    // setup for the SD card
    Serial.println("Mounting SD card...");

    if(!SD.begin(SD_CS)) 
    {
        Serial.println("Mounting failed!");
        // return;
    }
}

void unmountSD(void)
{
    // setup for the SD card
    Serial.println("Unmounting SD card...");
    SD.end();
}

WiFiCredentials readWiFiData(void)
{
    mountSD();

    File wifiFile = SD.open("/wifi.txt", FILE_READ); // open file

    std::string fullCredentials = wifiFile.readString().c_str(); // read data from file
    Serial.printf("Data: %s\n", fullCredentials.c_str());

    wifiFile.close(); // close file
    unmountSD();

    int semiColon = fullCredentials.find(';');
    WiFiCredentials SDCredentials;
    SDCredentials.SSID = fullCredentials.substr(0, semiColon);
    SDCredentials.Password = fullCredentials.substr(semiColon+1); 
    return SDCredentials;
}