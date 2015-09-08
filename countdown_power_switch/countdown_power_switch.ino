#define LED_PIN 0
#define POWER_RELAY 1
#define COUNTDOWN_RESET 2
#define OFF_BUTTON 3

#define COUNTDOWN_TIME 10
#define WARNING_BLINK 3

#define LOOP_DELAY 500

#define FALSE 0
#define TRUE 1

unsigned long EndTime; 
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
  digitalWrite(POWER_RELAY, HIGH);   // set high to cut primary power to circuit

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

  
