/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int r_pina = 9;
int r_pinb = 10;
int r_pinc = 11;
int r_pind = 12;


// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(r_pina, INPUT);
  pinMode(r_pinb, INPUT);
  pinMode(r_pinc, INPUT);
  pinMode(r_pind, INPUT);
  
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.print(digitalRead(r_pina));
  Serial.print(digitalRead(r_pinb));
  Serial.print(digitalRead(r_pinc));
  Serial.println(digitalRead(r_pind));
//  delay(1000);               // wait for a second
}
