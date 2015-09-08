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
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
#include <Ethernet.h>


#define TSL250_PIN  A0
#define INTERRUPT_INPUT 2

volatile unsigned long pulse_count = 0;


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);



void setup(void)
{
    // For noise suppression, enable pullup on interrupt pin
    pinMode(INTERRUPT_INPUT, INPUT);
    digitalWrite(INTERRUPT_INPUT, HIGH);
    attachInterrupt(INTERRUPT_INPUT - 2, interrupt_handler, FALLING);
    
  
    Serial.begin(9600);
    setSyncProvider(RTC.get);   // the function to get the time from the RTC
    if(timeStatus() != timeSet) 
        Serial.println(F("Unable to sync with the RTC"));
    else
        Serial.println(F("RTC has set the system time"));  
    
  
  
  
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print(F("server is at "));
  Serial.println(Ethernet.localIP());


}

void loop(void) {

    
      // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println(F("HTTP/1.1 200 OK"));
          client.println(F("Content-Type: text/html"));
          client.println(F("Connection: close"));  // the connection will be closed after completion of the response
          client.println(F("Refresh: 5"));  // refresh the page automatically every 5 sec
          client.println();
          client.println(F("<!DOCTYPE HTML>"));
          client.println(F("<html>"));
          // output the value of each analog input pin
          client.println(F("Pulse count = "));
          client.println(pulse_count);
          client.println(F("</html>"));
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println(F("client disconnected"));
  }
}

void digitalClockDisplay(void)
{
    // digital clock display of the time

    
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
    tone(9,440,4);
}


