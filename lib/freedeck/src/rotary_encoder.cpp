/*
 * RotaryEncoderWithButton.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: Konstantin Gredeskoul
 *
 *  (c) 2014 All rights reserved.  Please see LICENSE.
 */

#include "rotary_encoder.hpp"
#include "settings.hpp"
#include "util.hpp"
#include <bsp/board.h>
#include <pico/stdlib.h>


void RotaryEncoder::update(bool encoder_a_state, bool encoder_b_state, bool button_state) {
    // Handle button state
    if (button_state != _lastButtonState) {
        _lastButtonState = button_state;
        if (button_state) {
            callOnButtonClick();
        }
    }

    // Handle encoder state
    if (encoder_a_state != _lastEncoderAState || encoder_b_state != _lastEncoderBState) {
        _lastEncoderAState = encoder_a_state;
        _lastEncoderBState = encoder_b_state;

        if (encoder_a_state && !encoder_b_state) {
            callOnTurnCw();
        } else if (!encoder_a_state && encoder_b_state) {
            callOnTurnCcw();
        }
    }
}


void RotaryEncoder::callOnButtonClick() {
  if (onButtonClick != NULL)
    onButtonClick(index, false);
}

void RotaryEncoder::callOnTurnCw() {
  if (onTurnCw != NULL)
    onTurnCw(index, false);
}

void RotaryEncoder::callOnTurnCcw() {
  if (onTurnCcw != NULL)
    onTurnCcw(index, false);
}
