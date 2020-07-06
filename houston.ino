/* 
 * Jebediah's Launch Control System for Kerbal Space Program
 * Alpha Build 0.55
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

char thrustV, massV, gravityV;
int timeV = constrain(timeV, 15, 120);

byte rowPins[ROWS] = {12, 11, 10, 9};
byte colPins[COLS] = {8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

bool keyDetect = false;
bool menuKeyDetect = false;
bool goHomeDetect = false;

bool countDownDetect = false;
bool twrCalDetect = false;

String timeValue, thrustValue, massValue, gravityValue;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  
  Startup();
  
  timeV = 0;
}

void loop() {
  PressKey();
  
  if(menuKeyDetect == true) {
    PressMenuKey();
  }

  if(goHomeDetect == true) {
    GoHome();
  }

  if(countDownDetect == true) {
    CountDownSequence();
  }
}

// Pages
void Startup() {
  lcd.print("Jeb's Launch");
  
  lcd.setCursor(0, 1);
  lcd.print("Control System");
  
  delay(3000);
  
  lcd.clear();
  lcd.print("Alpha Build 0.55");

  lcd.setCursor(0, 1);
  lcd.print(" STUDIO HORIZON");
  
  delay(3000);
  
  lcd.clear();
  lcd.print("Welcome, Kerman");
  
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
  
  lcd.print("Time (sec): ");

  lcd.setCursor(0, 1);
  lcd.print("# to continue...");

  goHomeDetect = true;
  countDownDetect = true;
}

void CountDown2() {
  
}

void TwrCal() {
  lcd.print("Thrust: ");
  
  lcd.setCursor(0, 1);
  lcd.print("# to continue...");

   goHomeDetect = true;
}

// Actions & Behaviours
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

void CountDownSequence() {
  char key = keypad.getKey();
  if(key == '0') {
    timeV = 0;
  } else { timeV = (timeV * 10) + 0; }

  if(key == '1') {
    timeV = 0;
  } else { timeV = (timeV * 10) + 1; }

  if(key == '2') {
    timeV = 2;
  } else { timeV = (timeV * 10) + 2; }

  if(key == '3') {
    timeV = 3;
  } else { timeV = (timeV * 10) + 3; }

  if(key == '4') {
    timeV = 4;
  } else { timeV = (timeV * 10) + 4; }

  if(key == '5') {
    timeV = 5;
  } else { timeV = (timeV * 10) + 5; }

  if(key == '6') {
    timeV = 6;
  } else { timeV = (timeV * 10) + 6; }

  if(key == '7') {
    timeV = 7;
  } else { timeV = (timeV * 10) + 7; }

  if(key == '8') {
    timeV = 8;
  } else { timeV = (timeV * 10) + 8; }

  if(key == '9') {
    timeV = 9;
  } else { timeV = (timeV * 10) + 9; }

  if(key == '*') {
    ModeMenu();
  }

  if(key == '#') {
    CountDown2();
  }

  Serial.println(timeV);
  lcd.setCursor(13, 0);
  lcd.print(timeV);
  
  countDownDetect = false;
}

void CountDownSequence2() {
  
}
