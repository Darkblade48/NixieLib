#include <NixieLib.h>

struct Clock4IN12 {
  static const int TUBES = 4;
  static void initializeDisplay(NixieDisplay<Clock4IN12> &d) {
    d.setAnodePin(0, 2);
    d.setAnodePin(1, 4);
    d.setAnodePin(2, 10);
    d.setAnodePin(3, 11);
    d.setDotsAnodePin(12);
    d.setDriverPins(6,7,8,9);
    d.setBoostPins(3, A7);
  }
};
NixieDisplay<Clock4IN12> Nixies;
void yield() { Nixies.adjustVoltage(); }

void setup() {
  Nixies.begin(400);
}

void loop() {
  delay(300);
  Nixies.setDigits(rand()%10000);
  Nixies.setDots(rand()%2);
}
