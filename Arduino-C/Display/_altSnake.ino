#define FieldSize 17
const int RefreshRate = 60; // hz
const float RefreshRatePlayer = 1000; // ms

int snake[(int)pow(FieldSize, 2) - 1] = { (int)FieldSize / 2, };
int snakeSize = 1;
int point;
bool pointExists = false;

float lastTime = 0;
float lastTime2 = 0;

enum movement : int {
  up = -1,
  down = 1,
  left = -FieldSize,
  right = FieldSize
} theDirection = right;

void setup() {
  Serial.begin(9600);
}

void PrintState() {
  Serial.print("Point: " + (String)point);
  for (int i = 0; i < snakeSize; i++) {
    Serial.print(" - " + (String)i + ": " + snake[i]);
  }
  Serial.println();
}

void loop() {
  randomSeed(millis() * 100);

  PrintState();

  // Check if new point has to be spawned
  if (!pointExists) {
    point = SpawnPoint();
    pointExists = true;
  }

  // Get input

  // Change Snake
  if (millis() - lastTime >= RefreshRatePlayer) {
    lastTime = millis();
    MoveSnake();
  }

  // Display the field
  if (millis() - lastTime2 >= (float)(1000 / RefreshRate)) {
    lastTime2 = millis();
    //DrawField();
  }
}

void DrawField() {
  for (int i = 0; i < pow(FieldSize, 2); i++) {
    if (ContainsInArray(snake, i, snakeSize)) {
      Serial.print("S");
    } else if (i == point) {
      Serial.print("P");
    } else {
      Serial.print("F");
    }

    if (i % FieldSize == 0) {
      Serial.println();
    }
  }
}

void MoveSnake() {
  if (snakeSize == 1) {
    snake[0] = snake[0] + theDirection;
    CheckHeadEatPoint();
    return;
  }

  for (int i = 0; i < snakeSize - 1; i++) {
    snake[i] = snake[i + 1];
  }
  snake[snakeSize - 1] = snake[snakeSize - 2] + theDirection;

  CheckHeadEatPoint();
}

// TO DO
bool CheckIfOutOfRange(int n) {
  if (n >= pow(FieldSize, 2)) {
    return true;
  }
  return false;
}

// TO DO: lenght++
bool CheckHeadEatPoint() {
  if (ContainsInArray(snake, point, snakeSize)) {
    pointExists = false;
    return true;
  }
  return false;
}

int SpawnPoint() {
  while (true) {
    int x = random(0, pow(FieldSize, 2) - 1);

    if (!ContainsInArray(snake, x, sizeof(snake) / sizeof(snake[0]))) {
      return x;
    }
  }
}

void ChangeDirection(int direction) {
  switch (direction) {
    case 0:
      theDirection = up;
      break;
    case 1:
      theDirection = down;
      break;
    case 2:
      theDirection = left;
      break;
    case 3:
      theDirection = right;
      break;
  }
}

bool ContainsInArray(int Array[], int value, int lenght) {
  for (int i = 0; i < lenght; i++) {
    if (Array[i] == value) {
      return true;
    }
  }
  return false;
}
