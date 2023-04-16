
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_TR_FRAME__H
#define CHASM_TR_FRAME__H


#include "relae-graph/relae-node-ptr.h"

#include "kernel/chasm-tr-dominion.h"

#include "aqns.h"

AQNS_(ChasmTR)

class Chasm_TR_Frame : public node_frame<Chasm_TR_Dominion>
{
 Chasm_TR_Frame();
 // SY_Dominion::Connectors N_A;
 public:

 static Chasm_TR_Frame& instance();

};


_AQNS(ChasmTR)

#endif
