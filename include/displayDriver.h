#ifndef DISPLAYDRIVER
#define DISPLAYDRIVER

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include "SDDriver.h"
#include "AnimatedGIF.h"
#include <SPI.h>

class displayDriver // class to hold the display driver
{
    private:
        // PIN DEFINITIONS
        static constexpr int TFT_CS = 9; // this is the MISO pin so will have to be changed
        static constexpr int  TFT_RST = 1;
        static constexpr int TFT_DC = 34;
        static constexpr int TFT_MOSI  = MOSI;  // Data out
        static constexpr int TFT_SCLK  = SCK;  // Clock out
    
		Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

		void initialiseScreen(void);
        void initialiseLog(void);

	public:		

		displayDriver(void); // constructor
		void clearScreen(void); // clear screen function
        void resetCursor(void);
        void LOG(char*);
        void LOG(String);
        void LOG(int);
        void displayGIF(int);
};

#endif //DISPLAYDRIVER