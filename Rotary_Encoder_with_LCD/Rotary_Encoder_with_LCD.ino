

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);


// -----------------------------------------------------------------------------
// constants

const int                                 PinCLK   = 2;     // Used for generating interrupts using CLK signal
const int                                 PinDT    = 3;     // Used for reading DT signal
const int                                 PinSW    = 4;     // Used for the push button switch

// -----------------------------------------------------------------------------
// global vars

volatile int                             VirtualPosition    = 0;
int PreviousVirtualPosition = 0;
int lastCount = 0;

// -----------------------------------------------------------------------------
// forward decls

void isr();
void loop();
void setup();

// -----------------------------------------------------------------------------
// Interrupt service routine is executed when a HIGH to LOW transition is detected on CLK

void isr ()  {
    if (!digitalRead(PinDT))
        VirtualPosition = VirtualPosition - 1;
    else
        VirtualPosition = VirtualPosition + 1;
    } // isr

// -----------------------------------------------------------------------------


void setup() {
    pinMode(PinCLK,INPUT);
    pinMode(PinDT, INPUT);
    pinMode(PinSW, INPUT_PULLUP);

    attachInterrupt(0, isr, FALLING);   // interrupt 0 is always connected to pin 2 on Arduino UNO

  
  // set up the number of columns and rows on the LCD
  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.print("Rotary Encoder");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("Value: ");
}

void loop() {
     
      if ((!digitalRead(PinSW))) {        // check if pushbutton is pressed
            VirtualPosition = 0;            // if YES, then reset counter to ZERO
            while (!digitalRead(PinSW)) {}  // wait til switch is released
           delay(10);                      // debounce
      }

      if (PreviousVirtualPosition != VirtualPosition)
      {
        lcd.setCursor(8, 1);
        lcd.print("        ");
  
        lcd.setCursor(8, 1);
        lcd.print(VirtualPosition);
      }

      PreviousVirtualPosition = VirtualPosition;

}
