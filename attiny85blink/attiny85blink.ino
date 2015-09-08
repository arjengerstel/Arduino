#define LED1 0
#define LED2 1
#define IN1  2
#define IN2  3

void setup()
{
   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
   pinMode(IN1, INPUT);
   pinMode(IN2, INPUT);
}
void loop()
{
     if (digitalRead(IN1) == HIGH) {
        digitalWrite(LED1, HIGH); // set the LED on
     } else {
        digitalWrite(LED1, LOW);
     }
     
     if (digitalRead(IN2) == HIGH) {
        digitalWrite(LED2, HIGH); // set the LED on
     } else {
        digitalWrite(LED2, LOW);
     }
     
     
     delay(1000); // wait for a second
 
}
