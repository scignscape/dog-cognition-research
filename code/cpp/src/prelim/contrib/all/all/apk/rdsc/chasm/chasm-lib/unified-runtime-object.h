
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef UNIFIED_RUNTIME_OBJECT__H
#define UNIFIED_RUNTIME_OBJECT__H

#include <QString>
#include <QMap>

#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include "kans.h"


//KANS_(GTagML)

class Compilation_Unit_Object;
class Metatype_Object;

class Unified_Runtime_Object
{
 QString file_path_;

 QMap<QString, Compilation_Unit_Object*> registered_compilation_unit_objects_;
 QMap<QString, Metatype_Object*> registered_metatype_objects_;

 Unified_Runtime_Object(QString file_path);

public:

 static Unified_Runtime_Object* instance();

 ACCESSORS(QString ,file_path)

 void register_compilation_unit_object(Compilation_Unit_Object* cuo);
 void register_metatype_object(Metatype_Object* cuo);
 void register_new_metatype_object(QString type_name);

 Metatype_Object* get_metetype_object_by_type_name(QString type_name);

};

// _KANS(GTagML)

#endif
