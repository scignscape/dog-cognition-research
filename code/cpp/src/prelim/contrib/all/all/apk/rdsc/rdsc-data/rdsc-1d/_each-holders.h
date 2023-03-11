
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef _EACH_HOLDERS__H
#define _EACH_HOLDERS__H

#include <functional>

#include "kans.h"

#define _MAKE_FULL_HOLDER(name, suffix) \
template<typename _THIS_Type, typename VAL_type, \
  typename INDEX_type, typename PR_Type> \
struct _##name##_holder \
{ \
 _THIS_Type& _this;  \
 void operator <=(std::function<void(VAL_type suffix v)> fn) \
 { \
  _this._##name(fn); \
 } \
 PR_Type operator <<=(std::function<typename PR_Type::level_type(VAL_type suffix v)> fn) \
 { \
  return _this._pr_##name(fn); \
 } \
 void operator <=(std::function<void(VAL_type suffix v, INDEX_type index)> fn) \
 { \
  _this._##name(fn); \
 } \
 PR_Type operator <<=(std::function<typename PR_Type::level_type(VAL_type suffix v, INDEX_type index)> fn) \
 { \
  _this._pr_##name(fn); \
 } \
}; \


#define _MAKE_HOLDER(name, suffix) \
template<typename _THIS_Type, typename VAL_type> \
struct _##name##_holder \
{ \
 _THIS_Type& _this;  \
 void operator <=(std::function<void(VAL_type suffix v)> fn) \
 { \
  _this._##name(fn); \
 } \
}; \




_MAKE_FULL_HOLDER(each ,&)
_MAKE_FULL_HOLDER(reach ,&)
_MAKE_HOLDER(set_default ,**)

KANS_(RdSC)

template<typename VEC_Type, typename VAL_Type,
  typename INDEX_type, typename PR_Type>
struct each_holders
{
 union{
// _each_holder<VEC_Type, VAL_Type, typename INDEX_types::Numeric_Index_type, PR_Type> each;
// _reach_holder<VEC_Type, VAL_Type, typename INDEX_types::Numeric_Index_type, PR_Type> reach;

 _each_holder<VEC_Type, VAL_Type, INDEX_type, PR_Type> each;
 _reach_holder<VEC_Type, VAL_Type, INDEX_type, PR_Type> reach;

 _set_default_holder<VEC_Type, VAL_Type> set_default;
 };
};

_KANS(RdSC)

#endif // _EACH_HOLDERS__H
