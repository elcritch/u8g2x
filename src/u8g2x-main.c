
#include "u8g2-linux/u8g2_linux_impl.h"
#include "u8g2-fw-bindings.h"

#include <stdio.h>


#define DISPLAY_DC 48
#define DISPLAY_CS 51
#define DISPLAY_RESET 50

#define SPI_DEVICE "spidev1.0"

typedef void (*user_cb_t)();
extern user_cb_t *user_calls;

u8g2_t display_u8g2;
gpio_pins_t display_pins;

void clear_buffer(char *buf, uint8_t sz) {
  for (i = 0; i < sz; i++)
      buf[i] = 0;
}

void InitDisplay() {
	u8g2_InitDisplay(&display_u8g2);
}
void SetPowerSave() {
  fcell_t n = forth_pop();
	u8g2_SetPowerSave(&display_u8g2, n);
}
void ClearBuffer() {
	/* full buffer example, setup procedure ends in _f */
	u8g2_ClearBuffer(&display_u8g2);
}
void SetFont() {
  uint8_t font = forth_pop();
	u8g2_SetFont(&display_u8g2, font);
}
void DrawStr() {
  int16_t y = (int16_t)forth_pop();
  int16_t x = (int16_t)forth_pop();
  fcell_t strcnt = forth_pop();

  const int sz = 256;
  char msg[sz];
  clear_buffer(msg, sz);

  for (int i = 0; i < strcnt; i++)
    msg[i] = (uint8_t) forth_pop();

	u8g2_DrawStr(&display_u8g2, x, y, msg);
}
void SendBuffer() {
	u8g2_SendBuffer(&display_u8g2);
}
void DrawGlyph() {
  fcell_t y = forth_pop();
  fcell_t x = forth_pop();
  fcell_t glyph = forth_pop();

	u8g2_DrawGlyph(&display_u8g2, x, y, glyph);
}

user_cb_t u8g2_bindings[] = {
  ClearBuffer,
  DrawGlyph,
  DrawStr,
  InitDisplay,
  SendBuffer,
  SetFont,
  SetPowerSave,
};

int main(void)
{
  user_calls = &u8g2_bindings[0];

  // Setup
  u8g2_SetUserPtr(&display_u8g2, &display_pins);

  display_pins.dc = DISPLAY_DC;
  display_pins.reset = DISPLAY_RESET;
  display_pins.cs = DISPLAY_CS;
  display_pins.device_name = "/dev/spidev1.0";

  u8g2_cb_t *rotation = U8G2_R0;

  u8x8_msg_cb byte_cb = u8x8_byte_linux_hw_spi;
  u8x8_msg_cb gpio_and_delay_cb = u8x8_linux_gpio_and_delay;
  u8g2_Setup_ssd1322_nhd_128x64_f(&display_u8g2, rotation, byte_cb, gpio_and_delay_cb);

  // Run
	/* u8g2_InitDisplay(&display_u8g2); */
	u8g2_SetPowerSave(&display_u8g2, 0);

	/* /\* full buffer example, setup procedure ends in _f *\/ */
	/* u8g2_ClearBuffer(&display_u8g2); */
	/* u8g2_SetFont(&display_u8g2, u8g2_font_ncenB08_tr); */
	/* u8g2_DrawStr(&display_u8g2, 1, 18, "U8g2 on nerves"); */
	/* u8g2_SendBuffer(&display_u8g2); */

	/* u8g2_SetFont(&display_u8g2, u8g2_font_unifont_t_symbols); */
	/* u8g2_DrawGlyph(&display_u8g2, 112, 56, 0x2603 ); */
	/* u8g2_SendBuffer(&display_u8g2); */

	/* printf("Initialized ...\n"); */

	/* while  (1){ */
	/* } */

  forth_init();
  forth_bootstrap();

  const int buff_sz = 1024;
  char *rx_buff = calloc(1, buff_sz);
  char *tx_buff = calloc(1, buff_sz);

  prompt_init((char*)rx_buff, buff_sz, (char*)tx_buff, buff_sz);

  prompt_load_core();

  int prompt_read = 1;
  for (;;) {
    prompt_read = prompt_do(prompt_read);
  }

}
