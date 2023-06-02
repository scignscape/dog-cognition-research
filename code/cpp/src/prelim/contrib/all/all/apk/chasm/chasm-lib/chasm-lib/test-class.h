
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef TEST_CLASS__H
#define TEST_CLASS__H

#include <QString>

#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include <functional>

#include "kans.h"


//KANS_(GTagML)


class Test_Class
{
 QString text_;



public:


 Test_Class(QString text);

 ACCESSORS(QString ,text)

 void test_cuo();

 void test_method(QString path, u4 val1, u4 val2);


};

// _KANS(GTagML)

#endif
