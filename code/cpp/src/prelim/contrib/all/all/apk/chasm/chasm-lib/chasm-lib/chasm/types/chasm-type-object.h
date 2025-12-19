
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_TYPE_OBJECT__H
#define CHASM_TYPE_OBJECT__H

#include <QString>

#include <QMetaType>

#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include <functional>

#include "kans.h"

//#include "chasm-carrier.h"

#include "../chasm-runtime.h"

#include "flags.h"

//KANS_(GTagML)

class Chasm_Type_Object
{
public:

 enum class Built_In_Status : s2 {
  N_A = 0, u_like = 1, s_like = 2,
  r_like = 4, n8_like = 8,
  QString_like = 16,
  QByteArray_like = 32,
  QVariant_like = 64,
  QStringList_like = 128,

  associate_via_ptr = 8192,
  associate_via_ref = 16384,
 };

private:

 QString name_;

 Built_In_Status built_in_status_;
 u1 byte_span_;

 QMetaType* qmetatype_;

 u2 codes_with_position_[4];

 Chasm_Type_Object* associate_;

public:

 Chasm_Type_Object(QString name, Built_In_Status st,
  u1 byte_span, u2 c0, u2 c1, u2 c2, u2 c3);

 ACCESSORS(QString ,name)
 ACCESSORS(Built_In_Status ,built_in_status)
 ACCESSORS(u1 ,byte_span)

 u1 get_pretype_code();


 Chasm_Typed_Value_Representation with_rep(QString rep)
 {
  return {this, 0, rep};
 }

 Chasm_Typed_Value_Representation with_instance(void* v)
 {
  return {this, (n8) v, {}};
 }

 template<typename T>
 Chasm_Typed_Value_Representation make_instance(T* v)
 {
  if(name_.endsWith("!"))
  {
   std::shared_ptr<T>* ss = new std::shared_ptr<T>(v);
   return with_instance(ss);
  }
   // v = new std::shared_ptr<n8>((n8*) v);

  return with_instance(v);
 }

};

// _KANS(GTagML)

#endif // CHASM_TYPE_OBJECT__H

