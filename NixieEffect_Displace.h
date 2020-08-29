#pragma once
#include "NixieEffect.h"

namespace Nixie {

  template <class Model>
  class Effect_Displace : public Effect<Model> {
  public:
    void perform(uint8_t tube, uint8_t tick, uint8_t progress) {
      this->setDriver(progress>HALF_PROGRESS? NEW_DIGIT : OLD_DIGIT);
      this->setAnode(
        tube,
        //progress > NIXIE_HALF_PROGRESS? (tick > (progress - NIXIE_HALF_PROGRESS)/2) : ((tick >> 1) > progress)
        progress>HALF_PROGRESS || (tick>>1) > progress
      );
    }
  };
  
}
