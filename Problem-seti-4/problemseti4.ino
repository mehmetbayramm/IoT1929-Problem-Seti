#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define potpin A0
#define motorpin 9
#define led 6
int pot,potVal,rpm ;
void setup() {
  lcd.begin(16,2);
  pinMode(motorpin, OUTPUT);
  pinMode(potpin, INPUT);
  pinMode(led,OUTPUT);
 
}

void loop() {
  pot = analogRead(potpin);
  potVal = map(pot, 0, 1023, 0, 255);
  analogWrite (motorpin, potVal);
  rpm = map(pot,0,1023,0,5555);
  delay(20);
  lcd.setCursor(0,0);
  lcd.print("Rpm = ");
  lcd.print(rpm);
  delay (20);
  if(rpm>=3500){
    digitalWrite(led,HIGH);
  }
  else{
    digitalWrite(led,LOW);
  }
}
