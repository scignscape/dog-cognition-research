

//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef unless
#define unless(x) if(!(x))
#endif

#ifndef block_init_2
#define block_init_2(x, y) x = [&]() ->decltype(x) {decltype(x) y;
#endif

#ifndef block_init_1
#define block_init_1(x) x = [&]() ->decltype(x) {decltype(x) _;
#endif

#ifndef block_init
#define block_init(...) _preproc_CONCAT(block_init_, _preproc_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)
#endif


#ifndef block_result_
#define block_result_(x) return x; }();
#endif

#ifndef block_result
#define block_result return _; }();
#endif

#include "preproc-concat.h"
