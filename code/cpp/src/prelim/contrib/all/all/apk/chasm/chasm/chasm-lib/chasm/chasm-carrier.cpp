
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-carrier.h"


//#include "kans.h"
//USING_KANS(GTagML)

#include <QDebug>

//#include "compilation-unit-object.h"
//#include "unified-runtime-object.h"
//#include "metatype-object.h"


Chasm_Carrier::Chasm_Carrier()
  :  key_(), raw_value_(0)
{

}

template<>
QString Chasm_Carrier::value<QString>()
{
 return value_as<QString>();
}


template<>
void Chasm_Carrier::set_value_as<QString>(const QString& val)
{
 take_value(const_cast<QString*>(&val));
}

template<>
void Chasm_Carrier::set_value_as<void*>(void* const& val)
{
 take_value(const_cast<void**>(&val));
}

template<>
void Chasm_Carrier::set_value_as<QByteArray>(const QByteArray& val)
{
 take_value(const_cast<QByteArray*>(&val));
}

template<>
void Chasm_Carrier::set_value_as<QVariant>(const QVariant& val)
{
 take_value(const_cast<QVariant*>(&val));
}

//Chasm_Carrier& Chasm_Carrier::take_string_value()
//{
// u1 tf = key_.type_flag();

// switch (tf)
// {
// case 0:
// }
//}


n8 Chasm_Carrier::pasn8()
{
 u1 tf = key_.type_flag();

 if( (tf == 0) || (tf == 3) || (tf == 5) || (tf == 7) )
   return raw_value_;

 if(tf == 14)
 {
  return (n8) ((std::shared_ptr<n8>*) raw_value_)->get();
 }

 return (n8) &raw_value_;
}


Chasm_Carrier& Chasm_Carrier::take_shared_ref_value(std::shared_ptr<n8>* ss)
{
 u1 tf = key_.type_flag();

 // // tf only = 0?

 if(tf != 0)
   return *this;

 key_.set_type_flag(14);

 raw_value_ = (n8) ss; //->get();

 //delete ss;

}


Chasm_Carrier& Chasm_Carrier::take_value(void* pv)
{
 u1 tf = key_.type_flag();

 switch (tf)
 {
 case 0: set_raw_value( (n8) pv ); break; //

 case 1: set_raw_value( (n8) *(u1*)pv ); break;
 case 2: set_raw_value( (n8) *(u2*)pv ); break;
 case 3: set_raw_value( (n8) new QString(*(QString*)pv) ); break;
 case 4: set_raw_value( (n8) *(u4*)pv ); break;
 case 5: set_raw_value( (n8) new QByteArray(*(QByteArray*)pv) ); break;
 case 6: set_value_reinterpret(pv); break;
 case 7: set_raw_value( (n8) new QVariant(*(QVariant*)pv) ); break;
 case 8: set_raw_value( (n8) *(n8*)pv ); break;
 case 9: set_raw_value( (n8) *(void**)pv ); break;

 default: break;

 }

 return *this;

}


