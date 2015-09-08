/*
 * TimeRTC.pde
 * Example code illustrating Time library with Real Time Clock.
 * This example is identical to the example provided with the Time Library,
 * only the #include statement has been changed to include the DS3232RTC library.
 */

#include <SPI.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TSL250_PIN  A0
#define INTERRUPT_INPUT 2


// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

volatile unsigned long pulse_count = 0;

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
char s[4];


void setup(void)
{
    // For noise suppression, enable pullup on interrupt pin
    pinMode(INTERRUPT_INPUT, INPUT);
    digitalWrite(INTERRUPT_INPUT, HIGH);
    attachInterrupt(INTERRUPT_INPUT - 2, interrupt_handler, FALLING);
    
  
    Serial.begin(9600);
    setSyncProvider(RTC.get);   // the function to get the time from the RTC
    if(timeStatus() != timeSet) 
        Serial.println("Unable to sync with the RTC");
    else
        Serial.println("RTC has set the system time");  
    
  
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();
  
    // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

}

void loop(void)
{
    digitalClockDisplay();  
    delay(1000);
}

void digitalClockDisplay(void)
{
    // digital clock display of the time
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print(hour());
    formatDigits(minute());
    display.print((char*)s);
    formatDigits(second());
    display.println((char*)s);
//    display.println(analogRead(TSL250_PIN));
    display.println(pulse_count);
    display.display();
    
    Serial.print(' ');
    Serial.print(day());
    Serial.print(' ');
    Serial.print(month());
    Serial.print(' ');
    Serial.print(year()); 
    Serial.println(); 
    Serial.println(pulse_count);
}

void interrupt_handler()
{
    pulse_count = pulse_count + 1;
}

void formatDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    s[0] = ':';
    s[1] = (digits / 10) + 0x30;
    s[2] = (digits % 10) + 0x30;
    s[3] = '\0';
}
