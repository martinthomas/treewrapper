#include <Adafruit_NeoPixel.h>

#include "helper.h"

//#define PIN 6 // Circuit Playground
//#define PIN 5 // Node MCU D1
#define PIN SDA // Adafruit Feather 32u4
//#define PIN 2 // Adafruit Feather RP2040

#define PXCNT 300
#define DELAY 5 // ms
#define DELAYx15 DELAY*30 // ms
#define BRIGHT 25
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PXCNT, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

#define BLACK strip.gamma32(strip.Color(0,0,0))
#define RED strip.gamma32(strip.Color(255,0,0))
#define GREEN strip.gamma32(strip.Color(0, 255, 0))
#define YELLOW strip.gamma32(strip.Color(255, 150, 0))
#define BLUE strip.gamma32(strip.Color(0, 0, 255))
#define WHITE strip.gamma32(strip.Color(255, 255, 255))
#define AQUA strip.gamma32(strip.Color(50, 255, 25))
#define PURPLE strip.gamma32(strip.Color(180, 0, 255))


static const uint32_t pattern[300] = {
  RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,
  WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
  GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
  RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,
  WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
  GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
  RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,
  WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
  GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
  RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,
  WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
  GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
  RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,
  WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
  GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
  BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
  BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
  BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
  RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,
  WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
  GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
  RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,
  WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
  GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
  RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,
  WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
  GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
  RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,
  WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
  GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
};

void setup() {
  pinMode(PIN, OUTPUT);
  Serial.begin(115200);
  delay(500);
  Serial.println("Starting");
  delay(500);
  strip.begin();
  strip.setBrightness(BRIGHT);

  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

//    xy_test();
//    blocks();
  delay(DELAYx15);
//  for (size_t idx = 0; idx < PXCNT * 5; idx += 15) {
//    displayPattern(idx, DELAYx15);
//  }
  colorWipe(RED, 0); // Red
  colorWipe(BLACK, 0); // Red
  colorWipe(GREEN, 0); // Green
  colorWipe(BLACK, 0); // Red
  colorWipe(BLUE, 0); // Blue
  colorWipe(BLACK, DELAY); // Red
  colorFill(RED, DELAYx15); // Red
  colorFill(BLACK, DELAYx15); // Red
  colorFill(GREEN, DELAYx15); // Green
  colorFill(BLACK, DELAYx15);
  colorFill(BLUE, DELAYx15); // Blue
  colorFill(BLACK, DELAYx15);
  rainbow(DELAY);
  rainbowCycle(DELAY);
}

void xy_test() {
  Serial.println("XY Test");
  for (size_t idy = 0; idy < 20; idy++) {
    strip.fill(RED, XY(0, idy), 5);
    strip.fill(GREEN, XY(5, idy), 5);
    strip.fill(YELLOW, XY(10, idy), 5);
    strip.show();
    delay(DELAYx15);
  }
}

//
void blocks() {
  Serial.println("Blocks");
  for (size_t idx = 0; idx < 15; idx ++) {
    block(idx, AQUA);
    strip.show();
    delay(DELAY);
  }
}

void block(size_t x, uint32_t c) {
  size_t height = random(18);
  for (size_t idy = 0; idy < 2 + height; idy ++) {
    strip.setPixelColor(XY(x, idy), strip.Color(Adafruit_NeoPixel::sine8(idy * 256 / 20), 0, 0));
  }
  for (size_t idy = 2 + height; idy < 20; idy ++) {
    strip.setPixelColor(XY(x, idy), BLACK);
  }

}

//Display pattern
void displayPattern(uint16_t offset, uint16_t wait) {
  Serial.println("Pattern display");
  for (size_t idx = 0; idx < PXCNT; idx++) {
    strip.setPixelColor((idx + offset) % PXCNT, pattern[idx % PXCNT]);
  }
  strip.show();
  delay(wait);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint16_t wait) {
  Serial.println("Color wipe");
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    Serial.print("Pixel: ");
    Serial.println(i);
    strip.setPixelColor(i, c);
    strip.show();
    if (wait)
      delay(wait);
  }
}
void colorFill(uint32_t c, uint16_t wait) {
  Serial.println("Color fill");
  strip.fill(c, 0, strip.numPixels());
  strip.show();
  delay(wait);
}

void sonar(uint32_t color, uint16_t pxCnt, uint16_t wait) {
  for (uint16_t idx = pxCnt; idx < strip.numPixels(); idx++) {
    for (uint16_t jdx = idx - pxCnt; jdx < idx; jdx++)
    {
      strip.setPixelColor(jdx, color);
    }
    strip.show();
    delay(wait);

    for (uint16_t jdx = idx - pxCnt; jdx < idx; jdx++)
    {
      strip.setPixelColor(jdx, BLACK);
    }
    strip.show();
  }
}

void rainbow(uint16_t wait) {
  Serial.println("Rainbow");
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint16_t wait) {
  Serial.println("Rainbow Cycle");
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint16_t wait) {
  Serial.println("TheatreChase");
  for (uint16_t j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (uint16_t q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint16_t wait) {
  Serial.println("TheatreChaseRainbow");
  for (uint16_t j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (uint16_t q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
