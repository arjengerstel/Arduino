#include <Ethernet.h>
#include <SPI.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Time.h>
#include <Wire.h>
#include <String.h>

#define INTERRUPT_INPUT 2

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
EthernetClient client;
// String ip = "192.168.0.177";
const int port = 81;

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 60000; // READING INTERVAL

String start_interval = "";	
String end_interval = "";	
long duration;
long prev_duration;
volatile int pulse_count = 0;
String FormattedDate = "";


void setup() { 
        // Set up interrupt handler
        pinMode(INTERRUPT_INPUT, INPUT);
        digitalWrite(INTERRUPT_INPUT, HIGH);
        attachInterrupt(INTERRUPT_INPUT - 2, interrupt_handler, FALLING);

        Serial.begin(115200);

        // set up clock
        setSyncProvider(RTC.get);   // the function to get the time from the RTC
        if(timeStatus() != timeSet) 
            Serial.println(F("Unable to sync with the RTC"));
        else
            Serial.println(F("RTC has set the system time"));  
  
        // set up TCP/IP network
	if (Ethernet.begin(mac) == 0) {
		Serial.println("Failed to configure Ethernet using DHCP"); 
	}
        Serial.print("IP = ");
        Serial.println(Ethernet.localIP());

        // set up log timing
        formatdate(year(), month(), day(), hour(), minute(), second());
        end_interval = FormattedDate;
        duration = 0;
        prev_duration = 0;
        pulse_count = 0;
}

void loop(){
       
        delay(interval);
        log_pulses_to_db();

}

void log_pulses_to_db()
{
  String data;
  float power_use;
  
  start_interval = end_interval;
  formatdate(year(), month(), day(), hour(), minute(), second());
  end_interval = FormattedDate;
  
  // determine interval duration
  duration = millis() - prev_duration;
  prev_duration = millis();
  
  //for testing only
  //pulse_count = random(2, 30);
  
  // calculate power use
  power_use = (3600000.0 * pulse_count) / (duration);
  Serial.println(power_use);
    
  // create logging URL
  data = "";
  data = data + "?start_interval=" + start_interval;
  data = data + "&end_interval=" + end_interval;
  data = data + "&duration=" + String(duration);
  data = data + "&power_use=" + String(power_use);
  data = data + "&pulse_count=" + pulse_count;
  
  pulse_count = 0;
  
  Serial.println(data);
  
  if (client.connect("192.168.0.2",80)) { 

                client.print("POST /plog/add.php");
                client.print(data);
                client.println(" HTTP/1.1"); 
		client.println("Host: kelud.local"); // SERVER ADDRESS HERE TOO
                client.println();
	} 

	if (client.connected()) { 
		client.stop();	// DISCONNECT FROM THE SERVER
	}

  
}
  

void formatdate(int year, int month, int day, int hour, int minute, int second)
{
  char strOut[3]; 
  formatTimeDigits(strOut, month);
  FormattedDate = String(year) + "-" + strOut + "-";
  formatTimeDigits(strOut, day);
  FormattedDate = FormattedDate + strOut + "\%20";
  formatTimeDigits(strOut, hour);
  FormattedDate = FormattedDate + strOut + ":";
  formatTimeDigits(strOut, minute);
  FormattedDate = FormattedDate + strOut + ":";
  formatTimeDigits(strOut, second);
  FormattedDate = FormattedDate + strOut;
 }

void formatTimeDigits(char strOut[3], int num)
{
  strOut[0] = '0' + (num / 10);
  strOut[1] = '0' + (num % 10);
  strOut[2] = '\0';
}

void interrupt_handler()
{
    pulse_count = pulse_count + 1;
    tone(9,440,4);
}


