
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "demo-class.h"

#include <QDataStream>

#include <QIODevice>


Demo_Class::Demo_Class()
 : a_number_(0)
{

}

void Demo_Class::supply_data(QByteArray& qba)
{
 QDataStream qds(&qba, QIODevice::WriteOnly);
 qds << a_string_ << a_number_;
}

void Demo_Class::absorb_data(const QByteArray& qba)
{
 QDataStream qds(qba);
 qds >> a_string_ >> a_number_;
}



