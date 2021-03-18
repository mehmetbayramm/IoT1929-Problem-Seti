#include <MFRC522.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
int kirmizi = 6;  
int yesil = 5;  
int mavi = 4; 

int buzzerpin = 3;

int RST_PIN = 9;                         
int SS_PIN = 10; 

MFRC522 rfid(SS_PIN, RST_PIN);           
byte ID[4] = {192,6,180,53};
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(buzzerpin , OUTPUT);
   pinMode(kirmizi, OUTPUT);   
  pinMode(yesil, OUTPUT);   
  pinMode(mavi, OUTPUT); 
  SPI.begin();                         
  rfid.PCD_Init();
  lcd.begin();
 
}

void loop() {
         lcd.setCursor(0,0);
        lcd.print("Lutfen Kartinizi");
        lcd.setCursor(0,1);
        lcd.print("    Okutunuz");
        digitalWrite(yesil,HIGH);
        digitalWrite(mavi,LOW);
        digitalWrite(kirmizi, HIGH);
 
  if ( ! rfid.PICC_IsNewCardPresent())    //Yeni kartın okunmasını bekliyoruz.
    return;

  if ( ! rfid.PICC_ReadCardSerial())      //Kart okunmadığı zaman bekliyoruz.
    return;

  if (rfid.uid.uidByte[0] == ID[0] &&     //Okunan kart ID'si ile ID değişkenini karşılaştırıyoruz.
    rfid.uid.uidByte[1] == ID[1] && 
    rfid.uid.uidByte[2] == ID[2] && 
    rfid.uid.uidByte[3] == ID[3] ) {
        digitalWrite(kirmizi,HIGH);
        digitalWrite(mavi,HIGH);
        digitalWrite(yesil, LOW);
        tone(buzzerpin , 1568);
        delay(100);
        tone(buzzerpin, 1075);
        delay(300);
        noTone(buzzerpin);
        lcd.setCursor(0,0);
        lcd.print("   Mehmet Bey   ");
        lcd.setCursor(0,1);
        lcd.print("  Hosgeldiniz!");
        delay(3000);
        lcd.clear();
    }
   else {
         digitalWrite(yesil,HIGH);
        digitalWrite(mavi,HIGH);
        digitalWrite(kirmizi, LOW);
        tone(buzzerpin , 300);
        delay(300);
        tone(buzzerpin, 200);
        delay(200);
        noTone(buzzerpin);
        lcd.setCursor(0,0);
        lcd.print("Giris Basarisiz.");
        lcd.setCursor(0,1);
        lcd.print(" Gecersiz Kart!");
        delay(3000);
        lcd.clear();
    }
        
    }
    
