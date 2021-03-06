#ifndef _U8G2_LINUX_IMPL_H_
#define _U8G2_LINUX_IMPL_H_

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

#include <periphery/spi.h>
#include <periphery/i2c.h>
#include <periphery/gpio.h>

#include <u8g2.h>

// Time
void sleep_ms(unsigned long milliseconds);
void sleep_us(unsigned long microseconds);
void sleep_ns(unsigned long nanoseconds);

// Devices Struct
struct gpio_devs {
  gpio_t cs;
  gpio_t dc;
  gpio_t reset;
  gpio_t d0;

  spi_t spi;
  i2c_t i2c;
};

struct gpio_pins {
  char *device_name;
  int32_t cs;
  int32_t dc;
  int32_t d0;
  int32_t reset;
  struct gpio_devs devs;
};
typedef struct gpio_pins gpio_pins_t;

// Linux Hardware
uint8_t u8x8_linux_gpio_and_delay(u8x8_t *u8x8,
                                  uint8_t msg,
                                  uint8_t arg_int,
                                  void *arg_ptr);

uint8_t u8x8_byte_linux_hw_i2c(u8x8_t *u8x8,
                               uint8_t msg,
                               uint8_t arg_int,
                               void *arg_ptr);


uint8_t u8x8_byte_linux_hw_spi(u8x8_t *u8x8,
                               uint8_t msg,
                               uint8_t arg_int,
                               void *arg_ptr);


#endif // _U8G2_LINUX_IMPL_H_
