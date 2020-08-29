#pragma once
#include <Arduino.h>
#include <util/atomic.h>
#include "NixieDefines.h"
#include "NixieBoostConverter.h"
#include "utils.h"

namespace Nixie {

  template <class Model>
  class Effect;

  template <class Model>
  class Display {
    friend class Effect<Model>;
  public:
    typedef Model MODEL;
    Display();
    ~Display() {} // NOT virtual to save some RAM
    void setAnodePin(uint8_t idx, pin_t pin);
    void setDotsAnodePin(pin_t pin);
    void setDriverPins(pin_t a, pin_t b, pin_t c, pin_t d);
    void setBoostPins(pin_t pwm, pin_t fb) { boostcvt.setPins(pwm, fb); }
    void setBoostUnregulated() { boostcvt.setUnregulated(); }
    void setBoostFeedback(uint16_t fb) { boostcvt.setDesiredFeedback(fb); }
    void begin(int boost_required_feedback);
    void end();
    void setEffect(Effect<Model> *e);
    void setProgressSpeed(uint8_t speed) { progress_speed = speed; }
    void setDigits(uint_for_tubes<Model::TUBES> number);
    uint_for_tubes<Model::TUBES> getDigits() const;
    void setDigit(uint8_t idx, uint8_t digit);
    uint8_t getDigit(uint8_t idx) const { return digits[reverse_order(idx)]; }
    void setDots(bool enabled) { dots = enabled; }
    bool getDots() const { return dots; }
    void enableDigit(uint8_t idx, bool enable=true) { digit_enabled[reverse_order(idx)] = enable; }
    bool isDigitEnabled(uint8_t idx) { return digit_enabled[reverse_order(idx)]; }
    void adjustVoltage();
    uint8_t getPWM() const { return boostcvt.getPWM(); }
  protected:
    uint8_t reverse_order(uint8_t idx) const {
      return Model::TUBES-idx-1;
    }
    __attribute__((always_inline)) void setAnode(uint8_t index, bool enabled) {
      digitalWrite(anode_pins[index], enabled && digit_enabled[index]);    
    }
    __attribute__((always_inline)) void setDriver(uint8_t v) {
      if (v < 10) {
        digitalWrite(drv_a_pin, v&0b0001);
        digitalWrite(drv_b_pin, v&0b0010);
        digitalWrite(drv_c_pin, v&0b0100);
        digitalWrite(drv_d_pin, v&0b1000);
      }    
    }
    __attribute__((always_inline)) void setAnodeDots(bool enabled) {
      digitalWrite(anode_dots_pin, enabled);    
    }
  protected:
    pin_t anode_pins[Model::TUBES], anode_dots_pin;
    bool digit_enabled[Model::TUBES];
    pin_t drv_a_pin, drv_b_pin, drv_c_pin, drv_d_pin;
    uint8_t digits[Model::TUBES];
    uint8_t prevdigits[Model::TUBES];
    uint8_t progress[Model::TUBES+1];
    bool dots;
    uint8_t tick, tube;
    Effect<Model> *effect;
    uint8_t progress_speed;
    BoostConverter boostcvt;
    bool started;
    bool dots_present;
  private:
    static Display<Model> *instance;
    void update();
    void default_effect(uint8_t tube, uint8_t tick, uint8_t progress);
  };

  void startTimer1(void (*handler)());

  template <class Model>
  void Display<Model>::adjustVoltage() {
    if (started)
      boostcvt.adjustVoltage();
  }

  template <class Model>
  void Display<Model>::setEffect(Effect<Model> *e) {
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
      effect = e;
      e->setDisplay(this);
    }
  }

  template <class Model>
  Display<Model>::Display()
    : progress_speed(NORMAL_PROGRESS),
      effect(nullptr),
      dots_present(false),
      started(false)
  {
    Model::initializeDisplay(*this);
  }

  template <class Model>
  void Display<Model>::setDigits(uint_for_tubes<Model::TUBES> number) {
    for(uint8_t i=0; i<Model::TUBES; ++i) {
      setDigit(i, number%10);
      number /= 10;
    }
  }

  template <class Model>
  uint_for_tubes<Model::TUBES> Display<Model>::getDigits() const {
    uint_for_tubes<Model::TUBES> res = getDigit(0);
    uint_for_tubes<Model::TUBES> coeff = 10;
    for(uint8_t i=1; i<Model::TUBES; ++i) {
      res += getDigit(i)*coeff;
      coeff *= 10;
    }
    return res;
  }

  template <class Model>
  void Display<Model>::setDigit(uint8_t i, uint8_t digit) {
    uint8_t idx = reverse_order(i);
    if (digit != digits[idx]) {
      progress[idx] = 0;
      prevdigits[idx] = digits[idx];
      digits[idx] = digit;
    }
  }

  template <class Model>
  void Display<Model>::setAnodePin(uint8_t anode_idx, pin_t pin) {
    anode_pins[anode_idx] = pin;
  }

  template <class Model>
  void Display<Model>::setDotsAnodePin(pin_t pin) {
    anode_dots_pin = pin;
    dots_present = true;
  }

  template <class Model>
  void Display<Model>::setDriverPins(pin_t drv_a, pin_t drv_b, pin_t drv_c, pin_t drv_d) {
    drv_a_pin = drv_a;
    drv_b_pin = drv_b;
    drv_c_pin = drv_c;
    drv_d_pin = drv_d;
  }

  template <class Model>
  void Display<Model>::begin(int boost_required_feedback) {
    if (started) return;
    tick = 0;
    tube = 0;
    pinMode(drv_a_pin, OUTPUT);
    pinMode(drv_b_pin, OUTPUT);
    pinMode(drv_c_pin, OUTPUT);
    pinMode(drv_d_pin, OUTPUT);
    if (dots_present) pinMode(anode_dots_pin, OUTPUT);
    for(int i=0; i<Model::TUBES; ++i)
      pinMode(anode_pins[i], OUTPUT);
    for(uint8_t i=0; i<Model::TUBES; ++i) {
      digits[i] = 0;
      prevdigits[i] = 0;
      progress[i] = 0;
      digit_enabled[i] = true;
    }
    boostcvt.begin(boost_required_feedback);
    instance = this;
    startTimer1([]() {
      Display<Model>::instance->update();
    });
    started = true;
  }

  template <class Model>
  void Display<Model>::update() {
    ++tick;
    if (tick >= (
          tube == Model::TUBES?
              (DOTS_ON_TICKS + DOTS_OFF_TICKS)
            : (DIGIT_ON_TICKS + DIGIT_OFF_TICKS)
       ))
    {
      tube = (tube + 1) % (Model::TUBES+(dots_present? 1 : 0));
      tick = 0;
      if (progress[tube] < MAX_PROGRESS)
        progress[tube] += progress_speed;
    }
    if (tube == Model::TUBES && dots_present)
      setAnodeDots(dots && tick < DOTS_ON_TICKS);
    if (tube != Model::TUBES) {
      if (tick < DIGIT_ON_TICKS) {
        if (effect)
          effect->updateTube(tube, tick, progress[tube]);
        else
          default_effect(tube, tick, progress[tube]);
      }
      else {
        setAnode(tube, false);
      }
    }
  }

  template <class Model>
  void Display<Model>::default_effect(uint8_t tube, uint8_t tick, uint8_t progress) {
    setDriver(digits[tube]);
    setAnode(tube, true);
  }

  template <class Model>
  Display<Model> *Display<Model>::instance = nullptr;
}
