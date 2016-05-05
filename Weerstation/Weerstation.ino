#define DHTTYPE DHT22   // DHT 22  (AM2302)


#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#include "DHT.h"
#include <Adafruit_BMP085.h>

#define DHTPIN 2     // what pin we're connected to

LiquidCrystal_I2C	lcd(0x27,2,1,0,4,5,6,7);
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

   


void setup()
{
   dht.begin();
   bmp.begin();

  lcd.begin (16,2);
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);


  lcd.home ();                   // go home
  lcd.print("Hello, Arduino ");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print("Lekker weertje!");

  delay ( 1000 );
}

void loop()
{
  float p;


 // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  p = bmp.readPressure();

   lcd.clear ();
   lcd.home ();
   lcd.print("T=");
   lcd.print(t);
   lcd.print(" RH=");
   lcd.print(round(h));
   lcd.print("%");
 
 
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print("P=");
  lcd.print(round(p/100));
  lcd.print("HPa");
  


   delay (5000);
}

