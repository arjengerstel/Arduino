/*
  Night Light driver
  
  My kids like to have a light on when going to sleep, but they always
  forget to turn it of. Of course this wastes energy and may disturb
  their sleep cycle.
  This little circuit and program takes care of this problem.
  
  This program runs on an ATTINY85 and controls a circuit that turns on
  a 12V Power LED on pressing a pushbutton and turns it off after a preset
  time (ON_TIME). Pressing the button again while the Power LED is on turns it 
  off immediately.
  Another (Low power) LED is turned on when the Power LED is off and vice versa.

  The entire circuit is powered by a 12V adapter, so no mains voltage is present in the circuit. 
  The 5V to power the logic is obtained by using a voltage regulator. The small LED is 
  driven directly from the ATTINY, the power LED is controlled by an opto coupler which 
  in turn drives an IRF520 MOSFET (a hunge overkill for this job, I know).

  Designed and written by Arjen Gerstel, november 2015
  
 */

#define MAIN_LIGHT 0          // output port driving the main LED
#define INDICATOR_LIGHT 2     // output port for the indicator LED

#define SWITCH_PIN 4          // input port for the pushbutton switch
#define DELAY 100

#define LIGHT_OFF 0           // system state value
#define LIGHT_ON 1            // system state value
#define ON_TIME 1800000         // duration the main LED stays on (milliseconds)
#define BOUNCE 500            // delay after change of state for debouncing

int status;          // status of the system
unsigned long endtime = 0;    // end time of current burn


void setup() 
// Init ports and turn off main LED
{
  pinMode(MAIN_LIGHT, OUTPUT);
  pinMode(INDICATOR_LIGHT, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  lights_off();
}

void loop() 
{
  // button pressed? Change state!
  if (digitalRead(SWITCH_PIN) != 0) 
  {
    if (status == LIGHT_ON)
    {
      lights_off();
    }
    else
    {
      lights_on();
    }
  }

  // main LED on and time elapsed?
  if ((status == LIGHT_ON) && (millis() > endtime))
  {
    lights_off();
  }
   
  // wait 
  delay(DELAY);              
  }

void lights_off()
{
  digitalWrite(MAIN_LIGHT, HIGH);
  digitalWrite(INDICATOR_LIGHT, HIGH);
  status = LIGHT_OFF;
  delay(BOUNCE);
}

void lights_on()
{
  digitalWrite(MAIN_LIGHT, LOW);
  digitalWrite(INDICATOR_LIGHT, LOW);
  endtime = millis() + ON_TIME;
  status = LIGHT_ON;
  delay(BOUNCE);
}

