
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef FLAGS__H
#define FLAGS__H

#include <QtGlobal>

#ifdef QT_WIN_VC
#include <QtGlobal>
#endif


// //   Note:  if using the form in which flags can
//      be tested as a context in a grammar
//      (via the macro flag_(index, name)
//        -- in contrast to the form where flags are
//        just declared, as in _flag(name) which is
//        equivalent to bool name:1; --
//      the "flags" struct needs gcc alignment
//      (see the __attribute__((gcc_struct)) below.)
//      My assumption is that this is because a different
//      alignment (according to the GCC manual, the
//      alternative is ms_struct) will cause the bitfields
//      not to be aligned in sequence when separated by an
//      enum declaration (even though the enum obviously
//      requires no allocation), I assume because it is treated
//      as a zero-width declaration intended to set an alignment
//      boundary.  If it is necessary to compile with something
//      other than gcc_struct it will be needed to either
//      use a different compiler flag indicating that this
//      behavior (forcing a boundary at zero-width fields)
//      is not intended; or else to redesign the interface.
//      The simplest way to do this is to separate the flag test
//      enum fields from their bitfield declarations, which
//      requires the flags be listed twice, which is why
//      the gcc-alignment is better.  TODO: write new macros
//      to automate that form.  Something like this should work:
//
//       #define flag_(index, name) bool name:1;
//        (or some other macro name if both forms want to be available)
//       #define flag_index(index, name)
//          enum { name##_ = (1 << (index - 1)), _##name = index };
//
//      Then write the flag_ and flag_index fields separately.
//      If the flag_index fields are written outside the anonymous
//      union modify the flags_all_, flags_none_, and flags_any_
//      macro to obj.flags_all(obj.flags._##name) rather than
//       obj.flags_all(obj.flags.name##_)


#include <bitset>

#ifndef RELAE_namespace
#define RELAE_namespace(x)
#endif

#ifndef RELAE_end_namespace
#define RELAE_end_namespace(x)
#endif



template<int i>
struct RZ_Flags_type
{
 typedef size_t type;
};

template<>
struct RZ_Flags_type<1>
{
 typedef unsigned char type;
};

template<>
struct RZ_Flags_type<2>
{
 typedef unsigned short type;
};

template<>
struct RZ_Flags_type<5>
{
 typedef qint64 type;
};

template<>
struct RZ_Flags_type<6>
{
 typedef qint64 type;
};

template<>
struct RZ_Flags_type<7>
{
 typedef qint64 type;
};

template<>
struct RZ_Flags_type<8>
{
 typedef qint64 type;
};


struct RZ_Flag_Test
{
 enum Test_Type { Test_Any, Test_All, Test_None };
 Test_Type test_type;
 void* bitset;
 size_t bitset_byte_length;
 unsigned long mask;
 RZ_Flag_Test(Test_Type tt, void* v, size_t l, unsigned long m):test_type(tt), bitset(v), bitset_byte_length(l), mask(m)
 {

 }

 #define TEST_IMPL_RESTORE_BITS(byte_count) \
  RZ_Flags_type<byte_count>::type* bits =  \
   reinterpret_cast< RZ_Flags_type<byte_count>::type* >(bitset); \

 bool test_any()
 {
  #define TEST_IMPL_CASE(byte_count) case byte_count: { \
   TEST_IMPL_RESTORE_BITS(byte_count) \
   return *bits & mask; }
  switch(bitset_byte_length)
  {
   TEST_IMPL_CASE(1)
   TEST_IMPL_CASE(2)
   TEST_IMPL_CASE(3)
   TEST_IMPL_CASE(4)
   default: return false;
  }
  #undef TEST_IMPL_CASE
 }

 bool test_all()
 {
  #define TEST_IMPL_CASE(byte_count) case byte_count: { \
   TEST_IMPL_RESTORE_BITS(byte_count) \
    return (*bits & mask) == mask; }
  switch(bitset_byte_length)
  {
   TEST_IMPL_CASE(1)
   TEST_IMPL_CASE(2)
   TEST_IMPL_CASE(3)
   TEST_IMPL_CASE(4)
   default: return false;
  }
  #undef TEST_IMPL_CASE
 }

 bool test_none()
 {
  #define TEST_IMPL_CASE(byte_count) case byte_count: { \
   TEST_IMPL_RESTORE_BITS(byte_count) \
   return (*bits & mask) == 0; }
  switch(bitset_byte_length)
  {
   TEST_IMPL_CASE(1)
   TEST_IMPL_CASE(2)
   TEST_IMPL_CASE(3)
   TEST_IMPL_CASE(4)
   default: return false;
  }
  #undef TEST_IMPL_CASE
 }

 operator bool()
 {
  switch(test_type)
  {
   case Test_Any: return test_any();
   case Test_All: return test_all();
   case Test_None: return test_none();
  }
  return false;
 }
};


#ifndef flags_
#ifdef QT_WIN_VC
#define flags_(byte_count) \
static const quint64 _Flags_byte_count_ = byte_count; \
typedef RZ_Flags_type<byte_count>::type Flags_type; \
union { RZ_Flags_type<byte_count>::type Flags; struct \
{
#else
#define flags_(byte_count) \
 static constexpr size_t _Flags_byte_count_ = byte_count; \
 typedef RZ_Flags_type<byte_count>::type Flags_type; \
 union { RZ_Flags_type<byte_count>::type Flags; struct \
  __attribute__((gcc_struct)) {
#endif
#endif

//
//#define flags_(byte_count) \
// static constexpr size_t _Flags_byte_count_ = byte_count; \
// union { RZ_Flags_type<byte_count>::type Flags; struct \
//  __attribute__((gcc_struct)) {
//#endif

#ifndef mask_
#define mask_(name, byte_count) \
 union { RZ_Flags_type<byte_count>::type name##_##mask; struct {
#endif

#ifndef flags__
#define flags__(byte_count) \
 union { std::bitset<byte_count * 8> Flags; struct {
#endif

#ifndef _mask
#define _mask(name) \
 } name; };
#endif

#ifndef _flags
#define _flags \
 } flags; };
#endif

#ifndef _Flags
#define _Flags \
 } flags; }; \
 Flags = 0; \
 auto Flags_ = [&Flags] ( decltype(Flags) f = 0 ) { Flags = f; };
#endif

#ifndef _Flags_
#define _Flags_(fl) \
 } flags; }; \
 Flags = 0; \
 auto Flags_ = [&Flags] ( decltype(Flags) f = 0 ) { Flags = f; }; \
 flags.fl = true;
#endif


#ifndef Flag_
#define Flag_(f) \
 Flags_(); flags.f = true;
#endif

#ifndef _flag_
#define _flag_(f1, f2) \
 flag.f1 = false; flag.f2 = true;
#endif

#ifndef _flags_
#define _flags_ \
 } flags; }; \
 RZ_Flag_Test flags_all(unsigned long mask) \
 { \
  return RZ_Flag_Test(RZ_Flag_Test::Test_All, &Flags, _Flags_byte_count_, mask); \
 } \
 RZ_Flag_Test flags_any(unsigned long mask) \
 { \
  return RZ_Flag_Test(RZ_Flag_Test::Test_Any, &Flags, _Flags_byte_count_, mask); \
 } \
 RZ_Flag_Test flags_none(unsigned long mask) \
 { \
  return RZ_Flag_Test(RZ_Flag_Test::Test_None, &Flags, _Flags_byte_count_, mask); \
 }
#endif

#ifndef flags_none_
#define flags_none_( obj, flag ) \
 obj.flags_none(obj.flags.flag##_)
#endif


#ifndef flags_all_
#define flags_all_( obj, flag ) \
 obj.flags_all(obj.flags.flag##_)
#endif

#ifndef flags_any_
#define flags_any_( obj, flag ) \
 obj.flags_any(obj.flags.flag##_)
#endif

#ifndef flag_
#define flag_(index ,name) \
 bool name:1; \
 enum { name##_ = (1 << (index - 1)), _##name = index };
#endif

#ifndef _flag
#define _flag(name) \
 bool name:1;
#endif


#endif //FLAGS__H
