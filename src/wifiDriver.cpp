#include "wifiDriver.h"

std::string wifiDriver::getSSIDfromFile(void)
{
    return "NOWQYH9M;5sqspkg8qTEa";
}

wifiDriver::wifiDriver(void)
{
    mCredentials = getSSIDfromFile();
    int semiColon = mCredentials.find(';');
    mSSID = mCredentials.substr(0, semiColon);
    mPwd = mCredentials.substr(semiColon+1); 
    Serial.printf("SSID: %s\nPassword: %s\n", mSSID.c_str(), mPwd.c_str());
}

void wifiDriver::wifiConnect(void)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        if (WiFi.status() == 255)
        {
            Serial.print("Connecting...\n");
            WiFi.begin(mSSID.c_str(), mPwd.c_str());
        }
        else
        {
            Serial.print("Reconnecting...\n");
            WiFi.reconnect();
        }
    }
    else
    {
        Serial.print("Still connected...\n");
    }
    
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.printf("Connecting to WiFi, please wait... Current status %d\n", WiFi.status());
        delay(1000);
    }
}