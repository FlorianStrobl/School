// Florian Crafter 2020
// Display 0.7

#include <Adafruit_NeoPixel.h>

#include "Pictures.h" // the pictures

#define PIN 6 // the pin for the arduino

const int baut = 9600; // signal frequency between the PC and the arduino

// number of pixel per side of the display
const int fieldSize = 17;
const int numberOfPixels = pow(fieldSize, 2);
// set the brightness of the display
const int brightness = 50;

// duration of the start animation
const int startAnimationLenght = 1000;
const bool includeStartAnimation = false;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numberOfPixels, PIN, NEO_GRB + NEO_KHZ800);

const uint32_t mainColor = strip.Color(136, 0, 255); // start animation color

void setup() {
  Start(); // sets the right values for the display and arduino

  GameLoop();
}

// RGBCheckPattern(500); // shows red - green - blue
void loop() {
  /*
  int d = 1000;

  ShowPic(Tree0, d); // draws an piture

  ShowPic(Tree1, d); // draws an piture

  ShowPic(Tree2, d); // draws an piture

  ShowPic(Tree3, d); // draws an piture

  ShowPic(Tree4, d); // draws an piture

  ShowPic(Tree5, d); // draws an piture
  */
}


// Check pattern, shows red - green - blue
void RGBCheckPattern(int ourDelay) {
  SetColor(255, 0, 0); // red
  delay(ourDelay); // lets an delay  between the colors

  SetColor(0, 255, 0); // green
  delay(ourDelay); // lets an delay  between the colors

  SetColor(0, 0, 255); // blue
  delay(ourDelay); // lets an delay  between the colors
}

// draws an picture on the display
void ShowPic(const byte pic[289][3], int duration) {
  NoColor(); // resets the color for error correction

  for (int i = 0; i < 289; i++) { // gos throw all pixel
    strip.setPixelColor(i, strip.Color(pic[i][0], pic[i][1], pic[i][2])); // set the color of the right pixel
    //Serial.println("Pixel: " + (String)(i) + " - Color: r: " + (String)(pic[i][0]) + " g: " + (String)(pic[i][1]) + " b: " + (String)(pic[i][2]));
    //strip.show(); // show the current state of the picture
  }
  strip.show();

  delay(duration);
}

void ShowCompressedPic(const byte pic[][4], int lenght, int duration) {
  NoColor(); // resets the color for error correction

  for (int i = 0; i < lenght; i++) { // gos throw all pixel
    byte lC = pic[i][4];
    uint32_t oldC = strip.Color(pic[i][0], pic[i][1], pic[i][2]);

    for (int y = 0; i < lC; y++) {
      strip.setPixelColor(i, oldC); // set the color of the right pixel
      strip.show(); // show the current state of the picture
    }
  }
  strip.show();

  delay(duration);
}

// draws multiple pictures on the display
void ShowGif(const byte picAr[2][289][3], int wait) {
  for (int n = 0; n < 5; n++) {
    for (int i = 0; i < 289; i++) {
      strip.setPixelColor(i, strip.Color(picAr[n][i][0], picAr[n][i][1], picAr[n][i][2]));
      //Serial.println("Picture: " + (String)(n) + " - Pixel: " + (String)(i) + " - Color: r: " + (String)(picAr[n][i][0]) + " g: " + (String)(picAr[n][i][1]) + " b: " + (String)(picAr[n][i][2]));
    }
    strip.show();
    delay(wait);
  }
}

// enum for start animation
enum Thing : int
{
  start = 1,
  second = fieldSize,
  third = -1,
  last = -fieldSize
};

enum Thing ourEnum = start;

// draws a snake going to the middle
void StartAnimation() {
  int value = 0; // current pixel
  int counter = 0; // checks for edges
  int anzahlAnDasMachen = fieldSize - 1; //
  int nerfigeVariable = 1; //
  int wait = startAnimationLenght / numberOfPixels; // delay between the next led

  // all "colors"
  for (int i = 0; i < (fieldSize * 2) - 1; i++) {
    strip.setPixelColor(0, mainColor); // the first led
    delay(wait);
    // mach anzahlAnDasMachen die Rechnung und gib jeweils die Zahl aus
    for (int z = 0; z < anzahlAnDasMachen; z++) {
      value += (int)ourEnum; // sets the next pixel
      //Serial.println(value);
      strip.setPixelColor(value, mainColor); // set the right led on with the seted color
      strip.show();
      delay(wait);
    }

    NextValue();
    counter++;

    // if on an edge
    if (nerfigeVariable + 2 == counter) {
      anzahlAnDasMachen--;
      nerfigeVariable = 0;
      counter = 0;
    }
  }

  delay(1000);
}
