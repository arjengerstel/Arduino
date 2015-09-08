/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
 
 #define RELAY_1 2
 #define RELAY_2 3

#define DELAY 500

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, LOW);
  
}

// the loop function runs over and over again forever
void loop() {
//  digitalWrite(RELAY_2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(DELAY);              // wait for a second
//  digitalWrite(RELAY_2, LOW);    // turn the LED off by making the voltage LOW
  delay(DELAY);           // wait for a second
}
