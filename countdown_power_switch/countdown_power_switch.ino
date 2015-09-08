/*
 * Smart power countdown timer   (c) 2015 Arjen Gerstel
 * 
 * Code for a device that can temporarily switch on power to any mains-powered device.
 * Features:
 * One-button press to activate
 * Button to reset the timer
 * Button for immediate shutdown
 * LED that blinks when timer has nearly expired
 * Zero power use when switched off
 * 
 */



// Pin number of control LED
#define LED_PIN 0

// Pin number of relay that cuts power when done
#define POWER_RELAY 1

// Pin number of Countdown Reset switch
#define COUNTDOWN_RESET 2

// Pin number of Off switch
#define OFF_BUTTON 3

// Duration of power in seconds
#define COUNTDOWN_TIME 10

// Length of warning blink before cutting power
#define WARNING_BLINK 3

// Interval for loop
#define LOOP_DELAY 500

#define FALSE 0
#define TRUE 1

// Global variable for Time to cut power 
unsigned long EndTime; 

// Global variable for Time to start blinking (before cutting power)
unsigned long WarningTime; 
boolean LedOn = FALSE; 

void setup() {

// set up I/O ports
  pinMode(LED_PIN, OUTPUT);
  pinMode(POWER_RELAY, OUTPUT);
  pinMode(COUNTDOWN_RESET, INPUT);
  pinMode(OFF_BUTTON, INPUT);

// initialize ports
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(POWER_RELAY, LOW);   // set high to cut primary power to circuit

  ResetTimers();
}

void loop() 
{
  if (digitalRead(COUNTDOWN_RESET) == HIGH)
  {
      ResetTimers();
      digitalWrite(LED_PIN, HIGH);
      LedOn = TRUE;
  }
  
  if (digitalRead(OFF_BUTTON) == HIGH)
  {
      CutPower();
  }
  
  if (millis() > EndTime)
  {
      // timer has expired: cut power
      CutPower();
  }
  
  if (millis() > WarningTime)
  {
      // timer almost expired: blink led
      if (LedOn == FALSE) 
      {
          digitalWrite(LED_PIN, HIGH);
          LedOn = TRUE;
      }
      else
      {
          digitalWrite(LED_PIN, LOW);
          LedOn = FALSE;
      }

  }
  
  delay(LOOP_DELAY);
}

void CutPower()
{
    digitalWrite(POWER_RELAY, HIGH);   // cut primary power to circuit
    digitalWrite(LED_PIN, LOW);
    
    // disable interrupts and enter endless loop
    // cli();
    while( true );
    
}

void ResetTimers()
{
    EndTime = millis() + (COUNTDOWN_TIME * 1000);
    WarningTime = EndTime - (WARNING_BLINK * 1000);
}

  
