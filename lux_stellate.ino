/**
 * Patterns for 3D stellated tetrahedrons chandelier.
 * Uses the WS2811B addressable RGB LED (single data pin).
 */
 
#include <PololuLedStrip.h>

// Constants.
const boolean debug_mode = false;

// Light data objects.
#define LED_COUNT_PER_STRIP 60
PololuLedStrip<3> ledStrip1;
PololuLedStrip<5> ledStrip2;
rgb_color meta_strip[665];

static unsigned int wait = 50;

/**
 * Required functions...
 */

// Basic setup.
void setup() {
  //randomSeed(analogRead(0));

  if(debug_mode) {
    Serial.begin(115200);
    Serial.println("Ready to send data.");
  }
}

// Master looper.
void loop() {
  rainbow();
  delay(wait);
}


/**
 * Light patterns...
 */

int rainbow() {
  byte time = millis() >> 2;
  for(uint16_t i = 0; i < LED_COUNT_PER_STRIP; i++) {
    byte x = time - 8*i;
    meta_strip[i] = Wheel(x);
  }

  ledStrip1.write(meta_strip, LED_COUNT_PER_STRIP);
  ledStrip2.write(meta_strip, LED_COUNT_PER_STRIP);
}


/**
 * Helper functions...
 */

/**
 * Create a 24 bit color value from R,G,B.
 */
uint32_t Color(byte r, byte g, byte b) {
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

/**
 * Input a value 0 to 255 to get a color value.
 * The colours are a transition r - g -b - back to r
 */
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

