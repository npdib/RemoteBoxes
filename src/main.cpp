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
    
    // mountSD();
    displayDriver displayDriver;
    wifiDriver wifiDriver;
    restDriver restDriver(wifiDriver);
    setupButtonInterrupts();

    // fetch time from internet

    while (true)  // main loop
    {
        static unsigned long loop_timer = 0;
        loop_timer = millis();

        // POLL FOR BUTTON PRESSES

        for (int i = 0; i < 5; i++)
        {
            if (buttons[i].pressed)
            {
                buttons[i].pressed = false;
                restDriver.updateBoxValue(BOX1, i+1);
            }
        }

        // CHECK DATABASE VALUES (this will be for box 2)

        static int box1 = 0;
        box1 = restDriver.retrieveBoxValue(BOX1);

        if (box1 != 0)
        {
            char logMessage[64];
            displayDriver.displayGIF(box1);
            // snprintf(logMessage, 64, "Noticed that BOX1 has value %d, changing back to 0", box1);
            // displayDriver.LOG(logMessage); // this will be changed to display a gif (displayDriver.showGIF(box1))
            restDriver.updateBoxValue(BOX1, 0);
        }

        // WAIT AT LEAST A SECOND

        while ((millis() - loop_timer) < 1000){}

        displayDriver.clearScreen();
        displayDriver.resetCursor();
        
        if (WiFi.status() != WL_CONNECTED)
        {

            displayDriver.LOG("DISCONNECTED");
            Serial.println("DISCONNECTED");
        }
        else
        {
            displayDriver.LOG("CONNECTED");
            Serial.println("CONNECTED");
        }
    }
}

void loop()
{
    
}