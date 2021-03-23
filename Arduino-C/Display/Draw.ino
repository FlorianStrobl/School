// Check pattern, shows red - green - blue
void RGBCheckPattern(int _delay) {
  for (unsigned int i = 0; i < 3; ++i) {
    SetColor(((i ^ 1) % 3) * 255, (i & 1) * 255, ((i >> 1) & 1) * 255); // Color (bitwise operations which gives you 0 or 1 for this special range of 0, 1, 2)
    delay(_delay); // lets an delay  between the colors
  }
}

// draw a picture on the display
void ShowPic(const byte pic[289][3], int duration) {
  NoColor(); // resets the display to prevent any errors

  for (int i = 0; i < 289; ++i) { // go through all pixel
    strip.setPixelColor(i, strip.Color(pic[i][0], pic[i][1], pic[i][2])); // set the color of the right pixel
    // strip.show(); // live updating picture
  }
  strip.show();

  delay(duration);
}

void ShowCompressedPic(const byte pic[][4], int lenght, int duration) {
  NoColor(); // resets the display to prevent any errors

  for (int i = 0; i < lenght; ++i) { // gos throw all pixel
    byte lC = pic[i][4];
    uint32_t oldColor = strip.Color(pic[i][0], pic[i][1], pic[i][2]);

    for (int y = 0; i < oldColor; ++y) {
      strip.setPixelColor(i, oldColor); // set the color of the right pixel
      strip.show(); // show the current state of the picture
    }
  }
  strip.show();

  delay(duration);
}
