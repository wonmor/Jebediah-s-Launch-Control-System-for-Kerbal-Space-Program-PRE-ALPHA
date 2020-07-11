/*
   Jebediah's Launch Control System for Kerbal Space Program
   Alpha Build 1.1
   An Open-Source Project by John Seong
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {12, 11, 10, 9};
byte colPins[COLS] = {8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Show a two-line message on the LCD.
void lcdShow(const char *line0, const char *line1) {
  lcd.clear();
  lcd.print(line0);
  lcd.setCursor(0, 1);
  lcd.print(line1);
}

void lcdShowResult(float result) {
  lcd.print(result);
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcdShow("Jeb's Launch", "Control System");
  delay(3000);
  lcdShow("Alpha Build 1.1", " STUDIO HORIZON");
  delay(3000);
  lcdShow("Welcome, Kerman", "Press any key...");
  while (!keypad.getKey()) ;  // wait for key press
}

void loop() {
  static enum {START, MENU, SET_COUNT, COUNT_DOWN, SET_THRUST, SET_WEIGHT, TWR_COMPUTE} state = START;
  static uint32_t last_second;  // millis() value on last full second
  static int count, thrust, weight;             // countdown, thrust, weight value
  static float ratio;

  char key = keypad.getKey();

  switch (state) {
    case START:  // transitional state
      lcdShow("1. Countdown", "2. TWR");
      state = MENU;
    /* fallthrough */
    case MENU:
      if (key == '1') {  // Countdown
        lcdShow("Countdown Timer", "Seconds: ");
        count = 0;
        state = SET_COUNT;
      } else if (key == '2') {  // TWR
        lcdShow("TWR Calculator", "Thrust: ");
        thrust = 0, weight = 0, ratio = 0;
        state = SET_THRUST;
      }
      break;
    case SET_COUNT:
      if (key >= '0' && key <= '9' && count <= 99) {
        lcd.print(key);
        count = 10 * count + (key - '0');
      } else if (key == '#') {
        lcdShow("Lift off in", "     seconds");
        // Force a refresh on entering COUNT_DOWN:
        last_second = millis() - 1000;
        count++;
        state = COUNT_DOWN;
      } else if (key == '*') {
        state = START;
      }
      break;
    case COUNT_DOWN:
      if (millis() - last_second >= 1000) {
        last_second += 1000;
        count--;
        if (count == 0) {
          Serial.println("Lift off!");
        } else if (count < 0) {
          state = START;
          break;
        }
        lcd.setCursor(1, 1);
        lcd.print(count < 10 ? "  " : count < 100 ? " " : ""); // pad
        lcd.print(count);
      } else if (key == '*') {
        state = START;
      }
      break;
    case SET_THRUST:
      if (key >= '0' && key <= '9' && thrust <= 9999) {
        lcd.print(key);
        thrust = 10 * thrust + (key - '0');
      } else if (key == '#') {
        lcdShow("TWR Calculator", "Weight: ");
        state = SET_WEIGHT;
      } else if (key == '*') {
        state = START;
      }
      break;
    case SET_WEIGHT:
      if (key >= '0' && key <= '9' && weight <= 9999) {
        lcd.print(key);
        weight = 10 * weight + (key - '0');
      } else if (key == '#') {
        lcdShow("Thrust-to-weight", "ratio: ");
        ratio = thrust / weight;
        lcdShowResult(ratio);
      } else if (key == '*') {
        state = START;
      }
      break;
  }
}
