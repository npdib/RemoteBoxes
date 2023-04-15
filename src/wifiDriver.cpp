#include "wifiDriver.h"

WiFiCredentials wifiDriver::getSSIDfromFile(void)
{
    return readWiFiData();
}

wifiDriver::wifiDriver(void)
{
    mCredentials = getSSIDfromFile();
    Serial.printf("SSID: %s\nPassword: %s\n", mCredentials.SSID.c_str(), mCredentials.Password.c_str());
}

void wifiDriver::wifiConnect(void)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        if (WiFi.status() == 255)
        {
            Serial.print("Connecting...\n");
            WiFi.disconnect(true);
            WiFi.mode(WIFI_STA);
            WiFi.begin(mCredentials.SSID.c_str(), mCredentials.Password.c_str());
        }
        else
        {
            Serial.print("Reconnecting...\n");
            WiFi.reconnect();
        }
    }
    
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.printf("Connecting to WiFi, please wait... Current status %d\n", WiFi.status());
        delay(1000);
    }
}