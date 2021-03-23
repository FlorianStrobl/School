void Start(int _baut, int _brightness) {
  Serial.begin(_baut);
  strip.begin();
  strip.setBrightness(_brightness);

  if (includeStartAnimation) StartAnimation();

  pinMode(2, INPUT);

  Serial.println("Start display!");
}

// set display off
void NoColor() {
  for (int i = 0; i < strip.numPixels(); ++i)
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  strip.show();
}

// checks if an integer is in an array
bool IsIntInArray(int theArray[], int value, int lenght) { // lenght = (int)( sizeof(theArray) / sizeof(theArray[0]))
  for (int i = 0; i < lenght; i++) {
    if (theArray[i] == value) {
      return true;
    }
  }
  return false;
}

// set a color on the full display
void SetColor(int r, int g, int b) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

// Not in use
int CoordsToNumber(int x, int y) {
  return fieldSize * y + x;
}

// (0, 0) is the middle of the field
int XYToCoords(int x, int y) {
  int middlePoint = fieldSize * (int)(fieldSize / 2) + (int)(fieldSize / 2);
  return fieldSize * x + middlePoint + y;
}
