#include "NixieBoostConverter.h"
#include <util/atomic.h>
#define VOLTAGE_DELTA 5
#define MAX_PWM 243

namespace Nixie {

  void BoostConverter::setPins(pin_t pwm_pin, pin_t fb_pin) {
    pin_pwm = pwm_pin;
    pin_fb = fb_pin;
    regulated = true;
  }

  void BoostConverter::setUnregulated() {
    regulated = false;
  }

  void BoostConverter::begin(uint16_t feedback_desired_value = 0) {
    if (regulated) {
      pwm = 1;
      desired_fb = feedback_desired_value;
    }
    else {
      pwm = feedback_desired_value;
    }
    pinMode(pin_pwm, OUTPUT);
    TCCR2B = TCCR2B & 0b11111000 | 0x01;
    analogWrite(pin_pwm, pwm);
  }

  void BoostConverter::end() {
    analogWrite(pin_pwm, 0);
  }

  void BoostConverter::adjustVoltage() {
    if (!regulated) return;
    int dfb;
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
      dfb = desired_fb;
    }

    if (dfb == 0) return; // not started yet
    int feedback = analogRead(pin_fb);
    int oldpwm = pwm;
    if (feedback == 0 || feedback > 1000) {
      // it seems something's wrong with feedback
      pwm = 0;
    }
    else if (feedback < dfb-VOLTAGE_DELTA) {
      pwm += 7;
    }
    else if (feedback > dfb+VOLTAGE_DELTA) {
      pwm -= 7;
    }
    if (oldpwm != pwm) {
      pwm = min(MAX_PWM, max(1, pwm));
      analogWrite(pin_pwm, pwm);
    }
  }

  void BoostConverter::setDesiredFeedback(uint16_t fb) {
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
      desired_fb = fb;
    }
  }

}
