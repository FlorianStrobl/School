void Start() {
  Serial.begin(baut);
  strip.begin();
  Serial.println("Start display!");

  pinMode(2, INPUT);

  strip.setBrightness(brightness);
  if (includeStartAnimation) {
    StartAnimation();
  }
  NoColor();
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

int CoordinatenInZahl(int x, int y) {
  return fieldSize * y + x;
}

int richtigeCoordsInXCoords(int y) {
  return y * (-1) + 2;
}

// (0, 0) is the middle of the field
int XYToCoords(int x, int y) {
  int middlePoint = fieldSize * (int)(fieldSize / 2) + (int)(fieldSize / 2);
  return fieldSize * x + middlePoint + y;
}

// sets color off
void NoColor() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

// set an color
void SetColor(int r, int g, int b) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

// sets the enum to the next value for the start animation
void NextValue() {
  switch (ourEnum) {
    case start:
      ourEnum = second;
      break;
    case second:
      ourEnum = third;
      break;
    case third:
      ourEnum = last;
      break;
    case last:
      ourEnum = start;
      break;
  }
}
