
// void setup() {
//   Serial.begin(115200);
//   while (!Serial);

//   Serial.println("Adafruit SPIFlash Animated GIF Example");

//   // Initialize flash library and check its chip ID.
//   if (!flash.begin()) {
// 	Serial.println("Error, failed to initialize flash chip!");
// 	while(1);
//   }
//   Serial.print("Flash chip JEDEC ID: 0x"); Serial.println(flash.getJEDECID(), HEX);

//   // First call begin to mount the filesystem.  Check that it returns true
//   // to make sure the filesystem was mounted.
//   if (!fatfs.begin(&flash)) {
// 	Serial.println("Failed to mount filesystem!");
// 	Serial.println("Was CircuitPython loaded on the board first to create the filesystem?");
// 	while(1);
//   }
//   Serial.println("Mounted filesystem!");

//   if (!root.open(GIFDIRNAME)) {
// 	Serial.println("Open dir failed");
//   }
//   while (f.openNext(&root, O_RDONLY)) {
// 	f.printFileSize(&Serial);
// 	Serial.write(' ');
// 	f.printModifyDateTime(&Serial);
// 	Serial.write(' ');
// 	f.printName(&Serial);
// 	if (f.isDir()) {
// 	  // Indicate a directory.
// 	  Serial.write('/');
// 	}
// 	Serial.println();
// 	f.close();
//   }
//   root.close();
  
//   tft.init(DISPLAY_HEIGHT, DISPLAY_WIDTH);
//   tft.fillScreen(ST77XX_BLUE);
//   tft.setRotation(1);
//   gif.begin(LITTLE_ENDIAN_PIXELS);
// }

// void loop() {
//   char thefilename[80];
  
//   if (!root.open(GIFDIRNAME)) {
// 	Serial.println("Open GIF directory failed");
// 	while (1);
//   }
//   while (f.openNext(&root, O_RDONLY)) {
// 	f.printFileSize(&Serial);
// 	Serial.write(' ');
// 	f.printModifyDateTime(&Serial);
// 	Serial.write(' ');
// 	f.printName(&Serial);
// 	if (f.isDir()) {
// 	  // Indicate a directory.
// 	  Serial.write('/');
// 	}
// 	Serial.println();
// 	f.getName(thefilename, sizeof(thefilename)-1);
// 	f.close();
// 	if (strstr(thefilename, ".gif") || strstr(thefilename, ".GIF")) {
// 	  // found a gif mebe!
// 	  if (gif.open(thefilename, GIFOpenFile, GIFCloseFile, GIFReadFile, GIFSeekFile, GIFDraw)) {
// 		GIFINFO gi;
// 		Serial.printf("Successfully opened GIF %s; Canvas size = %d x %d\n",  thefilename, gif.getCanvasWidth(), gif.getCanvasHeight());
// 		if (gif.getInfo(&gi)) {
// 		  Serial.printf("frame count: %d\n", gi.iFrameCount);
// 		  Serial.printf("duration: %d ms\n", gi.iDuration);
// 		  Serial.printf("max delay: %d ms\n", gi.iMaxDelay);
// 		  Serial.printf("min delay: %d ms\n", gi.iMinDelay);
// 		}
// 		// play thru n times
// 		for (int loops=0; loops<NUM_LOOPS; loops++) {
// 		  while (gif.playFrame(true, NULL));
// 		  gif.reset();
// 		}
// 		gif.close();
// 	  } else {
// 		Serial.printf("Error opening file %s = %d\n", thefilename, gif.getLastError());
// 	  }
// 	}
//   }
//   root.close();
// }
