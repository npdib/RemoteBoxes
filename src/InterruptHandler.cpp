#include "InterruptHandler.h"

Button buttons[5];

void IRAM_ATTR Button1ISR(void)
{
    if ((millis() - buttons[0].timer) > READY_THRESHOLD)
    {
        buttons[0].pressed = true;
        buttons[0].timer = millis();
    }
}

void IRAM_ATTR Button2ISR(void)
{
    if ((millis() - buttons[1].timer) > READY_THRESHOLD)
    {
        buttons[1].pressed = true;
        buttons[1].timer = millis();
    }
}

void IRAM_ATTR Button3ISR(void)
{
    if ((millis() - buttons[2].timer) > READY_THRESHOLD)
    {
        buttons[2].pressed = true;
        buttons[2].timer = millis();
    }
}

void IRAM_ATTR Button4ISR(void)
{
    if ((millis() - buttons[3].timer) > READY_THRESHOLD)
    {
        buttons[3].pressed = true;
        buttons[3].timer = millis();
    }
}

void IRAM_ATTR Button5ISR(void)
{
    if ((millis() - buttons[4].timer) > READY_THRESHOLD)
    {
        buttons[4].pressed = true;
        buttons[4].timer = millis();
    }
}

void setupButtonInterrupts(void)
{
    // setup button pins
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);
    pinMode(BUTTON3_PIN, INPUT_PULLUP);
    pinMode(BUTTON4_PIN, INPUT_PULLUP);
    pinMode(BUTTON5_PIN, INPUT_PULLUP);

    // attach button interrupts
    attachInterrupt(BUTTON1_PIN, Button1ISR, FALLING);
    attachInterrupt(BUTTON2_PIN, Button2ISR, FALLING);
    attachInterrupt(BUTTON3_PIN, Button3ISR, FALLING);
    attachInterrupt(BUTTON4_PIN, Button4ISR, FALLING);
    attachInterrupt(BUTTON5_PIN, Button5ISR, FALLING);
}