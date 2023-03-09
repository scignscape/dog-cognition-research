
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef HIVE_STRUCTURE__H
#define HIVE_STRUCTURE__H


#include "accessors.h"

#include "global-types.h"

#include "enum-macros.h"

#include <QVector>
#include <QString>
#include <QMap>

#include "xcns.h"

#include <limits>

#include <vector>


#ifndef Contiguous_breakdown_
#define Contiguous_breakdown_(_fn_, \
  _Contiguous_it1_, _Contiguous_it2_, _Contiguous_it3_,\
  _Non_Contiguous_it0_, \
  _Non_Contiguous_it1_, _Non_Contiguous_it2_, _Non_Contiguous_it3_,\
  _coll_, _ty1_, _ty2_, _start_, _end_) \
do{\
QVector<QPair<_ty1_*, _ty2_>> _breakdown_; \
if(_ty1_* Contiguous_it = _coll_.contiguous(_start_, _end_, _breakdown_)) \
{ \
 _fn_(_Contiguous_it1_, _Contiguous_it2_, _Contiguous_it3_); \
} \
else \
{ \
 auto Non_Contiguous_it = _Non_Contiguous_it0_; \
 for(QPair<_ty1_*, _ty2_> pr : _breakdown_) \
 { \
  _fn_(_Non_Contiguous_it1_, _Non_Contiguous_it2_, _Non_Contiguous_it3_); \
  Non_Contiguous_it += pr.second; \
 } \
}} while(0)
#endif



#ifndef _Contiguous_breakdown_
#define _Contiguous_breakdown_(_fn_, _target_, _coll_, _ty1_, _ty2_, _start_, _end_) \
{ \
 QVector<QPair<_ty1_*, _ty2_>> _breakdown_; \
 if(_ty1_* it = _coll_.contiguous(_start_, _end_, _breakdown_)) \
 { \
  _fn_(it, it + _end_, _target_.begin()); \
 } \
 else \
 { \
  auto it1 = _target_.begin(); \
  for(QPair<_ty1_*, _ty2_> pr : _breakdown_) \
  { \
   _fn_(pr.first, pr.first + pr.second, it1); \
   it1 += pr.second; \
  } \
}} while(0)
#endif


#ifndef Contiguous_breakdown_source_
#define Contiguous_breakdown_source_(_fn_, _target_, _coll_, _ty1_, _ty2_, _start_, _end_) \
Contiguous_breakdown_(_fn_, \
  (Contiguous_it), (Contiguous_it + _end_ + 1 - _start_), _target_.begin(), \
  _target_.begin(), \
  pr.first, pr.first + pr.second, Non_Contiguous_it, \
  _coll_, _ty1_, _ty2_, _start_, _end_)
#endif


#ifndef Contiguous_breakdown_target_
#define Contiguous_breakdown_target_(_fn_, _source_, _coll_, _ty1_, _ty2_, _start_, _end_) \
Contiguous_breakdown_(_fn_,\
  _source_.begin(), _source_.end(), Contiguous_it, \
  _source_.begin(), \
  Non_Contiguous_it, Non_Contiguous_it + pr.second, pr.first, \
  _coll_, _ty1_, _ty2_, _start_, _end_)
#endif



//do{\
//QVector<QPair<_ty1_*, _ty2_>> _breakdown_; \
//if(_ty1_* it = _coll_.contiguous(_start_, _end_, _breakdown_)) \
//{ \
// _fn_(_source_.begin(), _source_.end(), it); \
//} \
//else \
//{ \
// auto it1 = _source_.begin(); \
// for(QPair<_ty1_*, _ty2_> pr : _breakdown_) \
// { \
//  _fn_(it1, it1 + pr.second, pr.first); \
//  it1 += pr.second; \
// } \
//}} while(0)

#ifndef Contiguous_breakdown_target
#define Contiguous_breakdown_target(_fn_, _source_, _coll_, _start_, _end_) \
  Contiguous_breakdown_target_(_fn_, _source_, _coll_, typename decltype(_coll_)::Element_type, \
  typename decltype(_coll_)::Numeric_Index_type, _start_, _end_)
#endif

#ifndef Contiguous_breakdown_source
#define Contiguous_breakdown_source(_fn_, _source_, _coll_, _start_, _end_) \
  Contiguous_breakdown_source_(_fn_, _source_, _coll_, typename decltype(_coll_)::Element_type, \
  typename decltype(_coll_)::Numeric_Index_type, _start_, _end_)
#endif


#ifndef Action_scan
#define Action_scan(_fn_, _source_, _coll_, _start_, _end_) \
  Contiguous_breakdown_target(_fn_, _source_, _coll_, _start_, _end_)
#endif

#ifndef Action_span
#define Action_span(_fn_, _target_, _coll_, _start_, _end_) \
  Contiguous_breakdown_source(_fn_, _target_, _coll_, _start_, _end_)
#endif



//Contiguous_breakdown(std::copy, test2, vec, 19, 20);


//#ifndef Contiguous_breakdown
//#define Contiguous_breakdown(_fn_, _source_, _coll_, _start_, _end_) \
//  Contiguous_breakdown_(_fn_, _source_, _coll_, val_t, \
//  nx, _start_, _end_)
//#endif

XCNS_(XCSD)

//template<typename T, typename Numeric_Index_type = signed short>
//struct hive_galaxy
//{
// typedef T element_type;
//// typedef T index_type;
//// typedef T type_descriptor_type;
// typedef Numeric_Index_type nx;
//};



template <typename T, typename NT = s2>
struct index_types
{
 typedef T Numeric_Index_type;
 typedef T Numeric_Nested_Index_type;
};

template <typename T>
T _lower_limit()
{
 return std::numeric_limits<T>::min();
}

template <typename T>
T _the_invalid_index()
{
 return _lower_limit<T>();
}


template <typename T>
T _upper_limit()
{
 return std::numeric_limits<T>::max();
}

template <typename T>
T _the_invalid_upper_index()
{
 return _upper_limit<T>();
}

//template <>
//s2 _lower_bound()
//{
// return std::numeric_limits<s2>::lowest();
//}


//template<typename Numeric_Index_type = signed short,
//  typename Numeric_Nested_Index_type = Numeric_Index_type>


//template<typename NUMERIC_INDEX_Type = signed short,
//  typename NUMERIC_NESTED_INDEX_Type = NUMERIC_INDEX_Type>

//struct Fetch_Location_Options
//{
// enum {
//  N_A = 0,
//  _index_location = 1,
//  _fallback_location = 2,
//  _rebound_index_location = 4,
//  _rebound_fallback_location = 8,
//  _default_value_pointer = 16,
//  _default_function_temporary = 32,
//  _default_constructor_temporary = 64,
// };

// void* index_location;
// void* fallback_location;
// void* rebound_index_location;
// void* rebound_fallback_location;
// void* default_value_pointer;
// void* default_function_temporary;
// void* default_constructor_temporary;
// void** primary_location;
// void** positional_location;

// u1 current_location_option;
// u1 current_positional_redirect;
// u1 current_active_position;

// Fetch_Location_Options()
//  : index_location(nullptr),
//    fallback_location(nullptr),
//    rebound_index_location(nullptr),
//    rebound_fallback_location(nullptr),
//    default_value_pointer(nullptr),
//    default_function_temporary(nullptr),
//    default_constructor_temporary(nullptr),
//    primary_location(nullptr),
//    positional_location(nullptr),
//    current_location_option(0),
//    current_positional_redirect(0),
//    current_active_position(0)
// {}

// void check_current(u1 c)
// {
//  if(get_location(c)) //  i.e., the pointer there is not nullptr
//    current_location_option = c;
//  else if(positional_location)
//  {
//   if(*positional_location)
//     current_location_option = c;
//  }
// }

// void check_position(u1 c)
// {
//  if(primary_location)
//  {
//   positional_location = primary_location;
//   current_positional_redirect = c;
//   current_active_position = N_A;
//  }
//  else
//  {
//   positional_location = get_location_ptr(c);
//   current_positional_redirect = N_A;
//   current_active_position = c;
//  }
// }

// u1 aggregation_location_options()
// {
//  u1 result = 0;
//  if(index_location) result |= _index_location;
//  if(fallback_location) result |= _fallback_location;
//  if(rebound_index_location) result |= _rebound_index_location;
//  if(rebound_fallback_location) result |= _rebound_fallback_location;

//  if(default_value_pointer) result |= _default_value_pointer;
//  if(default_function_temporary) result |= _default_function_temporary;
//  if(default_constructor_temporary) result |= _default_constructor_temporary;

//  return result;
// }

// void current_to_primary()
// {
//  primary_location = get_current_location_ptr();
// }

// void** get_location_ptr(u1 c)
// {
//  switch (c)
//  {
//  case _index_location: return &index_location;
//  case _fallback_location: return &fallback_location;
//  case _rebound_index_location: return &rebound_index_location;
//  case _rebound_fallback_location: return &rebound_fallback_location;
//  case _default_value_pointer: return &default_value_pointer;
//  case _default_function_temporary: return &default_function_temporary;
//  case _default_constructor_temporary: return &default_constructor_temporary;
//  default: return nullptr;
//  }
// }

// void** get_current_location_ptr()
// {
//  return get_location_ptr(current_location_option);
// }


// void* get_location(u1 c)
// {
//  void** pv = get_location_ptr(c);
//  if(pv)
//    return *pv;
//  return nullptr;
// }

// void* get_current_location()
// {
//  return get_location(current_location_option);
// }

// struct _opeq_pack {
//  Fetch_Location_Options& _this;
//  u1 c;
//  void operator = (void* v)
//  {
//   if(!v)
//     return;
//   switch (c)
//   {
//   case _index_location: _this.index_location = v; break;
//   case _fallback_location: _this.fallback_location = v; break;
//   case _rebound_index_location: _this.rebound_index_location = v; break;
//   case _rebound_fallback_location: _this.rebound_fallback_location = v; break;
//   case _default_value_pointer: _this.default_value_pointer = v; break;
//   case _default_function_temporary: _this.default_function_temporary = v; break;
//   case _default_constructor_temporary: _this.default_constructor_temporary = v; break;
//   default: return;
//   }
//   _this.current_location_option = c;
//  };

// };
// _opeq_pack current_location(u1 c) { return {*this, c}; }

//};


struct Fetch_Location_Options
{
 enum Premise {
  N_A = 0,
  index_location = 1,
  fallback_location = 2,
  rebound_index_location = 4,
  rebound_fallback_location = 8,
  default_value_pointer = 16,
  default_function = 32,
  default_constructor_temporary = 64,
  zeroed_location = 128,
 };

 void* in_hive_location;
 void* out_of_hive_location;
 void** primary_location;
 void* temporary_value_holder;

 void activate_temporary_value_holder()
 {
  primary_location = &temporary_value_holder;
 }

 void deactivate_temporary_value_holder()
 {
  primary_location = nullptr;
  temporary_value_holder = nullptr;
 }

 void activate_out_of_hive_location()
 {
  primary_location = &out_of_hive_location;
 }

 void deactivate_out_of_hive_location()
 {
  primary_location = nullptr;
 }

 Premise primary_location_premise;
 Premise in_hive_location_premise;
 Premise out_of_hive_location_premise;
 Premise temporary_location_premise;

 Fetch_Location_Options()
  : in_hive_location(nullptr),
    out_of_hive_location(nullptr),
    primary_location(nullptr),
    temporary_value_holder(nullptr),
    primary_location_premise(Premise::N_A),
    in_hive_location_premise(Premise::N_A),
    out_of_hive_location_premise(Premise::N_A),
    temporary_location_premise(Premise::N_A)
 {
 }

// void check_current(u1 c)
// {
//  if(get_location(c)) //  i.e., the pointer there is not nullptr
//    current_location_option = c;
//  else if(positional_location)
//  {
//   if(*positional_location)
//     current_location_option = c;
//  }
// }

// void check_position(u1 c)
// {
//  if(primary_location)
//  {
//   positional_location = primary_location;
//   current_positional_redirect = c;
//   current_active_position = N_A;
//  }
//  else
//  {
//   positional_location = get_location_ptr(c);
//   current_positional_redirect = N_A;
//   current_active_position = c;
//  }
// }

// u1 aggregation_location_options()
// {
//  u1 result = 0;
//  if(index_location) result |= _index_location;
//  if(fallback_location) result |= _fallback_location;
//  if(rebound_index_location) result |= _rebound_index_location;
//  if(rebound_fallback_location) result |= _rebound_fallback_location;

//  if(default_value_pointer) result |= _default_value_pointer;
//  if(default_function_temporary) result |= _default_function_temporary;
//  if(default_constructor_temporary) result |= _default_constructor_temporary;

//  return result;
// }

// void current_to_primary()
// {
//  primary_location = get_current_location_ptr();
// }

// void** get_location_ptr(u1 c)
// {
//  switch (c)
//  {
//  case _index_location: return &index_location;
//  case _fallback_location: return &fallback_location;
//  case _rebound_index_location: return &rebound_index_location;
//  case _rebound_fallback_location: return &rebound_fallback_location;
//  case _default_value_pointer: return &default_value_pointer;
//  case _default_function_temporary: return &default_function_temporary;
//  case _default_constructor_temporary: return &default_constructor_temporary;
//  default: return nullptr;
//  }
// }

// void** get_current_location_ptr()
// {
//  return get_location_ptr(current_location_option);
// }


// void* get_location(u1 c)
// {
//  void** pv = get_location_ptr(c);
//  if(pv)
//    return *pv;
//  return nullptr;
// }

// void* get_current_location()
// {
//  return get_location(current_location_option);
// }

 struct temporary_opeq_pack {
  Fetch_Location_Options& _this;
  u1 c;
  void operator = (void* v)
  {
   if(!v)
     return;
   _this.temporary_value_holder = v;
   _this.temporary_location_premise = (Premise) c;
  }
 };

 struct in_hive_opeq_pack {
  Fetch_Location_Options& _this;
  u1 c;
  void operator = (void* v)
  {
   if(!v)
     return;
   _this.in_hive_location = v;
   _this.in_hive_location_premise = (Premise) c;
  }
 };

 struct out_of_hive_opeq_pack {
  Fetch_Location_Options& _this;
  u1 c;
  void operator = (void* v)
  {
   if(!v)
     return;
   _this.out_of_hive_location = v;
   _this.out_of_hive_location_premise = (Premise) c;
  }
 };


 struct primary_opeq_pack {
  Fetch_Location_Options& _this;
  u1 c;
  void operator = (void** v)
  {
   if(!v)
     return;
   _this.primary_location = v;
   _this.primary_location_premise = (Premise) c;
  }
 };

 temporary_opeq_pack temporary(u1 c) { return {*this, c}; }
 primary_opeq_pack primary(u1 c) { return {*this, c}; }
 in_hive_opeq_pack in_hive(u1 c) { return {*this, c}; }

 void* get_value()
 {
  void* pl = primary_location; //  for debugging
  if(primary_location)
  {
   if(*primary_location)
     return *primary_location;
  }

  return temporary_value_holder;
 }

 void reconcile_in_hive_location(u1 size, void** result = nullptr)
 {
  if(in_hive_location)
  {
   memcpy(in_hive_location, get_value(), size);
   if(result)
     *result = in_hive_location;
  }
 }

};


enum class Out_of_Bounds_Resolution_Flags : u2 {
  N_A = 0,

  Use_Exceptions = 1,
  Accept_Initialize_to_Zero = 2,

  // //  because 1 and 2 are not compatible the combination of the
   //    two can serve as a separate flag ...
  Fallback_Initialize_to_Zero = 3,
  // //  rebound-related flags
   //

  Accept_Default_Value_Nullptr = 4,

  Automatic_Rebound = 8,
  Fallback_Automatic_Rebound = 16,

  Delay_Mitigation_on_Fallback = 32,

  Index_and_Fallback_Shared_Options = 63,

  Automatic_Rebound_and_Accept_Zeroed_Memory = Accept_Initialize_to_Zero | Automatic_Rebound,

 // Highest_Value_Before_Actions = 32,

  Call_Default_Value_Function = 64,
  Use_Default_Value_Pointer = 128,
  Call_Default_Constructor_if_Possible = 256,
  Use_Alternate_Fallback_Index = 512,

// Call_Default_Value_Function = 16,
// Use_Default_Value_Pointer = 32,
// Call_Default_Constructor_if_Possible = 64,
// Use_Alternate_Fallback_Index = 128,


 //  Apply_Mitigation_to_Default_Fallback = 512,

 // Index_and_Fallback_Shared_Options = 15,

  Value_Type_Specific_Options = Use_Default_Value_Pointer | Call_Default_Value_Function
    | Call_Default_Constructor_if_Possible,

//  Alternate_Fallback_Index_Options =
//    Use_Alternate_Fallback_Index | Defer_to_Alternate_Fallback_Index,

  Try_Default_Function_then_Pointer = Call_Default_Value_Function
     | Use_Default_Value_Pointer,

 Try_Default_Function_then_Constructor = Call_Default_Value_Function
     | Call_Default_Constructor_if_Possible,

 Try_Default_Pointer_then_Constructor = Use_Default_Value_Pointer
     | Call_Default_Constructor_if_Possible,

};


#define _oob_N_A    Out_of_Bounds_Resolution_Flags::N_A
#define _oob_Use_Exceptions    Out_of_Bounds_Resolution_Flags::Use_Exceptions
#define _oob_Accept_Initialize_to_Zero   Out_of_Bounds_Resolution_Flags::Accept_Initialize_to_Zero
#define _oob_Fallback_Initialize_to_Zero   Out_of_Bounds_Resolution_Flags::Fallback_Initialize_to_Zero
#define _oob_Accept_Default_Value_Nullptr   Out_of_Bounds_Resolution_Flags::Accept_Default_Value_Nullptr
#define _oob_Automatic_Rebound   Out_of_Bounds_Resolution_Flags::Automatic_Rebound
#define _oob_Fallback_Automatic_Rebound   Out_of_Bounds_Resolution_Flags::Fallback_Automatic_Rebound
#define _oob_Delay_Mitigation_on_Fallback   Out_of_Bounds_Resolution_Flags::Delay_Mitigation_on_Fallback
#define _oob_Call_Default_Value_Function   Out_of_Bounds_Resolution_Flags::Call_Default_Value_Function
#define _oob_Use_Default_Value_Pointer   Out_of_Bounds_Resolution_Flags::Use_Default_Value_Pointer
#define _oob_Call_Default_Constructor_if_Possible   Out_of_Bounds_Resolution_Flags::Call_Default_Constructor_if_Possible
#define _oob_Use_Alternate_Fallback_Index   Out_of_Bounds_Resolution_Flags::Use_Alternate_Fallback_Index


ENUM_FLAGS_OP_MACROS_FREESTANDING(Out_of_Bounds_Resolution_Flags)

inline u2 octal(u1 a1, u1 a2)
{
 return a2 + 8*a1;
}

inline u2 octal(u1 a1, u1 a2, u1 a3)
{
 return a3 + 8*a2 + 64*a1;
}

inline u2 octal(u1 a1, u1 a2, u1 a3, u1 a4)
{
 return a4 + 8*a3 + 64*a2 + 512*a1;
}

constexpr u1 monotone_offset = 6;

inline u1 monotone(Out_of_Bounds_Resolution_Flags f)
{
 u1 mshifted = (u2) f >> monotone_offset;
 return (mshifted == 8)? 4:
  (mshifted == 4)? 3: mshifted;
}

inline Out_of_Bounds_Resolution_Flags demonotone(u1 m)
{
 return (Out_of_Bounds_Resolution_Flags)
   ((u2) ((m == 4)? 8: (m == 3)? 4: m) << monotone_offset);
}

bool get_permutation_numbers(u1 code, u1& first, u1& second, u1& third, u1& fourth);
bool get_permutation_numbers(u1 code, u1& first, u1& second, u1& third);

s1 get_permutation_code(u1& mask, Out_of_Bounds_Resolution_Flags first,
  Out_of_Bounds_Resolution_Flags second,
  Out_of_Bounds_Resolution_Flags third, Out_of_Bounds_Resolution_Flags fourth);
s1 get_permutation_code(u1& mask, Out_of_Bounds_Resolution_Flags first,
  Out_of_Bounds_Resolution_Flags second,
  Out_of_Bounds_Resolution_Flags third);
s1 get_permutation_code(u1& mask, Out_of_Bounds_Resolution_Flags first,
  Out_of_Bounds_Resolution_Flags second);

void parse_permutation_code(u1 code, u1 mask,
  Out_of_Bounds_Resolution_Flags& first, Out_of_Bounds_Resolution_Flags& second,
  Out_of_Bounds_Resolution_Flags& third, Out_of_Bounds_Resolution_Flags& fourth);

u1 encode_mitigation_flags(Out_of_Bounds_Resolution_Flags f1);
u1 encode_mitigation_flags(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2);
u1 encode_mitigation_flags(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3);
u1 encode_mitigation_flags(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4);

u1 encode_fallback_mitigation_flags(Out_of_Bounds_Resolution_Flags f1);
u1 encode_fallback_mitigation_flags(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2);
u1 encode_fallback_mitigation_flags(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3);

std::pair<u1, u1> parse_double_mitigation_flags_encoding(u2 encoding);

std::pair<u1, u1> decode_double_mitigation_flags(u2 encoding,
  Out_of_Bounds_Resolution_Flags& supplement,
  Out_of_Bounds_Resolution_Flags& f11,
  Out_of_Bounds_Resolution_Flags& f12,
  Out_of_Bounds_Resolution_Flags& f13,
  Out_of_Bounds_Resolution_Flags& f14,
  Out_of_Bounds_Resolution_Flags& f21,
  Out_of_Bounds_Resolution_Flags& f22,
  Out_of_Bounds_Resolution_Flags& f23,
  Out_of_Bounds_Resolution_Flags& f24);

u1 decode_mitigation_flags(u1 encoding,
  Out_of_Bounds_Resolution_Flags& f1,
  Out_of_Bounds_Resolution_Flags& f2,
  Out_of_Bounds_Resolution_Flags& f3,
  Out_of_Bounds_Resolution_Flags& f4);

u1 decode_fallback_mitigation_flags(u1 encoding,
  Out_of_Bounds_Resolution_Flags& f1,
  Out_of_Bounds_Resolution_Flags& f2,
  Out_of_Bounds_Resolution_Flags& f3,
  Out_of_Bounds_Resolution_Flags& f4);

u2 encode_double_mitigation_flags_0_0();
u2 encode_double_mitigation_flags_0_1(Out_of_Bounds_Resolution_Flags f21);
u2 encode_double_mitigation_flags_0_2(Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22);
u2 encode_double_mitigation_flags_0_3(Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23);
u2 encode_double_mitigation_flags_0_4(Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23,
  Out_of_Bounds_Resolution_Flags f24);


u2 encode_double_mitigation_flags_1_0(Out_of_Bounds_Resolution_Flags f11);
u2 encode_double_mitigation_flags_1_1(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f21);
u2 encode_double_mitigation_flags_1_2(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22);
u2 encode_double_mitigation_flags_1_3(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23);
u2 encode_double_mitigation_flags_1_4(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23,
  Out_of_Bounds_Resolution_Flags f24);

u2 encode_double_mitigation_flags_2_0(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12);
u2 encode_double_mitigation_flags_2_1(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f21);
u2 encode_double_mitigation_flags_2_2(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22);
u2 encode_double_mitigation_flags_2_3(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23);
u2 encode_double_mitigation_flags_2_4(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23,
  Out_of_Bounds_Resolution_Flags f24);

u2 encode_double_mitigation_flags_3_0(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13);
u2 encode_double_mitigation_flags_3_1(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f21);
u2 encode_double_mitigation_flags_3_2(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22);
u2 encode_double_mitigation_flags_3_3(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23);
u2 encode_double_mitigation_flags_3_4(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23,
  Out_of_Bounds_Resolution_Flags f24);

u2 encode_double_mitigation_flags_4_0(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f14);
u2 encode_double_mitigation_flags_4_1(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f14,
  Out_of_Bounds_Resolution_Flags f21);
u2 encode_double_mitigation_flags_4_2(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f14,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22);
u2 encode_double_mitigation_flags_4_3(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f14,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23);
u2 encode_double_mitigation_flags_4_4(Out_of_Bounds_Resolution_Flags f11,
  Out_of_Bounds_Resolution_Flags f12,
  Out_of_Bounds_Resolution_Flags f13,
  Out_of_Bounds_Resolution_Flags f14,
  Out_of_Bounds_Resolution_Flags f21,
  Out_of_Bounds_Resolution_Flags f22,
  Out_of_Bounds_Resolution_Flags f23,
  Out_of_Bounds_Resolution_Flags f24);

inline u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4,
  Out_of_Bounds_Resolution_Flags f5,
  Out_of_Bounds_Resolution_Flags f6,
  Out_of_Bounds_Resolution_Flags f7,
  Out_of_Bounds_Resolution_Flags f8)
{
 if(split == 4)
   return encode_double_mitigation_flags_4_4(f1, f2, f3, f4, f5, f6, f7, f8);
 return 0;
}

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4,
  Out_of_Bounds_Resolution_Flags f5,
  Out_of_Bounds_Resolution_Flags f6,
  Out_of_Bounds_Resolution_Flags f7);

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4,
  Out_of_Bounds_Resolution_Flags f5,
  Out_of_Bounds_Resolution_Flags f6);

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4,
  Out_of_Bounds_Resolution_Flags f5);

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4);

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3);

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2);

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1);

u2 encode_double_mitigation_flags(s1 split, Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4,
  Out_of_Bounds_Resolution_Flags f5);

inline u2 encode_double_mitigation_flags_shared(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3,
  Out_of_Bounds_Resolution_Flags f4)
{
 return encode_double_mitigation_flags(4, f1, f2, f3, f4, f1, f2, f3, f4);
}

inline u2 encode_double_mitigation_flags_shared(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2,
  Out_of_Bounds_Resolution_Flags f3)
{
 return encode_double_mitigation_flags(3, f1, f2, f3, f1, f2, f3);
}

inline u2 encode_double_mitigation_flags_shared(Out_of_Bounds_Resolution_Flags f1,
  Out_of_Bounds_Resolution_Flags f2)
{
 return encode_double_mitigation_flags(2, f1, f2, f1, f2);
}

inline u2 encode_double_mitigation_flags_shared(Out_of_Bounds_Resolution_Flags f1)
{
 return encode_double_mitigation_flags(1, f1, f1);
}

struct _On_Out_of_Bounds_Pack
{
 u1 for_index_length:3;
 u1 for_fallback_length:3;
 u1 supplement:6;
 u1 for_index_encoding:6;
 u1 f11:4;
 u1 f12:4;
 u1 f13:4;
 u1 f14:4;
 u1 for_fallback_encoding:4;
 u1 f21:4;
 u1 f22:4;
 u1 f23:4;
 u1 f24;

 Out_of_Bounds_Resolution_Flags get_supplement() { return (Out_of_Bounds_Resolution_Flags) supplement; }

 std::pair<u1, u1> unpack(
   Out_of_Bounds_Resolution_Flags& _supplement,
   Out_of_Bounds_Resolution_Flags& _f11,
   Out_of_Bounds_Resolution_Flags& _f12,
   Out_of_Bounds_Resolution_Flags& _f13,
   Out_of_Bounds_Resolution_Flags& _f14,
   Out_of_Bounds_Resolution_Flags& _f21,
   Out_of_Bounds_Resolution_Flags& _f22,
   Out_of_Bounds_Resolution_Flags& _f23,
   Out_of_Bounds_Resolution_Flags& _f24)
 {
  _supplement = (Out_of_Bounds_Resolution_Flags) supplement,
  _f11 = (Out_of_Bounds_Resolution_Flags) (f11 << monotone_offset);
  _f12 = (Out_of_Bounds_Resolution_Flags) (f12 << monotone_offset);
  _f13 = (Out_of_Bounds_Resolution_Flags) (f13 << monotone_offset);
  _f14 = (Out_of_Bounds_Resolution_Flags) (f14 << monotone_offset);
  _f21 = (Out_of_Bounds_Resolution_Flags) (f21 << monotone_offset);
  _f22 = (Out_of_Bounds_Resolution_Flags) (f22 << monotone_offset);
  _f23 = (Out_of_Bounds_Resolution_Flags) (f23 << monotone_offset);
  _f24 = (Out_of_Bounds_Resolution_Flags) (f24 << monotone_offset);
  return {(u1)for_index_encoding, (u1)for_fallback_encoding};
 }
};

inline _On_Out_of_Bounds_Pack decode_out_of_bounds(u2 enc)
{
 Out_of_Bounds_Resolution_Flags f11;
 Out_of_Bounds_Resolution_Flags f12;
 Out_of_Bounds_Resolution_Flags f13;
 Out_of_Bounds_Resolution_Flags f14;

 Out_of_Bounds_Resolution_Flags f21;
 Out_of_Bounds_Resolution_Flags f22;
 Out_of_Bounds_Resolution_Flags f23;
 Out_of_Bounds_Resolution_Flags f24;

 Out_of_Bounds_Resolution_Flags supplement;


 std::pair<u1, u1> pr = decode_double_mitigation_flags(enc, supplement,
   f11, f12, f13, f14, f21, f22, f23, f24);

 std::pair<u1, u1> encs = parse_double_mitigation_flags_encoding(enc);

 return { pr.first, pr.second, (u1) supplement,
  encs.first, (u1)((u2) f11 >> monotone_offset), (u1)((u2) f12 >> monotone_offset),
    (u1)((u2) f13 >> monotone_offset), (u1)((u2) f14 >> monotone_offset),
  encs.second, (u1)((u1) f21 >> monotone_offset),
    (u1)((u2) f22 >> monotone_offset), (u1)((u2) f23 >> monotone_offset),
    (u1)((u2) f24 >> monotone_offset)
  };

}

struct _On_Out_of_Bounds
{
 std::vector<Out_of_Bounds_Resolution_Flags> for_index;
 std::vector<Out_of_Bounds_Resolution_Flags> for_fallback;
 Out_of_Bounds_Resolution_Flags supplement;

 template<typename... Args>
 _On_Out_of_Bounds& operator()(Out_of_Bounds_Resolution_Flags f21, Args... args)
 {
  for_fallback = {f21, args ...};
  return *this;
 }

 _On_Out_of_Bounds& operator [](Out_of_Bounds_Resolution_Flags oob)
 {
  supplement = oob;
  return *this;
 }

 operator u2()
 {
  s2 no_action_flag = 0;
  u2 result = 0;
  u2 sizes = octal((u1)for_index.size(), (u1)for_fallback.size());
  switch(sizes)
  {
  case 0: // // we need a signal that a 0 in the primary
           //   mitigation means no action, not a permutation

          // // Assume it makes no sense to delay mitigation on
           //   fallback if no mitigation is attempted in the first place
   no_action_flag = (u2) _oob_Delay_Mitigation_on_Fallback;
   result = encode_double_mitigation_flags_0_0();
   break;
  case 010: result = encode_double_mitigation_flags(0, for_index[0]);
   break;
  case 020: result = encode_double_mitigation_flags(0, for_index[0], for_index[1]);
   break;
  case 030: result = encode_double_mitigation_flags(0, for_index[0], for_index[1], for_index[2]);
   break;
  case 040: result = encode_double_mitigation_flags(0, for_index[0], for_index[1], for_index[2], for_index[3]);
   break;

  case 001: result = encode_double_mitigation_flags(-1, for_fallback[0]);
   break;
  case 002: result = encode_double_mitigation_flags(-1, for_fallback[0], for_fallback[1]);
   break;
  case 003: result = encode_double_mitigation_flags(-1, for_fallback[0], for_fallback[1], for_fallback[2]);
   break;
  case 004: result = encode_double_mitigation_flags(-1, for_fallback[0], for_fallback[1], for_fallback[2], for_fallback[3]);
   break;

  case 011: result = encode_double_mitigation_flags(1, for_index[0], for_fallback[0]);
   break;
  case 021: result = encode_double_mitigation_flags(2, for_index[0], for_index[1],
              for_fallback[0]);
   break;
  case 031: result = encode_double_mitigation_flags(3, for_index[0], for_index[1], for_index[2],
              for_fallback[0]);
   break;
  case 041: result = encode_double_mitigation_flags(4, for_index[0], for_index[1], for_index[2], for_index[3],
              for_fallback[0]);
   break;

  case 012: result = encode_double_mitigation_flags(1, for_index[0], for_fallback[0], for_fallback[1]);
   break;
  case 022: result = encode_double_mitigation_flags(2, for_index[0], for_index[1],
              for_fallback[0], for_fallback[1]);
   break;
  case 032: result = encode_double_mitigation_flags(3, for_index[0], for_index[1], for_index[2],
              for_fallback[0], for_fallback[1]);
   break;
  case 042: result = encode_double_mitigation_flags(4, for_index[0], for_index[1], for_index[2], for_index[3],
              for_fallback[0], for_fallback[1]);
   break;

  case 013: result = encode_double_mitigation_flags(1, for_index[0], for_fallback[0],
              for_fallback[1], for_fallback[2]);
   break;
  case 023: result = encode_double_mitigation_flags(2, for_index[0], for_index[1],
              for_fallback[0], for_fallback[1], for_fallback[2]);
   break;
  case 033: result = encode_double_mitigation_flags(3, for_index[0], for_index[1], for_index[2],
              for_fallback[0], for_fallback[1], for_fallback[2]);
   break;
  case 043: result = encode_double_mitigation_flags(4, for_index[0], for_index[1], for_index[2], for_index[3],
              for_fallback[0], for_fallback[1], for_fallback[2]);
   break;

  case 014: result = encode_double_mitigation_flags(1, for_index[0], for_fallback[0],
              for_fallback[1], for_fallback[2], for_fallback[3]);
   break;
  case 024: result = encode_double_mitigation_flags(2, for_index[0], for_index[1],
              for_fallback[0], for_fallback[1], for_fallback[2], for_fallback[3]);
   break;
  case 034: result = encode_double_mitigation_flags(3, for_index[0], for_index[1], for_index[2],
              for_fallback[0], for_fallback[1], for_fallback[2], for_fallback[3]);
   break;
  case 044: result = encode_double_mitigation_flags(4, for_index[0], for_index[1], for_index[2], for_index[3],
              for_fallback[0], for_fallback[1], for_fallback[2], for_fallback[3]);
   break;

  default: break;
  }
  u2 s1 = supplement &
    Out_of_Bounds_Resolution_Flags::Index_and_Fallback_Shared_Options; // mask to first four options
  s1 |= no_action_flag;
  u2 s = s1 << 10;
  return result | s;
 }
};

inline _On_Out_of_Bounds on_out_of_bounds(std::vector<Out_of_Bounds_Resolution_Flags> fs)
{
 return {fs, {}, Out_of_Bounds_Resolution_Flags::N_A};
}

template<typename... Args>
_On_Out_of_Bounds on_out_of_bounds(Out_of_Bounds_Resolution_Flags f1, Args... args)
{
 return on_out_of_bounds({f1, args ...});
}

inline _On_Out_of_Bounds on_out_of_bounds(Out_of_Bounds_Resolution_Flags f1)
{
 return on_out_of_bounds(std::vector<Out_of_Bounds_Resolution_Flags>{f1});
}

inline _On_Out_of_Bounds on_out_of_bounds()
{
 return {{}, {}, Out_of_Bounds_Resolution_Flags::N_A};
}


template<typename INDEX_Types>
class Hive_Structure
{
public:


// enum class Out_of_Bounds_Resolution_Flags : u1 {
//   N_A = 0,
//   Use_Exceptions = 1,
//   Automatic_Rebound = 2,
//   Use_Default_Value_Pointer = 4,
//   Call_Default_Value_Function = 8,
//   Call_Default_Constructor_if_Possible = 16,
//   Prefer_Initialize_to_Zero = 32,
//   Use_Alternate_Fallback_Index = 64,
//   Defer_to_Alternate_Fallback_Index = 128,

//   Alternate_Fallback_Index_Options =
//     Use_Alternate_Fallback_Index | Defer_to_Alternate_Fallback_Index,


// };

// ENUM_FLAGS_OP_MACROS(Out_of_Bounds_Resolution_Flags)


 typedef typename INDEX_Types::Numeric_Index_type Numeric_Index_type;
 typedef typename INDEX_Types::Numeric_Nested_Index_type Numeric_Nested_Index_type;

 typedef typename INDEX_Types::Numeric_Index_type nx;
 typedef typename INDEX_Types::Numeric_Nested_Index_type nnx;

// typedef typename GALAXY_Type::element_type element_type;
// typedef typename GALAXY_Type::index_type index_type;
// typedef typename GALAXY_Type::nx nx;
// typedef typename GALAXY_Type::type_descriptor_type type_descriptor_type;


 struct Hive_Layer
 {
  void* elements_;
 };

 struct Hive_Layer_Block
 {
  Hive_Layer* layers_;
  Hive_Layer_Block* next_;
 };

 struct Hive_Layer_Array_Package
 {
  Hive_Layer layer_;
  nnx size_;
//  nnx min_index_;
 };

 struct Hive_Layer_Block_Package
 {
  Hive_Layer_Block* first_block_;
  nnx block_size_;
//  nnx min_index_;
//  nnx max_index_;
 };


// u2 block_size_;
// u4 total_size_;
// u2 value_size_;

// Hive_Layer_Block* first_block_;

 union {
  Hive_Layer_Block_Package* block_package_;
  Hive_Layer_Array_Package* array_package_;
  Hive_Layer single_layer_;
 };

 nnx layer_size_;
 nnx value_size_;
 nx total_size_;

 Out_of_Bounds_Resolution_Flags default_out_of_bounds_resolution_flags_;

public:

// union {
//  Hypocell_Block_Package* block_package_;
//  Hypocell_Array_Package* array_package_;
//  Hypocell cell_;
// };
// nx size_;

 Hive_Structure(nnx layer_size, nnx block_size)
  :  block_package_(new Hive_Layer_Block_Package(
      {new Hive_Layer_Block{new Hive_Layer[block_size], nullptr}, block_size})), //?, 0, 0
      layer_size_(-layer_size), value_size_(QT_POINTER_SIZE), total_size_(0),
      default_out_of_bounds_resolution_flags_(Out_of_Bounds_Resolution_Flags::N_A)
 {
  for(nnx i = 0; i < block_size; ++i)
  {
   block_package_->first_block_->layers_[i] = {nullptr};
  }
 }


 Hive_Structure(Hive_Layer_Block_Package* block_package, nnx size)
  :  block_package_(block_package), layer_size_(-size), value_size_(QT_POINTER_SIZE), total_size_(0),
     default_out_of_bounds_resolution_flags_(Out_of_Bounds_Resolution_Flags::N_A)
 {
 }

 Hive_Structure(Hive_Layer_Array_Package* array_package)
  :  array_package_(array_package), layer_size_(0), value_size_(QT_POINTER_SIZE), total_size_(0),
     default_out_of_bounds_resolution_flags_(Out_of_Bounds_Resolution_Flags::N_A)
 {
 }

 Hive_Structure(Hive_Layer layer, nnx size)
  :  single_layer_(layer), layer_size_(size), value_size_(QT_POINTER_SIZE), total_size_(0),
     default_out_of_bounds_resolution_flags_(Out_of_Bounds_Resolution_Flags::N_A)
 {
 }

 Hive_Structure()
  :  block_package_(nullptr), layer_size_(0), value_size_(QT_POINTER_SIZE), total_size_(0),
     default_out_of_bounds_resolution_flags_(Out_of_Bounds_Resolution_Flags::N_A)
 {
 }

 ACCESSORS(nnx ,value_size)
 ACCESSORS(nx ,total_size)

 void init_single_layer(nx size)
 {
  layer_size_ = size;
  single_layer_.elements_ = malloc(value_size_ * size);
 }

 void** get_zeroed_location()
 {
  static void* result = nullptr;
  if(!result)
    result = calloc(1, value_size_);
  return &result;
 }

 Hive_Layer* get_fixed_size_layer()
 {
  if(layer_size_ == 0)
    return &array_package_->layer_;
  return &single_layer_;
 }

 nnx get_block_number(Numeric_Index_type nix)
 {
  return nix / ((nx) block_size() * layer_size());
 }

 nnx get_block_position(Numeric_Index_type nix)
 {
  return nix % ((nx) block_size() * layer_size());
 }

 nnx get_layer_order(Numeric_Index_type nix)
 {
  return get_block_position(nix) / layer_size();
 }

 nx get_layer_rank(Numeric_Index_type nix)
 {
  return nix / layer_size();
 }

 nnx get_inner_index(Numeric_Index_type nix)
 {
  return nix % layer_size();
 }

 nnx block_size()
 {
  if(layer_size_ < 0)
    return block_package_->block_size_;
  return 0;
 }

 Numeric_Nested_Index_type layer_size()
 {
  if(layer_size_ < 0)
    return -layer_size_;
  if(layer_size_ == 0)
    return array_package_->size_;
  return layer_size_;
 }

 Hive_Layer* layer_ptr()
 {
  if(layer_size_ == 0)
    return &array_package_->layer_;
  return &single_layer_;
 }

 Hive_Layer* get_layer_by_layer_order(nnx block_number, nnx layer_order);
 Hive_Layer* get_layer_by_layer_rank(nnx layer_rank)
 {
  return get_layer_by_layer_order(layer_rank / block_size(), layer_rank % block_size());
 }

 void check_init_layer(Hive_Layer* hl)
 {
  if(!hl->elements_)
    hl->elements_ = malloc(value_size_ * layer_size());
 }

 Hive_Layer* new_hive_layers();

 bool fixed_size()
 {
  return layer_size_ >= 0;
 }

 void delete_block(Hive_Layer_Block* hlb)
 {
  for(nnx i = 0; i < block_package_->block_size_; ++i)
  {
   if(hlb->layers_[i].elements_)
     delete hlb->layers_[i].elements_;
  }
 }

 void check_max_index(nx ind)
 {
  if(layer_size_ < 0)
  {
   if(block_package_->max_index_ < ind)
     block_package_->max_index_ = ind;
  }
 }

 static nx the_invalid_index()
 {
  return _the_invalid_index<Numeric_Index_type>();
 }

 static nx the_invalid_upper_index()
 {
  return _the_invalid_upper_index<Numeric_Index_type>();
 }


 nx get_minimum_array_index()
 {
  if(layer_size_ < 0)
    return block_package_->min_index_;
  if(layer_size_ == 0)
    return array_package_->min_index;
  return 0;
 }

 void set_maximum_array_index(nx ind)
 {
  if(layer_size_ < 0)
    block_package_->max_index_ = ind;
//   if(size_ == 0)
//     return 0; // array_package_->max_index;
//   return 0;
 }

 nx get_maximum_array_index()
 {
  if(layer_size_ < 0)
    return block_package_->max_index_;
  if(layer_size_ == 0)
    return 0; // array_package_->max_index;
  return 0;
 }

 nx normalized_array_index(nx ind)
 {
  if(layer_size_ < 0)
  {
   nx minin = block_package_->min_index_;
   nx maxin = block_package_->max_index_;

   ind += minin;
   maxin += minin;
   if(ind > maxin)
     ind = minin;
  }
  else if(layer_size_ == 0)
  {
   nx minin = array_package_->min_index;
   ind += minin;
   ind %= array_package_->size;
  }
  return ind;
 }

 //element_type& get_element(nx index);
 void* get_location(nx nix);

 struct pre_iterator
 {
  nnx block_number;
  nnx layer_order;
  nnx inner_index;

  QString to_qstring()
  {
   return QString("Block Number: %1\nLayer Order: %2\nInner Index: %3")
     .arg(block_number).arg(layer_order).arg(inner_index);
  }
 };

 void resize(nx nix);

 void rebound_to(nx nix)
 {
  set_total_size(nix + 1);
 }

 void* rebound(nx nix);

 void* rebound(nx nix, void* pv)
 {
  void* spot = rebound(nix);
  memcpy(spot, pv, value_size());
  return spot;
 }

 void* check_rebound(nx nix, void* pv)
 {
  void* spot = rebound(nix);
  if(!spot)
    spot = get_indexed_location_unchecked(nix);
  memcpy(spot, pv, value_size());
  return spot;
 }

// void* fetch(nx nix, nx fallback, Out_of_Bounds_Resolution_Flags oob);

 void* fetch_out_of_bounds(nx nix, Out_of_Bounds_Resolution_Flags oob);
 void* fetch(nx nix, Out_of_Bounds_Resolution_Flags oob);
// {
//  fetch(nix, 0, oob);
// }

 void* fetch_at(nx nix, Out_of_Bounds_Resolution_Flags oob);

// void* fetch(nx nix, nx fallback)
// {
//  fetch(nix, fallback, default_out_of_bounds_resolution_flags_);
// }

 //void* fetch_at(nx nix, nx fallback, u1* val);

 void* get(nx nix);

 pre_iterator parse_location(nx nix);

 struct iterator
 {
  nnx block_number;
  nnx layer_order;
  nnx inner_index;
  nx total_index;

  static iterator start()
  {
   return iterator{0,0,0,0};
  }

  bool within(const iterator& rhs)
  {
   if(end())
     return false;
   return total_index < rhs.total_index;
  }

  bool end()
  {
   return total_index == the_invalid_index();
  }

  iterator _end()
  {
   return iterator{block_number, layer_order, inner_index, the_invalid_upper_index()};
  }

 };

 iterator iterator_at(nx nix)
 {
  pre_iterator pre = parse_location(nix);
  return {pre.block_number, pre.layer_order, pre.inner_index, nix};
 }

 //void fill(iterator it, const VAL_Type& v, iterator bound)

// Hive_Structure();


// ACCESSORS(u2, block_size)
// ACCESSORS(u4, total_size)
// ACCESSORS(u2, value_size)

// ACCESSORS(Hive_Block*, first_block)

 void* contiguous(nx nix1, nx nix2);
 void* contiguous(nx nix1, nx nix2, QVector<QPair<void*, nx>>* breakdown);



 void* get_push_back_location();
 void* get_back_location();

 void* get_indexed_location(nx nix);
 void* get_indexed_location(nnx block_number, nnx layer_order, nnx inner_index);

 void* get_raw_indexed_location(nx nix);
 void* get_raw_indexed_location(nnx block_number, nnx layer_order, nnx inner_index);

 void* get_indexed_location_unchecked(nx nix);

 Hive_Layer* get_layer_for_indexed_location(nnx block_number, nnx layer_order);

 Hive_Layer_Block* check_init_blocks(nnx max);
 Hive_Layer_Block* get_block_by_number(nnx desired_block_number);

 void* get_iterator_location(iterator& hit);

 void increment_iterator(iterator& hit);
 void increment_total_size();
 void reverse_iterator(iterator& hit);
 void decrement_iterator(iterator& hit);
 void position_iterator(iterator& hit, Numeric_Index_type nix);

 void check_start_iterator(iterator& hit);

 void pop_back();
 void pop_first_block();
 void push_first_block();

};

_XCNS(XCSD)

#include "hive-structure.templates.h"

USING_XCNS(XCSD)

using Hive_Structure_s2 = Hive_Structure<index_types<s2>>;
using Hive_Structure_s4 = Hive_Structure<index_types<s4>>;



#ifdef HIDE
struct Hive_Block
{
 void* values;
 Hive_Block* next_block;
};


class Hive_Structure
{
 u2 block_size_;
 u4 total_size_;
 u2 value_size_;

 Hive_Block* first_block_;

public:


 struct iterator
 {
  u4 block_index;
  u2 inner_index;
  u4 total_index;

  static iterator start()
  {
   return iterator{0,0,0};
  }

  bool end()
  {
   return total_index == -1;
  }
 };


 Hive_Structure();


 ACCESSORS(u2, block_size)
 ACCESSORS(u4, total_size)
 ACCESSORS(u2, value_size)

 ACCESSORS(Hive_Block*, first_block)

 void* get_push_back_location();
 void* get_back_location();

 void* get_indexed_location(u4 index);
 void* get_indexed_location(u4 blkn, u2 blki);
 void* get_indexed_location_unchecked(u4 index);

 Hive_Block* check_init_blocks(u4 max);

 void* get_iterator_location(iterator& hit);

 void increment_iterator(iterator& hit);
 void increment_total_size();
 void reverse_iterator(iterator& hit);
 void decrement_iterator(iterator& hit);
 void position_iterator(iterator& hit, u4 ix);

 void check_start_iterator(iterator& hit);

 void pop_back();
 void pop_first_block();
 void push_first_block();
};

#endif



#endif // HIVE_STRUCTURE__H
