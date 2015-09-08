/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int pin_w1a = 2;
int pin_w1b = 3;
int pin_w2a = 4;
int pin_w2b = 5;
int pin_13 = 13;

int waittime = 2000;
int pulse_length = 200;

void pulse(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(pulse_length);
  digitalWrite(pin, LOW);
}

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  // pinMode(pin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  pulse(pin_w1a);
  pulse(pin_w1b);
  pulse(pin_w2a);
  delay(waittime);
  pulse(pin_w2b);
  delay(waittime);



/*
  pulse(pin_w1b);
  delay(waittime);

  pulse(pin_w2a);
  delay(waittime);

  pulse(pin_w2b);
  delay(waittime);
*/ 
 // pulse(pin_13);
 // delay(waittime);
  
 }
