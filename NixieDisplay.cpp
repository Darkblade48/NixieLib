#include "NixieDisplay.h"
#include "NixieEffect.h"

namespace Nixie {

  static void (*timer_handler)();
  void startTimer1(void (*handler)()) {
    timer_handler = handler;
    TCCR1A = _BV(COM1A0) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10); // Fast PWM mode - compare to OCR1A
    TCCR1B = _BV(WGM12) | _BV(CS10); // No prescalar
    OCR1A = 1;
    TIMSK1 |= _BV(OCIE1A);
  }
  
}

SIGNAL(TIMER1_COMPA_vect) {
  Nixie::timer_handler();
}
