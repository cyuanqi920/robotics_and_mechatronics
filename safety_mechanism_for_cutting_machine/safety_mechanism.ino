#include "pitches.h"
#define echoPin 8 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 9 //attach pin D3 Arduino to pin Trig of HC-SR04
#define buzzPin 3
#define optoPin 5

int optoState;
long distance;

void setup() {
    Serial.begin(9600);
    pinMode(optoPin, INPUT);
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
}

void loop() {
    optoState = digitalRead(optoPin);

    if (optoState){
        distance = get_distance();
        Serial.println(distance);

        if (distance > 40)
            buzz(NOTE_C4, 1);
        else if (distance <= 40 && distance > 20)
            buzz(NOTE_C4, 2);
        else
            buzz(NOTE_C4, 3);
    }
}

long get_distance(){
    long duration;
    digitalWrite(trigPin, LOW);delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);delayMicroseconds(2);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    return duration * 0.034 / 2;
}

void buzz(int melody, int freq){
    int noteDuration = 1000 / freq;
    tone(buzzPin, melody, noteDuration);
    delay(1.3 * noteDuration);
    noTone(buzzPin);
}
