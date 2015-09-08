#include <BitBool.h>
#include <OnewireKeypad.h>

#include <Keypad.h>

const byte RELAYS = 4;
int RelayState[RELAYS] = {0, 0, 0, 0};
int RelayPin[RELAYS] = {13, 12, 11, 10};

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void toggle_relay(int r)
{
  Serial.println(r);
  if (RelayState[r] == 0)
  {  
    RelayState[r] = 1;
  }
  else
  {
    RelayState[r] = 0;
  }
  
  int i;
  for (i=0; i<RELAYS; i++) 
  {
    Serial.println(RelayState[i]);
    if (RelayState[i] == 0) 
    {
      digitalWrite(RelayPin[i], LOW);
    }
    else
    {
      digitalWrite(RelayPin[i], HIGH);
    }
  }
}
    
    

void setup()
{
  int i;
  for (i=0; i<RELAYS; i++)
  {
    pinMode(RelayPin[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    toggle_relay(key - '0');
    Serial.println(key);
  }
}
