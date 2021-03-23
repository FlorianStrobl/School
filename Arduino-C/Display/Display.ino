// Florian Crafter 2020
// Display 0.7

#include <Adafruit_NeoPixel.h>
#include "Pictures.h" // the pictures

#define PIN 6 // the pin for the arduino
const int baut = 9600; // signal frequency between the PC and the arduino
const int brightness = 50; // set the brightness of the display
const int fieldSize = 17; // number of pixel per side of the squared display
const int numberOfPixels = pow(fieldSize, 2); // total number of pixel
const bool includeStartAnimation = false; // start animation
const int startAnimationLenght = 1000; // duration of the start animation (and it's speed)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numberOfPixels, PIN, NEO_GRB + NEO_KHZ800);

const uint32_t mainColor = strip.Color(136, 0, 255); // start animation color

void setup() {
  Start(baut, brightness); // sets the right values for the display and arduino

  GameStart();
}

void loop() {}
