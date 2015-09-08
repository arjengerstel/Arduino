#include <OnewireKeypad.h>

#define Rows 4
#define Cols 4
#define Pin A0
#define Col_Res 4700
#define Row_Res 1000

char KEYS[]= {
  '0','1','2','3',
  '4','5','6','7',
  '8','9','A','B',
  'C','D','E','F'
};

OnewireKeypad <Print, 16> KeyPad(Serial, KEYS, Rows, Cols, Pin, Col_Res, Row_Res );

void setup()
{

  Serial.begin(9600);
}

void loop(){
  char key = KeyPad.Getkey();

  if (key != NO_KEY){
    Serial.println(key);
  }
}
