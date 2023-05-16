#ifndef INTERRUPTHANDLER
#define INTERRUPTHANDLER

#include <Arduino.h>

#define BUTTON1_PIN GPIO_NUM_42
#define BUTTON2_PIN GPIO_NUM_41
#define BUTTON3_PIN GPIO_NUM_40
#define BUTTON4_PIN GPIO_NUM_39
#define BUTTON5_PIN GPIO_NUM_38
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