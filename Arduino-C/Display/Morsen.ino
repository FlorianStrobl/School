int ledPin = 13;
int myDelay = 300;
String theMorseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "...", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
String stringWithMorse;


// nur kleinbuchstaben und keine leerzeichen (a-z sind möglich)
//morseAnString("sos"); // morses sos on the display

// get an string to convert it to morse
void morseAnString(char chares[]) {
  Serial.println();
  Serial.print(chares);

  for (int i = 0; i < strlen(chares); i++) {
    stringWithMorse = theMorseCode[(int)chares[i] - 97];
    Serial.println("");
    Serial.print(chares[i]);
    Serial.print(":");

    while (true) {
      if (stringWithMorse == "") {
        break;
      }

      if (stringWithMorse.startsWith(".")) {
        ledFlash(myDelay, 1);
      } else if (stringWithMorse.startsWith("-")) {
        ledFlash(myDelay * 3, 1);
      } else {
        delay(myDelay * 3);
      }

      stringWithMorse.remove(0, 1);
    }
  }
  Serial.println("");
  delay(7 * myDelay);
}

String ledFlash(int theDelay, int times) {
  for (int i = 0; i < times; i++) {
    if (theDelay == myDelay) {
      Serial.print(" dit");
    } else {
      Serial.print(" dah");
    }

    AllLeds();
    delay(theDelay);
    NoLeds();
    delay(myDelay);
  }
}

void AllLeds() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
}

void NoLeds() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}
