#include <Servo.h>
Servo servo;
int potpin= A0;
int buttonpin = 6;
int deger=0;


void setup(){
  pinMode(buttonpin, INPUT);
  servo.attach(9);
  }
void loop(){
  if (digitalRead(buttonpin) == HIGH){
    deger =analogRead(potpin);
    deger = map(deger,0,1023,0,180);
    servo.write(deger);
    delay(10);
  }
  else if(digitalRead(buttonpin) == LOW){
    deger =analogRead(potpin);
    deger = map(deger,0,1023,0,90);
    servo.write(deger);
    delay(10);
  }
  
  
  
  
  }
