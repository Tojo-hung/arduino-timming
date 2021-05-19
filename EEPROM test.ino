#include <EEPROM.h>

struct Savetime{
  int minutes;
  float seconds;
};

Savetime customVar;

void setup(){

  int eeAddress = 1; //EEPROM address to start reading from

  Serial.begin( 9600 );


  // get() can be used with custom structures too.
 //Move address to the next byte after float 'f'.
  EEPROM.get(eeAddress, customVar);

  Serial.print("Saved Time:");
  if (customVar.minutes < 10) {
   Serial.print("0");
  }
  Serial.print(customVar.minutes);
  Serial.print(":");
  if (customVar.seconds < 10) {
        Serial.print("0");
  }
  Serial.print(customVar.seconds);
}

void loop() {   /* Empty loop */ }