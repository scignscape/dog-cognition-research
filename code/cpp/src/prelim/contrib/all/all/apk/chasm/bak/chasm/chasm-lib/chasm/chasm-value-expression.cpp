
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-value-expression.h"

#include "chasm/chasm-runtime.h"
#include "chasm/chasm-call-package.h"


#include <QString>
#include <QVariant>
#include <QByteArray>

#include <QUrl>

#include <QPoint>

#include <QRegularExpression>

#include <tuple>

Chasm_Value_Expression::Chasm_Value_Expression(n8 raw_value)
  :  raw_value_(raw_value)
{
}

//Chasm_Value_Expression::Rep_State Chasm_Value_Expression::rep_state_1()
//{
// QPair<n8, n8>* pr = (QPair<n8, n8>*) (raw_value_ - 1);
// switch (code)
// {
// case 0: return Type_Object;
// case 1: return Type_Object;

// case 3: return Fixnum;
// }
//}


//Chasm_Value_Expression::Rep_State Chasm_Value_Expression::rep_state()
//{
// if(raw_value_ == 0)
//   return N_A;
// u1 code = raw_value_ & 3;
// switch (code)
// {
// case 0: return Type_Object;
// case 1: return Type_Object;

// case 3: return Fixnum;
// }
//}

u1 Chasm_Value_Expression::get_pair_code2()
{
 std::pair<n8, n8>* pr = (std::pair<n8, n8>*) (raw_value_ - 1);
 u1 c1 = pr->first & 3;
 if(c1 == 2)
 {
  // //  i.e. the first is a type object and second is raw n8 
  return 0b00100010; // (34) 
 }
 u1 c2 = pr->second & 3;
 return (c1 << 4) | (c2 << 2) | 2;
}

u1 Chasm_Value_Expression::get_pair_code3()
{
 std::tuple<n8, n8, n8>* triple = (std::tuple<n8, n8, n8>*) (raw_value_ - 1);
 u1 c1 = std::get<0>( *triple ) & 3;
 u1 c3 = std::get<2>( *triple ) & 3;

 if(c1 == 2)
 {
  // //  i.e. the first is a type object and second is raw n8 
  return 0b10000010 | (c3 << 2); // (34) 
 }
 
 u1 c2 = std::get<1>( *triple ) & 3;

 return (c1 << 6) | (c2 << 4) | (c3 << 2) | 3;
}

u1 Chasm_Value_Expression::get_pair_code()
{
 if(raw_value_ == 0)
   return 0;
 u1 code = raw_value_ & 3;

 switch (code)
 {
  case 0: return 1;
  case 1: return get_pair_code2();
  case 2: return get_pair_code3();
  case 3: return 5;
 }
}

Chasm_Value_Expression::Chasm_Value_Expression(QString rep)
  :  raw_value_(0)
{
}

u1 Chasm_Value_Expression::get_hint_pretype_code()
{
 u1 spread = raw_value_ & 3;
 if(spread == 3)
 {
  u1 hints = raw_value_ - 3;
  if(hints == 0)
    return 1;
 }
 return 0;
}


u1 Chasm_Value_Expression::get_u1()
{
 u1 spread = raw_value_ & 3;
 if(spread == 3)
 {
  return (raw_value_ >> 8) & 255;
 }
 return 0;
}


QString* Chasm_Value_Expression::get_qstring()
{
 u1 spread = raw_value_  & 3;
 if(spread == 2)
 {
  QPair<n8, n8>* pr = (QPair<n8, n8>*) (raw_value_ - 2);
  u1 pr1code = pr->first & 3;
  if(pr1code == 0)
  {
   u1 pr2code = pr->second & 3;
   if(pr2code == 1)
     return (QString*) (pr->second - 1);
  }
 }

 return nullptr;
}


Chasm_Type_Object* Chasm_Value_Expression::get_type_object()
{
 u1 spread = raw_value_  & 3;
 if(spread == 2)
 {
  QPair<n8, n8>* pr = (QPair<n8, n8>*) (raw_value_ - 2);
  u1 pr1code = pr->first & 3;
  if(pr1code == 0)
    return (Chasm_Type_Object*) pr->first;
  return nullptr;
 }
 if(spread == 3)
 {

 }
 return nullptr;
}

void Chasm_Value_Expression::split_defer(QString rep, Chasm_Type_Object* cto)
{
 QString* prep = new QString(rep);
 QPair<n8, n8>* pr = new QPair<n8, n8>((n8)cto, (n8)prep);
 pr->second |= 1;
 raw_value_ = (n8) pr;
 raw_value_ |= 2;
}

void Chasm_Value_Expression::parse_qsl(QString rep, Chasm_Type_Object* cto)
{
 split_defer(rep, cto);
}

void Chasm_Value_Expression::parse_qs(QString rep, Chasm_Type_Object* cto)
{
 split_defer(rep, cto);
}

void Chasm_Value_Expression::parse_b1(QString rep, Chasm_Type_Object* cto)
{

}
void Chasm_Value_Expression::parse_u1(QString rep, Chasm_Type_Object* cto)
{
 raw_value_ = 3;

 u1 u = rep.toUInt();

 raw_value_ |= (u << 8);
}
void Chasm_Value_Expression::parse_u2(QString rep, Chasm_Type_Object* cto)
{

}
void Chasm_Value_Expression::parse_u4(QString rep, Chasm_Type_Object* cto)
{

}
void Chasm_Value_Expression::parse_s1(QString rep, Chasm_Type_Object* cto)
{

}
void Chasm_Value_Expression::parse_s2(QString rep, Chasm_Type_Object* cto)
{

}
void Chasm_Value_Expression::parse_s4(QString rep, Chasm_Type_Object* cto)
{

}
void Chasm_Value_Expression::parse_n8(QString rep, Chasm_Type_Object* cto)
{

}
void Chasm_Value_Expression::parse_r8(QString rep, Chasm_Type_Object* cto)
{

}
void Chasm_Value_Expression::parse_r4(QString rep, Chasm_Type_Object* cto)
{

}
void Chasm_Value_Expression::parse_other(QString rep) //, Chasm_Type_Object* cto)
{

}

//void Chasm_Value_Expression::parse(QString type_string, QString rep)
//{
// Known_Type_Strings k = parse_known_type_string(type_string);

// switch (k)
// {
// default: parse_other(rep); break;
// case Known_Type_Strings::QSL: parse_qsl(rep); break;
// case Known_Type_Strings::QS: parse_qs(rep); break;
// case Known_Type_Strings::B1: parse_b1(rep); break;
// case Known_Type_Strings::U1: parse_u1(rep); break;
// case Known_Type_Strings::U2: parse_u2(rep); break;
// case Known_Type_Strings::U4: parse_u4(rep); break;
// case Known_Type_Strings::S1: parse_s1(rep); break;
// case Known_Type_Strings::S2: parse_s2(rep); break;
// case Known_Type_Strings::S4: parse_s4(rep); break;
// case Known_Type_Strings::N8: parse_n8(rep); break;
// case Known_Type_Strings::R4: parse_r4(rep); break;
// case Known_Type_Strings::R8: parse_r8(rep); break;
// }
// //raw_value_ = rep.toInt();
//}

//QVector<Chasm_Value_Expression> operator""_cvx(const char* ss, unsigned long len)
//{
//}

//void* Chasm_Value_Expression::val1of2()
//{

//}


//Chasm_Type_Object* Chasm_Value_Expression::get_type_object()
//{
// u1 pc = get_pair_code();
// switch(pc & 3)
// {
// case 0: return nullptr; // // i.e. just a qstring (pointer)
// case 1:
//  {
//   u1 c1 = pc >> 4;
//   if( (c1 == 1) || (c1 == 3) ) return nullptr;
//   return (Chasm_Type_Object*) val1of2();
//  }

// case 2: return get_pair_code3();
// case 3: return nullptr; // // i.e. just a number
// }

//}


