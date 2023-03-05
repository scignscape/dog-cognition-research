
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-class-object.h"

#include "qhr/qh-type-system.h"
#include "qhr/qh-type.h"


USING_KANS(RdSC)


Qh_Class_Object::Qh_Class_Object(Qh_Type* qh_type, QString name)
  :  qh_type_(qh_type), name_(name)
{

}

Qh_Type_System* Qh_Class_Object::operator->()
{
 return qh_type_->operator->();
}
