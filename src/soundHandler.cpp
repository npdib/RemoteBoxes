#include "soundHandler.h"

void playPitch(Pitch pitch, int octave, Duration duration, bool turnOff = false)
{
    unsigned int freq = (octave >=0 ) ? (pitch << (octave)) : (pitch >> (octave * -1));
    tone(buzzerPin, (unsigned int) (octave >= 0) ? (pitch << octave) : (pitch >> (octave * -1)));
    delay((uint32_t) duration - 5);
    noTone(buzzerPin);
    delay(5);
}

void playFanfare(void)
{
    playPitch(A, 1, SemiQuaver);
    playPitch(B, 1, Quaver);
    playPitch(C, 1, DottedQuaver);
    playPitch(B, 1, SemiQuaver);
    playPitch(A, 1, Quaver);
    playPitch(Ab, 0, DottedQuaver);
    playPitch(Gb, 0, SemiQuaver);
    playPitch(Ab, 0, Quaver);
    playPitch(A, 1, DottedQuaver);
    playPitch(G, 0, SemiQuaver);
    playPitch(F, 0, Quaver);
    playPitch(E, 0, DottedQuaver);
    playPitch(D, 0, SemiQuaver);
    playPitch(E, 0, Quaver);
    playPitch(F, 0, Quaver);
    playPitch(E, 0, Quaver);
    playPitch(D, 0, Quaver);
    playPitch(Db, 0, Quaver);
    playPitch(B, 0, Quaver);
    playPitch(Db, 0, Quaver);
    playPitch(D, 0, Quaver);
    playPitch(A, 0, Quaver);
    playPitch(Gb, -1, Quaver);
    playPitch(D, -1, DottedCrotchet);
}

void happyBirthday(void)
{
    playPitch(C, 0, DottedQuaver);
    playPitch(C, 0, SemiQuaver);
    playPitch(D, 0, Crotchet);
    playPitch(C, 0, Crotchet);
    playPitch(F, 0, Crotchet);
    playPitch(E, 0, Crotchet);
    delay(Crotchet);
    playPitch(C, 0, DottedQuaver);
    playPitch(C, 0, SemiQuaver);
    playPitch(D, 0, Crotchet);
    playPitch(C, 0, Crotchet);
    playPitch(G, 0, Crotchet);
    playPitch(F, 0, Crotchet);
    delay(Crotchet);
    playPitch(C, 0, DottedQuaver);
    playPitch(C, 0, SemiQuaver);
    playPitch(C, 1, Crotchet);
    playPitch(A, 1, Crotchet);
    playPitch(F, 0, Crotchet);
    playPitch(E, 0, Crotchet);
    playPitch(D, 0, Crotchet);
    delay(Crotchet);
    playPitch(Bb, 1, DottedQuaver);
    playPitch(Bb, 1, SemiQuaver);
    playPitch(A, 1, Crotchet);
    playPitch(F, 0, Crotchet);
    playPitch(G, 0, Crotchet);
    playPitch(F, 0, Minum);    
}

void messageReceived(void)
{
    playPitch(D, 0, SemiQuaver);
    playPitch(Gb, 0, SemiQuaver);
    playPitch(A, 1, Quaver);
}

void dismissSound(void)
{
    playPitch(E, 0, SemiQuaver);
    playPitch(Db, 0, SemiQuaver);
}

void replaySound(void)
{
    playPitch(A, 0, SemiQuaver);
    playPitch(D, 0, SemiQuaver);
}