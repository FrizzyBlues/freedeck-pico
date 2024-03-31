#pragma once
#define DEBUG 1

#define ROW_SIZE 128

#define BD_COUNT 2
#define CONFIG_NAME "config.bin"
#define CONFIG_NAME_TEMP "config.tmp"
#define CONFIG_NAME_OLD "config.bin.old"
#define LONG_PRESS_DURATION 250
#define PAGE_CHANGE_SERIAL_TIMEOUT 1500
// timeout in seconds (this is 5minutes)
// will be overwritten by the config
#define TIMEOUT_TIME 1L * 60L
// #define WAKE_ON_GET_PAGE_SERIAL // will wake up the displays everytime you focus another window
#define WAKE_ON_SET_PAGE_SERIAL // will only wake up the display if you focus a new window that has
                                // a configurator page

#define BUTTON_PIN 0
#define ENCODER_A_PIN 4
#define ENCODER_B_PIN 5

#define S0_PIN 12
#define S1_PIN 13
#define S2_PIN 14
#define S3_PIN 15

#define OLED_SDA 2
#define OLED_SCL 3
#define OLED_ADDRESS 0x3C

// for faster displays
//#define OLED_SPEED 120
// for slower displays
#define OLED_SPEED 50

// Change this value from 0x11 up to 0xff to reduce coil whine. different
// from display to display
#define PRE_CHARGE_PERIOD 0x11

// NOT IMPLEMENTED YET
// Minimum Brightness value for displays. If your displays image quality gets
// worse at lower brighness choose a bigger value here
// #define MINIMUM_BRIGHTNESS 0x20
// #define MINIMUM_BRIGHTNESS 0x00 //almost dark, good displays only
// #define MINIMUM_BRIGHTNESS 0x30 //brightest for cheap displays

// if your screen is flickering, choose a lower number. the worse the screen,
// the lower the number.
#define REFRESH_FREQUENCY 0xf2
// #define REFRESH_FREQUENCY 0xf1
// #define REFRESH_FREQUENCY 0xc1
// #define REFRESH_FREQUENCY 0x80

// SD card configuration
// for faster sdcards
// #define SD_MHZ 16
#define SD_MHZ 10
// for slower sdcards
// #define SD_MHZ 5
#define SD_SPI spi1
#define SD_MISO 8
#define SD_MOSI 11
#define SD_SCK 10
#define SD_CS 9
#define SD_DETECT 24 // leave this as 24 if you dont know what it means

#define OK "ok"
#define ERROR "error"
