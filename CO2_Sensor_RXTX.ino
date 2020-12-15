// Coder: Florian Crafter 2020
// This is the code to let an mhz19b co2 sensor adjust the color of an LED.
// about 90 sec delay

// the library for the sensor
#include <MHZ19_uart.h>

// pins
const int rx_pin = 5;	// the arduino RX pin and sensor TX pin
const int tx_pin = 4;	// the arduino TX pin and sensor RX pin
const int led_pins[3] = {6, 9, 3}; // the pins were the LED is on

// settings
const bool Warm = false; // let the sensor warm at start
const bool AutoCalibrate = false; // calibare the sensor at start
const int Delay = 1000; // time the program waits until next LED refresh
const int limitPPM1 = 800; // values below that, makes the LED green
const int limitPPM2 = 1000; // values below that, makes the LED orange, and values over that makes it red
const int limitThreshhold = 30; // +-ppm for the sensor

// the three colors
const int c1[3] = {0, 255, 0}; // color for state 1 (Green)
const int c2[3] = {255, 255, 0}; // color for state 2 (Orange)
const int c3[3] = {255, 0, 0}; // color for state 3 (Red)
const int errorColor[3] = {0, 0, 255}; // Color for state ERROR (Blue)

// variables
byte firstStart = true; // check if first start

// the sensor
MHZ19_uart mhz19;

// fires up on arduino start and set it right
void setup() {
  Serial.begin(9600);

  // set the sensor right
  mhz19.begin(rx_pin, tx_pin);
  mhz19.setAutoCalibration(AutoCalibrate);

  // start animation
  StartAnimation();

  // let the sensor warm at the start
  while ( mhz19.isWarming() && Warm ) {
    Serial.print("MH-Z19 now warming up - status:"); Serial.println(mhz19.getStatus());
    analogWrite(led_pins[2], 255);
    delay(Delay / 2);
    SetNullColor();
    delay(Delay / 2);
  }

  // resets the color
  SetNullColor();

  Serial.println("start");
}

// the loop
void loop() {
  delay(Delay); // wait

  Serial.println("------------");

  // check if error
  if (mhz19.getStatus() != 0) {
    Serial.println("error");
    ErrorColor();
    return;
  }

  // get data from sensor
  int co2ppm = mhz19.getPPM();
  int temp = mhz19.getTemperature();

  // print the values to the console
  Serial.print("state: "); Serial.println(mhz19.getStatus());
  Serial.print("co2: "); Serial.println(co2ppm);
  Serial.print("temp: "); Serial.println(temp);

  // get the color variable acording to the ppm & set the LED color
  SetColor(GetColor(co2ppm));

  if (firstStart)
    firstStart = false;
}

// chose the right color for the LED
int GetColor(int ppm) {
  if ( ((limitPPM1 - limitThreshhold < ppm && ppm < limitPPM1 + limitThreshhold) || (limitPPM2 - limitThreshhold < ppm && ppm < limitPPM2 + limitThreshhold)) && !firstStart ) {
    Serial.println("Values are in threashhold");
    return -1;
  }

  if (ppm < limitPPM1) {
    return 0;
  } else if (ppm >= limitPPM1 && ppm < limitPPM2) {
    return 1;
  } else {
    return 2;
  }
}

void SetColor(int c) {
  Serial.print("color: ");
  switch (c) {
    case -1:
      break;
    case 0:
      Serial.println("Green");
      analogWrite(led_pins[0], c1[0]);
      analogWrite(led_pins[1], c1[1]);
      analogWrite(led_pins[2], c1[2]);
      break;
    case 1:
      Serial.println("Orange");
      analogWrite(led_pins[0], c2[0]);
      analogWrite(led_pins[1], c2[1]);
      analogWrite(led_pins[2], c2[2]);
      break;
    case 2:
      Serial.println("Red");
      analogWrite(led_pins[0], c3[0]);
      analogWrite(led_pins[1], c3[1]);
      analogWrite(led_pins[2], c3[2]);
      break;
  }
}

void ErrorColor() {
  analogWrite(led_pins[0], errorColor[0]);
  analogWrite(led_pins[1], errorColor[1]);
  analogWrite(led_pins[2], errorColor[2]);
}

void SetNullColor() {
  analogWrite(led_pins[0], 0);
  analogWrite(led_pins[1], 0);
  analogWrite(led_pins[2], 0);
}

void StartAnimation() {
  for (int i = 0; i < 3; i++) {
    analogWrite(led_pins[0], 255);
    analogWrite(led_pins[1], 255);
    analogWrite(led_pins[2], 255);
    delay(500);
    SetNullColor();
    delay(500);
  }
}

