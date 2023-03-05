
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "global-macros.h"

#ifndef break_or_else
#define break_or_else \
else continue; break;
#endif

#ifndef and_break
#define and_break \
; else continue; break;
#endif

#ifndef _break
#define _break \
0; else continue; break;
#endif



#ifndef and_then
#define and_then(x) \
 _preproc_CONCAT(and_, x)
#endif



#ifndef DEFINED_SCOPED_BOOL_TEST
#define DEFINED_SCOPED_BOOL_TEST

#define MAKE_SCOPED_BOOL_TEST(struct_name_variant, fn_name, bool_test_pre, bool_test_post) \
template<typename T, typename _FN = decltype(&T::fn_name), _FN FN = &T::fn_name>  \
struct _scoped_bool_test__ ## struct_name_variant ##_## fn_name  \
{  \
 T value;  \
 explicit operator bool()  \
 {  \
  return bool_test_pre (value.*FN)() bool_test_post;  \
 }  \
 operator T() { return value; }  \
 _scoped_bool_test__  ## struct_name_variant ##_## fn_name<T, _FN, FN> (T val) : value(val)  \
 {  \
 }  \
};  \


//template<typename T, typename _FN = decltype(&T::isEmpty), _FN FN = &T::isEmpty>
//struct _scoped_bool_test__no_isEmpty
//{
// T value;
// explicit operator bool()
// {
//  return ! (value.*FN)();
// }
// operator const T&() { return value; }
// _scoped_bool_test__no_isEmpty<T, _FN, FN> (T val) : value(val)
// {
// }
//};

MAKE_SCOPED_BOOL_TEST(no, isEmpty, !,)
MAKE_SCOPED_BOOL_TEST(no, isNull, !,)
//?MAKE_SCOPED_BOOL_TEST(yes, size, , !=0)

#endif


#ifndef SCOPED_BOOL_TEST_MACRO(a1, a2, arg)
#define SCOPED_BOOL_TEST_MACRO(a1, a2, arg) if(_scoped_bool_test ##__## a1 ##_## a2 arg)
#endif


#ifndef _if_no_isEmpty(arg)
#define _if_no_isEmpty(arg) SCOPED_BOOL_TEST_MACRO(no, isEmpty, arg)
#endif

#ifndef _if_isEmpty_(arg)
#define _if_isEmpty_(arg) SCOPED_BOOL_TEST_MACRO(no, isEmpty, arg)
#endif

#ifndef _if_yes_size(arg)
#define _if_yes_size(arg) SCOPED_BOOL_TEST_MACRO(yes, size, arg)
#endif


#ifndef _if_2
#define _if_2(test_result,test_description) _preproc_CONCAT(_if, _## test_description ##_## test_result)
#endif


#ifndef _if_1
#define _if_1(arg) if(_scoped_bool_test__no_isEmpty arg)
#endif

#ifndef _if
#define _if(...) _preproc_CONCAT(_if_, _preproc_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)
#endif




