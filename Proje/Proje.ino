
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>       //RFID,Servo,Oled,Lcd ekran için kütüphanelermizi ekliyoruz
#include <Servo.h>
#include "U8glib.h"

int kirmizi = 5;  
int yesil = 4;              //RGB ledimizin bacaklarını tanımlıyoruz.
int mavi = 2; 

char bufferX [20];
char bufferY [20];        //Oled ekranımızın satır geenişliğini ayarlıyoruz
char bufferZ [20];

int buzzerpin = 3;        //Buzzer'ı arduino'nun 3. pinine takıyoruz.
int kizilpin = A1;       //Kızılötesi sensörümüzü A1 pinine bağlıyoruz.
int RST_PIN = 9;        //RFID kart okuyucunun RST girişini 9.pine bağladık.               
int SS_PIN = 10;       //RFID kart okuyucuun SDA girişini 10. pine bağlıyoruz.

MFRC522 rfid(SS_PIN, RST_PIN);                                        //RFID kütüphanesinden kodda kullanmak için bir obje oluşturuyoruz.
LiquidCrystal_I2C lcd(0x27,16,2);                                    //LCD ekran kütüphanesinden kodda kullanmak için bir obje oluşturuyoruz.
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);    //OLED kütüphanesinden kodda kullanmak için bir obje oluşturuyoruz.
         
byte ID[4] = {192,6,180,53};    //Bu bizim elimizdeki kartın PIN'i.

Servo servo;      //Servo kütüphanesinden kodda kullanmak için bir obje oluşturuyoruz.
void setup() {
  Serial.begin(9600); //Serial Port ile 9600 baudrate hızında haberleşme başlatıyoruz
  pinMode(kizilpin ,INPUT);          //Sensor değer okuyacağı için "giriş" olarak tanımlıyoruz.
  pinMode(buzzerpin , OUTPUT);       
  pinMode(kirmizi, OUTPUT);         
  pinMode(yesil, OUTPUT);          //Kullandıgımız komponentleri "çıkış" olarak tanımlıyoruz.
  pinMode(mavi, OUTPUT);          
  lcd.begin();                     //LCD ekranı başlatıyoruz.
  SPI.begin();                    //SPI haberleşme protokolünü başlatıyoruz.     
  rfid.PCD_Init();               //RFID kart okuyucuyu başlatıyoruz.             
  servo.attach(6);              //Servo pinimizi 6 olarak tanımlıyoruz.
  servo.write(0);              //Servo motoru başlangıç olarak 0 konumuna getiriyoruz.
  sprintf(bufferX, "LUTFEN KARTINIZI");
  sprintf(bufferY, " KART OKUYUCUYA");          //OLED ekranında yazmasını istediğimiz metni giriyoruz.
  sprintf(bufferZ, "   OKUTUNUZ");            // Ekranda hep aynı metin olacağı için setup kısmına bir kez yazıyoruz.
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );               //OLED ekranın doğru metni yazması için gerekli olan fonksiyonlar.
  delay(10);
}
  
void loop() {
      int sensorVal = analogRead(kizilpin);    //Sensörün okuduğu değeri integer olarak tanımladığımız "sensorVal" değişkenine atıyoruz.
      Serial.println(sensorVal);              //Sensör değerini serial port ekranına yazdırıyoruz
   
        if(sensorVal<700){                    //Sensör değeri 700 den düşük olduğunda(kapı açıldığında bu if state'inin içine giriyor.
           tone(buzzerpin,600);               //Buzzer komşulara haber vermek ya da gelen kişinin dikkatini dağıtmak için ses çıkarıyor.
           lcd.setCursor(0,0);
           lcd.print("Hirsiz Var");           //Hırısızı panikletmek için"Hırsız var 155 aranıyor." yazısınız yazdırıyoruz.
           lcd.setCursor(0,1);               //Fakat gerçekten de aramıyor. Sadece panikeltmek için.
           lcd.print("155 Araniyor!!");
           delay(500);

           }
     
      
      if ( ! rfid.PICC_IsNewCardPresent())    //Yeni kartın okunmasını bekliyoruz.
      return;

      if ( ! rfid.PICC_ReadCardSerial())
    return;    //Kart okunmadığı zaman bekliyoruz.
     

     if (rfid.uid.uidByte[0] == ID[0] &&     //Okunan kart ID'si ile ID değişkenini karşılaştırıyoruz.
      rfid.uid.uidByte[1] == ID[1] &&       //Eğer doğruysa buradaki if state'inin içine giriyor
      rfid.uid.uidByte[2] == ID[2] && 
      rfid.uid.uidByte[3] == ID[3] ) {
        tone(buzzerpin , 1568);
        delay(100);
        tone(buzzerpin, 1075);       //Buzzer girişin onayllandığını belirtmek için ses çıkarıyor.
        delay(300);
        noTone(buzzerpin);          //Buzzer susturuldu.
        lcd.setCursor(0,0);
        lcd.print("Hos Geldiniz");
        lcd.setCursor(0,1);           //Ev sahibine karşılama yapılıyor.
        lcd.print("Alarm Susturuldu");
        
        digitalWrite(kirmizi,HIGH);
        digitalWrite(mavi,HIGH);      //RGB ledimizde yeşil yanmasını sağlıyoruz.
        digitalWrite(yesil, LOW);
           
        servo.write(90);            //Servo motorumuzu kapıymış gibi düşünüyoruz.Doğru kart okunduğunda kapıyı açıyor.
        delay(800);
        
        lcd.clear();                 //LCD ekranımızı temizliyoruz.
        lcd.setCursor(0,0);
        lcd.print("Hos Geldiniz");   
        lcd.setCursor(0,1);          
        lcd.print("Kapi Acildi.");      //Ev sahibine kapının açıldığını haber veriyoruz. Aslında bunu kendisi de bakarak anlayabilir
        delay(2000);
        
        digitalWrite(yesil,HIGH);
        digitalWrite(mavi,HIGH);          //RGB ledimizi söndürüyoruz.
        digitalWrite(kirmizi, HIGH);
        
        exit(0);                          //Ev sahibinin eve girişinden sonra sensörümüzün değer okumaması için döngüyü sonlandırıyoruz.
       }

    delay(1000);
}
void draw(void)
{


  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 20, bufferX);       //üst tarafta kullandığımız draw() fonksiyonunun tanımlaması.
  u8g.drawStr( 0, 40, bufferY);
  u8g.drawStr( 0, 60, bufferZ);
}
