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

typedef enum duration_t {
    SemiQuaver = 150,
    Quaver = 300,
    TripletQuaver = 200,
    Crotchet = 600, 
    Minum = 1200,
    SemiBreve = 2400,
    DottedCrotchet = 900,
    DottedQuaver = 450,
    TripletCrotchet = 400
} Duration;

// octave 0 is the octave from A4 to Ab5
void playPitch(Pitch, int, Duration, bool);
void playFanfare(void);
void happyBirthday(void);
void messageReceived(void);
void dismissSound(void);
void replaySound(void);

#endif // SOUNDHANDLER