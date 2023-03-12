#ifndef DISPLAYDRIVER
#define DISPLAYDRIVER

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

class displayDriver // class to hold the display driver
{
    private:
        // PIN DEFINITIONS
        static constexpr int TFT_CS = 37;
        static constexpr int  TFT_RST = 1;
        static constexpr int TFT_DC = 34;
        static constexpr int TFT_MOSI  = MOSI;  // Data out
        static constexpr int TFT_SCLK  = SCK;  // Clock out
    
		Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

		void initialiseScreen(void);

	public:		

		displayDriver(void); // constructor
		void clearScreen(void){tft.fillScreen(ST77XX_BLACK);} // clear screen function

};

#endif //DISPLAYDRIVER