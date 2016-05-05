void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  analogWrite(3, 0x90);
}

void loop() {
  // put your main code here, to run repeatedly:



/*
for(int i=0; i<0x100; i++) {
    analogWrite(3, i);
    delay(10);
  }

delay(1000);

for(int i=0xff; i>0; i--) {
    analogWrite(3, i);
    delay(10);
  }

delay(1000);
//    analogWrite(3, 0x80);
 //   delay(500);

*/

}
