#ifndef SOUNDHANDLER
#define SOUNDHANDLER

#include <Arduino.h>

constexpr gpio_num_t buzzerPin = GPIO_NUM_6;

typedef enum pitch_t{
    A = 440,
    Bb = 466,
    B = 494,
    C = 523,
    Db = 554,
    D = 587,
    Eb = 622,
    E = 659,
    F = 698,
    Gb = 740,
    G = 784,
    Ab = 831
} Pitch;

// octave 0 is the octave from A4 to Ab5
void playPitch(Pitch, int, unsigned long);

#endif // SOUNDHANDLER