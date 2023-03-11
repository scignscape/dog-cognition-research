

//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#define enum_label

#ifndef _preproc_STRING
#define _preproc_STRING(x) #x
#endif

#ifndef _preproc_NUM_ARGS_
#define _preproc_NUM_ARGS_(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, TOTAL, ...) TOTAL
#endif

//? #define VA_ARGS(...) , ##__VA_ARGS__

#ifndef _preproc_NUM_ARGS
#define _preproc_NUM_ARGS(...) _preproc_NUM_ARGS_(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif

#ifndef _preproc_CONCAT_
#define _preproc_CONCAT_(X, Y) X##Y
#endif

#ifndef _preproc_CONCAT
#define _preproc_CONCAT(MACRO, NUMBER) _preproc_CONCAT_(MACRO, NUMBER)
#endif


#define _preproc_get1(_1, _2) _1
#define _preproc_get2(_1, _2) _2


