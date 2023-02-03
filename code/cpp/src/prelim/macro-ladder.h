
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef MACRO_LADDER__H
#define MACRO_LADDER__H

#include "global-macros.h"


#define _TEMP_MACRO_LADDER_1(a1) _TEMP_MACRO_LADDER(1, a1)

#define _TEMP_MACRO_LADDER_2(a1, a2) \
  _TEMP_MACRO_LADDER(2, a2) _TEMP_MACRO_LADDER_1(a1)

#define _TEMP_MACRO_LADDER_3(a1, a2, a3) \
  _TEMP_MACRO_LADDER(3, a3) _TEMP_MACRO_LADDER_2(a1, a2)

#define _TEMP_MACRO_LADDER_4(a1, a2, a3, a4) \
  _TEMP_MACRO_LADDER(4, a4) _TEMP_MACRO_LADDER_3(a1, a2, a3)

#define _TEMP_MACRO_LADDER_5(a1, a2, a3, a4, a5) \
  _TEMP_MACRO_LADDER(5, a5) _TEMP_MACRO_LADDER_4(a1, a2, a3, a4)

#define _TEMP_MACRO_LADDER_6(a1, a2, a3, a4, a5, a6) \
  _TEMP_MACRO_LADDER(6, a6) _TEMP_MACRO_LADDER_5(a1, a2, a3, a4, a5)

#define _TEMP_MACRO_LADDER_7(a1, a2, a3, a4, a5, a6, a7) \
  _TEMP_MACRO_LADDER(7, a7) _TEMP_MACRO_LADDER_6(a1, a2, a3, a4, a5, a6)

#define _TEMP_MACRO_LADDER_8(a1, a2, a3, a4, a5, a6, a7, a8) \
  _TEMP_MACRO_LADDER(8, a8) _TEMP_MACRO_LADDER_7(a1, a2, a3, a4, a5, a6, a7)

#define _TEMP_MACRO_LADDER_9(a1, a2, a3, a4, a5, a6, a7, a8, a9) \
  _TEMP_MACRO_LADDER(9, a9) _TEMP_MACRO_LADDER_8(a1, a2, a3, a4, a5, a6, a7, a8)

#define _TEMP_MACRO_LADDER_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
  _TEMP_MACRO_LADDER(10, a10) _TEMP_MACRO_LADDER_9(a1, a2, a3, a4, a5, a6, a7, a8, a9)

#define TEMP_MACRO_LADDER(...) _preproc_CONCAT(_TEMP_MACRO_LADDER_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)




#endif  // MACRO_LADDER
