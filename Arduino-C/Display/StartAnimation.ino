// enum for start animation
enum Direction : int
{
  up_ = 1,
  left_ = fieldSize,
  down_ = -1,
  right_ = -fieldSize
} currentDirection = up_;

// draws a snake going to the middle
void StartAnimation() {
  int value = 0; // current pixel
  int counter = 0; // checks for edges
  int anzahlAnDasMachen = fieldSize - 1; //
  int nerfigeVariable = 1; //
  int wait = startAnimationLenght / numberOfPixels; // delay between the next led

  // all "colors"
  for (int i = 0; i < (fieldSize * 2) - 1; ++i) {
    strip.setPixelColor(0, mainColor); // the first led
    delay(wait);

    // mach anzahlAnDasMachen die Rechnung und gib jeweils die Zahl aus
    for (int y = 0; y < anzahlAnDasMachen; ++y) {
      value += (int)currentDirection; // sets the next pixel
      // Serial.println(value);
      strip.setPixelColor(value, mainColor); // set the right led on with the seted color
      strip.show();
      delay(wait);
    }

    NextValue();
    counter++;

    // on an edge
    if (nerfigeVariable + 2 == counter) {
      anzahlAnDasMachen--;
      nerfigeVariable = 0;
      counter = 0;
    }
  }

  delay(1000);
  NoColor();
}

// sets the enum to the next value for the start animation
void NextValue() {
  switch (currentDirection) {
    case up_:
      currentDirection = left_;
      break;
    case left_:
      currentDirection = down_;
      break;
    case down_:
      currentDirection = right_;
      break;
    case right_:
      currentDirection = up_;
      break;
  }
}
