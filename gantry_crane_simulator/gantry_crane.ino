#define pushButton 13
#define toggleSwitch 12
#define potentiometer A0

#define motorPin1 3
#define motorPin2 2

int pushState; //init 1
int toggleState; //init 0
int val;

void setup() {
    Serial.begin(9600);
    pinMode(pushButton, INPUT);
    pinMode(toggleSwitch, INPUT);
    
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
}

void loop() {
    pushState = digitalRead(pushButton);
    toggleState = digitalRead(toggleSwitch);
    val = analogRead(potentiometer); //0-1023
    //Serial.println(pushState);
    //Serial.println(toggleState);
    //Serial.println(val);
}
