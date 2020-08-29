#pragma once
#include "NixieEffect.h"

namespace Nixie {

  template <class Model>
  class Effect_SlotMachine : public Effect<Model> {
  public:
    void perform(uint8_t tube, uint8_t tick, uint8_t progress) {
      if (progress < 10)
        digitchangeprogress[tube] = 0;
      else if (progress > MAX_PROGRESS-10)
        this->setDriver(NEW_DIGIT);
      else {
        if (progress > digitchangeprogress[tube]) {
          slot[tube] = (slot[tube] + rand()%9 + 1) % 10;
          digitchangeprogress[tube] += 10;
        }
        this->setDriver(slot[tube]);
      }
      this->setAnode(tube, true);
    }
  private:
    uint8_t slot[Model::TUBES];
    uint8_t digitchangeprogress[Model::TUBES];
  };
  
}
