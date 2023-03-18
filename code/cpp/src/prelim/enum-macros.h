
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ENUM_MACROS__H
#define ENUM_MACROS__H

#include "global-macros.h"



#define _enum_macro_1(a1) enum_macro(a1)

#define _enum_macro_2(a1, a2) enum_macro(a1)  enum_macro(a2)

#define _enum_macro_3(a1, a2, a3) enum_macro(a1)  enum_macro(a2) \
  enum_macro(a3)

#define _enum_macro_4(a1, a2, a3, a4) enum_macro(a1)  enum_macro(a2) \
  enum_macro(a3) enum_macro(a4)

#define _enum_macro_5(a1, a2, a3, a4, a5) enum_macro(a1)  enum_macro(a2) \
  enum_macro(a3) enum_macro(a4) enum_macro(a5)

#define _enum_macro_6(a1, a2, a3, a4, a5, a6) enum_macro(a1)  enum_macro(a2) \
  enum_macro(a3) enum_macro(a4) enum_macro(a5) enum_macro(a6)

#define _enum_macro_7(a1, a2, a3, a4, a5, a6, a7) enum_macro(a1)  enum_macro(a2) \
  enum_macro(a3) enum_macro(a4) enum_macro(a5) enum_macro(a6) enum_macro(a7)

#define _enum_macro_8(a1, a2, a3, a4, a5, a6, a7, a8) enum_macro(a1)  enum_macro(a2) \
  enum_macro(a3) enum_macro(a4) enum_macro(a5) enum_macro(a6) enum_macro(a7) enum_macro(a8)

#define enum_macros(...) _preproc_CONCAT(_enum_macro_, _preproc_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)


//#define enum_dbl_macros(...) _preproc_CONCAT(_enum_dbl_macro_, _preproc_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)




#define ENUM_FLAGS_OP_MACROS_(e, ty, f) \
 f e operator|(e lhs, e rhs) \
 { \
  return (e) ( (ty) lhs | (ty) rhs ); \
 } \
 f e operator|=(e& lhs, e rhs) \
 { \
  return lhs = (e) (lhs | rhs); \
 } \
 f ty operator^(e lhs, e rhs) \
 { \
  return (ty) lhs ^ (ty) rhs; \
 } \
 f ty operator^(e lhs, ty rhs) \
 { \
  return (ty) lhs ^ (ty) rhs; \
 } \
 f ty operator>>(e lhs, ty rhs) \
 { \
  return (ty) lhs >> (ty) rhs; \
 } \
 f e operator^=(e& lhs, e rhs) \
 { \
  return lhs = (e) (lhs ^ rhs); \
 } \
 f e operator^=(e& lhs, ty rhs) \
 { \
  return lhs = (e) (lhs ^ rhs); \
 } \
 f ty operator&(e lhs, e rhs) \
 { \
  return (ty) lhs & (ty) rhs; \
 } \
 f ty operator&(e lhs, ty rhs) \
 { \
  return (ty) lhs & rhs; \
 } \
 f e operator&=(e& lhs, e rhs) \
 { \
  return lhs = (e) (lhs & rhs); \
 } \
 f e operator&=(e& lhs, ty rhs) \
 { \
  return lhs = (e) (lhs & rhs); \
 } \


 #define ENUM_FLAGS_OP_MACROS_2(e, ty) ENUM_FLAGS_OP_MACROS_(e, ty, friend constexpr)
 #define ENUM_FLAGS_OP_MACROS_1(e) ENUM_FLAGS_OP_MACROS_(e, u1, friend constexpr)

 #define ENUM_FLAGS_OP_MACROS(...) \
   _preproc_CONCAT(ENUM_FLAGS_OP_MACROS_, _preproc_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)


#define ENUM_FLAGS_OP_MACROS_FREESTANDING_2(e, ty) ENUM_FLAGS_OP_MACROS_(e, ty, inline)
#define ENUM_FLAGS_OP_MACROS_FREESTANDING_1(e) ENUM_FLAGS_OP_MACROS_(e, u1, inline)

#define ENUM_FLAGS_OP_MACROS_FREESTANDING(...) \
  _preproc_CONCAT(ENUM_FLAGS_OP_MACROS_FREESTANDING_, _preproc_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)



//friend constexpr e operator,(e& lhs, e rhs) \
//{ \
// if(lhs & rhs) lhs = (e) (lhs ^ rhs); \
// return lhs; \
//} \

//friend constexpr e operator,(e& lhs, u1 rhs) \
//{ \
// if(lhs & rhs) lhs = (e) (lhs ^ rhs); \
// return lhs; \
//} \


#define ENUM_PLUS_MACRO(e) \
 friend u1 operator +(e lhs) \
 { \
  return (u1) lhs; \
 } \


#endif // ENUM_MACROS__H
