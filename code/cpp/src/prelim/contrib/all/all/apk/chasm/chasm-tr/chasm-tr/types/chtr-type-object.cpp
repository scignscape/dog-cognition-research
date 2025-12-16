

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "chtr-type-object.h"


USING_AQNS(Chasm_TR)


ChTR_Type_Object::ChTR_Type_Object(QString name, bool built_in)
  :  Flags(0), name_(name)
{
 if(built_in)
   flags.built_in = true;
}

