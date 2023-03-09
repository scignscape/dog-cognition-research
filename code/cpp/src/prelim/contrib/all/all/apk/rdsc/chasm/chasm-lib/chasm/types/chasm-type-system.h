
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_TYPE_SYSTEM__H
#define CHASM_TYPE_SYSTEM__H

#include <QString>

#include <QStack>
#include <QVariant>

#include <QDebug>

#include "accessors.h"
#include "global-types.h"

class Chasm_Type_Object;

class Chasm_Type_System
{
 QMap<QString, Chasm_Type_Object*> type_objects_;

 QVector<Chasm_Type_Object*>* pretype_type_objects_;

public:

 Chasm_Type_System();

 ACCESSORS__GET(QVector<Chasm_Type_Object*>* ,pretype_type_objects)

 Chasm_Type_Object* register_type_object(QString name, u2 pos1code, u2 pos2code,
   u2 pos3code, u2 pos4code);

 Chasm_Type_Object* get_type_object_by_name(QString name);

};

// _KANS(GTagML)

#endif // CHASM_TYPE_SYSTEM__H
