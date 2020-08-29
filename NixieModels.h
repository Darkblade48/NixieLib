#pragma once
#include "NixieDisplay.h"

namespace Nixie {

  struct Shield4IN14 {
    static const uint8_t TUBES = 4;
    static void initializeDisplay(Display<Shield4IN14> &d) {
      d.setAnodePin(0, 12);
      d.setAnodePin(1, 11);
      d.setAnodePin(2, 9);
      d.setAnodePin(3, 8);
      d.setDotsAnodePin(10);
      d.setDriverPins(4,6,7,5);
      d.setBoostPins(3, A0);
    }
  };

  struct Shield5IN14 {
    static const int TUBES = 5;
    static void initializeDisplay(Display<Shield5IN14> &d) {
      d.setAnodePin(0, 12);
      d.setAnodePin(1, 11);
      d.setAnodePin(2, 10);
      d.setAnodePin(3, 9);
      d.setAnodePin(4, 8);
      d.setDriverPins(4,6,7,5);
      d.setBoostPins(3, A0);
    }
  };

  struct Shield6IN14 {
    static const int TUBES = 6;
    static void initializeDisplay(Display<Shield6IN14> &d) {
      d.setAnodePin(0, 12);
      d.setAnodePin(1, 11);
      d.setAnodePin(2, 9);
      d.setAnodePin(3, 8);
      d.setAnodePin(4, A1);
      d.setAnodePin(5, A2);
      d.setDotsAnodePin(10);
      d.setDriverPins(4,6,7,5);
      d.setBoostPins(3, A0);
    }
  };

  struct Shield8IN14 {
    static const int TUBES = 8;
    static void initializeDisplay(Display<Shield8IN14> &d) {
      d.setAnodePin(0, 12);
      d.setAnodePin(1, 11);
      d.setAnodePin(2, 9);
      d.setAnodePin(3, 8);
      d.setAnodePin(4, A1);
      d.setAnodePin(5, A2);
      d.setAnodePin(6, 10);
      d.setAnodePin(7, 13);
      d.setDriverPins(4,6,7,5);
      d.setBoostPins(3, A0);
    }
  };

}
