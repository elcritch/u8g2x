

#ifndef ___FORTHWITH_CORTEX_EXTRAS_H_
#define ___FORTHWITH_CORTEX_EXTRAS_H_


/* #ifdef __cplusplus */
extern "C" {
/* #endif */

  void domicros();
  void domillis();
  void dopinmode();
  int forth_cortex_bootstrap();

#include "forthwith-cortex.h"

  // Define Primitives, including function bodies, etc
#define FORTH_DEFINE_HEADERS
#include "../forthwith/src/xmacros.h"
#include "../impl/xmacros.cortex-extras.h"
#undef FORTH_DEFINE_HEADERS



/* #ifdef __cplusplus */
}
/* #endif */


#endif // _FORTHWITH_CORTEX_EXTRAS_H_

