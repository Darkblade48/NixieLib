#pragma once
#include <Arduino.h>
#include "NixieDefines.h"

namespace Nixie {
  
  class BoostConverter {
  public:
    BoostConverter()
      : desired_fb(0)
    {} 
    void setPins(pin_t pwm_pin, pin_t fb_pin);
    void setUnregulated();
    void begin(uint16_t feedback_desired_value);
    void end();
    void adjustVoltage();
    uint8_t getPWM() const { return min(255, max(0, pwm)); }
    void setDesiredFeedback(uint16_t feedback);
  private:
    bool regulated;
    int pwm;
    int desired_fb;
    pin_t pin_pwm, pin_fb;
  };

} // namespace Nixie