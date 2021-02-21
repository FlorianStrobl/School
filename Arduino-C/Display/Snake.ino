// enum for snake movement
enum movement : int
{
  up = 1,
  left = fieldSize,
  down = -1,
  right = -fieldSize
};

// gesamte schlange nach hinten verschieben , snakeIndex + m = snake[snakeIndex+1]

// wenn hinter dir schlange, kannst du nicht nach hinten...

const int startPos = (int)(fieldSize / 2); // were the snakes starts
const int framerate = 1000; // time per frame
enum movement m; // current movement direction as real value
byte cDirection; // current movement direction
int snake[numberOfPixels]; // the snake
int point; // the current point
int winnedPoints; // current winned points
int snakeIndex;
bool firstStart = true;
bool playTheGame = true;
int futureHead;
long oldTime;
bool oncePressed = true;

int pt = 0;

void GameLoop() {
  if (firstStart) {
    oldTime = millis();
    ResetGame();
    NewPoint();
    //point = 25;
    DrawDisplay();
    firstStart = false;
  }

  CheckInput(); // change the m

  if (oldTime + framerate <= millis() && playTheGame) {
    MoveSnake(); // move the snake

    CheckIfEnd(); // no normal fields more

    DrawDisplay(); // draws the frame

    oldTime = millis();
  }

  GameLoop(); // restarts itself recursivly
}

void CheckInput() {
  if ((digitalRead(2) == 1 || digitalRead(3) == 1 || digitalRead(4) == 1 || digitalRead(5) == 1) && oncePressed) {
    // TO DO second &&
    if (digitalRead(2) == 1 && !CheckIsInSnake(snake[snakeIndex] + right)) {
      ChangeDirection(0);
    }
    else if (digitalRead(3) == 1  && !CheckIsInSnake(snake[snakeIndex] + left)) {
      ChangeDirection(1);
    }
    else if (digitalRead(4) == 1  && !CheckIsInSnake(snake[snakeIndex] + up)) {
      ChangeDirection(2);
    }
    else if (digitalRead(5) == 1  && !CheckIsInSnake(snake[snakeIndex] + down)) {
      ChangeDirection(3);
    }

    Serial.println("pressed");
    oncePressed = false;
  } else if ((digitalRead(2) == 0 && digitalRead(3) == 0 && digitalRead(4) == 0 && digitalRead(5) == 0)) {
    oncePressed = true;
  }
}

void MoveSnake() {
  // move the head if it is possible (out of field)
  // sets the back right
  // check if point was eaten and if so longer Tail +  EatenPoint();
  futureHead = snake[snakeIndex] + m;
  int head = snake[snakeIndex] + m;

  switch (CheckIfRightEdge()) {
    case -1:
      break;// go to other side
    case 0:
      // right
      head += 271;
      break;
    case 1:
      // left TO DO wrong start pos
      head -= 272;
      break;
    case 2:
      // up
      head -= 17;
      break;
    case 3:
      // down
      head += 17;
      break;
  }

  if (CheckIsInSnake(futureHead)) { // hit itself
    End(false);
    return;
  }

  if (futureHead == point) {
    MoveLongerSnake();
    NewPoint();
  } else {
    MoveNormalSnake(head);
  }
}

void MoveNormalSnake(int head) {
  for (int i = 0; i < snakeIndex; i++) {
    snake[i] = snake[i + 1];
  }
  snake[snakeIndex] = head;
}

void MoveLongerSnake() {
  snakeIndex++;

  for (int i = 0; i < snakeIndex - 1; i++) {
    snake[i] = snake[i + 1];
  }

  snake[snakeIndex] = snake[snakeIndex - 1] + m;
}

void DrawDisplay() {
  NoColor();

  for (int i = 0; i < numberOfPixels; i++) {
    strip.setPixelColor(i, i % 2 == 1 ? strip.Color(0, 255, 0) : strip.Color(0, 255, 255));
  }
  for (int i = 0; i < snakeIndex + 1; i++) {
    strip.setPixelColor(snake[i], strip.Color(255, 0, 0));
  }
  strip.setPixelColor(point, strip.Color(255, 0, 255));
  strip.show();
}

void NewPoint() {
  do {
    point = random(0, numberOfPixels);
    //point = 25 + 17 + 17 + 17;
  } while (CheckIsInSnake(point));
}

void ResetGame() {
  randomSeed(analogRead(0));
  randomSeed(random(analogRead(0)));

  for (int i = 0; i < numberOfPixels; i++) {
    snake[i] = -1;
  }
  Serial.println("reset");
  m = left; // resets the movement
  cDirection = 0; // resets the movement input
  snake[0] = {startPos}; // emptys the snake
  point = 0; // resets the point coordinate
  winnedPoints = 0; // restes the winned points
  snakeIndex = 0; // sets the index to the right value
}

int CheckIfRightEdge() {
  if (m == up && (snake[snakeIndex] % 17 == 16 || snake[snakeIndex] == 16)) {
    return 2;
  }
  if (m == down && snake[snakeIndex] % 17 == 0) {
    return 3;
  }
  if (m == left && (snake[snakeIndex] - 272 >= 0)) {
    return 1;
  }

  return -1;
}

void CheckIfEnd() {
  if (!CheckIsInSnake(-1)) {
    End(true);
  }
}

void End(bool win) {
  if (win) {
    for (int y = 0; y < 3; y++) {
      for (int i = 0; i < numberOfPixels; i++) {
        strip.setPixelColor(i, strip.Color(0, 255, 0));
      }
      strip.show();
      delay(300);
      for (int i = 0; i < numberOfPixels; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      strip.show();
      delay(300);
    }
  } else {

    for (int y = 0; y < 3; y++) {
      for (int i = 0; i < numberOfPixels; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
      }
      strip.show();
      delay(300);
      for (int i = 0; i < numberOfPixels; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      strip.show();
      delay(300);
    }
  }

  playTheGame = false;
  delay(3000);
  ResetGame();
}

bool CheckIsInSnake(int f) {
  return IsIntInArray(snake, f, (int)( sizeof(snake) / sizeof(snake[0])));
}

bool CheckIsOutOfField(int f) {
  if (f < 0 || f > 288) {
    return true;
  }
  return false;
}

void ChangeDirection (byte nD) {
  switch (nD) {
    case 0:
      m = right;
      break;
    case 1:
      m = left;
      break;
    case 2:
      m = up;
      break;
    case 3:
      m = down;
      break;
  }
}
