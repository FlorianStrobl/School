// A Co2 projekct - 2020/2021
// Coding: Florian Crafter
// 3D Printing: Emile
// Soldering/Logistics: Lajosh
// This is the code to let an mhz19b co2 sensor adjust the color of an LED.
// Important: all values have about 90 sec delay. The sensor has a max of 5000ppm and you shouldn't use the data if the temperatur is above 50 degree.

// the library for the sensor
#include <MHZ19_uart.h>

// the sensor
MHZ19_uart mhz19;

// pins
const byte rx_pin = 5;  // the arduino RX pin and sensor TX pin
const byte tx_pin = 4;  // the arduino TX pin and sensor RX pin
const byte led_pins[3] = {6, 9, 3}; // (R, G, B) the pins where the LED is on

// settings
const bool Warm = false; // let the sensor warm at start
const bool AutoCalibrate = false; // calibare the sensor at start (only for outside use)
const short Delay = 1000; // time the program waits until next LED refresh
const short limitPPM1 = 800; // values below that, makes the LED green
const short limitPPM2 = 1000; // values below that, makes the LED orange, and values over that makes it red
const byte limitThreshold = 30; // +-ppm for the sensor

// the three colors
const byte c1[3] = {0, 255, 0}; // color for state 1 (Green)
const byte c2[3] = {255, 255, 0}; // color for state 2 (Orange)
const byte c3[3] = {255, 0, 0}; // color for state 3 (Red)
const byte errorColor[3] = {0, 0, 255}; // Color for state ERROR (Blue)

// variables
bool firstStart = true; // bool for the first start
int co2ppm = 0; // current co2 value in ppm
int temp = 0; // current temperature in C

// fires up on arduino start and set the settigns
void setup() {
  // starts connection to an PC if available
  Serial.begin(9600);

  // set the sensor settings
  mhz19.begin(rx_pin, tx_pin);
  mhz19.setAutoCalibration(AutoCalibrate);

  StartAnimation();

  // let the sensor warm up at start
  while ( mhz19.isWarming() && Warm ) {
    Serial.print("MH-Z19 now warming up - status:"); Serial.println(mhz19.getStatus());
    analogWrite(led_pins[2], 255);
    delay(Delay / 2);
    SetNoColor(); // "deactivates" the LED
    delay(Delay / 2);
  }

  // reset the color
  SetNoColor();

  Serial.println("start version 1.1");
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
  co2ppm = mhz19.getPPM();
  temp = mhz19.getTemperature();

  // print the values
  Serial.print("state: "); Serial.println(mhz19.getStatus());
  Serial.print("co2: "); Serial.println(co2ppm);
  Serial.print("temp: "); Serial.println(temp);
  Serial.print("color: ");
  
  // get the color variable acording to the ppm & set the LED color (does print the color name in the console)
  SetColor(GetColor(co2ppm));

  if (firstStart) firstStart = false;
}

// returns the color of the LED for the givin ppm
byte GetColor(int ppm) {
  // goes in it, if the values are in the setted threshold
  bool threshold1 = limitPPM1 - limitThreshold < ppm && ppm < limitPPM1 + limitThreshold;
  bool threshold2 = limitPPM2 - limitThreshold < ppm && ppm < limitPPM2 + limitThreshold;
  if (firstStart == false && (threshold1 || threshold2)) {
    Serial.println("Values are in threshold");
    return -1;
  }

  // returns the color for the given ppm
  if (ppm < limitPPM1)
    return 0;
  else if (ppm >= limitPPM1 && ppm < limitPPM2)
    return 1;
  else
    return 2;
}

// sets the color of the LED
void SetColor(short c) {
  switch (c) {
    case -1:
      Serial.println("No color");
      SetNoColor();
      break;
    case 0:
      Serial.println("Green");
      for (byte i = 0; i < 3; i++) 
        analogWrite(led_pins[i], c1[i]);
      break;
    case 1:
      Serial.println("Orange");
      for (byte i = 0; i < 3; i++)
        analogWrite(led_pins[i], c2[i]);
      break;
    case 2:
      Serial.println("Red");
      for (byte i = 0; i < 3; i++)
        analogWrite(led_pins[i], c3[i]);
      break;
  }
}

// sets the LED to the error color
void ErrorColor() {
  for (byte i = 0; i < 3; i++)
    analogWrite(led_pins[i], errorColor[i]);
}

// sets the LED to no color
void SetNoColor() {
  for (byte i = 0; i < 3; i++)
    analogWrite(led_pins[i], 0);
}

// three white blinks from the LED
void StartAnimation() {
  for (byte i = 0; i < 3; i++) {
    for (byte y = 0; y < 3; y++)
      analogWrite(led_pins[y], 255);
    delay(500);
    SetNoColor();
    delay(500);
  }
}
