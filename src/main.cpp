#include <Arduino.h>
#include "displayDriver.h"
#include "wifiDriver.h"
#include "restDriver.h"
#include "InterruptHandler.h" // test commit and push
#include "timeHandler.h"

// Box variables
constexpr int BOX1 = 1;
constexpr int BOX2 = 2;
int boxValue = 0;

unsigned long loop_timer = 0;

// UI Variables
bool UnseenGIF = false;
int LastGIF = 0;

void setup()
{
    // this will be unnecessary
    /*****************************************/
    Serial.begin(115200);
    for (size_t i = 5; i > 0; i--)
    {
        Serial.printf("Starting in %d\n", i);
        delay(1000);
    }
    Serial.println("Starting...");
    /******************************************/
    
    displayDriver displayDriver;
    displayDriver.displayBMP("/images/wifi_connecting.bmp", 0, 0); // connecting to wifi screen
    wifiDriver wifiDriver;
    restDriver restDriver(wifiDriver);

    configureRTC();
    setupButtonInterrupts();

    // fetch time from internet
    setTime();

    while (true)  // main loop
    {
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

        if (buttons[3].pressed) // dismiss unseen gif notification
        {
            UnseenGIF = false;
        }

        if (buttons[4].pressed) // replay last gif
        {
            for (int i = 0; i < 5; i++)
            {
                displayDriver.displayGIF(LastGIF);
            }
        }

        // CHECK DATABASE VALUES

        boxValue = restDriver.retrieveBoxValue(BOX1);

        if (boxValue != 0)
        {
            for (int i = 0; i < GIF_LOOP_COUNT; i++) // loop gif 5 times
            {
                displayDriver.displayGIF(boxValue); // play appropriate gif
            }

            restDriver.updateBoxValue(BOX1, 0);

            UnseenGIF = true;
            LastGIF = boxValue;
        }

        reFetchTime();

        // WAIT AT LEAST A HALF A SECOND EACH LOOP

        while ((millis() - loop_timer) < 500){}

        // HANDLE THE SCREEN DISPLAY
        //      this includes background, clock and notification


        /*************************************************/
        displayDriver.clearScreen();
        displayDriver.resetCursor();
        
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("DISCONNECTED");
        }
        else
        {
            Serial.println("CONNECTED");
        }
        /*************************************************/
    }
}

void loop()
{
    
}