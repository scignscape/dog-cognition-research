

//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


// //  we use this file itself as a "dummy" include
 //    for items in variadic macro parameter lists
 //    longer than the parameters given -- e.g.,
 //    parameter '_3_of_2' -- defining a temporary
 //    _SIGMA_INCLUDE_BLOCK macro which makes
 //    this file appear empty when including itself.
 //    Note '_3_of_2' and similar conditions therefore
 //    yield the __FILE__ symbol which when passed to
 //    #include serves as a noop.

#ifndef _SIGMA_INCLUDE_BLOCK

#include "global-macros.h"

// //  to enable either chaining and non-chaining of sigma-calls
//
//#define VOID_or_THISP void
//#define VOID_or_THISP_return
#define VOID_or_THISP this_xSigma_t*
#define VOID_or_THISP_return return this;

//#define VOID_or_THISP_return


#ifndef sigmans
#define sigmans(arg) _sigma_ns_(arg)::arg
#endif

#ifndef oself
#define oself get_oself()
#endif

#ifndef _SIGMA_INCLUDE
#define _SIGMA_INCLUDE(x) _preproc_STRING(sigmas/x.h)
#endif


#ifndef _SIGMA_ADAPTER_9
#define _SIGMA_ADAPTER_9(fname, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2, \
  _preproc_get1 arg3 _preproc_get2 arg3, \
  _preproc_get1 arg4 _preproc_get2 arg4, \
  _preproc_get1 arg5 _preproc_get2 arg5, \
  _preproc_get1 arg6 _preproc_get2 arg6, \
  _preproc_get1 arg7 _preproc_get2 arg7, \
  _preproc_get1 arg8 _preproc_get2 arg8 ) \
{ sigmans(fname)(oself, _preproc_get2 arg1, _preproc_get2 arg2, \
  _preproc_get2 arg3, _preproc_get2 arg4, _preproc_get2 arg5, \
  _preproc_get2 arg6, _preproc_get2 arg7, _preproc_get2 arg8); VOID_or_THISP_return}
#endif


#ifndef _SIGMA_ADAPTER_8
#define _SIGMA_ADAPTER_8(fname, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2, \
  _preproc_get1 arg3 _preproc_get2 arg3, \
  _preproc_get1 arg4 _preproc_get2 arg4, \
  _preproc_get1 arg5 _preproc_get2 arg5, \
  _preproc_get1 arg6 _preproc_get2 arg6, \
  _preproc_get1 arg7 _preproc_get2 arg7 ) \
{ sigmans(fname)(oself, _preproc_get2 arg1, _preproc_get2 arg2, \
  _preproc_get2 arg3, _preproc_get2 arg4, _preproc_get2 arg5, \
  _preproc_get2 arg6, _preproc_get2 arg7); VOID_or_THISP_return }
#endif


#ifndef _SIGMA_ADAPTER_7
#define _SIGMA_ADAPTER_7(fname, arg1, arg2, arg3, arg4, arg5, arg6) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2, \
  _preproc_get1 arg3 _preproc_get2 arg3, \
  _preproc_get1 arg4 _preproc_get2 arg4, \
  _preproc_get1 arg5 _preproc_get2 arg5, \
  _preproc_get1 arg6 _preproc_get2 arg6 ) \
{ sigmans(fname)(oself, _preproc_get2 arg1, _preproc_get2 arg2, \
  _preproc_get2 arg3, _preproc_get2 arg4, _preproc_get2 arg5, _preproc_get2 arg6); VOID_or_THISP_return }
#endif


#ifndef _SIGMA_ADAPTER_6
#define _SIGMA_ADAPTER_6(fname, arg1, arg2, arg3, arg4, arg5) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2, \
  _preproc_get1 arg3 _preproc_get2 arg3, \
  _preproc_get1 arg4 _preproc_get2 arg4, \
  _preproc_get1 arg5 _preproc_get2 arg5 ) \
{ sigmans(fname)(oself, _preproc_get2 arg1, _preproc_get2 arg2, \
  _preproc_get2 arg3, _preproc_get2 arg4, _preproc_get2 arg5); VOID_or_THISP_return }
#endif


#ifndef _SIGMA_ADAPTER_5
#define _SIGMA_ADAPTER_5(fname, arg1, arg2, arg3, arg4) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2, \
  _preproc_get1 arg3 _preproc_get2 arg3, \
  _preproc_get1 arg4 _preproc_get2 arg4 ) \
{ sigmans(fname)(oself, _preproc_get2 arg1, _preproc_get2 arg2, \
  _preproc_get2 arg3, _preproc_get2 arg4); VOID_or_THISP_return }
#endif


#ifndef _SIGMA_ADAPTER_4
#define _SIGMA_ADAPTER_4(fname, arg1, arg2, arg3) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2, \
  _preproc_get1 arg3 _preproc_get2 arg3) \
{ sigmans(fname)(oself, _preproc_get2 arg1, _preproc_get2 arg2, \
  _preproc_get2 arg3); VOID_or_THISP_return }
#endif


#ifndef _SIGMA_ADAPTER_3
#define _SIGMA_ADAPTER_3(fname, arg1, arg2) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2) \
{ sigmans(fname)(oself, _preproc_get2 arg1, _preproc_get2 arg2); VOID_or_THISP_return }
#endif

#ifndef _SIGMA_ADAPTER_2
#define _SIGMA_ADAPTER_2(fname, arg1) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1) \
{ sigmans(fname)(oself, _preproc_get2 arg1); VOID_or_THISP_return }
#endif

#ifndef _SIGMA_ADAPTER_1
#define _SIGMA_ADAPTER_1(fname) \
VOID_or_THISP fname() { sigmans(fname)(oself); VOID_or_THISP_return }
#endif


#ifndef SIGMA_ADAPTER
#define SIGMA_ADAPTER(...) \
  _preproc_CONCAT(_SIGMA_ADAPTER_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)
#endif


#ifndef _SIGMA_ADAPTER_PAIR_9
#define _SIGMA_ADAPTER_PAIR_9(fname, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2, \
  _preproc_get1 arg3 _preproc_get2 arg3, \
  _preproc_get1 arg4 _preproc_get2 arg4, \
  _preproc_get1 arg5 _preproc_get2 arg5, \
  _preproc_get1 arg6 _preproc_get2 arg6, \
  _preproc_get1 arg7 _preproc_get2 arg7, \
  _preproc_get1 arg8 _preproc_get2 arg8) \
{ sigmans(fname)(oself->first, oself->second, _preproc_get2 arg1, \
  _preproc_get2 arg2, _preproc_get2 arg3, \
  _preproc_get2 arg4, _preproc_get2 arg5, \
  _preproc_get2 arg6, _preproc_get2 arg7, _preproc_get2 arg8); oself_done(); }
#endif


#ifndef _SIGMA_ADAPTER_PAIR_8
#define _SIGMA_ADAPTER_PAIR_8(fname, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2, \
  _preproc_get1 arg3 _preproc_get2 arg3, \
  _preproc_get1 arg4 _preproc_get2 arg4, \
  _preproc_get1 arg5 _preproc_get2 arg5, \
  _preproc_get1 arg6 _preproc_get2 arg6, \
  _preproc_get1 arg7 _preproc_get2 arg7) \
{ sigmans(fname)(oself->first, oself->second, _preproc_get2 arg1, \
  _preproc_get2 arg2, _preproc_get2 arg3, \
  _preproc_get2 arg4, _preproc_get2 arg5, \
  _preproc_get2 arg6, _preproc_get2 arg7); oself_done(); }
#endif


#ifndef _SIGMA_ADAPTER_PAIR_7
#define _SIGMA_ADAPTER_PAIR_7(fname, arg1, arg2, arg3, arg4, arg5, arg6) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2, \
  _preproc_get1 arg3 _preproc_get2 arg3, \
  _preproc_get1 arg4 _preproc_get2 arg4, \
  _preproc_get1 arg5 _preproc_get2 arg5, \
  _preproc_get1 arg6 _preproc_get2 arg6) \
{ sigmans(fname)(oself->first, oself->second, _preproc_get2 arg1, \
  _preproc_get2 arg2, _preproc_get2 arg3, \
  _preproc_get2 arg4, _preproc_get2 arg5, \
  _preproc_get2 arg6); oself_done(); }
#endif


#ifndef _SIGMA_ADAPTER_PAIR_6
#define _SIGMA_ADAPTER_PAIR_6(fname, arg1, arg2, arg3, arg4, arg5) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2, \
  _preproc_get1 arg3 _preproc_get2 arg3, \
  _preproc_get1 arg4 _preproc_get2 arg4, \
  _preproc_get1 arg5 _preproc_get2 arg5) \
{ sigmans(fname)(oself->first, oself->second, _preproc_get2 arg1, \
  _preproc_get2 arg2, _preproc_get2 arg3, \
  _preproc_get2 arg4, _preproc_get2 arg5); oself_done(); }
#endif


#ifndef _SIGMA_ADAPTER_PAIR_5
#define _SIGMA_ADAPTER_PAIR_5(fname, arg1, arg2, arg3, arg4) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2, \
  _preproc_get1 arg3 _preproc_get2 arg3, \
  _preproc_get1 arg4 _preproc_get2 arg4) \
{ sigmans(fname)(oself->first, oself->second, _preproc_get2 arg1, \
  _preproc_get2 arg2, _preproc_get2 arg3, _preproc_get2 arg4); oself_done(); }
#endif


#ifndef _SIGMA_ADAPTER_PAIR_4
#define _SIGMA_ADAPTER_PAIR_4(fname, arg1, arg2, arg3) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2, \
  _preproc_get1 arg3 _preproc_get2 arg3) \
{ sigmans(fname)(oself->first, oself->second, _preproc_get2 arg1, \
  _preproc_get2 arg2, _preproc_get2 arg3); oself_done(); }
#endif


#ifndef _SIGMA_ADAPTER_PAIR_3
#define _SIGMA_ADAPTER_PAIR_3(fname, arg1, arg2) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1, \
  _preproc_get1 arg2 _preproc_get2 arg2) \
{ sigmans(fname)(oself->first, oself->second, _preproc_get2 arg1, \
  _preproc_get2 arg2); oself_done(); }
#endif


#ifndef _SIGMA_ADAPTER_PAIR_2
#define _SIGMA_ADAPTER_PAIR_2(fname, arg1) \
VOID_or_THISP fname(_preproc_get1 arg1 _preproc_get2 arg1) \
{ sigmans(fname)(oself->first, oself->second, _preproc_get2 arg1); oself_done(); }
#endif


#ifndef _SIGMA_ADAPTER_PAIR_1
#define _SIGMA_ADAPTER_PAIR_1(fname) \
void fname() \
{ sigmans(fname)(oself->first, oself->second); oself_done(); }
#endif


#ifndef SIGMA_ADAPTER_PAIR
#define SIGMA_ADAPTER_PAIR(...) \
  _preproc_CONCAT(_SIGMA_ADAPTER_PAIR_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)
#endif



#define _SIGMA_INCLUDE_1_of_VAR(...) _preproc_CONCAT(_SIGMA_INCLUDE_1_of_, _preproc_NUM_ARGS (__VA_ARGS__)) (__VA_ARGS__)
#define _SIGMA_INCLUDE_2_of_VAR(...) _preproc_CONCAT(_SIGMA_INCLUDE_2_of_, _preproc_NUM_ARGS (__VA_ARGS__)) (__VA_ARGS__)
#define _SIGMA_INCLUDE_3_of_VAR(...) _preproc_CONCAT(_SIGMA_INCLUDE_3_of_, _preproc_NUM_ARGS (__VA_ARGS__)) (__VA_ARGS__)

#define _SIGMA_INCLUDE_4_of_VAR(...) _preproc_CONCAT(_SIGMA_INCLUDE_4_of_, _preproc_NUM_ARGS (__VA_ARGS__)) (__VA_ARGS__)
#define _SIGMA_INCLUDE_5_of_VAR(...) _preproc_CONCAT(_SIGMA_INCLUDE_5_of_, _preproc_NUM_ARGS (__VA_ARGS__)) (__VA_ARGS__)
#define _SIGMA_INCLUDE_6_of_VAR(...) _preproc_CONCAT(_SIGMA_INCLUDE_6_of_, _preproc_NUM_ARGS (__VA_ARGS__)) (__VA_ARGS__)

#define _SIGMA_INCLUDE_7_of_VAR(...) _preproc_CONCAT(_SIGMA_INCLUDE_7_of_, _preproc_NUM_ARGS (__VA_ARGS__)) (__VA_ARGS__)
#define _SIGMA_INCLUDE_8_of_VAR(...) _preproc_CONCAT(_SIGMA_INCLUDE_8_of_, _preproc_NUM_ARGS (__VA_ARGS__)) (__VA_ARGS__)
#define _SIGMA_INCLUDE_9_of_VAR(...) _preproc_CONCAT(_SIGMA_INCLUDE_9_of_, _preproc_NUM_ARGS (__VA_ARGS__)) (__VA_ARGS__)


#ifndef _SIGMA_INCLUDE_1_of_1
#define _SIGMA_INCLUDE_1_of_1(_1) _preproc_STRING(sigmas/_1.h)
#endif

#ifndef _SIGMA_INCLUDE_1_of_2
#define _SIGMA_INCLUDE_1_of_2(_1, _2) _preproc_STRING(sigmas/_1.h)
#endif

#ifndef _SIGMA_INCLUDE_1_of_3
#define _SIGMA_INCLUDE_1_of_3(_1, _2, _3) _preproc_STRING(sigmas/_1.h)
#endif

#ifndef _SIGMA_INCLUDE_1_of_4
#define _SIGMA_INCLUDE_1_of_4(_1, _2, _3, _4) _preproc_STRING(sigmas/_1.h)
#endif

#ifndef _SIGMA_INCLUDE_1_of_5
#define _SIGMA_INCLUDE_1_of_5(_1, _2, _3, _4, _5) _preproc_STRING(sigmas/_1.h)
#endif

#ifndef _SIGMA_INCLUDE_1_of_6
#define _SIGMA_INCLUDE_1_of_6(_1, _2, _3, _4, _5, _6) _preproc_STRING(sigmas/_1.h)
#endif

#ifndef _SIGMA_INCLUDE_1_of_7
#define _SIGMA_INCLUDE_1_of_7(_1, _2, _3, _4, _5, _6, _7) _preproc_STRING(sigmas/_1.h)
#endif

#ifndef _SIGMA_INCLUDE_1_of_8
#define _SIGMA_INCLUDE_1_of_8(_1, _2, _3, _4, _5, _6, _7, _8) _preproc_STRING(sigmas/_1.h)
#endif

#ifndef _SIGMA_INCLUDE_1_of_9
#define _SIGMA_INCLUDE_1_of_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) _preproc_STRING(sigmas/_1.h)
#endif


#ifndef _SIGMA_INCLUDE_2_of_1
#define _SIGMA_INCLUDE_2_of_1(_1) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_2_of_2
#define _SIGMA_INCLUDE_2_of_2(_1, _2) _preproc_STRING(sigmas/_2.h)
#endif

#ifndef _SIGMA_INCLUDE_2_of_3
#define _SIGMA_INCLUDE_2_of_3(_1, _2, _3) _preproc_STRING(sigmas/_2.h)
#endif

#ifndef _SIGMA_INCLUDE_2_of_4
#define _SIGMA_INCLUDE_2_of_4(_1, _2, _3, _4) _preproc_STRING(sigmas/_2.h)
#endif

#ifndef _SIGMA_INCLUDE_2_of_5
#define _SIGMA_INCLUDE_2_of_5(_1, _2, _3, _4, _5) _preproc_STRING(sigmas/_2.h)
#endif

#ifndef _SIGMA_INCLUDE_2_of_6
#define _SIGMA_INCLUDE_2_of_6(_1, _2, _3, _4, _5, _6) _preproc_STRING(sigmas/_2.h)
#endif

#ifndef _SIGMA_INCLUDE_2_of_7
#define _SIGMA_INCLUDE_2_of_7(_1, _2, _3, _4, _5, _6, _7) _preproc_STRING(sigmas/_2.h)
#endif

#ifndef _SIGMA_INCLUDE_2_of_8
#define _SIGMA_INCLUDE_2_of_8(_1, _2, _3, _4, _5, _6, _7, _8) _preproc_STRING(sigmas/_2.h)
#endif

#ifndef _SIGMA_INCLUDE_2_of_9
#define _SIGMA_INCLUDE_2_of_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) _preproc_STRING(sigmas/_2.h)
#endif


#ifndef _SIGMA_INCLUDE_3_of_1
#define _SIGMA_INCLUDE_3_of_1(_1) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_3_of_2
#define _SIGMA_INCLUDE_3_of_2(_1, _2) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_3_of_3
#define _SIGMA_INCLUDE_3_of_3(_1, _2, _3) _preproc_STRING(sigmas/_3.h)
#endif

#ifndef _SIGMA_INCLUDE_3_of_4
#define _SIGMA_INCLUDE_3_of_4(_1, _2, _3, _4) _preproc_STRING(sigmas/_3.h)
#endif

#ifndef _SIGMA_INCLUDE_3_of_5
#define _SIGMA_INCLUDE_3_of_5(_1, _2, _3, _4, _5) _preproc_STRING(sigmas/_3.h)
#endif

#ifndef _SIGMA_INCLUDE_3_of_6
#define _SIGMA_INCLUDE_3_of_6(_1, _2, _3, _4, _5, _6) _preproc_STRING(sigmas/_3.h)
#endif

#ifndef _SIGMA_INCLUDE_3_of_7
#define _SIGMA_INCLUDE_3_of_7(_1, _2, _3, _4, _5, _6, _7) _preproc_STRING(sigmas/_3.h)
#endif

#ifndef _SIGMA_INCLUDE_3_of_8
#define _SIGMA_INCLUDE_3_of_8(_1, _2, _3, _4, _5, _6, _7, _8) _preproc_STRING(sigmas/_3.h)
#endif

#ifndef _SIGMA_INCLUDE_3_of_9
#define _SIGMA_INCLUDE_3_of_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) _preproc_STRING(sigmas/_3.h)
#endif


#ifndef _SIGMA_INCLUDE_4_of_1
#define _SIGMA_INCLUDE_4_of_1(_1) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_4_of_2
#define _SIGMA_INCLUDE_4_of_2(_1, _2) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_4_of_3
#define _SIGMA_INCLUDE_4_of_3(_1, _2, _3) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_4_of_4
#define _SIGMA_INCLUDE_4_of_4(_1, _2, _3, _4) _preproc_STRING(sigmas/_4.h)
#endif

#ifndef _SIGMA_INCLUDE_4_of_5
#define _SIGMA_INCLUDE_4_of_5(_1, _2, _3, _4, _5) _preproc_STRING(sigmas/_4.h)
#endif

#ifndef _SIGMA_INCLUDE_4_of_6
#define _SIGMA_INCLUDE_4_of_6(_1, _2, _3, _4, _5, _6) _preproc_STRING(sigmas/_4.h)
#endif

#ifndef _SIGMA_INCLUDE_4_of_7
#define _SIGMA_INCLUDE_4_of_7(_1, _2, _3, _4, _5, _6, _7) _preproc_STRING(sigmas/_4.h)
#endif

#ifndef _SIGMA_INCLUDE_4_of_8
#define _SIGMA_INCLUDE_4_of_8(_1, _2, _3, _4, _5, _6, _7, _8) _preproc_STRING(sigmas/_4.h)
#endif

#ifndef _SIGMA_INCLUDE_4_of_9
#define _SIGMA_INCLUDE_4_of_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) _preproc_STRING(sigmas/_4.h)
#endif


#ifndef _SIGMA_INCLUDE_5_of_1
#define _SIGMA_INCLUDE_5_of_1(_1) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_5_of_2
#define _SIGMA_INCLUDE_5_of_2(_1, _2) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_5_of_3
#define _SIGMA_INCLUDE_5_of_3(_1, _2, _3) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_5_of_4
#define _SIGMA_INCLUDE_5_of_4(_1, _2, _3, _4) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_5_of_5
#define _SIGMA_INCLUDE_5_of_5(_1, _2, _3, _4, _5) _preproc_STRING(sigmas/_5.h)
#endif

#ifndef _SIGMA_INCLUDE_5_of_6
#define _SIGMA_INCLUDE_5_of_6(_1, _2, _3, _4, _5, _6) _preproc_STRING(sigmas/_5.h)
#endif

#ifndef _SIGMA_INCLUDE_5_of_7
#define _SIGMA_INCLUDE_5_of_7(_1, _2, _3, _4, _5, _6, _7) _preproc_STRING(sigmas/_5.h)
#endif

#ifndef _SIGMA_INCLUDE_5_of_8
#define _SIGMA_INCLUDE_5_of_8(_1, _2, _3, _4, _5, _6, _7, _8) _preproc_STRING(sigmas/_5.h)
#endif

#ifndef _SIGMA_INCLUDE_5_of_9
#define _SIGMA_INCLUDE_5_of_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) _preproc_STRING(sigmas/_5.h)
#endif


#ifndef _SIGMA_INCLUDE_6_of_1
#define _SIGMA_INCLUDE_6_of_1(_1) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_6_of_2
#define _SIGMA_INCLUDE_6_of_2(_1, _2) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_6_of_3
#define _SIGMA_INCLUDE_6_of_3(_1, _2, _3) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_6_of_4
#define _SIGMA_INCLUDE_6_of_4(_1, _2, _3, _4) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_6_of_5
#define _SIGMA_INCLUDE_6_of_5(_1, _2, _3, _4, _5) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_6_of_6
#define _SIGMA_INCLUDE_6_of_6(_1, _2, _3, _4, _5, _6) _preproc_STRING(sigmas/_6.h)
#endif

#ifndef _SIGMA_INCLUDE_6_of_7
#define _SIGMA_INCLUDE_6_of_7(_1, _2, _3, _4, _5, _6, _7) _preproc_STRING(sigmas/_6.h)
#endif

#ifndef _SIGMA_INCLUDE_6_of_8
#define _SIGMA_INCLUDE_6_of_8(_1, _2, _3, _4, _5, _6, _7, _8) _preproc_STRING(sigmas/_6.h)
#endif

#ifndef _SIGMA_INCLUDE_6_of_9
#define _SIGMA_INCLUDE_6_of_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) _preproc_STRING(sigmas/_6.h)
#endif


#ifndef _SIGMA_INCLUDE_7_of_1
#define _SIGMA_INCLUDE_7_of_1(_1) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_7_of_2
#define _SIGMA_INCLUDE_7_of_2(_1, _2) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_7_of_3
#define _SIGMA_INCLUDE_7_of_3(_1, _2, _3) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_7_of_4
#define _SIGMA_INCLUDE_7_of_4(_1, _2, _3, _4) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_7_of_5
#define _SIGMA_INCLUDE_7_of_5(_1, _2, _3, _4, _5) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_7_of_6
#define _SIGMA_INCLUDE_7_of_6(_1, _2, _3, _4, _5, _6) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_7_of_7
#define _SIGMA_INCLUDE_7_of_7(_1, _2, _3, _4, _5, _6, _7) _preproc_STRING(sigmas/_7.h)
#endif

#ifndef _SIGMA_INCLUDE_7_of_8
#define _SIGMA_INCLUDE_7_of_8(_1, _2, _3, _4, _5, _6, _7, _8) _preproc_STRING(sigmas/_7.h)
#endif

#ifndef _SIGMA_INCLUDE_7_of_9
#define _SIGMA_INCLUDE_7_of_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) _preproc_STRING(sigmas/_7.h)
#endif


#ifndef _SIGMA_INCLUDE_8_of_1
#define _SIGMA_INCLUDE_8_of_1(_1) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_8_of_2
#define _SIGMA_INCLUDE_8_of_2(_1, _2) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_8_of_3
#define _SIGMA_INCLUDE_8_of_3(_1, _2, _3) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_8_of_4
#define _SIGMA_INCLUDE_8_of_4(_1, _2, _3, _4) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_8_of_5
#define _SIGMA_INCLUDE_8_of_5(_1, _2, _3, _4, _5) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_8_of_6
#define _SIGMA_INCLUDE_8_of_6(_1, _2, _3, _4, _5, _6) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_8_of_7
#define _SIGMA_INCLUDE_8_of_7(_1, _2, _3, _4, _5, _6, _7) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_8_of_8
#define _SIGMA_INCLUDE_8_of_8(_1, _2, _3, _4, _5, _6, _7, _8) _preproc_STRING(sigmas/_8.h)
#endif

#ifndef _SIGMA_INCLUDE_8_of_9
#define _SIGMA_INCLUDE_8_of_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) _preproc_STRING(sigmas/_8.h)
#endif


#ifndef _SIGMA_INCLUDE_9_of_1
#define _SIGMA_INCLUDE_9_of_1(_1) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_9_of_2
#define _SIGMA_INCLUDE_9_of_2(_1, _2) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_9_of_3
#define _SIGMA_INCLUDE_9_of_3(_1, _2, _3) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_9_of_4
#define _SIGMA_INCLUDE_9_of_4(_1, _2, _3, _4) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_9_of_5
#define _SIGMA_INCLUDE_9_of_5(_1, _2, _3, _4, _5) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_9_of_6
#define _SIGMA_INCLUDE_9_of_6(_1, _2, _3, _4, _5, _6) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_9_of_7
#define _SIGMA_INCLUDE_9_of_7(_1, _2, _3, _4, _5, _6, _7) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_9_of_8
#define _SIGMA_INCLUDE_9_of_8(_1, _2, _3, _4, _5, _6, _7, _8) __FILE__
#endif

#ifndef _SIGMA_INCLUDE_9_of_9
#define _SIGMA_INCLUDE_9_of_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) _preproc_STRING(sigmas/_9.h)
#endif


template<typename THIS_Type>
struct xSigma : THIS_Type {

 typedef xSigma<THIS_Type> this_xSigma_t;
 typedef THIS_Type oself_t;

 THIS_Type* get_oself()
 {
  return reinterpret_cast<THIS_Type*>(this);
 }

 void oself_done()
 {
  delete get_oself();
 }

#define _SIGMA_INCLUDE_BLOCK
#include _my_sigma_(_SIGMA_INCLUDE_1_of_VAR)
#include _my_sigma_(_SIGMA_INCLUDE_2_of_VAR)
#include _my_sigma_(_SIGMA_INCLUDE_3_of_VAR)
#include _my_sigma_(_SIGMA_INCLUDE_4_of_VAR)
#include _my_sigma_(_SIGMA_INCLUDE_5_of_VAR)
#include _my_sigma_(_SIGMA_INCLUDE_6_of_VAR)
#include _my_sigma_(_SIGMA_INCLUDE_7_of_VAR)
#include _my_sigma_(_SIGMA_INCLUDE_8_of_VAR)
#include _my_sigma_(_SIGMA_INCLUDE_9_of_VAR)
#undef _SIGMA_INCLUDE_BLOCK

};

template<typename THIS1_Type, typename THIS2_Type>
struct xSigmaPair : xSigma<QPair<THIS1_Type, THIS2_Type>>
{
};

template<typename THIS_Type>
xSigma<THIS_Type>* sigma(THIS_Type* o) { return reinterpret_cast<xSigma<THIS_Type>*>(o);}

template<typename THIS1_Type, typename THIS2_Type>
xSigmaPair<THIS1_Type, THIS2_Type>*
sigma(THIS1_Type o1, THIS2_Type o2)
{
 return reinterpret_cast<xSigmaPair<THIS1_Type, THIS2_Type>*>(
   new QPair<THIS1_Type, THIS2_Type>(o1, o2));
}


#ifndef left_cosigma_spec
#define left_cosigma_spec(x) \
 sigma(nullptr, x)
#endif

#ifndef left_cosigma_2
#define left_cosigma_2(x, y) \
left_cosigma_spec_##x(y)
#endif

#ifndef left_cosigma_1
#define left_cosigma_1(x) \
 sigma(this, x)
#endif

#ifndef right_cosigma_spec
#define right_cosigma_spec(x) \
 sigma(x, nullptr)
#endif

#ifndef right_cosigma_2
#define right_cosigma_2(x, y) \
right_cosigma_spec_##x(y)
#endif

#ifndef right_cosigma_1
#define right_cosigma_1(x) \
 sigma(x, this)
#endif


#ifndef cosigma
#define cosigma(...) \
_preproc_CONCAT(left_cosigma_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)
#endif

#ifndef _cosigma
#define _cosigma(...) \
_preproc_CONCAT(right_cosigma_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)
#endif


#endif //_SIGMA_INCLUDE_BLOCK
