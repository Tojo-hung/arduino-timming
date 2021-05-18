
#include <LiquidCrystal.h>

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


long seconds;
long mil;
int minutes = 0;
long time;
int sub;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  Serial.begin(9600);

  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
  pinMode(9, INPUT);
  digitalWrite(9, HIGH);
}
float a = millis();
float c;

void loop() {
  minutes = 0;
  seconds = 0;
  mil = 0;
  time = 0;
  sub = 0;
  lcd.clear();
  lcd.print("press start");
  delay(100);

  if (digitalRead(8) == LOW) {

    lcd.clear();
    a = millis();
    while (digitalRead(9) == HIGH) {

      c = millis();
      time = (c - a);

      mil = time;

      while (mil > 1000) {
        mil = mil - 1000;
      };


      seconds = (time - mil)/1000 - sub;
      if (seconds > 59) {
        sub = sub + 60;
        minutes++;
      }

      if (minutes < 10){
        lcd.print("0");
      }
      lcd.print(minutes);
      lcd.print(":");
      if (seconds < 10){
          lcd.print("0");
        }
      lcd.print(seconds);
      lcd.print(".");
      lcd.print(mil);
      lcd.setCursor(0, 0);
      delay(100);
    }

    if (digitalRead(9) == LOW) {
      while (digitalRead(8) == HIGH) {
        if (minutes < 10){
          lcd.print("0");
        }
        lcd.print(minutes);
        lcd.print(":");
        if (seconds < 10){
          lcd.print("0");
        }
        lcd.print(seconds);
        lcd.print(".");
        lcd.print(mil);
        lcd.setCursor(0, 0);
        delay(100);
      }
}
}
}
