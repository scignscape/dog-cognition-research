
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef CHTR_CODE_STATEMENT__H
#define CHTR_CODE_STATEMENT__H


#include "accessors.h"

#include "aqns.h"

#include "flags.h"

#include <QFile>
#include <QVector>

//?#include "tsl/ordered_map.h"

#include "global-types.h"

AQNS_(Chasm_TR)

class ChTR_Channel_Package;

class ChTR_Code_Statement
{

private:

 QString anchor_;
 ChTR_Channel_Package* channel_package_;

public:


 ChTR_Code_Statement();

 ACCESSORS(QString ,anchor)
 ACCESSORS(ChTR_Channel_Package* ,channel_package)


};

_AQNS(Chasm_TR)


#endif // CHTR_CODE_STATEMENT__H




