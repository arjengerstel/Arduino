// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

#include "SD.h"
#include "SPI.h"
#include <Wire.h>
#include "RTClib.h"

// A simple data logger for the Arduino analog pins
#define LOG_INTERVAL  1000 // mills between entries
#define ECHO_TO_SERIAL   1 // echo data to serial port
#define WAIT_TO_START    0 // Wait for serial input in setup()
 
 
// the digital pins that connect to the LEDs
#define redLEDpin 3
#define greenLEDpin 4
 
// The analog pins that connect to the sensors
#define photocellPin 0           // analog 0
#define tempPin 1                // analog 1

RTC_DS1307 RTC;


// for the data logging shield, we use digital pin 10 for the SD cs line
const int chipSelect = 10;
 
// the logging file
File logfile;

void setup () {
    Serial.begin(57600);
    Wire.begin();
    RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // uncomment it & upload to set the time, date and start run the RTC!
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

    // initialize the SD card
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
  // create a new file
  char filename[] = "LOGGER00.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      logfile = SD.open(filename, FILE_WRITE); 
      break;  // leave the loop!
    }
  }
  
  if (! logfile) {
    error("couldnt create file");
  }
  
  Serial.print("Logging to: ");
  Serial.println(filename);

}

void loop () {
    Serial.println("Getting RTC");

    DateTime now = RTC.now();

    Serial.println("Logging to SD");
    
    logfile.print(now.year(), DEC);
    logfile.print('/');
    logfile.print(now.month(), DEC);
    logfile.print('/');
    logfile.print(now.day(), DEC);
    logfile.print(' ');
    logfile.print(now.hour(), DEC);
    logfile.print(':');
    logfile.print(now.minute(), DEC);
    logfile.print(':');
    logfile.print(now.second(), DEC);
    logfile.println();
    
    delay(3000);
}

 
void error(char *str)
{
  Serial.print("error: ");
  Serial.println(str);
  
  // red LED indicates error
  digitalWrite(redLEDpin, HIGH);
  
  while(1);
}
