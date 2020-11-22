/*
   Jebediah's Launch Control System for Kerbal Space Program
   Alpha Build 2.65
   An Open-Source Project by John Seong
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Keyboard.h>

#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784

int melody[] = {
  NOTE_G4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_C4,
  NOTE_G4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_C4,
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_E4, NOTE_FS4, NOTE_G4,
  NOTE_G4, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_D5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_D5, NOTE_C5
};

int noteDurations[] = {
  6, 8, 4, 4, 4, 2, 6, 8, 4, 4, 4, 2, 8, 8, 3, 8, 4, 2, 6, 8, 4, 4, 4, 4, 4,
  6, 8, 4, 4, 4, 2, 6, 8, 4, 4, 4, 2, 8, 8, 3, 8, 4, 2, 6, 8, 4, 4, 4, 4, 4,
  8, 8, 4, 4, 4, 2, 8, 8, 4, 4, 4, 2, 4, 3, 8, 4, 2, 6, 8, 4, 4, 4, 2,
  4, 4, 4, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 4, 4, 8, 8, 3, 8, 8, 8, 2, 8, 8, 3, 8, 4, 2
};

const byte ROWS = 4;
const byte COLS = 3;

const int buzzer = A3;

const int ledAbort = 5;
const int ledStage = A5;

const int buttonAbort = A4;
const int buttonStage = 4;

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
  pinMode(buzzer, OUTPUT);

  pinMode(ledAbort, OUTPUT);
  pinMode(ledStage, OUTPUT);

  pinMode(buttonAbort, INPUT_PULLUP);
  pinMode(buttonStage, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  Keyboard.begin();
  lcdShow("  JEB'S LAUNCH", " CONTROL SYSTEM");
  delay(3000);
  lcdShow("ALPHA BUILD 2.65", " STUDIO HORIZON");
  delay(3000);
  lcdShow("WELCOME, KERMAN.", "PRESS ANY KEY...");
  while (!keypad.getKey()) ;  // wait for key press
}

void loop() {
  static enum {START, MENU, SET_COUNT, COUNT_DOWN, LAUNCH, SET_THRUST, SET_WEIGHT, LAUNCH_CONFIRMED, LAUNCH_CONFIRMED_FN} state = START;
  static uint32_t last_second, preMillis;  // millis() value on last full second
  static int count;
  static float thrust, weight, ratio;

  char key = keypad.getKey();

  switch (state) {
    case START:  // transitional state
      lcdShow("1. LAUNCH SEQ.", "2. TWR CALC.");
      noTone(buzzer);
      state = MENU;
    /* fallthrough */

    case MENU:
      if (key == '1') {  // Countdown
        lcdShow("COUNTDOWN TIMER", "SECONDS: ");
        count = 0;
        state = SET_COUNT;
      } else if (key == '2') {  // TWR
        lcdShow("TWR CALCULATOR", "THRUST: ");
        thrust = 0, weight = 0, ratio = 0;
        state = SET_THRUST;
      }
      break;

    case SET_COUNT:
      if (key >= '0' && key <= '9' && count <= 99) {
        lcd.print(key);
        count = 10 * count + (key - '0');
      } else if (key == '#') {
        lcdShow("    T-MINUS", "     SECONDS");
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
        if (count <= 10) {
          tone(buzzer, 500);
          delay(500);
          noTone(buzzer);
        }
        if (count == 0) {
          Serial.println("Lift off!");
        } else if (count < 0) {
          preMillis = millis() - 500;
          state = LAUNCH;
        }
        lcd.setCursor(1, 1);
        lcd.print(count < 10 ? "  " : count < 100 ? " " : ""); // pad
        lcd.print(count);
      } else if (key == '*') {
        state = START;
      }
      break;

    case LAUNCH:
      tone(buzzer, 3000);
      if (millis() - preMillis >= 500) {
        preMillis += 500;
        if (digitalRead(ledAbort) == LOW && digitalRead(ledStage) == LOW) {
          lcdShow(" T-ZERO WARNING", "CONFIRM IGNITION");
          digitalWrite(ledAbort, HIGH);
          digitalWrite(ledStage, HIGH);
        } else if (digitalRead(ledAbort) == HIGH && digitalRead(ledStage) == HIGH) {
          lcd.clear();
          digitalWrite(ledAbort, LOW);
          digitalWrite(ledStage, LOW);
        }
      } else if (key == '*' || (digitalRead(buttonAbort == HIGH) && digitalRead(buttonStage) == LOW)) {
        lcdShow("LAUNCH ABORT", "SELECTED");
        digitalWrite(ledAbort, HIGH);
        digitalWrite(ledStage, LOW);
        delay(2000);
        digitalWrite(ledAbort, LOW);
        state = START;
      } else if (key == '#' || (digitalRead(buttonStage == HIGH) && digitalRead(buttonAbort) == LOW)) {
        lcdShow("KERBIN, WE ARE", "GO FOR LAUNCH!");
        digitalWrite(ledAbort, LOW);
        digitalWrite(ledStage, HIGH);
        delay(2000);
        digitalWrite(ledStage, LOW);
        state = LAUNCH_CONFIRMED;
      }
      break;

    case SET_THRUST:
      if (key >= '0' && key <= '9' && thrust <= 9999) {
        lcd.print(key);
        thrust = 10 * thrust + (key - '0');
      } else if (key == '#') {
        lcdShow("TWR CALCULATOR", "WEIGHT: ");
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
        lcdShow("THRUST-TO-WEIGHT", "RATIO: ");
        if (thrust != 0 || weight != 0) {
          ratio = thrust / weight;
          lcdShowResult(ratio);
        }
      } else if (key == '*') {
        state = START;
      }
      break;

    case LAUNCH_CONFIRMED:
      lcdShow("KRAKEN BLESS", "AMERIKA!!!!!!!!!");
      // Keyboard.print();
      for (int thisNote = 0; thisNote < 101; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(buzzer, melody[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.40;
        delay(pauseBetweenNotes);
        noTone(buzzer);
      }
      Serial.print("FUCK");
      lcdShow("PRESS *", "TO PAY RESPECTS");
      state = LAUNCH_CONFIRMED_FN;
    /* fallthrough */

    case LAUNCH_CONFIRMED_FN:
      if (key == '*') {
        state = START;
      }
      break;
  }
}
