
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-cpp-source-file.h"

#include "qh-cpp-source-type.h"


USING_KANS(Qh)


Qh_CPP_Source_File::Qh_CPP_Source_File(QString path)
  :  path_(path)
{

}

void Qh_CPP_Source_File::add_source_type(Qh_CPP_Source_Type* sty)
{
 static u2 anon_count = 0;
 QString name = sty->full_name();
 if(name.isEmpty())
   name = "?%1"_qt.arg(anon_count);
 defined_types_.insert({name, sty});
}


//void Qh_CPP_Source_File::note_enum_field(QString label, QString value)
//{
// fields_.push_back(Field_Info(label));
// fields_.back().fixed_value() = value;
//}

