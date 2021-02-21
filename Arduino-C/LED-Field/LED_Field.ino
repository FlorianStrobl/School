const int fieldsize = 5;

void setup() {
  Serial.begin(9600);
}

// (0, 0) is the middle of the field
int XYToCoords(int x, int y) {
  int middlePoint = fieldsize * (int)(fieldsize / 2) + (int)(fieldsize / 2);
  return fieldsize * x + middlePoint + y;
}

// (0, 0) is the left-down corner of the field
int XYToNr(byte x, byte y) {
  int middlePoint = fieldsize * (int)(fieldsize / 2) + (int)(fieldsize / 2);
  return x * middlePoint + y;
}

// returns an bool if the int array contains the integer
bool IsIntInArray(int theArray[], int value, int lenght) { // lenght = (int)( sizeof(theArray) / sizeof(theArray[0]))
  for (int i = 0; i < lenght; i++) {
    if (theArray[i] == value) {
      return true;
    }
  }
  return false;
}

void loop() {
}
