#ifndef INTERRUPTHANDLER
#define INTERRUPTHANDLER

#include <Arduino.h>

#define BUTTON1_PIN GPIO_NUM_42

struct button
{
    bool pressed = false;
    bool ready = false;
    unsigned long timer = 0;
};

extern button button1;

void setupButtonInterrupts(void);

#endif