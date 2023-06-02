
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "unified-runtime-object.h"

#include "compilation-unit-object.h"
#include "metatype-object.h"


#include "kans.h"

//USING_KANS(GTagML)


Unified_Runtime_Object::Unified_Runtime_Object(QString file_path)
  :  file_path_(file_path)
{

}

Unified_Runtime_Object* Unified_Runtime_Object::instance()
{
 static Unified_Runtime_Object* result = new Unified_Runtime_Object(__FILE__);
 return result;
}

void Unified_Runtime_Object::register_compilation_unit_object(Compilation_Unit_Object* cuo)
{
 registered_compilation_unit_objects_[cuo->file_path()] = cuo;
}

void Unified_Runtime_Object::register_metatype_object(Metatype_Object* mto)
{
 registered_metatype_objects_[mto->get_full_name()] = mto;
}

void Unified_Runtime_Object::register_new_metatype_object(QString type_name)
{
 QString full_name;
 full_name = type_name;

 QString local_name;
 s4 index = type_name.lastIndexOf(':');
 if(index == -1)
   local_name = type_name;
 else
   local_name = type_name.mid(index + 1);

 Metatype_Object* mto = new Metatype_Object(local_name);

 mto->set_full_name(full_name);
 registered_metatype_objects_[type_name] = mto;
}


Metatype_Object* Unified_Runtime_Object::get_metetype_object_by_type_name(QString type_name)
{
 return registered_metatype_objects_.value(type_name);
}

