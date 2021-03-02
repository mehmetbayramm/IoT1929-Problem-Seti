int ledk = 8;
int leds= 9;
int ledy = 10;

void setup() {
 pinMode(ledk, OUTPUT);
 pinMode(leds, OUTPUT);
 pinMode(ledy, OUTPUT);



}

void loop() {
  digitalWrite(ledk, HIGH);
  delay(10000);
  digitalWrite(leds, HIGH);
  delay(2000);
  digitalWrite(ledk,LOW);
  digitalWrite(leds,LOW);
  digitalWrite(ledy,HIGH);
  delay(5000);
  digitalWrite(ledy,LOW);
  digitalWrite(leds,HIGH);
  delay(2000);
  digitalWrite(leds, LOW);
}
