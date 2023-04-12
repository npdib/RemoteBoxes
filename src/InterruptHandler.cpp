#include "InterruptHandler.h"

button button1;

void IRAM_ATTR Button1ISR(void)
{
    if (button1.ready)
    {
        button1.pressed = true;
        button1.ready = false;
        button1.timer = millis();
    }
}

void setupButtonInterrupts(void)
{
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    attachInterrupt(BUTTON1_PIN, Button1ISR, FALLING);
}