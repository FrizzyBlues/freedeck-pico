#include "init.hpp"
#include "freedeck.hpp"
#include "logo.hpp"
#include "settings.hpp"
#include "util.hpp"
#include <f_util.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hw_config.h>
#include <sd_card.h>

void init_oleds(uint8_t oled_speed, uint8_t pre_charge_period, uint8_t refresh_frequency) {
  i2c_init(i2c1, oled_speed * 10000);         // make this afap
  gpio_set_function(OLED_SDA, GPIO_FUNC_I2C); // Use GPIO2 as I2C
  gpio_set_function(OLED_SCL, GPIO_FUNC_I2C); // Use GPIO3 as I2C
  gpio_pull_up(OLED_SDA);                     // Pull up GPIO2
  gpio_pull_up(OLED_SCL);                     // Pull up GPIO3

  for (int i = 0; i < BD_COUNT; i++) {
    oled[i] = new GFX(OLED_ADDRESS, size::W128xH64, i2c1); // Declare oled instance
    set_mux_address(i);
    oled[i]->init(pre_charge_period, refresh_frequency);
    i % 2 ? oled[i]->display(logo) : oled[i]->display(fdlogo);
  }
}

void init_sdcard() {
  pSD = sd_get_by_num(0);
  FRESULT fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
  if (FR_OK != fr) {
    o_debug("sdcard error 1");
    o_debug(FRESULT_str(fr), 1);
  }
  const char *const filename = CONFIG_NAME;
  fr = f_open(&fil, filename, FA_READ);
  if (FR_OK != fr && FR_EXIST != fr) {
    o_debug("sdcard error 2");
    o_debug(FRESULT_str(fr), 1);
  }
}

void init_button() {
  // button pin
  gpio_set_input_enabled(BUTTON_PIN, true);
  gpio_init(BUTTON_PIN);
  gpio_set_dir(BUTTON_PIN, GPIO_IN);
  gpio_pull_up(BUTTON_PIN);

  for (int i = 0; i < BD_COUNT; i++) {
    buttons[i].index = i;
    buttons[i].onPressCallback = on_button_press; // to do: only do this initially
    buttons[i].onReleaseCallback = on_button_release;
  }
}

void init_encoder_button() {
  // encoder button pin
  for (int i = 0; i < ENCODER_COUNT; i++) {
    uint8_t encoder_button_pin[] = ENCODER_BUTTON_PIN;
    gpio_set_input_enabled(encoder_button_pin[i], true);
    gpio_init(encoder_button_pin[i]);
    gpio_set_dir(encoder_button_pin[i], GPIO_IN);
    gpio_pull_up(encoder_button_pin[i]);
    encoder_buttons[i].index = i;
    encoder_buttons[i].onPressCallback = on_button_press;
    encoder_buttons[i].onReleaseCallback = on_button_release;
  }
}

void init_encoder_knob() {
  // Initialize encoder knob pins
  for (int i = 0; i < ENCODER_COUNT; i++) {
    // Get pins for phase A and B of the encoder knob
    uint8_t knob_pin_a[] = ENCODER_KNOB_PIN_A;
    uint8_t knob_pin_b[] = ENCODER_KNOB_PIN_B;
    
    // Set up phase A pin
    gpio_set_input_enabled(knob_pin_a[i], true);
    gpio_init(knob_pin_a[i]);
    gpio_set_dir(knob_pin_a[i], GPIO_IN);
    gpio_pull_up(knob_pin_a[i]);
    
    // Set up phase B pin (if needed)
    // Note: If your encoder knobs have separate pins for phase A and B, you'll need to set up both pins similarly
    gpio_set_input_enabled(knob_pin_b[i], true);
    gpio_init(knob_pin_b[i]);
    gpio_set_dir(knob_pin_b[i], GPIO_IN);
    gpio_pull_up(knob_pin_b[i]);
    
    // Initialize the corresponding encoder knob
    encoder_knobs[i].index = i;
    encoder_knobs[i].pin_a = knob_pin_a[i];
    encoder_knobs[i].pin_b = knob_pin_b[i]; // Uncomment and modify if phase B pin is used
    encoder_knobs[i].onCWCallback = on_knob_turn_cw; // Assign the callback function for knob turn events
    encoder_knobs[i].onCCWCallback = on_knob_turn_ccw;
  }
}

void init_mux() {
  // mux pin 1
  gpio_init(S0_PIN);
  gpio_set_dir(S0_PIN, GPIO_OUT);
  gpio_pull_down(S0_PIN);
  gpio_put(S0_PIN, 0);
#if BD_COUNT > 2
  // mux pin 2
  gpio_init(S1_PIN);
  gpio_set_dir(S1_PIN, GPIO_OUT);
  gpio_pull_down(S1_PIN);
  gpio_put(S1_PIN, 0);
#endif
#if BD_COUNT > 4
  // mux pin 3
  gpio_init(S2_PIN);
  gpio_set_dir(S2_PIN, GPIO_OUT);
  gpio_pull_down(S2_PIN);
  gpio_put(S2_PIN, 0);
#endif
#if BD_COUNT > 8
  // mux pin 4
  gpio_init(S3_PIN);
  gpio_set_dir(S3_PIN, GPIO_OUT);
  gpio_pull_down(S3_PIN);
  gpio_put(S3_PIN, 0);
#endif
}