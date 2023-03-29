
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-cpp-source-type.h"


USING_KANS(Qh)


Qh_CPP_Source_Type::Qh_CPP_Source_Type()
  :  Flags(0), ref_line_number_(0)
{

}


void Qh_CPP_Source_Type::note_enum_field(QString label, QString value)
{
 fields_.push_back(Field_Info(label));
 fields_.back().fixed_value() = value;
}

