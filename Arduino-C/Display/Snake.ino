// -1: field
// 0: snake
// 1: point

// point

// direction
// not in itself
// not outside the field

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
int futureHead;
long oldTime;
bool playTheGame = true;

int pt = 0;

void Input() {
  // TODO second &&

  if (digitalRead(2) == 1 && !CheckIsInSnake(snake[snakeIndex] + right))
    ChangeDirection(0);
  else if (digitalRead(3) == 1  && !CheckIsInSnake(snake[snakeIndex] + left))
    ChangeDirection(1);
  else if (digitalRead(4) == 1  && !CheckIsInSnake(snake[snakeIndex] + up))
    ChangeDirection(2);
  else if (digitalRead(5) == 1  && !CheckIsInSnake(snake[snakeIndex] + down))
    ChangeDirection(3);

  Serial.println("pressed");
}

void GameStart() {
  attachInterrupt(digitalPinToInterrupt(2), Input, RISING);
  attachInterrupt(digitalPinToInterrupt(3), Input, RISING);
  attachInterrupt(digitalPinToInterrupt(4), Input, RISING);
  attachInterrupt(digitalPinToInterrupt(5), Input, RISING);

  GameReset();

  oldTime = millis();
  GeneratePoint(); // point = 25;

  DrawFrame();

  GameLoop();
}

void GameStop() {
  detachInterrupt(digitalPinToInterrupt(2));
  detachInterrupt(digitalPinToInterrupt(3));
  detachInterrupt(digitalPinToInterrupt(4));
  detachInterrupt(digitalPinToInterrupt(5));
}

void GameReset() {
  randomSeed(analogRead(0)); // random seed
  randomSeed(random(analogRead(0))); // seed is more random

  for (int i = 0; i < numberOfPixels; ++i)
    snake[i] = -1;

  winnedPoints = 0; // restes the winned points
  snake[0] = {startPos}; // emptys the snake
  snakeIndex = 0; // sets the index to the right value
  point = 0; // resets the point
  m = left; // resets the movement
  cDirection = 0; // resets the movement input

  Serial.println("reset");
}

void GameLoop() {
  if (oldTime + framerate <= millis() && playTheGame) {
    MoveSnake(); // move the snake

    // no normal fields more TODO: inside MoveSnake()
    if (!CheckIsInSnake(-1)) End(true);

    DrawFrame();

    oldTime = millis();
  }

  GameLoop(); // restarts itself recursivly
}

void DrawFrame() {
  NoColor();

  // check pattern
  for (int i = 0; i < numberOfPixels; ++i)
    strip.setPixelColor(i, i % 2 == 1 ? strip.Color(0, 255, 0) : strip.Color(0, 255, 255));

  // snake
  for (int i = 0; i <= snakeIndex; ++i)
    strip.setPixelColor(snake[i], strip.Color(255, 0, 0));

  // point
  strip.setPixelColor(point, strip.Color(255, 0, 255));

  strip.show();
}

void GeneratePoint() {
  do {
    point = random(0, numberOfPixels); // new point is chosen randomly and it is for save not in the snake
    // point = 25 + 17 + 17 + 17;
  } while (CheckIsInSnake(point));
}

void MoveSnake() {
  // move the head if it is possible (out of field)
  // sets the back right
  // check if point was eaten and if so longer Tail +  EatenPoint();
  futureHead = snake[snakeIndex] + m;
  int head = snake[snakeIndex] + m;

  switch (CheckEdge()) {
    case -1:
      break; // go to other side
    case 0:
      // right
      head += 271;
      break;
    case 1:
      // left TODO wrong start pos
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

  if (futureHead == point) { // snakes gets longer
    ChangeSnakePosition(-1, true);
    GeneratePoint();
  } else {
    ChangeSnakePosition(head, false); // snakes moves
  }
}

void ChangeSnakePosition(int _head, bool longer) {
  for (int i = 0; i < snakeIndex; ++i)
    snake[i] = snake[i + 1];

  if (longer) {
    snakeIndex++;
    snake[snakeIndex] = snake[snakeIndex - 1] + m;
  } else {
    snake[snakeIndex] = _head;
  }
}

int CheckEdge() {
  if (m == down && snake[snakeIndex] % 17 == 0) 
    return 3;
  if (m == up && (snake[snakeIndex] % 17 == 16 || snake[snakeIndex] == 16)) 
    return 2;
  if (m == left && (snake[snakeIndex] - 272 >= 0)) 
    return 1;
  
  return -1;
}

void End(bool win) {
  if (win) {
    for (int y = 0; y < 3; y++) {
      for (int i = 0; i < numberOfPixels; ++i)
        strip.setPixelColor(i, strip.Color(0, 255, 0)); // Green display
      strip.show();

      delay(300);

      for (int i = 0; i < numberOfPixels; ++i)
        strip.setPixelColor(i, strip.Color(0, 0, 0)); // No color display
      strip.show();

      delay(300);
    }
  } else {

    for (int y = 0; y < 3; y++) {
      for (int i = 0; i < numberOfPixels; ++i)
        strip.setPixelColor(i, strip.Color(255, 0, 0)); // Red display
      strip.show();

      delay(300);

      for (int i = 0; i < numberOfPixels; ++i)
        strip.setPixelColor(i, strip.Color(0, 0, 0)); // No color display
      strip.show();

      delay(300);
    }
  }

  playTheGame = false;

  delay(3000);
  GameReset();
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
