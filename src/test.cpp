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
