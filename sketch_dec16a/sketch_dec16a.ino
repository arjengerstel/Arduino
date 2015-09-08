int outs[] = { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46 };



void setup() {
  int i;
  for (i=0; i<16; i++) 
  {
    pinMode(outs[i],OUTPUT);
  }

  // put your setup code here, to run once:

}

void loop() {
  int i;
    for (i=0; i<16; i++) 
  {
    digitalWrite(outs[i],HIGH);
  }

    delay(2000);

    for (i=0; i<16; i++) 
  {
    digitalWrite(outs[i],LOW);
  }

      delay(2000);

  
  // put your main code here, to run repeatedly:

}
