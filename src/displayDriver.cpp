#include "displayDriver.h"

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
Adafruit_ImageReader reader(SD);
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
	tft.setTextColor(ST77XX_WHITE, ST77XX_BLUE);
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

void displayDriver::displayTime(std::string time)
{
  tft.setCursor(110, 65);
  tft.setTextSize(4);
  tft.print(time.c_str());
}

void displayDriver::displayDate(std::string date)
{
  tft.setCursor(138, 102);
  tft.setTextSize(2);
  tft.print(date.c_str());
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

void displayDriver::displayStillGIF(char * img)
{
	if (gif.open(img, GIFOpenFile, GIFCloseFile, GIFReadFile, GIFSeekFile, GIFDraw)) 
	{
		GIFINFO gi;
		Serial.printf("Successfully opened GIF %s; Canvas size = %d x %d\n",  img, gif.getCanvasWidth(), gif.getCanvasHeight());
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
		Serial.printf("Error opening file %s = %d\n", img, gif.getLastError());
	}
}

void displayDriver::displayBMP(char * bmp, int x, int y)
{
  mountSD();
  ImageReturnCode code = reader.drawBMP(bmp, tft, x, y);
  reader.printStatus(code);
  unmountSD();
}