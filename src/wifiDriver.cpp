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

    Serial.printf("SSID: %c\nPassword: %c\n", SSID, pwd);
}

void wifiDriver::wifiConnect(void)
{
    Serial.printf("SSID: %c\nPassword: %c\n", SSID, pwd);
    WiFi.begin(SSID.c_str(), pwd.c_str());

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.printf("Connecting to WiFi, please wait... Current status %d\n", WiFi.status());
        delay(1000);
    }

    Serial.print("Connected successfully");
}