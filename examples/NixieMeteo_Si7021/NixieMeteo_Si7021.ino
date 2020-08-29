#include <NixieLib.h>
#include <Adafruit_Si7021.h>
#include <FastLED.h>
enum { COLOR_COLD = 0x0000ff, COLOR_HOT = 0xff0000 };
CRGB leds[4];
Adafruit_Si7021 sensor;
NixieDisplay<Shield4IN14> Nixies;
void yield() { Nixies.adjustVoltage(); }

void setup() {
  Serial.begin(115200);
  Nixies.begin(550);
  FastLED.addLeds<WS2812B, 2, GRB>(leds, 4);
  if (!sensor.begin()) {
    Nixies.setDigits(9999);
    Serial.println(F("Can't initialize the sensor!"));
    while(1) delay(1);
  }
}

void loop() {
  float h = sensor.readHumidity();
  float t = sensor.readTemperature();
  if (!isnan(t) || !isnan(h)) {
    Nixies.setDigits(100*min(99, int(h)) + min(99, abs(int(t))));
    Nixies.setDots(t < 0);
    
    leds[0]=leds[1]=leds[2]=leds[3] = (t<0? COLOR_COLD : COLOR_HOT);
    FastLED.show(50);

    Serial.print(t); Serial.print(F("*C "));
    Serial.print(h); Serial.println(F("%"));
  }
  delay(1000); // important! call delay() to adjust boost converter voltage
}
