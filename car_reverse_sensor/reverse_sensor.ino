#include "pitches.h"

#define pushButtonPin 2
#define toggleSwitchPin 3
#define limitSwitchPin 4
#define buzzerPin 8
#define solenoidPin 10
#define onBoardLEDPin 13

int pushButtonState; //init 1
int toggleSwitchState; //init 1
int limitSwitchState; //init 0

void setup() {
    Serial.begin(9600);
    pinMode(pushButtonPin, INPUT);
    pinMode(toggleSwitchPin, INPUT);
    pinMode(limitSwitchPin, INPUT);
    pinMode(solenoidPin, OUTPUT);
    pinMode(onBoardLEDPin, OUTPUT);
}

void loop() {
    pushButtonState = digitalRead(pushButtonPin);
    toggleSwitchState = digitalRead(toggleSwitchPin);
    limitSwitchState = digitalRead(limitSwitchPin);
    //Serial.println(pushButtonState);
    //Serial.println(toggleSwitchState);
    //Serial.println(limitSwitchState);

    if (!toggleSwitchState){
        digitalWrite(onBoardLEDPin, 1); //on indicator
        
        if (limitSwitchState && !pushButtonState)
            cut(10);
            delay(500);
    }
    else
       digitalWrite(onBoardLEDPin, 0);
}

void buzz(int melody, int n){
    for (int i=0; i<n; i++){
        tone(buzzerPin, melody, 100);delay(100);
        noTone(buzzerPin);delay(100);
    }
}

void cut(int n){
    for (int i=0; i<n; i++){
        limitSwitchState = digitalRead(limitSwitchPin);
        if (!limitSwitchState){
            buzz(NOTE_C4, 3);
            return;
        }

        digitalWrite(solenoidPin, 1);
        delay(100);
        digitalWrite(solenoidPin, 0);
        delay(100);

    } 
}
