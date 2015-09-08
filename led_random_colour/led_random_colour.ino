

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
  int i;
//  analogWrite(ledRedPin, random(256));
//  analogWrite(ledGreenPin, random(256));
//  analogWrite(ledBluePin, random(256));
  for(i=0;i<50;i++) {
    analogWrite(ledRedPin, i);
    delay(10);
  }
  analogWrite(ledRedPin, 0);
  
  for(i=0;i<50;i++) {
    analogWrite(ledGreenPin, i);
    delay(10);
  }
  analogWrite(ledGreenPin, 0);
  
  for(i=0;i<50;i++) {
    analogWrite(ledBluePin, i);
    delay(10);
  }
  analogWrite(ledBluePin, 0);
  
  
}


