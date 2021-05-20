
#include <LiquidCrystal.h>

#include <EEPROM.h>

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

struct Savetime {
  int minutesS;
  float secondsS;
};

float seconds;
long mil;
int minutes = 0;
float time;
int sub;
float a = millis();
float c;
int eeAddress = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  Serial.begin(9600);

  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
  pinMode(9, INPUT);
  digitalWrite(9, HIGH);
  pinMode(10, INPUT);
  digitalWrite(10, HIGH);
  pinMode(11, INPUT);
  digitalWrite(11, HIGH);
}

void loop() {
  minutes = 0;
  seconds = 0;
  mil = 0;
  time = 0;
  sub = 0;
  lcd.clear();
  lcd.print("press start/read");
  delay(250);
  if (digitalRead(11) == LOW) {
    while (digitalRead(8) == HIGH) {
      Savetime customVar;
      EEPROM.get(eeAddress, customVar);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Saved Time:");
      lcd.setCursor(0, 1);
      if (customVar.minutesS < 10) {
        lcd.print("0");
      }
      lcd.print(customVar.minutesS);
      lcd.print(":");
      if (customVar.secondsS < 10) {
        lcd.print("0");
      }
      lcd.print(customVar.secondsS);
      delay(100);
    }
  }

  if (digitalRead(8) == LOW) {

    lcd.clear();
    a = millis();
    while (digitalRead(9) == HIGH) {

      c = millis();
      time = (c - a) / 1000;



      seconds = time - sub;
      if (seconds > 60) {
        sub = sub + 60;
        minutes++;
      }

      if (minutes < 10) {
        lcd.print("0");
      }
      lcd.print(minutes);
      lcd.print(":");
      if (seconds < 10) {
        lcd.print("0");
      }
      lcd.print(seconds);
      lcd.setCursor(0, 0);
      delay(100);
    }

    if (digitalRead(9) == LOW) {
      while (digitalRead(8) == HIGH) {
        lcd.clear();
        if (minutes < 10) {
          lcd.print("0");
        }
        lcd.print(minutes);
        lcd.print(":");
        if (seconds < 10) {
          lcd.print("0");
        }
        lcd.print(seconds);
        lcd.setCursor(0, 1);
        lcd.print("Save, Yes or NO: ");
        delay(100);
        if (digitalRead(10) == LOW) {
          while (digitalRead(8) == HIGH){
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Yes");
            lcd.setCursor(0, 1);
            if (minutes < 10) {
                lcd.print("0");
            }
            lcd.print(minutes);
            lcd.print(":");
            if (seconds < 10) {
              lcd.print("0");
            }
            lcd.print(seconds);
            delay(100);
          }
          Savetime customVar = {
              minutes,
              seconds,
            };
          EEPROM.put(eeAddress, customVar);
        }
      }
    }
  }
}
