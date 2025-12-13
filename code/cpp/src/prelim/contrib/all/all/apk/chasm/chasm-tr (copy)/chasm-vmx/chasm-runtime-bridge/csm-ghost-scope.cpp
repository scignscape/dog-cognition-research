
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "csm-ghost-scope.h"


#include "textio.h"
USING_KANS(TextIO)

#include <QString>
#include <QVariant>
#include <QByteArray>

#include <QUrl>

#include <QPoint>

CSM_Ghost_Scope::CSM_Ghost_Scope()
{

}

void CSM_Ghost_Scope::add_carrier(const Chasm_Carrier& cc)
{
 carriers_.push_back(cc);
}

void CSM_Ghost_Scope::clear_carrier(Chasm_Carrier& cc)
{
 u1 tf = cc.key().type_flag();
 switch(tf)
 {
 case 3: delete (QString*) cc.raw_value(); break;
 case 5: delete (QByteArray*) cc.raw_value(); break;
 case 7: delete (QVariant*) cc.raw_value(); break;

 default: break;
 }
}

void CSM_Ghost_Scope::clear_all()
{
 for(Chasm_Carrier& cc : carriers_)
 {
  clear_carrier(cc);
 }
}
