// test

int ledSystemPin = 13;
int ledRedPin = 3;
int ledGreenPin = 5;
int ledBluePin = 6;

void setup(){
  pinMode(ledSystemPin, OUTPUT); 
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);  
}

void loop(){
  digitalWrite(ledSystemPin, HIGH);
  delay(1000);
  analogWrite(ledRedPin, 255);
  delay(1000);
  analogWrite(ledGreenPin, 255);
  delay(1000);
  analogWrite(ledBluePin, 255);
  delay(1000);

  analogWrite(ledRedPin, 0);
  analogWrite(ledGreenPin, 0);
  analogWrite(ledBluePin, 0);
  
  digitalWrite(ledSystemPin, LOW);
  delay(1000);
}


