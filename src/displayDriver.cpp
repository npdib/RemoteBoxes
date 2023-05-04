#include "displayDriver.h"

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
File f;
AnimatedGIF gif;

// PROTECTED

void displayDriver::initialiseScreen(void)
{
	tft.init(DISPLAY_HEIGHT, DISPLAY_WIDTH); // Init ST7789 170x320
	tft.setRotation(1);
	clearScreen();
}

void displayDriver::initialiseLog(void)
{
	tft.setTextWrap(true);
	tft.setCursor(5, 5);
	tft.setTextColor(ST77XX_WHITE);
	tft.setTextSize(3);
}

void* GIFOpenFile(const char *fname, int32_t *pSize)
{
    mountSD();
    f = SD.open(fname);
    if (f)
      {
        *pSize = f.size();
        return (void *)&f;
      }
      return NULL;
} /* GIFOpenFile() */

void GIFCloseFile(void *pHandle)
{
    File *f = static_cast<File *>(pHandle);
    if (f != NULL)
        f->close();

    unmountSD();
} /* GIFCloseFile() */

int32_t GIFReadFile(GIFFILE *pFile, uint8_t *pBuf, int32_t iLen)
{
    int32_t iBytesRead;
    iBytesRead = iLen;
    File *f = static_cast<File *>(pFile->fHandle);
    // Note: If you read a file all the way to the last byte, seek() stops working
    if ((pFile->iSize - pFile->iPos) < iLen)
       iBytesRead = pFile->iSize - pFile->iPos - 1; // <-- ugly work-around
    if (iBytesRead <= 0)
       return 0;
    iBytesRead = (int32_t)f->read(pBuf, iBytesRead);
    pFile->iPos = f->position();
    return iBytesRead;
} /* GIFReadFile() */

int32_t GIFSeekFile(GIFFILE *pFile, int32_t iPosition)
{ 
  int i = micros();
  File *f = static_cast<File *>(pFile->fHandle);
  f->seek(iPosition);
  pFile->iPos = (int32_t)f->position();
  i = micros() - i;
//  Serial.printf("Seek time = %d us\n", i);
  return pFile->iPos;
} /* GIFSeekFile() */

// Draw a line of image directly on the LCD
void GIFDraw(GIFDRAW *pDraw)
{
    uint8_t *s;
    uint16_t *d, *usPalette, usTemp[320];
    int x, y, iWidth;

    iWidth = pDraw->iWidth;
    // Serial.printf("Drawing %d pixels\n", iWidth);

    if (iWidth + pDraw->iX > DISPLAY_WIDTH)
       iWidth = DISPLAY_WIDTH - pDraw->iX;
    usPalette = pDraw->pPalette;
    y = pDraw->iY + pDraw->y; // current line
    if (y >= DISPLAY_HEIGHT || pDraw->iX >= DISPLAY_WIDTH || iWidth < 1)
       return; 
    s = pDraw->pPixels;
    if (pDraw->ucDisposalMethod == 2) // restore to background color
    {
      for (x=0; x<iWidth; x++)
      {
        if (s[x] == pDraw->ucTransparent)
           s[x] = pDraw->ucBackground;
      }
      pDraw->ucHasTransparency = 0;
    }

    // Apply the new pixels to the main image
    if (pDraw->ucHasTransparency) // if transparency used
    {
      uint8_t *pEnd, c, ucTransparent = pDraw->ucTransparent;
      int x, iCount;
      pEnd = s + iWidth;
      x = 0;
      iCount = 0; // count non-transparent pixels
      while(x < iWidth)
      {
        c = ucTransparent-1;
        d = usTemp;
        while (c != ucTransparent && s < pEnd)
        {
          c = *s++;
          if (c == ucTransparent) // done, stop
          {
            s--; // back up to treat it like transparent
          }
          else // opaque
          {
             *d++ = usPalette[c];
             iCount++;
          }
        } // while looking for opaque pixels
        if (iCount) // any opaque pixels?
        {
			tft.startWrite();
			tft.setAddrWindow(pDraw->iX+x, y, iCount, 1);
			tft.writePixels(usTemp, iCount, false, false);
			tft.endWrite();
			x += iCount;
			iCount = 0;
        }
        // no, look for a run of transparent pixels
        c = ucTransparent;
        while (c == ucTransparent && s < pEnd)
        {
          c = *s++;
          if (c == ucTransparent)
             iCount++;
          else
             s--; 
        }
        if (iCount)
        {
          x += iCount; // skip these
          iCount = 0;
        }
      }
    }
    else
    {
		s = pDraw->pPixels;
		// Translate the 8-bit pixels through the RGB565 palette (already byte reversed)
		for (x=0; x<iWidth; x++)
			usTemp[x] = usPalette[*s++];
		tft.startWrite();
		tft.setAddrWindow(pDraw->iX, y, iWidth, 1);
		tft.writePixels(usTemp, iWidth, false, false);
		tft.endWrite();
    }
} /* GIFDraw() */

// PUBLIC

displayDriver::displayDriver(void)
{
	initialiseScreen();
	tft.fillScreen(ST77XX_BLACK);
	gif.begin(LITTLE_ENDIAN_PIXELS);
}

void displayDriver::clearScreen(void)
{
	tft.fillScreen(ST77XX_BLACK);
}

void displayDriver::resetCursor(void)
{
	tft.setCursor(5, 5);
}

void displayDriver::LOG(char* text)
{
	tft.println(text);
}

void displayDriver::LOG(String text)
{
	tft.println(text);
}

void displayDriver::LOG(int text)
{
	tft.println(text);
}

void displayDriver::displayGIF(int gifNum)
{

	// tft.println("TESTING");
    const char * prefix = "/gif/gif";
    const char * suffix = ".gif";

    char fileName[80];
    snprintf(fileName, 80, "%s%d%s", prefix, gifNum, suffix);

	if (gif.open(fileName, GIFOpenFile, GIFCloseFile, GIFReadFile, GIFSeekFile, GIFDraw)) 
	{
		GIFINFO gi;
		Serial.printf("Successfully opened GIF %s; Canvas size = %d x %d\n",  fileName, gif.getCanvasWidth(), gif.getCanvasHeight());
		if (gif.getInfo(&gi)) {
		  Serial.printf("frame count: %d\n", gi.iFrameCount);
		  Serial.printf("duration: %d ms\n", gi.iDuration);
		  Serial.printf("max delay: %d ms\n", gi.iMaxDelay);
		  Serial.printf("min delay: %d ms\n", gi.iMinDelay);
		}

		while (gif.playFrame(true, NULL));
		gif.reset();
		
		gif.close();
	} 
	else 
	{
		Serial.printf("Error opening file %s = %d\n", fileName, gif.getLastError());
	}
}

// void testlines(uint16_t color)
// {
// 	tft.fillScreen(ST77XX_BLACK);
// 	for (int16_t x = 0; x < tft.width(); x += 6)
// 	{
// 		tft.drawLine(0, 0, x, tft.height() - 1, color);
// 		delay(0);
// 	}
// 	for (int16_t y = 0; y < tft.height(); y += 6)
// 	{
// 		tft.drawLine(0, 0, tft.width() - 1, y, color);
// 		delay(0);
// 	}

// 	tft.fillScreen(ST77XX_BLACK);
// 	for (int16_t x = 0; x < tft.width(); x += 6)
// 	{
// 		tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
// 		delay(0);
// 	}
// 	for (int16_t y = 0; y < tft.height(); y += 6)
// 	{
// 		tft.drawLine(tft.width() - 1, 0, 0, y, color);
// 		delay(0);
// 	}

// 	tft.fillScreen(ST77XX_BLACK);
// 	for (int16_t x = 0; x < tft.width(); x += 6)
// 	{
// 		tft.drawLine(0, tft.height() - 1, x, 0, color);
// 		delay(0);
// 	}
// 	for (int16_t y = 0; y < tft.height(); y += 6)
// 	{
// 		tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
// 		delay(0);
// 	}

// 	tft.fillScreen(ST77XX_BLACK);
// 	for (int16_t x = 0; x < tft.width(); x += 6)
// 	{
// 		tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
// 		delay(0);
// 	}
// 	for (int16_t y = 0; y < tft.height(); y += 6)
// 	{
// 		tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
// 		delay(0);
// 	}
// }

// void testdrawtext(char *text, uint16_t color)
// {
// 	tft.setCursor(0, 0);
// 	tft.setTextColor(color);
// 	tft.setTextWrap(true);
// 	tft.print(text);
// }

// void testfastlines(uint16_t color1, uint16_t color2)
// {
// 	tft.fillScreen(ST77XX_BLACK);
// 	for (int16_t y = 0; y < tft.height(); y += 5)
// 	{
// 		tft.drawFastHLine(0, y, tft.width(), color1);
// 	}
// 	for (int16_t x = 0; x < tft.width(); x += 5)
// 	{
// 		tft.drawFastVLine(x, 0, tft.height(), color2);
// 	}
// }

// void testdrawrects(uint16_t color)
// {
// 	tft.fillScreen(ST77XX_BLACK);
// 	for (int16_t x = 0; x < tft.width(); x += 6)
// 	{
// 		tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color);
// 	}
// }

// void testfillrects(uint16_t color1, uint16_t color2)
// {
// 	tft.fillScreen(ST77XX_BLACK);
// 	for (int16_t x = tft.width() - 1; x > 6; x -= 6)
// 	{
// 		tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color1);
// 		tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color2);
// 	}
// }

// void testfillcircles(uint8_t radius, uint16_t color)
// {
// 	for (int16_t x = radius; x < tft.width(); x += radius * 2)
// 	{
// 		for (int16_t y = radius; y < tft.height(); y += radius * 2)
// 		{
// 			tft.fillCircle(x, y, radius, color);
// 		}
// 	}
// }

// void testdrawcircles(uint8_t radius, uint16_t color)
// {
// 	for (int16_t x = 0; x < tft.width() + radius; x += radius * 2)
// 	{
// 		for (int16_t y = 0; y < tft.height() + radius; y += radius * 2)
// 		{
// 			tft.drawCircle(x, y, radius, color);
// 		}
// 	}
// }

// void testtriangles()
// {
// 	tft.fillScreen(ST77XX_BLACK);
// 	uint16_t color = 0xF800;
// 	int t;
// 	int w = tft.width() / 2;
// 	int x = tft.height() - 1;
// 	int y = 0;
// 	int z = tft.width();
// 	for (t = 0; t <= 15; t++)
// 	{
// 		tft.drawTriangle(w, y, y, x, z, x, color);
// 		x -= 4;
// 		y += 4;
// 		z -= 4;
// 		color += 100;
// 	}
// }

// void testroundrects()
// {
// 	tft.fillScreen(ST77XX_BLACK);
// 	uint16_t color = 100;
// 	int i;
// 	int t;
// 	for (t = 0; t <= 4; t += 1)
// 	{
// 		int x = 0;
// 		int y = 0;
// 		int w = tft.width() - 2;
// 		int h = tft.height() - 2;
// 		for (i = 0; i <= 16; i += 1)
// 		{
// 			tft.drawRoundRect(x, y, w, h, 5, color);
// 			x += 2;
// 			y += 3;
// 			w -= 4;
// 			h -= 6;
// 			color += 1100;
// 		}
// 		color += 100;
// 	}
// }

// void tftPrintTest()
// {
// 	tft.setTextWrap(false);
// 	tft.fillScreen(ST77XX_BLACK);
// 	tft.setCursor(0, 30);
// 	tft.setTextColor(ST77XX_RED);
// 	tft.setTextSize(1);
// 	tft.println("Hello World!");
// 	tft.setTextColor(ST77XX_YELLOW);
// 	tft.setTextSize(2);
// 	tft.println("Hello World!");
// 	tft.setTextColor(ST77XX_GREEN);
// 	tft.setTextSize(3);
// 	tft.println("Hello World!");
// 	tft.setTextColor(ST77XX_BLUE);
// 	tft.setTextSize(4);
// 	tft.print(1234.567);
// 	delay(1500);
// 	tft.setCursor(0, 0);
// 	tft.fillScreen(ST77XX_BLACK);
// 	tft.setTextColor(ST77XX_WHITE);
// 	tft.setTextSize(0);
// 	tft.println("Hello World!");
// 	tft.setTextSize(1);
// 	tft.setTextColor(ST77XX_GREEN);
// 	tft.print(p, 6);
// 	tft.println(" Want pi?");
// 	tft.println(" ");
// 	tft.print(8675309, HEX); // print 8,675,309 out in HEX!
// 	tft.println(" Print HEX!");
// 	tft.println(" ");
// 	tft.setTextColor(ST77XX_WHITE);
// 	tft.println("Sketch has been");
// 	tft.println("running for: ");
// 	tft.setTextColor(ST77XX_MAGENTA);
// 	tft.print(millis() / 1000);
// 	tft.setTextColor(ST77XX_WHITE);
// 	tft.print(" seconds.");
// }

// void mediabuttons()
// {
// 	// play
// 	tft.fillScreen(ST77XX_BLACK);
// 	tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
// 	tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
// 	delay(500);
// 	// pause
// 	tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
// 	tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
// 	tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
// 	delay(500);
// 	// play color
// 	tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
// 	delay(50);
// 	// pause color
// 	tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
// 	tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
// 	// play color
// 	tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
// }

// void setup(void)
// {
// 	Serial.begin(9600);
// 	Serial.print(F("Hello! ST77xx TFT Test"));

// 	// OR use this initializer (uncomment) if using a 1.9" 170x320 TFT:

// 	// SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
// 	// Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
// 	// may end up with a black screen some times, or all the time.
// 	// tft.setSPISpeed(40000000);
// 	Serial.println(F("Initialized"));

// 	uint16_t time = millis();
// 	tft.fillScreen(ST77XX_BLACK);
// 	time = millis() - time;

// 	Serial.println(time, DEC);
// 	delay(500);

// 	// large block of text
// 	tft.fillScreen(ST77XX_BLACK);
// 	testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST77XX_WHITE);
// 	delay(1000);

// 	// tft print function!
// 	tftPrintTest();
// 	delay(4000);

// 	// a single pixel
// 	tft.drawPixel(tft.width() / 2, tft.height() / 2, ST77XX_GREEN);
// 	delay(500);

// 	// line draw test
// 	testlines(ST77XX_YELLOW);
// 	delay(500);

// 	// optimized lines
// 	testfastlines(ST77XX_RED, ST77XX_BLUE);
// 	delay(500);

// 	testdrawrects(ST77XX_GREEN);
// 	delay(500);

// 	testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
// 	delay(500);

// 	tft.fillScreen(ST77XX_BLACK);
// 	testfillcircles(10, ST77XX_BLUE);
// 	testdrawcircles(10, ST77XX_WHITE);
// 	delay(500);

// 	testroundrects();
// 	delay(500);

// 	testtriangles();
// 	delay(500);

// 	mediabuttons();
// 	delay(500);

// 	Serial.println("done");
// 	delay(1000);
// }

// void loop()
// {
// 	tft.invertDisplay(true);
// 	delay(500);
// 	tft.invertDisplay(false);
// 	delay(500);
// }