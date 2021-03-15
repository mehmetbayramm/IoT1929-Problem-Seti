

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <Servo.h>
Servo servo;
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "4hGVwh3-g4uomVW--gtneHoGh1zjWsEt";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Redmi 5 Plus";
char pass[] = "7b2bde714546";

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

void setup()
{
  // Debug console
  Serial.begin(115200);
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  servo.attach(13);
  Blynk.begin(auth, wifi, ssid, pass);
  
}

void loop()
{
  Blynk.run();
}
BLYNK_WRITE(V0){
  servo.write(param.asInt());
}
