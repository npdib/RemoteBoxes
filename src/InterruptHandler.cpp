#include "InterruptHandler.h"

Button buttons[5];

void IRAM_ATTR Button1ISR(void)
{
    if ((millis() - buttons[3].timer) > READY_THRESHOLD)
    {
        buttons[3].pressed = true;
        buttons[3].timer = millis();
    }
}

void setupButtonInterrupts(void)
{
    // setup button pins
    pinMode(BUTTON1_PIN, INPUT_PULLUP);

    // attach button interrupts
    attachInterrupt(BUTTON1_PIN, Button1ISR, FALLING);
}