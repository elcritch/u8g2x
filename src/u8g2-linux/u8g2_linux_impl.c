#include <periphery/gpio.h>
#include "u8g2_linux_impl.h"

void sleep_ms(unsigned long milliseconds)
{
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	nanosleep(&ts, NULL);
}

void sleep_us(unsigned long microseconds)
{
	struct timespec ts;
	ts.tv_sec = microseconds / 1000 / 1000;
	ts.tv_nsec = (microseconds % 1000000) * 1000;
	nanosleep(&ts, NULL);
}

void sleep_ns(unsigned long nanoseconds)
{
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = nanoseconds;
	nanosleep(&ts, NULL);
}

// Handles Various SPI & I2C Setups -- No support for 8Bit Pins
uint8_t u8x8_linux_gpio_and_delay(u8x8_t *u8x8,
                                  uint8_t msg,
                                  uint8_t arg_int,
                                  void *arg_ptr)
{
  gpio_pins_t *pins = u8x8_GetUserPtr(u8x8);
  char str_msg[256];

  switch(msg) {

    case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
      sleep_ns(arg_int);
      break;

    case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
      sleep_ns(arg_int * 100);
      break;

    case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
      sleep_us(arg_int * 10);
      break;

    case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
      sleep_ms(arg_int);
      break;

    case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8

      /* Open GPIO CS with output direction */
      if (pins->cs >= 0 && gpio_open(&pins->devs.cs, pins->cs, GPIO_DIR_OUT) < 0) {
        fprintf(stderr, "error: gpio_open(): %s\n", gpio_errmsg(&pins->devs.cs));
        return 0;
      } else {
        char str_msg[256];
        gpio_tostring(&pins->devs.cs, str_msg, 256);
        fprintf(stderr, "gpio_open(%s): %s\n", "CS", str_msg);
      }

      /* Open GPIO DC with output direction */
      if (pins->dc >= 0 && gpio_open(&pins->devs.dc, pins->dc, GPIO_DIR_OUT) < 0) {
        fprintf(stderr, "error: gpio_open(): %s\n", gpio_errmsg(&pins->devs.dc));
        return 0;
      } else {
        char str_msg[256];
        gpio_tostring(&pins->devs.dc, str_msg, 256);
        fprintf(stderr, "gpio_open(%s): %s\n", "DS", str_msg);
      }

      /* Open GPIO RESET with output direction */
      if (pins->reset >= 0 && gpio_open(&pins->devs.reset, pins->reset, GPIO_DIR_OUT) < 0) {
        fprintf(stderr, "error: gpio_open(): %s\n", gpio_errmsg(&pins->devs.reset));
        return 0;
      } else {
        char str_msg[256];
        gpio_tostring(&pins->devs.reset, str_msg, 256);
        fprintf(stderr, "gpio_open(%s): %s\n", "RESET", str_msg);
      }

      /* Open GPIO D0 with output direction */
      if (pins->d0 >= 0 && gpio_open(&pins->devs.d0, pins->d0, GPIO_DIR_OUT) < 0) {
        fprintf(stderr, "error: gpio_open(): %s\n", gpio_errmsg(&pins->devs.d0));
        return 0;
      } else {
        char str_msg[256];
        gpio_tostring(&pins->devs.d0, str_msg, 256);
        fprintf(stderr, "gpio_open(%s): %s\n", "D0", str_msg);
      }

      break;							// can be used to setup pins

    case U8X8_MSG_GPIO_D0:				// D0 or SPI clock pin: Output level in arg_int
      if (gpio_write(&pins->devs.d0, arg_int) >= 0)
        return 0;

    case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
      if (gpio_write(&pins->devs.cs, arg_int) >= 0)
        return 0;

    case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
      if (gpio_write(&pins->devs.dc, arg_int) >= 0)
        return 0;

    case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
      if (gpio_write(&pins->devs.reset, arg_int) >= 0)
        return 0;

    default:
      return 0;
  }

  return 1;
}

