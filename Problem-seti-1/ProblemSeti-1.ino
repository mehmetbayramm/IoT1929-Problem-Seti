int ledpinler[] = {8,9,10,11,12}; //5 led olduğu için tek tek tanımlamak yerine hepsini bir array içine yerleştirdim.
int bekleme = 500;// soruda 0.5 saniye istendiği için gecikmemizi 500 oalrak tanımladım.

void setup() {
 for(int led = 0; led<5 ; led++) //bütün ledileri for döngüsüne koyarak OUTPUT olarak ayarlıyoruz.
{
  pinMode(ledpinler[led],OUTPUT);
}
    digitalWrite(ledpinler[0] , HIGH);     //her denememde ya ilk ya da sonuncu led 2 kere yanıyordu.onun için bir kez
    delay(bekleme);                       //setup kısmında ilk ledi yakıp söndürdüm ve ilk for döngüsünü 1. ledden(ilk ledimize array 0 değerini verdiği için breadboarddaki 2. led kodda 1. led olmuş oluyor) başlattım.
    digitalWrite(ledpinler[0] , LOW);    //bu sayede her led tek sefer yandı.
    
}
void loop() {
  
    
  for(int led = 0;led<4;led++)        //ledlerimizi sırasıyla ileri doğru yakıp söndürüyor.
  {
    digitalWrite(ledpinler[led+1] , HIGH);
    delay(bekleme);
    digitalWrite(ledpinler[led+1] , LOW);
    
  }
  for(int led = 4;led >0;led--)     //ledlerimizi sırasıyla geri doğru yakıp söndürüyor.
  { 
    digitalWrite(ledpinler[led-1] , HIGH);
    delay(bekleme);
    digitalWrite(ledpinler[led-1], LOW);
    
  }
}
