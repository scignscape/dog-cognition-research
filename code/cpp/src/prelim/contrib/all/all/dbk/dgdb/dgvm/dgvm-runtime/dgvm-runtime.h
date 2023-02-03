
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DGVM_RUNTIME__H
#define DGVM_RUNTIME__H


#include "kans.h"

#include <QString>
#include <QVector>


KANS_CLASS_DECLARE(DGDB ,DgDb_Database_Instance)

USING_KANS(DGDB)

KANS_(DGVM)


class DGVM_Runtime
{
 DgDb_Database_Instance* database_;
 QVector<QString> known_flags_;


public:

 DGVM_Runtime();

 void init_database();
 void init_flags(QString flags_list);



};

_KANS(DGVM)


#endif // DGVM_RUNTIME__H
