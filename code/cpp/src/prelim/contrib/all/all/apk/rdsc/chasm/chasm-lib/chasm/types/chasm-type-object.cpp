
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-type-object.h"


#include <QDebug>


Chasm_Type_Object::Chasm_Type_Object(QString name, u2 c0, u2 c1, u2 c2, u2 c3)
 :  name_(name), qmetatype_(nullptr),
    codes_with_position_{c0, c1, c2, c3}
{

}

u1 Chasm_Type_Object::get_pretype_code()
{
 // // only covers pretypes for now ...
 return codes_with_position_[0];
}

