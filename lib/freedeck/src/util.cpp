#include "util.hpp"
#include "GFX.hpp"
#include "freedeck.hpp"
#include "init.hpp"
#include "settings.hpp"
#include <hardware/gpio.h>

#ifdef DEBUG
void o_debug(const char *message, uint display) {
  set_mux_address(display);
  oled[display]->clear();
  oled[display]->drawString(0, 0, message);
  oled[display]->display();
}
void o_debug(uint32_t number, uint display) {
  char tmp[10];
  sprintf(tmp, "%d", number);
  o_debug(tmp, display);
}
#else
void o_debug(const char *message, uint display) { (void *)message; }
#endif
int getBitValue(int number, int place) { return (number & (1 << place)) >> place; }

void set_mux_address(int address, uint8_t type) {
  int S0 = getBitValue(address, 0);
  gpio_put(S0_PIN, S0);

  int S1 = getBitValue(address, 1);
  gpio_put(S1_PIN, S1);

  int S2 = getBitValue(address, 2);
  gpio_put(S2_PIN, S2);

  int S3 = getBitValue(address, 3);
  gpio_put(S3_PIN, S3);

}
void set_mux_address(int address) { set_mux_address(address, TYPE_DISPLAY); }