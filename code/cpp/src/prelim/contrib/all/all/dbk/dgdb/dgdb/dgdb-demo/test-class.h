
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef TEST_CLASS__H
#define TEST_CLASS__H

#include "accessors.h"

#include "global-types.h"


#include <QString>
#include <QByteArray>

class Qh_Pack_Builder;
class Qh_Pack_Reader;
class Qh_Pack_Code;
class Qh_Hypernode;


// //  defines the serialization order ...
#define _Test_Class_FM(x) \
 x(a_sign) \
 x(a_string) \
 x(a_number)


class Test_Class
{
 QString a_string_;
 s1 a_sign_;
 u4 a_number_;

public:

 Test_Class();

 ACCESSORS(QString ,a_string)
 ACCESSORS(s2 ,a_sign)
 ACCESSORS(u4 ,a_number)

// Qh_Hypernode* (*as_hypernode)();

// static void init_pack_code(Qh_Pack_Code& qpc);

 void supply_data(QByteArray& qba);
 void absorb_data(const QByteArray& qba);

// void supply_pack(Qh_Pack_Builder& qpb);
// void absorb_pack(const Qh_Pack_Reader& qpr);

};



#endif // TEST_CLASS__H
