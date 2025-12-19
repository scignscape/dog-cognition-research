
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-type-system.h"

#include <QString>
#include <QVariant>
#include <QByteArray>

#include <QUrl>

#include <QPoint>


//#include "kans.h"
//USING_KANS(GTagML)

#include <QDebug>

#include "chasm-type-object.h"


Chasm_Type_System::Chasm_Type_System()
  :  pretype_type_objects_(new QVector<Chasm_Type_Object*>)
{
 pretype_type_objects_->resize(10);

 (*pretype_type_objects_)[0] = register_type_object("n8&",
    (s2) Chasm_Type_Object::Built_In_Status::N_A, 0, 0, 0, 0, -1);
 //(*pretype_type_objects_)[1] = register_type_object("n8&!", 0, 0, 0, -1);

 register_type_object("n8&!",
    (s2) Chasm_Type_Object::Built_In_Status::N_A, 0, 0, 0, 0, -1);

 (*pretype_type_objects_)[1] = register_type_object("u1",
    (s2) Chasm_Type_Object::Built_In_Status::u_like, 1, 1, 10, 100, 1000);

 (*pretype_type_objects_)[2] = register_type_object("u2",
    (s2) Chasm_Type_Object::Built_In_Status::u_like, 2, 2, 20, 200, 2000);

 (*pretype_type_objects_)[3] = register_type_object("QString",
    (s2) Chasm_Type_Object::Built_In_Status::QString_like, 0, 3, 30, 300, 3000);

 (*pretype_type_objects_)[4] = register_type_object("u4",
    (s2) Chasm_Type_Object::Built_In_Status::u_like, 4, 4, 40, 400, 4000);

 (*pretype_type_objects_)[5] = register_type_object("QByteArray",
    (s2) Chasm_Type_Object::Built_In_Status::QByteArray_like, 0, 5, 50, 500, 5000);

 (*pretype_type_objects_)[6] = register_type_object("r8",
    (s2) Chasm_Type_Object::Built_In_Status::r_like, 8, 6, 60, 600, 6000);

 (*pretype_type_objects_)[7] = register_type_object("QVariant",
    (s2) Chasm_Type_Object::Built_In_Status::QVariant_like, 0, 7, 70, 700, 7000);

 (*pretype_type_objects_)[8] = register_type_object("n8",
    (s2) Chasm_Type_Object::Built_In_Status::n8_like, 8, 8, 80, 800, 8000);

 (*pretype_type_objects_)[9] = register_type_object("void*",
    (s2) Chasm_Type_Object::Built_In_Status::N_A, 8, 9, 90, 900, 9000);

 register_type_object("QStringList&",
    (s2) Chasm_Type_Object::Built_In_Status::QStringList_like, 0, 0, 0, 0, -1);
}

Chasm_Type_Object* Chasm_Type_System::get_type_object_by_name(QString name)
{
 return type_objects_.value(name);
}

Chasm_Type_Object* Chasm_Type_System::register_type_object(QString name,
  s2 status, u1 byte_span,
  u2 pos1code, u2 pos2code, u2 pos3code, u2 pos4code)
{
 Chasm_Type_Object* result = new Chasm_Type_Object(name,
   (Chasm_Type_Object::Built_In_Status) status, byte_span,
   pos1code, pos2code, pos3code, pos4code);

 type_objects_.insert(name, result);

 return result;
}
