
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DEMO_CLASS__H
#define DEMO_CLASS__H 

#include "accessors.h"

#include "global-types.h"


#include <QString>
#include <QByteArray>


class Demo_Class
{
 QString a_string_;
 u4 a_number_;

public:

 Demo_Class();

 ACCESSORS(QString ,a_string)
 ACCESSORS(u4 ,a_number)

 void supply_data(QByteArray& qba);
 void absorb_data(const QByteArray& qba);


};



#endif // DEMO_CLASS__H 
