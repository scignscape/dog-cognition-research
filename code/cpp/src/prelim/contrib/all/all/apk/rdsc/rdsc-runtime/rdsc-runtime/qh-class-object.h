
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_CLASS_OBJECT__H
#define QH_CLASS_OBJECT__H

#include <QByteArray>

#include <functional>

#include "global-types.h"

#include "accessors.h"

#include "qh-pack-code.h"

KANS_(RdSC)

class Qh_Type;
class Qh_Type_System;

class Qh_Class_Object
{
 Qh_Type* qh_type_;
 QString name_;
 Qh_Pack_Code pack_code_;

 void* local_;

public:

 Qh_Class_Object(Qh_Type* qh_type, QString name = {});

 ACCESSORS(QString ,name)
 ACCESSORS__RGET(Qh_Pack_Code ,pack_code)
 ACCESSORS(Qh_Type* ,qh_type)

 Qh_Type_System* operator->();


 template<typename Local>
 Qh_Class_Object& qh_local(Local* lcl)
 {
  local_ = lcl;
  return *this;
 }

 template<typename PROV_Type>
 Qh_Class_Object& deffields(void(*fn)(PROV_Type*, Qh_Class_Object&))
 {
  fn((PROV_Type*) local_, *this);
  return *this;
 }

 template<typename PROV_Type>
 Qh_Class_Object& deffields(void(PROV_Type::*fn)(Qh_Class_Object&))
 {
  (((PROV_Type*) local_)->*fn)(*this);
  return *this;
 }

 Qh_Class_Object& deffields(void(*fn)(Qh_Class_Object&))
 {
  fn(*this);
  return *this;
 }

};

_KANS(RdSC)


#endif // QH_CLASS_OBJECT__H


