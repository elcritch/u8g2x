#include "u8g2_linux_i2c.h"


uint8_t u8x8_byte_linux_hw_i2c(u8x8_t *u8x8,
                               uint8_t msg,
                               uint8_t arg_int,
                               void *arg_ptr)
{
  gpio_pins_t *pins = u8x8_GetUserPtr(u8x8);

	uint8_t i = 0;

	static uint8_t buffer[128];
  static uint8_t buf_idx;

  uint8_t i2c_addr;
  struct i2c_msg msgs[4];

	switch(msg)
	{
		case U8X8_MSG_BYTE_INIT:
      if (i2c_open(&pins->devs.i2c, pins->device_name) < 0) {
        fprintf(stderr, "i2c_open(): %s\n", i2c_errmsg(&pins->devs.i2c));
        return 0;
      }
			break;

		case U8X8_MSG_BYTE_SET_DC:
			break;

		case U8X8_MSG_BYTE_START_TRANSFER:
      i2c_addr = u8x8_GetI2CAddress(u8x8) >> 1;
			buf_idx = 0;
			break;

    case U8X8_MSG_BYTE_SEND:
      uint8_t *data = (uint8_t *)arg_ptr;

      while( arg_int > 0 ) {
        buffer[buf_idx++] = *data;
        data++;
        arg_int--;
      }
      break;

		case U8X8_MSG_BYTE_END_TRANSFER:
      struct i2c_msg msgs[2] = {
        { .addr = i2c_addr, .flags = 0, .len = buf_idx, .buf = data },
      };

      /* Transfer a transaction with two I2C messages */
      if (i2c_transfer(&pins->devs.i2c, msgs, 2) < 0) {
        fprintf(stderr, "i2c_transfer(): %s\n", i2c_errmsg(&pins->devs.i2c));
        return 0;
      }

			break;

		default:
			return 0;
	}
	return 1;
}


