
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NTXH_PARSER__H
#define NTXH_PARSER__H

#include "relae-graph/relae-parser.h"

#include "ntxh/kernel/ntxh-dominion.h"

#include "kans.h"
KANS_(HGDMCore)

class NTXH_Graph;

class NTXH_Parser : public Relae_Parser<NTXH_Galaxy>
{
 QString raw_text_;

public:

 ACCESSORS(QString ,raw_text)

 NTXH_Parser(caon_ptr<NTXH_Graph> g);

};

_KANS(HGDMCore)


#endif
