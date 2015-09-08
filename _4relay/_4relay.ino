int relay1Pin = 2;
int relay2Pin = 3;
int relay3Pin = 4;
int relay4Pin = 5;

int delayTime = 1000;
  

void setup() {
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(relay4Pin, OUTPUT);

}

void loop() {
  digitalWrite(relay1Pin, HIGH);
  delay(delayTime);
  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay2Pin, HIGH);
  delay(delayTime);
  digitalWrite(relay2Pin, LOW);
  digitalWrite(relay3Pin, HIGH);
  delay(delayTime);
  digitalWrite(relay3Pin, LOW);
  digitalWrite(relay4Pin, HIGH);  
  delay(delayTime);
  digitalWrite(relay4Pin, LOW);



  // put your main code here, to run repeatedly:

}
