/*
   Jebediah's Launch Control System for Kerbal Space Program
   Alpha Build 0.70
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

int relay = 13;

int counter = 0;
int attempts = 0;
int max_attempts = 3;

String mymints;
int minutes = 0;

String mysecs;
int seconds = 0;
long int total_seconds = 0;
int secflag = 0;
int timer_started_flag = 0;

unsigned long previousMillis = 0;
unsigned long int previoussecs = 0;
unsigned long int currentsecs = 0;
unsigned long currentMillis = 0;
int interval = 1;
int tsecs = 0;

int timeV, thrustV, massV, gravityV;

byte rowPins[ROWS] = {12, 11, 10, 9};
byte colPins[COLS] = {8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

bool keyDetect = false;
bool menuKeyDetect = false;
bool goHomeDetect = false;

bool countDownDetect = false;
bool twrCalDetect = false;

String timeValue, thrustValue, massValue, gravityValue;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();

  Startup();

  timeV = constrain(timeV, 15, 120);
}

void loop() {
  PressKey();

  if (menuKeyDetect == true) {
    PressMenuKey();
  }

  if (goHomeDetect == true) {
    GoHome();
  }

  if (countDownDetect == true) {
    CountDownSequence();
  }
}

// Pages & Sections
void Startup() {
  lcd.print("Jeb's Launch");

  lcd.setCursor(0, 1);
  lcd.print("Control System");

  delay(3000);

  lcd.clear();
  lcd.print("Alpha Build 0.70");

  lcd.setCursor(0, 1);
  lcd.print(" STUDIO HORIZON");

  delay(3000);

  lcd.clear();
  lcd.print("Welcome, Kerman");

  lcd.setCursor(0, 1);
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
  // goHomeDetect = true;
  countDownDetect = true;
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
  if (key) {
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
  if (key == '1') {
    Serial.println(key);
    if (menuKeyDetect == true) {
      lcd.clear();
      CountDown();
      menuKeyDetect = false;
    }
  } else if (key == '2') {
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
  if (key == '*') {
    lcd.clear();
    ModeMenu();
  }
}

void CountDownSequence() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    counter = counter + 1;
    lcd.setCursor(counter, 1);
    lcd.print(key);
  }

  if (key == '1')
  {

    mymints = mymints + 1;
  }

  if (key == '2')
  {

    mymints = mymints + 2;
  }

  if (key == '3')
  {

    mymints = mymints + 3;
  }

  if (key == '4')
  {

    mymints = mymints + 4;
  }

  if (key == '5')
  {

    mymints = mymints + 5;
  }

  if (key == '6')
  {

    mymints = mymints + 6;
  }

  if (key == '7')
  {

    mymints = mymints + 7;
  }

  if (key == '8')
  {

    mymints = mymints + 8;
  }

  if (key == '9')
  {

    mymints = mymints + 9;
  }

  if (key == '0')
  {

    mymints = mymints + 0;
  }

  if (key == '#')
  {

    counter = 0;
    mymints = "";
    minutes = 0;
    mysecs = "";
    seconds = 0;
    secflag = 0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Minutes:");
  }


  if (key == '*')
  {
    lcd.clear();
    minutes = mymints.toInt();
    Serial.println(minutes);
    lcd.clear();
    lcd.print("Minutes: ");
    lcd.setCursor(0, 1);
    lcd.print(minutes);
    mymints = ""; // empty the string
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Seconds:");
    counter = 0;
    secflag = 1;

    while (secflag == 1)
    {
      forSeconds();
    }
  }

}

void forSeconds()
{
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    counter = counter + 1;
    lcd.setCursor(counter, 1);
    lcd.print(key);
  }

  if (key == '1')
  {

    mysecs = mysecs + 1;
  }

  if (key == '2')
  {

    mysecs = mysecs + 2;
  }

  if (key == '3')
  {

    mysecs = mysecs + 3;
  }

  if (key == '4')
  {

    mysecs = mysecs + 4;
  }

  if (key == '5')
  {

    mysecs = mysecs + 5;
  }

  if (key == '6')
  {

    mysecs = mysecs + 6;
  }

  if (key == '7')
  {

    mysecs = mysecs + 7;
  }

  if (key == '8')
  {

    mysecs = mysecs + 8;
  }

  if (key == '9')
  {

    mysecs = mysecs + 9;
  }

  if (key == '0')
  {

    mysecs = mysecs + 0;
  }

  if (key == '#')
  {

    counter = 0;
    mymints = "";
    minutes = 0;
    mysecs = "";
    seconds = 0;
    secflag = 0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Minutes:");
  }



  if (key == '*')
  {

    lcd.clear();
    seconds = mysecs.toInt();
    Serial.println(seconds);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Seconds: ");
    lcd.setCursor(0, 1);
    lcd.print(seconds);
    mysecs = ""; // empty the string
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);

    lcd.print("Mins      Secs");
    lcd.setCursor(1, 1);
    lcd.print(minutes);
    lcd.setCursor(10, 1);
    lcd.print(seconds);
    total_seconds = (minutes * 60) + seconds ;
    counter = 0;
    secflag = 0;
    timer_started_flag = 1;

    lcd.clear();
    lcd.print("T Seconds:");
    lcd.setCursor(11, 0);
    lcd.print( total_seconds );
    delay(3000);
    while ( timer_started_flag == 1)
    {
      char key = keypad.getKey();

      if (key) {
        Serial.println(key);
        counter = counter + 1;
        lcd.setCursor(counter, 1);

      }

      if (key == '#')
      {

        counter = 0;
        mymints = "";
        minutes = 0;
        mysecs = "";
        seconds = 0;
        secflag = 0;
        total_seconds = 0;
        timer_started_flag = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Minutes:");
      }

      //  lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("T Seconds:");
      lcd.setCursor(11, 0);
      lcd.print( total_seconds );
      lcd.setCursor(0, 1);
      if ( total_seconds > 0)
      {
        digitalWrite(relay, HIGH);
        lcd.print("load ON ");
      }

      if ( total_seconds <= 0)
      {
        total_seconds = 0;
        digitalWrite(relay, LOW);
        lcd.print("load OFF");
      }

      currentMillis = millis();
      currentsecs = currentMillis / 1000;
      if ((unsigned long)(currentsecs - previoussecs) >= interval) {
        total_seconds = total_seconds - 1;
        lcd.clear();
        previoussecs = currentsecs;
      }
    }
  }
}
