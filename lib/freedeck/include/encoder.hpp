#pragma once
#include <pico/stdlib.h>

// Encoder state constants
#define ENCODER_TURN_CW 0
#define ENCODER_TURN_CCW 1

// Define a callback type for encoder turn events
typedef void (*EncoderCallbackType)(uint8_t direction);

class Encoder {
public:
    // Public member variables
    uint8_t index = 0;
    uint8_t pin_a = 0; // Pin connected to phase A of the encoder
    uint8_t pin_b = 0; // Pin connected to phase B of the encoder

    // Callback functions for encoder turn events
    // Callback functions for knob turn events
    EncoderCallbackType onCWCallback;
    EncoderCallbackType onCCWCallback;

    // Public member function to update the encoder state
    void update(bool new_state_a, bool new_state_b);

private:
    // Private member functions to handle encoder turn events
    void handleCW();
    void handleCCW();
};