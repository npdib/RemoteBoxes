#ifndef INTERRUPTHANDLER
#define INTERRUPTHANDLER

#include <Arduino.h>

#define BUTTON1_PIN GPIO_NUM_42
#define BUTTON2_PIN GPIO_NUM_12
#define READY_THRESHOLD 5000

typedef struct
{
    bool pressed = false;
    unsigned long timer = 0;
} Button;

extern Button buttons[5];

void IRAM_ATTR Button1ISR(void);
void setupButtonInterrupts(void);

#endif