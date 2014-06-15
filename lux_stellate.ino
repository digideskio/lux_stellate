/**
 * Patterns for 3D stellated tetrahedrons chandelier.
 * Uses the WS2811B addressable RGB LED (single data pin).
 */
 
#include <PololuLedStrip.h>

// Constants.
const boolean debug_mode = false;

// Light data objects.
#define LED_COUNT_PER_STRIP 665
PololuLedStrip<3> ledStrip1;
PololuLedStrip<5> ledStrip2;
rgb_color meta_strip[LED_COUNT_PER_STRIP];

static unsigned int wait = 50;
static unsigned int segment_length = LED_COUNT_PER_STRIP / 6;

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

void rainbow() {
  byte time = millis() >> 2;
  for(uint16_t i = 0; i < LED_COUNT_PER_STRIP; i++) {
    byte x = time - 8*i;
    meta_strip[i] = Wheel(x);
  }

  ledStrip1.write(meta_strip, LED_COUNT_PER_STRIP);
  ledStrip2.write(meta_strip, LED_COUNT_PER_STRIP);
}

void segment_oscillate() {
  for (int i=0; i<6; i++) {
    light_segment(i, 0, 150);
  }
}

void corner_oscillate() {
  uint32_t color = Wheel(c);
  for (int i=0; i<4; i++) {
    switch (i) {
      case 1:
        light_segment(1, 1, color);
        light_segment(3, 2, color);
        light_segment(4, 1, color);
        break;
      case 2:
        light_segment(1, 2, color);
        light_segment(2, 1, color);
        light_segment(5, 2, color);
        break;
      case 3:
        light_segment(2, 2, color);
        light_segment(3, 1, color);
        light_segment(6, 1, color);
        break;
      case 4:
        light_segment(4, 2, color);
        light_segment(5, 1, color);
        light_segment(6, 2, color);
        break;
    }
  }
}


/**
 * Helper functions...
 */

/**
 * Illumiate a portion of the edge of the tetrahedron.
 */
int light_segment(int index, int half, int c) {
  uint32_t color = Wheel(c);
  int start = segment_length * (index -1)

  for (int i=start; i <= segment_length+start; i++) {
    if (i < (segment_length/2)) {
       // First half.
      if (half == 0 || half == 1) {
        meta_strip[i] = color;
      }
    }
    else {
      // Second half.
      if (half == 0 || half == 2) {
        meta_strip[i] = color;
      }
    }
  }

  ledStrip1.write(meta_strip, LED_COUNT_PER_STRIP);
  ledStrip2.write(meta_strip, LED_COUNT_PER_STRIP);
}

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

