
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef CHTR_CHANNEL_OBJECT__H
#define CHTR_CHANNEL_OBJECT__H


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


class ChTR_Channel_Object
{

private:

 QString channel_kind_;

 QVector<ChTR_Carrier*> carriers_;

public:


 ChTR_Channel_Object(QString text = {});

 ACCESSORS(QString ,channel_kind)

 ACCESSORS__CONST_RGET(QVector<ChTR_Carrier*> ,carriers)


 void add_carrier(QString carrier_string);

 QString get_proc_name();



};

_AQNS(Chasm_TR)


#endif // CHTR_CHANNEL_OBJECT__H




