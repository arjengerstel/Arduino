int PinL1 = 1;         // analoge pin voor LED 1 

// test comment

void setup()
{

  Serial.begin(9600);          //  setup serial

  int lo, hi, i, val, numsamples;
  
  float total=0;
  
  lo=9999;
  hi=0;
  numsamples=10000;
  
  delay(5000);
  
  for(i=0;i<numsamples;i++) {
      val = analogRead(PinL1);
      Serial.println(val);
      if (val>hi) {
        hi = val;
      }
      if (val<lo) {
        lo = val;
      }
      total+=val;
  }
  
  Serial.print("lo=");
  Serial.print(lo);
  Serial.print("  hi=");
  Serial.print(hi);
  Serial.print("  avg=");
  Serial.println(total/numsamples);
}



void loop()
{
  
  
}
