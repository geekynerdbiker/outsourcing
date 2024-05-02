#include <SoftwareSerial.h>

#define RX 2
#define TX 3

#define SOUND A0
#define SHOCK 6
#define D_AMP 7
#define RECORD 8
#define PLAY 9

#define SOUND_THRESHOLD 25
#define D_AMP_TONE 500
#define SEC 1000

// #define LED_R 8
// #define LED_G 9
// #define LED_B 10

SoftwareSerial HC06(TX, RX);

void setup() {
    Serial.begin(9600);
    HC06.begin(9600);
    
    pinMode(SOUND, INPUT);
    pinMode(SHOCK, INPUT);

    pinMode(D_AMP, OUTPUT);
    // pinMode(LED_R, OUTPUT);
    // pinMode(LED_G, OUTPUT);
    // pinMode(LED_B, OUTPUT);
    
}

void loop() {
    if (digitalRead(SHOCK) && analogRead(A0) >= SOUND_THRESHOLD) {
        tone(D_AMP, D_AMP_TONE, SEC);
        noTone(D_AMP);

        digitalWrite(REC, HIGH);
        delay(SEC);
        digitalWrite(REC, LOW);


        // digitalWrite(LED_R, HIGH);
        // digitalWrite(LED_G, HIGH);
        // digitalWrite(LED_B, HIGH);
    } else {
        // digitalWrite(LED_R, LOW);
        // digitalWrite(LED_G, LOW);
        // digitalWrite(LED_B, LOW);
    }
}
