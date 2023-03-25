#include <Arduino.h>
#include "displayDriver.h"
#include "wifiDriver.h"
#include "restDriver.h"

constexpr int KATIEBOX = 1;
constexpr int NICKBOX = 2;

void setup()
{
    Serial.begin(115200);
    for (size_t i = 5; i > 0; i--)
    {
        Serial.printf("Starting in %d\n", i);
        delay(1000);
    }
    Serial.println("Starting...");
    
    displayDriver displayDriver;
    wifiDriver wifiDriver;
    restDriver restDriver(wifiDriver);

    restDriver.updateBoxValue(KATIEBOX, 0);
    restDriver.updateBoxValue(NICKBOX, 0);

    int box1 = restDriver.retrieveBoxValue(KATIEBOX);
    int box2 = restDriver.retrieveBoxValue(NICKBOX);
    displayDriver.LOG(box1);
    displayDriver.LOG(box2);

    restDriver.updateBoxValue(KATIEBOX, 1);
    restDriver.updateBoxValue(NICKBOX, 1);

    box1 = restDriver.retrieveBoxValue(KATIEBOX);
    box2 = restDriver.retrieveBoxValue(NICKBOX);
    displayDriver.LOG(box1);
    displayDriver.LOG(box2);
}

void loop()
{
    delay(1000);
}