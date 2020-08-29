#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <NixieLib.h>
#include <FastLED.h>
NixieDisplay<Shield4IN14> Nixies;
void yield() { Nixies.adjustVoltage(); }
NixieEffect_SlotMachine<Shield4IN14> effect;
CRGB leds[4] = { 0x3300cc, 0x3300cc, 0x3300cc, 0x3300cc };

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Nixies.begin(550);
  setSyncProvider(RTC.get);
  Nixies.setEffect(&effect);
  FastLED.addLeds<WS2812B, 2, GRB>(leds, 4);
}

void loop() {
  readRTC();
  checkKeys();
  FastLED.show(20);
  delay(50); // to adjust the voltage
}

void readRTC() {
  auto second_changed = []()->bool {
    static int sec = 0;
    if (sec == second()) return false;
    sec = second();
    return true;
  };
  static long rtc_new_sec_millis = 0;
  if (second_changed()) rtc_new_sec_millis = millis();
  Nixies.setDigits(hour()*100+minute());
  Nixies.setDots(millis()-rtc_new_sec_millis < 60);
}

void checkKeys() {
  if (analogRead(A3) < 800)
    displayDate();
}

void displayDate() {
  Nixies.setDots(1);
  Nixies.setDigits(month()*100 + day());
  delay(1000);
  Nixies.setDots(0);
  Nixies.setDigits(year());
  delay(1000);
}
