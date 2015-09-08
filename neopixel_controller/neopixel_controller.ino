#include <Adafruit_NeoPixel.h>

#define PIN 6
#define stripLength 16
#define numPixels 2
#define numTypes 6
#define numPatterns 2
#define FALSE 0
#define TRUE 1

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
 #define h_arc 0x8080FF
 #define h_fire 0xFF4000
 #define h_yellow 0xFFFF00
 #define h_magenta 0xFF00FF
 #define h_cyan 0x00FFFF
 #define h_white 0xFFFFFF
 #define h_black 0x000000
 #define h_fluorescent 0xc0c0FF
 #define h_incandescent 0xFFFFA0
 
 // variable light source patterns
 #define l_off 0
 #define l_on 1
 #define l_slowblink 2
 #define l_fastblink 3
 #define l_irregularblink 4
 #define l_traffic 5
 
 
 #define p_tl    "000000000010000011000111100100011111111111111111111111110000000000000000"
 #define p_norm  "000000000000000000000000000000011111111111111111111111110000000000000000"
  
 char* pat[2] = {p_norm, p_tl};
 int patlen[2];
 
 struct PixelData {
   byte     Type;
   boolean  State;
   int      PatPos;
   byte     Brightness;
 };
  
 
 
 // light source states
 #define s_off 0
 #define s_starting 1
 #define s_on 2
 #define s_stopping 3

 
 PixelData pixel[stripLength];
 
 

    
void setup() {
   Serial.begin(115200);

   // initialize pixels 
   strip.begin();
   
   InitPixel(0,0);
   InitPixel(1,1);
   InitPixel(2,2);
   
}

void loop() {

  UpdatePixels(1000);

  strip.show();

 

}

void InitPixel(int px, byte pt) {
  pixel[px].Type = pt;
  pixel[px].State = FALSE;
  pixel[px].PatPos = 0;
  pixel[px].Brightness = 0;
}     

void UpdatePixel(int px) {
  if (px==0) {
    strip.setPixelColor(px, h_red);
  }
  if (px==1) {
    strip.setPixelColor(px, random(2000000000));
  }
  if (px==2) {
    strip.setPixelColor(px, h_blue);
  }
  
}
  

void UpdatePixels(unsigned long TimeSlice) {
  int i;  
  unsigned long StartTime, ElapsedTime;
  
  Serial.println("UpdateStrip");
  
  StartTime = millis();
  
  for (i=0; i<=numPixels; i++)
  {
    UpdatePixel(i);
  }
  
  ElapsedTime = millis() - StartTime;
  
  if (ElapsedTime <= TimeSlice) {
    delay(TimeSlice - ElapsedTime);
  }


}  

