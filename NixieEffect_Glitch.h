#pragma once
#include "NixieEffect.h"

namespace Nixie {

  template <class Model>
  class Effect_Glitch : public Effect<Model> {
  public:
    uint8_t glitch_enabled[Model::TUBES];
  public:
    void perform(uint8_t tube, uint8_t tick, uint8_t progress) {
      this->setDriver(NEW_DIGIT);
      this->setAnode(tube, !(glitch_enabled[tube] && rand()%10 < 9));
      if (tick == 0) {
        if (glitch_enabled[tube])
          --glitch_enabled[tube];
        else if (rand() % 400 == 1)
          glitch_enabled[tube] = rand()%100+20;
      }
    }
  };
  
}
