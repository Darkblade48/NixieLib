#pragma once

namespace Nixie {

  typedef uint8_t pin_t;
  enum {
    DIGIT_ON_TICKS = 25,
    DIGIT_OFF_TICKS = 9,
    DOTS_ON_TICKS = 1,
    DOTS_OFF_TICKS = 11,

    MAX_PROGRESS = DIGIT_ON_TICKS,
    HALF_PROGRESS = MAX_PROGRESS / 2,
    THIRD_PROGRESS = MAX_PROGRESS / 3,
    FOURTH_PROGRESS = MAX_PROGRESS / 4,

    SLOW_PROGRESS = 1,
    NORMAL_PROGRESS = 2,
    FAST_PROGRESS = 4,

    DIGIT_OFF = 10,
  };
  
}
