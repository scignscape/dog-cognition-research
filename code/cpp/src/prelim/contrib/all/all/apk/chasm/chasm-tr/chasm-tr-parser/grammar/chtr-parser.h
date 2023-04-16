
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_PARSER__H
#define CHTR_PARSER__H

#include "relae-graph/relae-parser.h"

#include "chasm-tr/kernel/chtr-dominion.h"

#include "aqns.h"
AQNS_(Chasm_TR)

class ChTR_Graph;

class ChTR_Parser : public Relae_Parser<ChTR_Galaxy>
{
 QString raw_text_;

public:

 ACCESSORS(QString ,raw_text)

 ChTR_Parser(caon_ptr<ChTR_Graph> g);

};

_AQNS(Chasm_TR)


#endif
