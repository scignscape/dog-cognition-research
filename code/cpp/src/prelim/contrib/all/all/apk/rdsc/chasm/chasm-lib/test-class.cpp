
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "test-class.h"

//#include "kans.h"
//USING_KANS(GTagML)

#include <QDebug>

#include "compilation-unit-object.h"
#include "unified-runtime-object.h"
#include "metatype-object.h"


Compilation_Unit_Object* _cuo()
{
 static Compilation_Unit_Object* result = Compilation_Unit_Object::init_new(__FILE__,
 [](Compilation_Unit_Object* r)
 {
  Unified_Runtime_Object& uro = *Unified_Runtime_Object::instance();
  Metatype_Object* mto = uro.get_metetype_object_by_type_name("Test_Class");
  r->set_principal_metatype_object(mto);
 });
 return result;
}


Test_Class::Test_Class(QString text)
  :  text_(text)
{

}


void Test_Class::test_method(QString path, u4 val1, u4 val2)
{
 Compilation_Unit_Object& cuo = *_cuo();
 Metatype_Object& mto = *cuo.principal_metatype_object();
 if(auto fn = mto.check_single_guard_fn("test_method@enter"))
   fn({(n8)&path, (n8)&val1, (n8)&val2});

 qDebug() << QString("Test method -- path = %1, val1 = %2, val2 = %3").arg(path).arg(val1).arg(val2);
}


void Test_Class::test_cuo()
{
 Compilation_Unit_Object& cuo = *_cuo();

 qDebug() << cuo.file_path();

}

