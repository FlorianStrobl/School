// A Co2 projekct - 2020/2021
// Coding: Florian Crafter
// 3D Printing: Emile
// Soldering/Logistics: Lajosh
// This is the code to let an mhz19b co2 sensor adjust the color of an LED.
// Important: all values have about 90 sec delay. The sensor has a max of 5000ppm and you shouldn't use the data if the temperatur is above 50 degree.

// the library for the sensor
#include <MHZ19_uart.h>
#include <LiquidCrystal.h>

const String currentVersion = "Ver 1.4";

// pins
const byte rx_pin = 5;  // the arduino RX pin and sensor TX pin
const byte tx_pin = 4;  // the arduino TX pin and sensor RX pin
const byte led_pins[3] = {6, 9, 3}; // (R, G, B) the pins where the LED is on
const int rs = 12, en = 11, d4 = 9, d5 = 10, d6 = 3, d7 = 2, contrast = 6;

// settings
const bool lcdDisplay = false; // set the output mode
const bool Warm = false; // let the sensor warm at start
const bool AutoCalibrate = false; // calibare the sensor at start (only for outside use)
const short Delay = 1000; // time the program waits until next LED refresh
const short limitPPM1 = 800; // values below that, makes the LED green
const short limitPPM2 = 1000; // values below that, makes the LED orange, and values over that makes it red
const byte limitThreshold = 30; // +-ppm for the sensor

// the sensor
MHZ19_uart mhz19;
// the display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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

  if (lcdDisplay == true) {
    lcd.begin(16, 2);
    analogWrite(contrast, 50);
    StartAnimationLCD();
  } else StartAnimation();

  // let the sensor warm up at start
  while ( mhz19.isWarming() && Warm ) {
    Serial.print("MH-Z19 now warming up - status:"); Serial.println(mhz19.getStatus());
    if (lcdDisplay) lcd.print("Warming");
    else analogWrite(led_pins[2], 255);
    delay(Delay / 2);
    if (lcdDisplay) SetNoColorLCD(); // "deactivates" the LED
    else SetNoColor();
    delay(Delay / 2);
  }

  // reset the color
  if (lcdDisplay) SetNoColorLCD();
  else SetNoColor();

  Serial.println(currentVersion);
}

// the loop
void loop() {
  delay(Delay); // wait

  Serial.println("------------");

  // check if error
  if (mhz19.getStatus() != 0) {
    Serial.println("error");
    lcd.clear();
    if (lcdDisplay) ErrorColorLCD();
    else ErrorColor();
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
  if (!lcdDisplay) SetColor(GetColor(co2ppm, temp));
  else SetDisplay(co2ppm, GetColor(co2ppm, temp));

  if (firstStart) firstStart = false;
}

// returns the color of the LED for the givin ppm
byte GetColor(int ppm, int temperatur) {
  // high or low temperatur
  if (temperatur >= 50 || temperatur <= 0) {
    //Serial.println("Sensor temperaturs are too high/low");
    //return 4;
  }

  // goes in it, if the values are in the setted threshold
  bool threshold1 = limitPPM1 - limitThreshold < ppm && ppm < limitPPM1 + limitThreshold;
  bool threshold2 = limitPPM2 - limitThreshold < ppm && ppm < limitPPM2 + limitThreshold;
  if (firstStart == false && (threshold1 || threshold2)) {
    Serial.println("Values are in threshold");
    return 3;
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
    case 4:
      Serial.println("Wrong temperatur");
      for (byte i = 0; i < 3; i++) {
        for (byte y = 0; y < 3; y++)
          analogWrite(led_pins[y], 255);
        delay(500);

        SetNoColor();
        delay(500);
      }
      break;
    case 3:
      Serial.println("No color");
      // last color
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

// sets the LCD to the error color
void ErrorColorLCD() {
  lcd.clear();
  lcd.print("Error");
}

// sets the LED to no color
void SetNoColor() {
  for (byte i = 0; i < 3; i++)
    analogWrite(led_pins[i], 0);
}

// sets the LCD to no color
void SetNoColorLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
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

// three white blinks from the LED
void StartAnimationLCD() {
  lcd.print("CO2 Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Start - " + (String)currentVersion);
  delay(2500);
}

void SetDisplay(int ppm, short c) {
  if (c == 3) return;
  SetNoColorLCD();
  if (c == 4) {
    lcd.print("overheating");
    return;
  }

  lcd.print("CO2: " + (String)ppm + "ppm");
  bool threshold1 = limitPPM1 - limitThreshold < ppm && ppm < limitPPM1 + limitThreshold;
  bool threshold2 = limitPPM2 - limitThreshold < ppm && ppm < limitPPM2 + limitThreshold;
  if (firstStart == false && (threshold1 || threshold2))
    return;

  lcd.setCursor(0, 1);
  switch (c) {
    case 3:
      Serial.println("No change");
      // last color
      break;
    case 0:
        lcd.print("Normaler Wert");
      Serial.println("Green");
      break;
    case 1:
        lcd.print("Hoher Wert");
      Serial.println("Orange");
      break;
    case 2:
    lcd.print("Kritischer Wert");
      Serial.println("Red");
      break;
  }
}
