




#include <Adafruit_NeoPixel.h>

#define PIN 6
#define stripLength 16
#define numPixels 6
#define numTypes 6
#define numPatterns 2
#define FALSE 0
#define TRUE 1

#define T_GRB 0
#define T_RGB -1

#define T_OFF                   0   // Always off
#define T_FIRE                  1   // Fire, flames
#define T_WELDING               2   // Industrial welding flashes
#define T_INCANDESCENT          3   // Classic incandescent light
#define T_FLUORECSCENT          4   // Fluorescent tube lighting
#define T_TV                    5   // Flickering TV set in living room
#define T_GAS                   6   // Gas lamp
#define T_SODIUM                7   // Low pressure Sodium (yellow street light)
#define T_TRAFFIC_3             8   // 3 state traffic light (NL, B)
#define T_TRAFFIC_4             9   // 4-state traffic light (UK, D)
#define T_TRAFFIC_NIGHT         10  // blinking orange/yellow 
#define T_RUNNING               11  // 3 red running lights
#define T_LEVEL_CROSSING_NL_AKI 12  // Unguarded level crossing (NL)
#define T_GREEN                 201 // Steady Green
#define T_RED                   202 // Steady Red
#define T_BLUE                  203 // Steady Blue


#define P_ON 1
#define P_OFF 0

#define P_RED 0
#define P_YELLOW 1
#define P_GREEN 2
#define P_RED_YELLOW 3
#define P_LEFT 0
#define P_RIGHT 1

#define M_OFF 0        // not operating (off)
#define M_ON 1         // operating (on)

#define M_SAFE 2       // show safe lighting (level crossings and traffic lights)
#define M_UNSAFE 3     // unsafe 


#define T_RED_LENGTH 10000
#define T_YELLOW_LENGTH 2000
#define T_GREEN_LENGTH 8000
#define T_RED_YELLOW_LENGTH 2000

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(stripLength, PIN, NEO_GRB + NEO_KHZ800);


 
 // predefined colors
 #define h_defaultcolor 0x000000
 #define h_red 0xFF0000
 #define h_green 0x00FF00
 #define h_blue 0x0000FF
 #define h_yellow 0xFFFF00
 #define h_orange 0xFF8000
 #define h_arc 0x8080FF
 #define h_fire 0xFF4000
 #define h_yellow 0xFFFF00
 #define h_magenta 0xFF00FF
 #define h_cyan 0x00FFFF
 #define h_white 0xFFFFFF
 #define h_black 0x000000
 #define h_fluorescent 0xc0c0FF
 #define h_incandescent 0xFF8040
 #define h_tl_red 0x00FF00
 #define h_tl_yellow 0xFF0000
 #define h_tl_green 0x0000FF
 #define h_aki_safe 0x1f0000
 #define h_aki_unsafe1 0x0000FF
 #define h_aki_unsafe2 0x00FF00
 
 
 
 struct PixelData {
   boolean        RGB_Type;
   byte           Type;
   byte           On;
   byte           Mode;
   byte           State;
   unsigned long  EndTime;
   int            PatPos;
   byte           Brightness;
 };
  

 
 PixelData pixel[stripLength];
 
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
 

    
void setup() {
   Serial.begin(115200);

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

   // initialize pixels 
   strip.begin();
   
/*   
   InitPixel(0,T_GRB, 0);
   InitPixel(1,T_RGB, 1);
   InitPixel(2,T_RGB, 2);
   InitPixel(3,T_RGB, 2);
   InitPixel(4,T_RGB, 2);
*/

   for (int i=0; i<numPixels; i++)
   {
     InitPixel(i,T_GRB, 2);
   }
   
   InitPixel(0, T_GRB, T_WELDING);
   InitPixel(1, T_GRB, T_FIRE);
   InitPixel(2, T_GRB, T_TRAFFIC_3);
   InitPixel(3, T_GRB, T_LEVEL_CROSSING_NL_AKI);
   InitPixel(4, T_GRB, T_OFF);
   InitPixel(5, T_GRB, T_OFF);
   

   
   //initialize random generator
   randomSeed(analogRead(0));
  
   //  InitPixel(1,1);
 // InitPixel(2,2);
   
}

void loop() {

//  pixel[5].Enabled = TRUE;
//  pixel[9].Enabled = TRUE;
  
  
  
  UpdatePixels(25);

  strip.show();

 // Serial.println("loop");
      if ((!digitalRead(PinSW))) {        // check if pushbutton is pressed
            // VirtualPosition = 0;            // if YES, then reset counter to ZERO
            if (pixel[VirtualPosition].Mode == M_SAFE)
            {
              pixel[VirtualPosition].Mode = M_UNSAFE;
            }
            else
            {  
              pixel[VirtualPosition].Mode = M_SAFE;
            }  
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

void InitPixel(int px, boolean tp, byte pt) {
  pixel[px].RGB_Type = tp;          // Type of LED(s) 
  pixel[px].Type = pt;              // Type of light to be emulated
  pixel[px].On = M_ON;              // switch on pixel
  pixel[px].State = P_OFF;          // current state for intermittent/repeating effects
  pixel[px].Mode = M_SAFE;          // current operationg mode (M_OFF, M_SAFE)
  pixel[px].EndTime = 0;
  pixel[px].PatPos = 0;
  pixel[px].Brightness = 0;
}     

void UpdatePixel(int px) 
{
//  Serial.println("UpdatePixel");
  
  if (pixel[px].On == TRUE)
  {
 //   Serial.println(pixel[px].Type);
    switch (pixel[px].Type) {
      case T_OFF: 
        strip.setPixelColor(px, h_black);
        break;
    
      case T_FIRE: 
        strip.setPixelColor(px, random(0xFF), random(0x40), 0);
        break;
    
      case T_WELDING: 
        update_welding(px);
        break;
      
      case T_TRAFFIC_3:
        UpdateTrafficLight3(px);
        break;
      
      case T_TRAFFIC_4:
        UpdateTrafficLight4(px);
        break;
        
      case T_LEVEL_CROSSING_NL_AKI:
        UpdateAKI(px);
        break;
        
      case T_GREEN:
        strip.setPixelColor(px, h_green);
        break;
        
      case T_RED:
        strip.setPixelColor(px, h_red);
        break;
        
      case T_BLUE:
        strip.setPixelColor(px, h_blue);
        break;
        
      default: 
        strip.setPixelColor(px, h_black);
    }
  }
  else
  {
    strip.setPixelColor(px, h_black);
  }
}
   
void update_welding(int px)
{
  
  if (millis() > pixel[px].EndTime) 
  {
    if (pixel[px].State==P_OFF) 
    {
      pixel[px].EndTime = millis() + random(15000);
      pixel[px].State = P_ON;
     } 
    else
    {
      pixel[px].EndTime = millis() + random(20000);
      pixel[px].State = P_OFF;
      strip.setPixelColor(px, h_black);
    }
  } 
  
  if (pixel[px].State==P_ON)
  {
    if (random(2) == 0L) 
    {
      strip.setPixelColor(px, h_arc);
    }
    else
    {
      strip.setPixelColor(px, h_black);
    }
  }

}  
  
void UpdateTrafficLight3(int px)
{  
  if (pixel[px].Mode == M_SAFE)
  {
    if (millis() > pixel[px].EndTime)
    {
      switch (pixel[px].State) 
      {
      case P_RED:
        pixel[px].EndTime = millis() + T_GREEN_LENGTH;
        pixel[px].State=P_GREEN;
        strip.setPixelColor(px, h_tl_green);
        break;
      case P_GREEN:
        pixel[px].EndTime = millis() + T_YELLOW_LENGTH;
        pixel[px].State=P_YELLOW;
        strip.setPixelColor(px, h_tl_yellow);
        break;
      case P_YELLOW:
        pixel[px].EndTime = millis() + T_RED_LENGTH;
        pixel[px].State=P_RED;
        strip.setPixelColor(px, h_tl_red);
        break;
      default:
        break;
      }
    }
  }  
  else
  {
    if (millis() > pixel[px].EndTime) 
    {
      if (pixel[px].State==P_OFF) 
      {
        pixel[px].EndTime = millis() + 500;
        pixel[px].State = P_YELLOW;
        strip.setPixelColor(px, h_tl_yellow);
      } 
      else
      {
        pixel[px].EndTime = millis() + 500;
        pixel[px].State = P_OFF;
        strip.setPixelColor(px, h_black);
      }
    }
  }
}

void UpdateTrafficLight4(int px)
{
  if (millis() > pixel[px].EndTime)
  {
    switch (pixel[px].State) {
    case P_RED:
      pixel[px].EndTime = millis() + T_RED_YELLOW_LENGTH;
      pixel[px].State=P_RED_YELLOW;
      strip.setPixelColor(px, h_tl_red + h_tl_yellow);
      break;
    case P_RED_YELLOW:
      pixel[px].EndTime = millis() + T_GREEN_LENGTH;
      pixel[px].State=P_GREEN;
      strip.setPixelColor(px, h_tl_green);
      break;
    case P_GREEN:
      pixel[px].EndTime = millis() + T_YELLOW_LENGTH;
      pixel[px].State=P_YELLOW;
     strip.setPixelColor(px, h_tl_yellow);
      break;
    case P_YELLOW:
      pixel[px].EndTime = millis() + T_RED_LENGTH;
      pixel[px].State=P_RED;
      strip.setPixelColor(px, h_tl_red);
      break;
    default:
      break;
    }
  }
}

void UpdateAKI(int px)
{
  if (pixel[px].Mode == M_SAFE)
  {
    if (millis() > pixel[px].EndTime) 
    {
      if (pixel[px].State==P_OFF) 
      {
        pixel[px].EndTime = millis() + 500;
        pixel[px].State = P_ON;
        strip.setPixelColor(px, h_aki_safe);
      } 
      else
      {
        pixel[px].EndTime = millis() + 500;
        pixel[px].State = P_OFF;
        strip.setPixelColor(px, h_black);
      }
    }
  } 
  else
  {
    if (millis() > pixel[px].EndTime) 
    {
      if (pixel[px].State==P_LEFT) 
      {
        pixel[px].EndTime = millis() + 500;
        pixel[px].State = P_RIGHT;
        strip.setPixelColor(px, h_aki_unsafe1);
      } 
      else
      {
        pixel[px].EndTime = millis() + 500;
        pixel[px].State = P_LEFT;
        strip.setPixelColor(px, h_aki_unsafe2);
      }
    }
  } 
  
  
  

}


void UpdatePixels(unsigned long TimeSlice) {
  int i;  
  unsigned long StartTime, ElapsedTime;
   
//  Serial.println("UpdatePixels");
  
  StartTime = millis();
  
  for (i=0; i<numPixels; i++)
  {
    UpdatePixel(i);
  }
  
  ElapsedTime = millis() - StartTime;
  
  if (ElapsedTime <= TimeSlice) {
    delay(TimeSlice - ElapsedTime);
  }


}  

