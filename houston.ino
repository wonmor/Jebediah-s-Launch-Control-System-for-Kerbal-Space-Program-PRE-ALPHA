/* 
 * Jebediah's Launch Control System for Kerbal Space Program
 * Alpha Build 0.52
 * An Open-Source Project by John Seong
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

bool keyDetect = false;
bool menuKeyDetect = false;
bool goHomeDetect = false;

int countDownInput = constrain(countDownInput, 15, 100);

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  Startup();
}

void loop() {
  PressKey();
  
  if(menuKeyDetect == true) {
    PressMenuKey();
  }

  if(goHomeDetect == true) {
    GoHome();
  }
}

// Pages
void Startup() {
  lcd.print("Jeb's Launch");
  
  lcd.setCursor(0, 1);
  lcd.print("Control System");
  
  delay(3000);
  
  lcd.clear();
  lcd.print("Alpha Build 0.52");

  lcd.setCursor(0, 1);
  lcd.print(" STUDIO HORIZON");
  
  delay(3000);
  
  lcd.clear();
  lcd.print(" Welcome, User");
  
  lcd.setCursor(0,1);
  lcd.print("Press any key...");

  keyDetect = true;
}

void ModeMenu() {
  lcd.print("Jebediah's");

  lcd.setCursor(0, 1);
  lcd.print("Mode Selection");
  
  delay(2000);

  lcd.clear();
  lcd.print("1. Countdown");
  
  lcd.setCursor(0, 1);
  lcd.print("2. TWR");

  menuKeyDetect = true;
}

void CountDown() {
  char key = keypad.getKey();
  Serial.println(key);
  
  lcd.print("Time (sec): ");

  lcd.setCursor(11, 0);
  lcd.print(key);

  lcd.setCursor(0, 1);
  lcd.print("# to continue...");

  goHomeDetect = true;
}

void TwrCal() {
  lcd.print("Thrust: ");
  
  lcd.setCursor(0, 1);
  lcd.print("# to continue...");

   goHomeDetect = true;
}

// Actions
void PressKey() {
  char key = keypad.getKey();
  if(key) {
    Serial.println(key);
    if (keyDetect == true) {
      lcd.clear();
      ModeMenu();
      keyDetect = false;
    }
  }
}

void PressMenuKey() {
    char key = keypad.getKey();
    if(key == '1') {
      Serial.println(key);
      if (menuKeyDetect == true) {
        lcd.clear();
        CountDown();
        menuKeyDetect = false;
      }
    } else if(key == '2') {
      Serial.println(key);
      if (menuKeyDetect == true) {
        lcd.clear();
        TwrCal();
        menuKeyDetect = false;
      }
    }
}

void GoHome() {
  char key = keypad.getKey();
  if(key == '*') {
      lcd.clear();
      ModeMenu();
  }
}
