#ifndef INTERRUPTHANDLER
#define INTERRUPTHANDLER

#include <Arduino.h>

#define BUTTON1_PIN GPIO_NUM_16
#define BUTTON2_PIN GPIO_NUM_15
#define BUTTON3_PIN GPIO_NUM_14
#define BUTTON4_PIN GPIO_NUM_13
#define BUTTON5_PIN GPIO_NUM_12
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