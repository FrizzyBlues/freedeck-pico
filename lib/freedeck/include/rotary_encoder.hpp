#pragma once
#include <pico/stdlib.h>

#define ENCODER_A_STATE 0
#define ENCODER_B_STATE 1
#define BUTTON_STATE 2

typedef void (*CallbackType)(uint8_t index, uint8_t secondary);

class RotaryEncoder {
public:
  uint8_t index = 0;
  bool encoder_a_state = ENCODER_A_STATE;
  bool encoder_b_state = ENCODER_B_STATE;
  bool button_state = BUTTON_STATE;
  bool has_secondary = false;

  CallbackType onButtonClick;
  CallbackType onTurnCw;
  CallbackType onTurnCcw;

  void update(bool new_encoder_a_state, bool new_encoder_b_state, bool new_button_state);

private:
  bool _lastEncoderAState;
  bool _lastEncoderBState;
  bool _lastButtonState;

  void callOnButtonClick();
  void callOnTurnCw();
  void callOnTurnCcw();
};