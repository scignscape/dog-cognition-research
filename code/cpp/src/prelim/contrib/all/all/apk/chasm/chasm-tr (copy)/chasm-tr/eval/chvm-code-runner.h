
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef CHVM_CODE_RUNNER__H
#define CHVM_CODE_RUNNER__H


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


class ChVM_Code_Runner
{
 ChVM_Code_Block* code_block_;

public:


 ChVM_Code_Runner();

// ACCESSORS(QString ,anchor)
// ACCESSORS(ChTR_Channel_Package* ,channel_package)


};

_AQNS(Chasm_TR)


#endif // CHVM_CODE_RUNNER__H




