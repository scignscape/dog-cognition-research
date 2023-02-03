

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "demo-class.h"

#include <QDataStream>
#include <QIODevice>


Demo_Class::Demo_Class()
 : u4_in_block_(0), u4_for_query_(0),
   s1_in_block_(0), s2_for_query_(0),
   test_enum_(Test_Enum::Enum_Val_0),
   test_enum_flags_(Test_Enum_Flags::Enum_Flags_1)
{

}

void Demo_Class::supply_data(QByteArray& qba)
{
 QDataStream qds(&qba, QIODevice::WriteOnly);
// qds << a_string_ << a_number_;


#define TEMP_MACRO(cast, type ,name) << cast name##_
 qds _Demo_Class_fm(TEMP_MACRO);
#undef TEMP_MACRO


}

void Demo_Class::absorb_data(const QByteArray& qba)
{
 QDataStream qds(qba);
// qds >> a_string_ >> a_number_;


#define TEMP_MACRO(cast, type ,name) >> cast name##_
 qds _Demo_Class_fm(TEMP_MACRO);
#undef TEMP_MACRO


}



