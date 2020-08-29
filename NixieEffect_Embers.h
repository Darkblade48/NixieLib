#pragma once
#include "NixieEffect.h"

namespace Nixie {

  template <class Model>
  class Effect_Embers : public Effect<Model> {
    uint8_t emberglow[Model::TUBES];
    uint8_t delta[Model::TUBES];
    uint8_t skip;
  public:
    void perform(uint8_t tube, uint8_t tick, uint8_t progress) {
      this->setDriver(NEW_DIGIT);
      this->setAnode(tube, tick < (emberglow[tube] + 10));
      if (tube == 0 && tick==0) {
        skip = (skip+1) % 5;
      }
      if (tick == 0 && skip==0) {
        emberglow[tube] += delta[tube] - 5;
        emberglow[tube] %= 40;
        delta[tube] = rand() % 10;
      }
    }
  };
  
}
