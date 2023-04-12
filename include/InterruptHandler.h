#ifndef INTERRUPTHANDLER
#define INTERRUPTHANDLER

#include <Arduino.h>

#define BUTTON1_PIN GPIO_NUM_42

extern bool button1pressed;

void setupButtonInterrupts(void);

#endif