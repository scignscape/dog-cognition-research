
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_RUNTIME__H
#define QH_RUNTIME__H

#include <QByteArray>

#include <functional>

#include "global-types.h"

#include "accessors.h"

#include "qh-type-system.h"
#include "qh-type.h"


KANS_(RdSC)

//class Qh_Type_System;
class Qh_Hypernode;

class Qh_Runtime
{
 Qh_Type_System* type_system_;

 //Qh_Hypernode* new_hypernode(void* pv, Qh_Type* qht);

public:

 Qh_Runtime();


 ACCESSORS(Qh_Type_System* ,type_system)

 Qh_Pack_Builder* serialize(Qh_Type* qht, void* obj);

 template<typename OBJ_Type>
 Qh_Pack_Builder* serialize(OBJ_Type* obj)
 {
  QString res;
  QString tn = QString::fromStdString(typeid(OBJ_Type).name());
  Qh_Type* qht = type_system_->get_type_by_name(tn, &res);
  return serialize(qht, obj);
 }


};

_KANS(RdSC)

#endif // QH_RUNTIME__H


