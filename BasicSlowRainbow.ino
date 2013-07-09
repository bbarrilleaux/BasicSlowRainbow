
// LED Code for basic slow cycling rainbow in Neopixel WS2811 LED strip, with variable brightness, speed, and amount of rainbow shown at one time.
/*************************************************************************************/

#include "FastSPI_LED2.h"

#define NUM_LEDS 120 //length of LED strip

struct CRGB leds[NUM_LEDS];

// "Mood light" color cycling
int colorval = 0; // Variable to hold the changing "mood light" strip color.
const int mooddelay = 1; // Increase this to slow down the color cycling.
int moodcounter = 0; // just a counter...

void setup() {
    	LEDS.setBrightness(75); // set total brightness, from 1 to 255.
   LEDS.addLeds<WS2811, 5>(leds, NUM_LEDS); // set the data pin.
}


void loop() {
   rainbow(leds, colorval);
   delay(10); 
  LEDS.show();   // write all the pixels out 

  //Cycle through colorval with variable delay.
  if(moodcounter < mooddelay) moodcounter++;
  else 
    {
      colorval++;
      moodcounter = 0;
    }
  if(colorval>384) colorval=0;
}

 //Fill the strip with rainbow starting from color c
void rainbow(struct CRGB *leds, uint32_t c) {
  uint16_t i;
  //rainbowquant controls the "amount" of rainbow displayed at one time. higher number = more different colors at once.
  int rainbowquant = 200;
    for (i=0; i < NUM_LEDS; i++) {
      leds[i] = RGBWheel(((i * rainbowquant / NUM_LEDS) + c) % 384); 
    }
}

/* RGB Color Wheel Helper function */
//Input a value 0 to 384 to get a color value. 
CRGB RGBWheel(uint16_t WheelPos) {
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = (127 - WheelPos % 128); // red down
      g = (WheelPos % 128);       // green up
      b = 0;                    // blue off
      break;
    case 1:
      g = (127 - WheelPos % 128); // green down
      b = (WheelPos % 128);       // blue up
      r = 0;                    // red off
      break;
    case 2:
      b = (127 - WheelPos % 128); // blue down
      r = (WheelPos % 128);       // red up
      g = 0;                    // green off
      break;
  }
  return(CRGB(g, r, b));    
}

