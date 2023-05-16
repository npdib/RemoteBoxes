#include "soundHandler.h"

void playPitch(Pitch pitch, int octave, unsigned long length)
{
    tone(buzzerPin, (uint8_t) (pitch * (2^octave)));
    delay(length);
    noTone(buzzerPin);
}