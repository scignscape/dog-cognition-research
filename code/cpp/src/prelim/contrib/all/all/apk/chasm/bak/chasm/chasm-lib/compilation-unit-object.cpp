
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "compilation-unit-object.h"

#include "unified-runtime-object.h"

#include "kans.h"

//USING_KANS(GTagML)

//uro

Unified_Runtime_Object* Compilation_Unit_Object::unified_runtime_object_ = nullptr;



Compilation_Unit_Object::Compilation_Unit_Object(QString file_path)
  :  file_path_(file_path)
{
 if(!unified_runtime_object_)
   unified_runtime_object_ = Unified_Runtime_Object::instance();

 unified_runtime_object_->register_compilation_unit_object(this);
}

Compilation_Unit_Object* Compilation_Unit_Object::init_new(QString file_path, std::function<void(Compilation_Unit_Object*)> fn)
{
 Compilation_Unit_Object* result = new Compilation_Unit_Object(file_path);
 if(fn)
   fn(result);
 return result;
}

