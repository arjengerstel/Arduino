int testPin = 7;
int period = 0;

void setup(){
    pinMode(testPin, OUTPUT);
}

void loop(){
  digitalWrite(testPin,HIGH);
  delay(period);
  digitalWrite(testPin,LOW);
  delay(period);
}
