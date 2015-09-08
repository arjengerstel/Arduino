/*

 Arduino TFT Bitmap Logo example
 
 This example reads an image file from a micro-SD card
 and draws it on the screen, at random locations.
 
 In this sketch, the Arduino logo is read from a micro-SD card.
 There is a .bmp file included with this sketch. 
 - open the sketch folder (Ctrl-K or Cmd-K)
 - copy the "arduino.bmp" file to a micro-SD
 - put the SD into the SD slot of the Arduino TFT module.
 
 This example code is in the public domain.
 
 Created 19 April 2013 by Enrico Gueli
 
 http://arduino.cc/en/Tutorial/TFTBitmapLogo
 
 */
 
// include the necessary libraries
#include <SPI.h>
#include <SD.h>
#include <TFT.h>  // Arduino LCD library

// pin definition for the Uno
#define sd_cs  4
#define lcd_cs 10
#define dc     9
#define rst    8  
#define bl     6

// pin definition for the Leonardo
//#define sd_cs  8
//#define lcd_cs 7
//#define dc     0
//#define rst    1  

TFT TFTscreen = TFT(lcd_cs, dc, rst);

// this variable represents the image to be drawn on screen
PImage logo;


void setup() {
  // set backlight to MAX
  pinMode(bl, OUTPUT);
  analogWrite(bl,0);
  // initialize the GLCD and show a message
  // asking the user to open the serial line
  TFTscreen.begin();
  TFTscreen.background(0, 0,0);

  TFTscreen.stroke(0, 0, 255);
  TFTscreen.println();
  TFTscreen.println("Arduino TFT Bitmap Example");
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.println("Open serial monitor");
  TFTscreen.stroke(255, 0, 0);
  TFTscreen.println("to run the sketch");
   TFTscreen.stroke(0, 255, 0);
  TFTscreen.println("to run the sketch");

  // initialize the serial port: it will be used to 
  // print some diagnostic info  
  //Serial.begin(9600);
  //while (!Serial) {
    // wait for serial line to be ready
  //}

  // clear the GLCD screen before starting
  
  
}

void loop() {
 
  // wait a little bit before drawing again
  delay(1500);
}

