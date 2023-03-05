
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_FIELD_INFO__H
#define QH_FIELD_INFO__H

#include <QByteArray>

#include <functional>

#include "global-types.h"

#include "accessors.h"

#include "qh-pack-code.h"

KANS_(RdSC)

class Qh_Field_Info
{
 QString name_;

 QString accessors_code_;

 QString units_quantity_;
 QString units_scale_;


public:

 Qh_Field_Info(QString name = {});

 ACCESSORS(QString ,name)

 ACCESSORS__DECLARATIVE(Qh_Field_Info,QString ,accessors_code)
 ACCESSORS__DECLARATIVE__SET(Qh_Field_Info,QString ,units_quantity)
 ACCESSORS__DECLARATIVE__SET(Qh_Field_Info,QString ,units_scale)


};

_KANS(RdSC)


#endif // QH_CLASS_OBJECT__H


