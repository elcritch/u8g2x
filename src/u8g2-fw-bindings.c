
#include "u8g2-extras.h"
#include "forthwith-cortex.h"

  // Define Primitives, including function bodies, etc
#define FORTH_DEFINE_PRIMITIVES
#include "../forthwith/src/xmacros.h"
#include "../impl/xmacros.cortex-extras.h"
#undef FORTH_DEFINE_PRIMITIVES

  void doDot() {
    fcell_t n = forth_pop();

    String s = String(n);

    write_str(s.length(), (char *)s.c_str());
  }


__fw_noinline__
int forth_bootstrap_u8g2() {

  #define FORTH_DEFINE_DICT_ENTRIES
  #include "xmacros.h"
  #include "xmacros.u8g2-extras.h"
  #undef FORTH_DEFINE_DICT_ENTRIES

  return FW_OK;
}


