
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_TR_PARSER__H
#define CHASM_TR_PARSER__H

#include "relae-graph/relae-parser.h"

#include "chasm-tr/kernel/chasm-tr-dominion.h"

#include "aqns.h"
AQNS_(ChasmTR)

class Chasm_TR_Graph;

class Chasm_TR_Parser : public Relae_Parser<Chasm_TR_Galaxy>
{
 QString raw_text_;

public:

 ACCESSORS(QString ,raw_text)

 Chasm_TR_Parser(caon_ptr<Chasm_TR_Graph> g);

};

_AQNS(ChasmTR)


#endif
