#pragma once
#include "NixieEffect.h"

namespace Nixie {

  template <class Model>
  class Effect_Crossfade : public Effect<Model> {
  public:
    void perform(uint8_t tube, uint8_t tick, uint8_t progress) {
      this->setDriver(tick < progress? NEW_DIGIT : OLD_DIGIT);
      this->setAnode(tube, true);
    }
  };
  
}
