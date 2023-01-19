
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ENUM_MACROS__H
#define ENUM_MACROS__H


#define ENUM_FLAGS_OP_MACROS_(e, f) \
 f e operator|(e lhs, e rhs) \
 { \
  return (e) ( (u1) lhs | (u1) rhs ); \
 } \
 f e operator|=(e& lhs, e rhs) \
 { \
  return lhs = (e) (lhs | rhs); \
 } \
 f u1 operator^(e lhs, e rhs) \
 { \
  return (u1) lhs ^ (u1) rhs; \
 } \
 f u1 operator^(e lhs, u1 rhs) \
 { \
  return (u1) lhs ^ (u1) rhs; \
 } \
 f u1 operator>>(e lhs, u1 rhs) \
 { \
  return (u1) lhs >> (u1) rhs; \
 } \
 f e operator^=(e& lhs, e rhs) \
 { \
  return lhs = (e) (lhs ^ rhs); \
 } \
 f e operator^=(e& lhs, u1 rhs) \
 { \
  return lhs = (e) (lhs ^ rhs); \
 } \
 f u1 operator&(e lhs, e rhs) \
 { \
  return (u1) lhs & (u1) rhs; \
 } \
 f u1 operator&(e lhs, u1 rhs) \
 { \
  return (u1) lhs & rhs; \
 } \

 #define ENUM_FLAGS_OP_MACROS(e) ENUM_FLAGS_OP_MACROS_(e, friend constexpr)
 #define ENUM_FLAGS_OP_MACROS_FREESTANDING(e) ENUM_FLAGS_OP_MACROS_(e,inline)


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
