#include "InterruptHandler.h"

bool button1pressed = false;

void IRAM_ATTR Button1ISR(void)
{
    button1pressed = true;
}

void setupButtonInterrupts(void)
{
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    attachInterrupt(BUTTON1_PIN, Button1ISR, FALLING);
}