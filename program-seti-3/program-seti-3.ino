const int DHT11_pin=2;
#include <LiquidCrystal_I2C.h>
#include <dht11.h>
LiquidCrystal_I2C  lcd(0x27,16,2);
dht11 DHT11;


void setup()
{
  lcd.begin ();
  
}
void loop()
{
  int chk = DHT11.read(DHT11_pin);
  lcd.print("Nem orani: ");
  lcd.print((float)DHT11.humidity, 2); 
  lcd.setCursor (0,1);
  lcd.print("Sicaklik(C)"); 
  lcd.print((float)DHT11.temperature, 2);
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nem orani: ");
  lcd.print((float)DHT11.humidity, 2);
  lcd.setCursor (0,1);
  lcd.print("Sicaklik(K)"); 
  lcd.print((float)DHT11.kelvin(), 2);
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nem orani: ");
  lcd.print((float)DHT11.humidity, 2);
  lcd.setCursor (0,1);
  lcd.print("Sicaklik(F)"); 
  lcd.print((float)DHT11.fahrenheit(), 2);
  delay(5000);
  lcd.clear();
  
 }
