#include <NixieLib.h>
NixieDisplay<Shield4IN14> Nixies;
void yield() { Nixies.adjustVoltage(); }
int num = 0;

void setup() {
  Serial.begin(115200);
  Nixies.begin(550);
}

void loop() {
  Nixies.setDigits(num++ % 10000);
  Nixies.setDots(num % 2);
  delay(100); // important! call delay() to adjust boost converter voltage
}
