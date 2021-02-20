#include <LiquidCrystal.h>
#include <ctype.h>

#define len 8

const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int KB_DataAvailable=A5;
int KB_A=10;
int KB_B=11;
int KB_C=12;
int KB_D=13;
char arr[len+1];

int calcMode = 0;

char kb_keys[] = {'1','2','3','F',
               '4','5','6','E',
               '7','8','9','D',
               'A','0','B','C'};
               
char calc_keys[] = {'1','2','3','F',
               '4','5','6','=',
               '7','8','9','/',
               '+','0','-','*'};
int output;

void setup() {
    Serial.begin(9600);
    pinMode(KB_DataAvailable,INPUT);
    pinMode(KB_A,INPUT);
    pinMode(KB_B,INPUT);
    pinMode(KB_C,INPUT);
    pinMode(KB_D,INPUT);
    lcd.begin(16, 2);
    lcd.print("Keyboard Mode");
    delay(1000);
    lcd.clear();
    initStr(arr);
}

void loop() {
    if(digitalRead(KB_DataAvailable)){
        KB_Read(arr, calcMode);
        lcd.setCursor(0, 0);
        lcd.print(arr);
        delay(200);
    }
    else if (calcMode==0 & arr[len-1]=='F' && arr[len-2]=='F'){
        lcd.clear();
        lcd.print("Calculator Mode");
        delay(1000);
        lcd.clear();
        initStr(arr);
        calcMode = 1;
    }
    else if (calcMode==1){
        if ((arr[len-1]=='=') && (arr[len-2]=='F')){
            lcd.clear();
            lcd.print("Keyboard Mode");
            delay(1000);
            initStr(arr);
            lcd.clear();
            calcMode = 0;
        }
        else if (arr[len-1]=='='){
            output = calculate(arr);
            lcd.setCursor(0, 1);
            if (output == -404)
                lcd.println("Error 404");
            else{
                Serial.println(output);
                lcd.println(output);
            }
            delay(5000);
            initStr(arr);
            lcd.clear();
        }
    }
}


void initStr(char str[]){
    for(int i=0; i<len; i++) str[i]=' ';
    str[len] = '\0';
}

void KB_Read(char str[], int calcMode){
    int ka,kb,kc,kd,i;
    char k;
    ka=digitalRead(KB_A); //read encoder output A
    kb=digitalRead(KB_B); //read encoder output B
    kc=digitalRead(KB_C); //read encoder output C
    kd=digitalRead(KB_D); //read encoder output D
    k=ka+kb*2+kc*4+kd*8; // combine the encoder outputs 
    
    for(i=0; i<len-1; i++) str[i]=str[i+1];//move displayed characters in FIFO queue forward discarding the first one
    if (calcMode)
        str[len-1] = calc_keys[k]; // update the key into the queue
    else
        str[len-1] = kb_keys[k];
    str[len]='\0'; // end with NULL
    //Serial.println(keys[k]);
}

int calculate(char str[]){
    int i = 0;
    char mathOperator;
    int num1 = 0, num2 = 0, num = 0;
    int result;
    int n=0;

    while (str[i] != '='){  
        if (!isdigit(str[i])){
            mathOperator = str[i];
            num1 = num;
            num = 0;
            n++;
        }

        else
            num = num*10 + int(str[i])-48;
        i++;
    }
    num2 = num;
    Serial.println(num1);
    Serial.println(num2);
    Serial.println(mathOperator);
    return operation(num1, num2, mathOperator);
}

int operation(int num1, int num2, char mathOperator){
    if (num1>999 || num2>999)
        return -404; //error
    else if (mathOperator == '+')
        return num1+num2;

    else if (mathOperator == '-')
        return num1-num2;

    else if (mathOperator == '*')
        return num1*num2;

    else if (mathOperator == '/')
        return num1/num2;

    else
        return -404; //error
   
}
