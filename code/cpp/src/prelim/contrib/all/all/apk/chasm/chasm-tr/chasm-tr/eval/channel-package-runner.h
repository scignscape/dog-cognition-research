
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef CHANNEL_PACKAGE_RUNNER__H
#define CHANNEL_PACKAGE_RUNNER__H


#include "accessors.h"

#include "aqns.h"

#include "flags.h"

#include <QFile>
#include <QVector>

//?#include "tsl/ordered_map.h"

#include "global-types.h"

AQNS_(Chasm_TR)

class ChTR_Channel_Package;
class ChTR_Graph;

class ChVM_Code_Block;


class Channel_Package_Runner
{
 ChVM_Code_Block* code_block_;

public:


 Channel_Package_Runner();

// ACCESSORS(QString ,anchor)
// ACCESSORS(ChTR_Channel_Package* ,channel_package)


};

_AQNS(Chasm_TR)


#endif // CHANNEL_PACKAGE_RUNNER__H




