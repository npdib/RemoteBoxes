#include <Arduino.h>
#include "soundHandler.h"
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
bool redrawScreen = true;
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

    playFanfare();
    
    displayDriver displayDriver;
    displayDriver.displayBMP("/images/wifi_connecting.bmp", 0, 0); // connecting to wifi screen
    wifiDriver wifiDriver;
    restDriver restDriver(wifiDriver);

    configureRTC();
    setupButtonInterrupts();

    // fetch time from internet
    setTime();

    std::string loopTime = getTime();
    std::string loopDate = getDate();
    std::string oldLoopDate= "00:00";
    std::string oldLoopTime = "00:00";

    while (true)  // main loop
    {
        loop_timer = millis();

        // POLL FOR BUTTON PRESSES

        for (int i = 0; i < 3; i++)
        {
            if (buttons[i].pressed) // gif buttons
            {
                buttons[i].pressed = false;
                restDriver.updateBoxValue(BOX1, i+1);
            }
        }

        if (buttons[3].pressed) // dismiss unseen gif notification
        {
            Serial.println("Dismiss");
            buttons[3].pressed = false;
            UnseenGIF = false;
            redrawScreen = true;
        }

        if (buttons[4].pressed) // replay last gif
        {
            Serial.println("Replay");
            buttons[4].pressed = false;
            for (int i = 0; i < 5; i++)
            {
                displayDriver.displayGIF(LastGIF);
            }
            redrawScreen = true;
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

            redrawScreen = true;
            UnseenGIF = true;
            LastGIF = boxValue;
        }

        reFetchTime(); // refetch the current time from the internet every hour

        loopTime = getTime();
        loopDate = getDate();
        if ((loopTime != oldLoopTime) or (loopDate != oldLoopDate)) // only update the on screen time if necessary
        {
            redrawScreen = true;
        }
        oldLoopTime = loopTime;
        oldLoopDate = loopDate;

        // HANDLE THE SCREEN DISPLAY
        //      this includes background, clock and notification      

        if (redrawScreen)
        {
            displayDriver.clearScreen();
            displayDriver.displayStillGIF("/images/background.gif");
            if (UnseenGIF) // notification
            {

            }
            displayDriver.displayTime(loopTime.c_str()); // clock
            displayDriver.displayDate(loopDate.c_str());
            redrawScreen = false;
        }

        // WAIT AT LEAST A HALF A SECOND EACH LOOP
        Serial.println(millis() - loop_timer);
        while ((millis() - loop_timer) < 1000){}

        
        /*************************************************/
        
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