#include "soundHandler.h"

void playPitch(Pitch pitch, int octave, Duration duration, bool turnOff = false)
{
    tone(buzzerPin, (uint8_t) (pitch * (2^octave)));
    delay((uint32_t) duration);
    if (turnOff)
    {    
        noTone(buzzerPin);
    }
}

void playFanfare(void)
{
    playPitch(A, 0, TripletQuaver);
    playPitch(Db, 0, TripletQuaver);
    playPitch(E, 0, TripletQuaver);
    playPitch(A, 1, TripletCrotchet);
    playPitch(E, 0, TripletQuaver);
    playPitch(A, 1, Crotchet, true);
}