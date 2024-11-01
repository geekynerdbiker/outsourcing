#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

#define TOUCH 3

#define HUM 5

#define LED_R 8
#define LED_G 9
#define LED_B 10

DHT dht11(DHTPIN, DHTTYPE);

bool dht = false;

bool touch = false;
unsigned long touchStart;

bool ultrasonic = false;
int ultrasonicCount = 0;

void setup() {
    Serial.begin(9600);
    
    pinMode(TOUCH, INPUT);
    
    pinMode(HUM, OUTPUT);
    
    pinMode(LED_R,OUTPUT);
    pinMode(LED_G,OUTPUT);
    pinMode(LED_B,OUTPUT);
    
}

void loop() {
    if (!touch && digitalRead(TOUCH)) {
        touch = true;
        touchStart = millis();
    }
    
    if (millis() - touchStart < 1000 && touch && !digitalRead(TOUCH))
        touch = false;
    else if (millis() - touchStart >= 1000 && touch && digitalRead(TOUCH)) {
        dht = true;
        touch = false;
    }
    
    if (dht) {
        digitalWrite(LED_G, HIGH);
        
        int temp = dht11.readTemperature();
        
        Serial.print("Temperature: ");
        Serial.print(temp);
        Serial.println(" C");
        
        if (temp >= 40) {
            digitalWrite(LED_R, HIGH);
            
            ultrasonic = true;
            unsigned long ultrasonicStart = millis();
        }
        
        if (ultrasonic) {
            if ((millis() - ultrasonicStart) % 6000 == 0) {
                digitalWrite(HUM, HIGH);
                delay(1000);
                digitalWrite(HUM, LOW);
                ultrasonicCount++;
            }
        }
        
        if (ultrasonicCount == 6) {
            ultrasonicCount = 0;
            ultrasonic = false;
            digitalWrite(LED_R, LOW);
        }
        
        if (digitalRead(TOUCH) && touch) {
            touch = false;
            touchStart = millis();
        }
        
        if (!touch && digitalRead(TOUCH)) {
            touch = true;
            touchStart = millis();
        }
    
        if (millis() - touchStart < 1000 && touch && !digitalRead(TOUCH))
            touch = false;
        else if (millis() - touchStart >= 1000 && touch && digitalRead(TOUCH)) {
            dht = false;
            touch = false;
        }
        
    }
}
