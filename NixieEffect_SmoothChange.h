#pragma once
#include "NixieEffect.h"

namespace Nixie {

  template <class Model>
  class Effect_SmoothChange : public Effect<Model> {
  public:
    void perform(uint8_t tube, uint8_t tick, uint8_t progress) {
      //setDriver(progress < HALF_PROGRESS? OLD_DIGIT : NEW_DIGIT);
      //setAnode(tube, progress < HALF_PROGRESS? (progress < (tick>>1)) : (progress-HALF_PROGRESS > (tick<<1)));
      this->setDriver(progress < HALF_PROGRESS? OLD_DIGIT : NEW_DIGIT);
      this->setAnode(tube, tick > (
        progress < HALF_PROGRESS?
            (progress << 2)
          : ((MAX_PROGRESS - progress) << 2)
      ));
    }
  };
  
}
