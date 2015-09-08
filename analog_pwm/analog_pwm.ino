int testPin = 3;
int testPinB = 5;
int period = 0;
int pwmvalue = 100;
int speed = 25;

void setup(){
    pinMode(testPin, OUTPUT);
}

void loop(){
  int i;
  for(i=0;i<256;i++){    
    analogWrite(testPin, i);
    analogWrite(testPinB, 255-i);
    delay(speed);  
}
  
}
