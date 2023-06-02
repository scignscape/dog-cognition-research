
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_CARRIER__H
#define CHASM_CARRIER__H

#include <QString>

#include <memory>

#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include <functional>

#include "kans.h"


//KANS_(GTagML)

struct trisym
{
 n8 code;

 // //  15 type flag = unknown
 trisym() : code(15) {}

 void set_fcode(u4 val)
 {
  // // only lowest three bytes
  val &= 0xFFFFFF;

  // // clear highest three bytes
  code &= 0x000000FFFFFFFFFF;

  code |= (((n8) val) << 40);
 }

 void set_lcode(s4 val)
 {
  // // only lowest three bytes
  val &= 0xFFFFFF;

  // // clear bytes 4-6
  code &= 0xFFFFFF000000FFFF;

  code |= (((n8) val) << 24);
 }

 void set_ccode(u2 val)
 {
  // // reserve lowest 4 val bits
  val <<= 4;

  // // clear lowest 2 bytes except lowest 4 bits
  code &= ~((n8)0xFFF0);

  code |= val;
 }

 void set_type_flag(u1 tf)
 {
  // // only lowest 4 bits
  tf &= 0x0F;

  // // clear lowest 4 bits
  code &= ~((n8)0x0F);

  code |= tf;
 }


 u4 fcode() { return (code & 0xFFFFFF0000000000) >> 40; }
 s4 scode() { return (code & 0x000000FFFFFF0000) >> 24; }
 u4 ccode() { return (code & 0xFFF0) >> 4; }

 u1 type_flag() { return (code & 0x0F); }

};


class Chasm_Carrier
{
 template<typename VALUE_Type>
 friend struct _value;
 //QString text_;

 trisym key_;
 n8 raw_value_;

public:

 Chasm_Carrier();

 ACCESSORS(trisym ,key)
 ACCESSORS(n8 ,raw_value)

 void set_type_flag(u1 tf)
 {
  key_.set_type_flag(tf);
 }

 void set_value_reinterpret(const void* val)
 {
//  double* dd = (double*)val;
//  n8* nn = (n8*)dd;
//  n8 n = *nn;
  raw_value_ = *(n8*)val;
 }

 Chasm_Carrier& take_value(void* pv);

// Chasm_Carrier& take_string_value();

 Chasm_Carrier& take_shared_ref_value(std::shared_ptr<n8>* ss);

 n8 pasn8();

// n8& pasn8_ref()
// {
//  u1 tf = key_.type_flag();
//  if(tf == 3)
//  {
//   QString* qs = (QString*) raw_value_;
//   return raw_value_;
//  }
//  if(tf == 0)
//  {
//   return (n8&) *(n8*)raw_value_;
//  }
//  //return (n8) &raw_value_;
// }

 template<typename VALUE_Type>
 VALUE_Type& value_as()
 {
  return *(VALUE_Type*)raw_value_;
 }

 template<typename VALUE_Type>
 VALUE_Type raw_value_as()
 {
  return (VALUE_Type)raw_value_;
 }

 template<typename VALUE_Type>
 VALUE_Type reinterpret_value()
 {
  return *(VALUE_Type*)&raw_value_;
 }

 template<typename VALUE_Type>
 void set_value_as(const VALUE_Type& val);


 template<typename VALUE_Type>
 void set_value(const VALUE_Type& val)
 {
  u1 tf = key_.type_flag();

  switch (tf)
  {
  case 1: case 2: case 4: case 8: set_raw_value( (n8) val ); break;
  case 6: set_value_reinterpret(&val); break;

//  case 3:
  default: take_value((void*) &val );
  }
 }

// QString qstring_value()
// {
//  return value_as<QString>();
// }

 template<typename VALUE_Type>
 VALUE_Type _value()
 {
  u1 tf = key_.type_flag();

  switch (tf)
  {
  case 1: case 2: case 4: case 8: case 9: return (VALUE_Type) raw_value_; break;
  case 6: return reinterpret_value<VALUE_Type>(); break;

  default: return value_as<VALUE_Type>();
  }
 }


 template<typename VALUE_Type>
 VALUE_Type value();

// void test_method(QString path, u4 val1, u4 val2);


};

struct FALSE_Type{};
struct TRUE_Type{};

template<typename BOOL_Type>
struct _Value
{
 template<typename VALUE_Type>
 static VALUE_Type get(Chasm_Carrier& cc);
};

template<>
template<typename VALUE_Type>
VALUE_Type _Value<FALSE_Type>::get(Chasm_Carrier& _this)
{
 return _this._value<VALUE_Type>();
}

template<>
template<typename VALUE_Type>
VALUE_Type _Value<TRUE_Type>::get(Chasm_Carrier& _this)
{
 return _this.value_as<VALUE_Type>();
}


template<typename VALUE_Type>
struct Special_Type
{
 typedef FALSE_Type _typ;
};

template<>
struct Special_Type<QString>
{
 typedef TRUE_Type _typ;
};

template<>
struct Special_Type<QByteArray>
{
 typedef TRUE_Type _typ;
};


template<typename VALUE_Type>
VALUE_Type Chasm_Carrier::value()
{
 return _Value<typename Special_Type<VALUE_Type>::_typ>::template get<VALUE_Type>(*this);
}

//template<typename VALUE_Type>
//VALUE_Type Chasm_Carrier::value()
//{
// return Chasm_Carrier_value(*this);
//}

// void test_cuo();



// _KANS(GTagML)

#endif // CHASM_CARRIER__H

