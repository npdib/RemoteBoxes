#include <Arduino.h>
#include "displayDriver.h"
#include "wifiDriver.h"
#include "restDriver.h"
#include "InterruptHandler.h" // test commit and push

constexpr int BOX1 = 1;
constexpr int BOX2 = 2;

bool UnseenGIF = false;
int LastGIF = 0;

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

        for (int i = 0; i < 3; i++)
        {
            if (buttons[i].pressed)
            {
                buttons[i].pressed = false;
                restDriver.updateBoxValue(BOX1, i+1);
            }
        }

        if (buttons[3].pressed) // dismiss unseen gif
        {
            UnseenGIF = false;
        }

        if (buttons[4].pressed) // replay last gif
        {
            for (int i = 0; i < 5; i++)
            {
                displayDriver.displayGIF(LastGIF);
                i ++;
            }
        }

        // CHECK DATABASE VALUES (this will be for box 2)

        static int boxValue = 0;
        boxValue = restDriver.retrieveBoxValue(BOX1);

        if (boxValue != 0)
        {
            // char logMessage[64];
            for (int i = 0; i < 5; i++)
            {
                displayDriver.displayGIF(boxValue);
                i ++;
            }
            
            // snprintf(logMessage, 64, "Noticed that BOX1 has value %d, changing back to 0", box1);
            // displayDriver.LOG(logMessage); // this will be changed to display a gif (displayDriver.showGIF(box1))
            restDriver.updateBoxValue(BOX1, 0);
            UnseenGIF = true;
            LastGIF = boxValue;
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