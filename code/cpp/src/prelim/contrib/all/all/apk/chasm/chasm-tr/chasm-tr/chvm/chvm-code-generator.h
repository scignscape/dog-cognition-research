
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef CHVM_CODE_GENERATOR__H
#define CHVM_CODE_GENERATOR__H


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

class ChVM_Procedure;

class ChTR_Graph;

class ChVM_Code_Generator
{
 QVector<ChVM_Procedure*> procedures_;

 ChTR_Graph* ir_graph_;

public:


 ChVM_Code_Generator(ChTR_Graph* ir_graph);

 void graph_to_chvm(QString& chvm);


};

_AQNS(Chasm_TR)


#endif // CHVM_CODE_GENERATOR__H




