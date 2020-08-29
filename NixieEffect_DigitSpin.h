#pragma once
#include "NixieEffect.h"

namespace Nixie {

  template <class Model>
  class Effect_DigitSpin: public Effect<Model> {
    uint8_t digit;
  public:
    void perform(uint8_t tube, uint8_t tick, uint8_t progress) {
      this->setDriver(progress < MAX_PROGRESS? (digit>>4) : NEW_DIGIT);
      digit = (digit + 1) % (10*(1<<4));
      this->setAnode(tube, true);
    }
  };
  
}
