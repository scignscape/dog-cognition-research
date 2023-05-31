
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef CHVM_CODE_STATEMENT_GENERATOR__H
#define CHVM_CODE_STATEMENT_GENERATOR__H


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

class ChTR_Relae_Query;

class ChVM_Code_Generator;
class ChTR_Code_Statement;
class ChVM_Code_Statement;

class ChVM_Code_Statement_Generator
{
 ChVM_Code_Generator& gen_;
 ChTR_Code_Statement& ccs_;

// const ChTR_Relae_Query& qry_;
// const ChTR_Relae_Query& qry_;


public:


 ChVM_Code_Statement_Generator(ChVM_Code_Generator& gen, ChTR_Code_Statement& ccs);

 void graph_to_chvm(ChVM_Code_Statement& cvcs);

 QString enter_channel(QString channel_kind);
 QString enter_carrier();
 QString load_symbol(QString symbol_string);

 void statement_line(QString* ln);
 QString statement_line(QString ln);

};

_AQNS(Chasm_TR)


#endif // CHVM_CODE_GENERATOR__H




