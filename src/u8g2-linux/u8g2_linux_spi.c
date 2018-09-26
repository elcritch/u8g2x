#include <periphery/gpio.h>
#include "u8g2_linux_impl.h"

uint8_t u8x8_byte_linux_hw_spi(u8x8_t *u8x8,
                               uint8_t msg,
                               uint8_t arg_int,
                               void *arg_ptr)
{
  gpio_pins_t *pins = u8x8_GetUserPtr(u8x8);
  uint8_t spi_mode = u8x8->display_info->spi_mode;
  uint32_t spi_clock_hz = u8x8->display_info->sck_clock_hz;

  switch(msg) {
    case U8X8_MSG_BYTE_INIT:
      u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);

      /* Open spidev1.0 with mode 0 and max speed 1MHz */
      if (spi_open(&pins->devs.spi, pins->device_name, spi_mode, spi_clock_hz) < 0) {
        fprintf(stderr, "spi_open('%s'): %s\n",
                pins->device_name, spi_errmsg(&pins->devs.spi));
        return 0;
      } else {
        char str_msg[256];
        spi_tostring(&pins->devs.spi, str_msg, 256);
        fprintf(stderr, "spi_open: %s\n", str_msg);
      }

      if (spi_set_bit_order(&pins->devs.spi, MSB_FIRST) < 0) {
        fprintf(stderr, "spi_set_bit_order(): %s\n",
                spi_errmsg(&pins->devs.spi));
      }


      break;

    case U8X8_MSG_BYTE_SET_DC:
      u8x8_gpio_SetDC(u8x8, arg_int);
      break;

    case U8X8_MSG_BYTE_START_TRANSFER:
      /* SPI mode has to be mapped to the mode of the current controller, */
      u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);

      u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);
      u8x8->gpio_and_delay_cb(u8x8,
                              U8X8_MSG_DELAY_NANO,
                              u8x8->display_info->post_chip_enable_wait_ns,
                              NULL);

      break;

    case U8X8_MSG_BYTE_SEND:
      // Send SPI Data
      /* fprintf(stderr, "spi_transfer: size: %u ptr: %p\n", arg_int, arg_ptr); */

      if (spi_transfer(&pins->devs.spi, (uint8_t *)arg_ptr, NULL, arg_int) < 0) {
        fprintf(stderr, "spi_transfer(): %s\n", spi_errmsg(&pins->devs.spi));
        return 0;
      }
      break;

    case U8X8_MSG_BYTE_END_TRANSFER:
      fprintf(stderr, "spi_end_transfer: size: %u ptr: %p\n", arg_int, arg_ptr);
      u8x8->gpio_and_delay_cb(u8x8,
                              U8X8_MSG_DELAY_NANO,
                              u8x8->display_info->pre_chip_disable_wait_ns,
                              NULL);
      u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
      break;

    default:
      return 0;
  }

  return 1;

}

