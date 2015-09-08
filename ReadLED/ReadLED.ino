/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */
 
// #include <Fat16.h> // the SD Card library - http://code.google.com/p/fat16lib/
// #include <Wire.h>  
 
 // include the library code:
#include <LiquidCrystal.h>

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
const int led = 13;
const int tsl250 = 3;
const int logInterrupt = 1; // ATmega 168 and 328 - interrupt 0 = pin 2, 1 = pin 3
const long logInterval = 5000;


int val = 0;
volatile unsigned long WattSensor = 0;
volatile unsigned long WattPulseCount = 0;
volatile unsigned long TotalWatts = 0;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  // 
  attachInterrupt(logInterrupt, interruptHandler, FALLING);  
   // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Time:");
  lcd.setCursor(0,1);
  lcd.print("Pulses:");

}

// the loop routine runs over and over again forever:
void loop() {
   val = analogRead(tsl250);    // read the input pin
  if (val>500) { digitalWrite(led, HIGH); }
  else {digitalWrite(led, LOW); }
  
  Serial.println(val);             // debug value

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(6, 0);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
  
  MeterPulseLog();
 
  delay(logInterval);

//  lcd.print(millis()/1000);
}

void MeterPulseLog()
{
    unsigned long WattSensorCount; //number of watts during this logging interval 
    uint8_t oldSREG = SREG;   // save interrupt register
    cli();                    // prevent interrupts while accessing the count   
    WattSensorCount = WattSensor; //get the count from the interrupt handler 
    WattSensor = 0;           //reset the watts count
    SREG = oldSREG;           // restore interrupts

    TotalWatts = TotalWatts + WattSensorCount; //total watts counter
    lcd.setCursor(8,1);
    lcd.print(WattSensorCount);
}

void interruptHandler() // routine called when external interrupt is triggered
{
  WattSensor += 1;  //Update number of pulses, 1 pulse = 1 watt
}

