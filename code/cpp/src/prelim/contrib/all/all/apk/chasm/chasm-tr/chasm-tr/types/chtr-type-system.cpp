

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "chtr-type-system.h"

#include "chtr-type-object.h"

USING_AQNS(Chasm_TR)


ChTR_Type_System::ChTR_Type_System()
{
 types_by_name_["u1"] = new ChTR_Type_Object("u1", true);
 types_by_name_["u2"] = new ChTR_Type_Object("u2", true);
 types_by_name_["u4"] = new ChTR_Type_Object("u4", true);

 types_by_name_["s1"] = new ChTR_Type_Object("s1", true);
 types_by_name_["s2"] = new ChTR_Type_Object("s2", true);
 types_by_name_["s4"] = new ChTR_Type_Object("s4", true);

}


ChTR_Type_Object* ChTR_Type_System::find_type(QString name)
{
 return types_by_name_.value(name);
}


