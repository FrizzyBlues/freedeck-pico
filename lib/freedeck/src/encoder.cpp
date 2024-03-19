#include "encoder.hpp"
#include "settings.hpp"
#include "util.hpp"
#include <bsp/board.h>
#include <pico/stdlib.h>

void Encoder::update(bool new_state_a, bool new_state_b) {
    // Compare the new states of phase A and B with the current states
    // to determine the direction of the encoder turn

    // If the state of phase A or B has changed, a turn event has occurred
    if (new_state_a != state_a || new_state_b != state_b) {
        if (new_state_a == state_b) {
            // Phase A and B are in the same state, clockwise turn
            handleCW();
        } else {
            // Phase A and B are in different states, counterclockwise turn
            handleCCW();
        }
    }

    // Update the current states of phase A and B
    state_a = new_state_a;
    state_b = new_state_b;
}

void Encoder::handleCW() {
    // Call the callback function for clockwise turn event (if provided)
    if (onCWCallback != nullptr) {
        onCWCallback(index);
    }
}

void Encoder::handleCCW() {
    // Call the callback function for counterclockwise turn event (if provided)
    if (onCCWCallback != nullptr) {
        onCCWCallback(index);
    }
}
