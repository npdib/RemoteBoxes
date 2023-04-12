#include <Arduino.h>
#include "displayDriver.h"
#include "wifiDriver.h"
#include "restDriver.h"
#include "InterruptHandler.h"

constexpr int BOX1 = 1;
constexpr int BOX2 = 2;

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
    setupButtonInterrupts();

    // restDriver.updateBoxValue(BOX1, 0);
    // restDriver.updateBoxValue(BOX2, 0);

    // int box1 = restDriver.retrieveBoxValue(BOX1);
    // int box2 = restDriver.retrieveBoxValue(BOX2);
    // char logMessage[64];
    // snprintf(logMessage, 64, "Old value for Box 1 is %d", box1);
    // displayDriver.LOG(logMessage);
    // snprintf(logMessage, 64, "Old value for Box 2 is %d", box2);
    // displayDriver.LOG(logMessage);

    // restDriver.updateBoxValue(BOX1, 1);
    // restDriver.updateBoxValue(BOX2, 1);

    // box1 = restDriver.retrieveBoxValue(BOX1);
    // box2 = restDriver.retrieveBoxValue(BOX2);
    // snprintf(logMessage, 64, "New value for Box 1 is %d", box1);
    // displayDriver.LOG(logMessage);
    // snprintf(logMessage, 64, "New value for Box 2 is %d", box2);
    // displayDriver.LOG(logMessage);

    while (true)
    {
        static unsigned long loop_timer = 0;
        loop_timer = millis();

        if (button1.pressed)
        {
            button1.pressed = false;
            restDriver.updateBoxValue(BOX1, 1);
        }

        if (restDriver.retrieveBoxValue(BOX1) == 1)
        {
            String logMessage = "Noticed that BOX1 has value 1, changing back to 0";
            displayDriver.LOG(logMessage);
            restDriver.updateBoxValue(BOX1, 0);
        }

        if (millis() - button1.timer > 5000)
        {
            button1.ready = true; 
        }

        while ((millis() - loop_timer) < 1000){}
    }
}

void loop()
{
    
}