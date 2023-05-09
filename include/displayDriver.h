#ifndef DISPLAYDRIVER
#define DISPLAYDRIVER

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include "Adafruit_ImageReader.h"
#include "SDDriver.h"
#include "AnimatedGIF.h"
#include <SPI.h>

#define GIF_LOOP_COUNT 5

static constexpr int DISPLAY_HEIGHT = 170; 
static constexpr int  DISPLAY_WIDTH = 320;

static constexpr int TFT_CS = 9; // this is the MISO pin so will have to be changed
static constexpr int  TFT_RST = 1;
static constexpr int TFT_DC = 34;
static constexpr int TFT_MOSI  = MOSI;  // Data out
static constexpr int TFT_SCLK  = SCK;  // Clock out

class displayDriver // class to hold the display driver
{
    private:
        // PIN DEFINITIONS

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
        void displayBMP(char *, int, int);
};

#endif //DISPLAYDRIVER