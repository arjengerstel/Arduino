//***********************************************************************************************
//DECLARATIONS

int BLUE = 6;                   
int GREEN = 5; 
int RED = 3; 
int brightness = 0;
int DELAY = 5;


//***********************************************************************************************
//SETUP

void setup() {

//pinMode(BLUE, OUTPUT);           

}

//***********************************************************************************************
//MAIN

void loop() {
  
   for (brightness = 0; brightness < 255; brightness ++) {
      analogWrite(RED, brightness);
      delay(DELAY);
  }
  for (brightness = 255; brightness > 0; brightness --) {
      analogWrite(RED, brightness);
      delay(DELAY);
  }
  analogWrite(RED, 0);
  //----
  for (brightness = 0; brightness < 255; brightness ++) {
      analogWrite(GREEN, brightness);
      delay(DELAY);
  }
  for (brightness = 255; brightness > 0; brightness --) {
      analogWrite(GREEN, brightness);
      delay(DELAY);
  }
  analogWrite(GREEN, 0);
  //----
   for (brightness = 0; brightness < 255; brightness ++) {
      analogWrite(BLUE, brightness);
      delay(DELAY);
  }
  for (brightness = 255; brightness > 0; brightness --) {
      analogWrite(BLUE, brightness);
      delay(DELAY);
  }
  analogWrite(BLUE, 0);
  //----
    for (brightness = 0; brightness < 255; brightness ++) {
      analogWrite(GREEN, brightness);
      analogWrite(RED, brightness);
      analogWrite(BLUE, brightness);
      delay(DELAY);
  }
  for (brightness = 255; brightness > 0; brightness --) {
      analogWrite(GREEN, brightness);
      analogWrite(RED, brightness);
      analogWrite(BLUE, brightness);
      delay(DELAY);
  }
  for (brightness = 10; brightness > 0; brightness --) {
  analogWrite(GREEN, 0);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  delay(50);
  analogWrite(GREEN, 255);
  analogWrite(RED, 255);
  analogWrite(BLUE, 255);
  delay(50);
  }
  
  for (brightness = 10; brightness > 0; brightness --) {
  analogWrite(GREEN, 0);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  delay(50);
  analogWrite(GREEN, 0);
  analogWrite(RED, 255);
  analogWrite(BLUE, 0);
  delay(50);
  }
  for (brightness = 10; brightness > 0; brightness --) {
  analogWrite(GREEN, 0);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  delay(50);
  analogWrite(GREEN, 0);
  analogWrite(RED, 0);
  analogWrite(BLUE, 255);
  delay(50);
  }
  for (brightness = 10; brightness > 0; brightness --) {
  analogWrite(GREEN, 0);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  delay(50);
  analogWrite(GREEN, 255);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  delay(50);
  }
  
  analogWrite(GREEN, 0);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
}
//***********************************************************************************************
