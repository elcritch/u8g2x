
#include "u8g2-fw-bindings.h"
#include <stdio.h>
#include <string.h>

void doDot() {
  fcell_t n = forth_pop();

  char msg[128];
  int len;

  sprintf(msg, "%d", n);
  len = strlen(msg);

  write_str(len, msg);
}

void doDotDot() {
  fcell_t n = forth_pop();

  char msg[128];
  int len;

  sprintf(msg, "%X", n);
  len = strlen((char*)msg);

  write_str(len, msg);
}


