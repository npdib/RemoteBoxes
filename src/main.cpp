#include <Arduino.h>
#include "displayDriver.h"
#include "wifiDriver.h"

void setup()
{
    Serial.begin(115200);
    for (size_t i = 5; i > 0; i--)
    {
        Serial.printf("Starting in %d\n", i);
        delay(1000);
    }
    
    displayDriver displayDriver;
    wifiDriver wifiDriver;

    displayDriver.LOG("About to connect to WiFi");
    wifiDriver.wifiConnect();
    displayDriver.LOG("Connected!!");
}

void loop()
{
    delay(1000);
}