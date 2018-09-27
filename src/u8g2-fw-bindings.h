

#ifndef ___FORTHWITH_U8G2_EXTRAS_H_
#define ___FORTHWITH_U8G2_EXTRAS_H_


void doDot();
int forth_bootstrap_u8g2();

#include "forthwith/_build/forthwith-consts.h"
#include "forthwith/_build/forthwith.h"

  // Define Primitives, including function bodies, etc
#define FORTH_DEFINE_HEADERS
#include "forthwith/src/xmacros.h"
#include "xmacros.u8g2.bindings.h"
#undef FORTH_DEFINE_HEADERS

#endif // _FORTHWITH_U8G2_EXTRAS_H_

