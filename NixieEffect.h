#pragma once
#include "NixieDisplay.h"

namespace Nixie {

  template <class Model>
  class Effect {
  public:
    void setDisplay(Display<Model> *display);
    inline void setDriver(uint8_t value);
    inline void setAnode(uint8_t tube, bool enabled);
    inline void updateTube(uint8_t tube, uint8_t tick, uint8_t progress);
  public:
    virtual void perform(uint8_t tube, uint8_t tick, uint8_t progress) = 0;
  protected:
    Display<Model> *display;
    uint8_t current_tube;
  };

  enum {
    OLD_DIGIT = 20,
    NEW_DIGIT = 21
  };

  template <class Model>
  inline void Effect<Model>::setDisplay(Display<Model> *display) {
    this->display = display;
  }

  template <class Model>
  inline void Effect<Model>::setDriver(uint8_t value) {
    if (value == OLD_DIGIT)
      display->setDriver(display->prevdigits[current_tube]);
    else if (value == NEW_DIGIT)
      display->setDriver(display->digits[current_tube]);
    else
      display->setDriver(value);
  }

  template <class Model>
  inline void Effect<Model>::setAnode(uint8_t tube, bool enabled) {
    display->setAnode(tube, enabled);
  }

  template <class Model>
  inline void Effect<Model>::updateTube(uint8_t tube, uint8_t tick, uint8_t progress) {
    current_tube = tube;
    perform(tube, tick, progress);
  }
  
}
