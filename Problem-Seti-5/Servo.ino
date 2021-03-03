#include<Servo.h>

Servo servo;
void setup() {
  servo.attach(3);
 
}

void loop() {
 for(int i=0 ;i <= 180 ;i+=15){
    servo.write(i);
    delay(1000);
 }
 for(int g=180 ; g>=0 ;g-=30){
  servo.write(g);
  delay(1000);
 }

}
