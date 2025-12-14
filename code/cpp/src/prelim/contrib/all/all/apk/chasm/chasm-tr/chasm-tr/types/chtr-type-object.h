
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef CHTR_TYPE_OBJECT__H
#define CHTR_TYPE_OBJECT__H


#include "accessors.h"

#include "aqns.h"

#include "flags.h"

#include <QFile>
#include <QVector>

//?#include "tsl/ordered_map.h"

#include "global-types.h"

#include <QVector>

AQNS_(Chasm_TR)


class ChTR_Carrier;


class ChTR_Type_Object
{
 QString name_;

public:


 ChTR_Type_Object(QString name = {});

 ACCESSORS(QString ,name)


};

_AQNS(Chasm_TR)


#endif // CHTR_TYPE_OBJECT__H




