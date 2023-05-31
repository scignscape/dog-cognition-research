
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_FRAME__H
#define CHTR_FRAME__H


#include "relae-graph/relae-node-ptr.h"

#include "kernel/chtr-dominion.h"

#include "aqns.h"

AQNS_(Chasm_TR)

class ChTR_Relae_Frame : public node_frame<ChTR_Dominion>
{
 ChTR_Relae_Frame();
 // SY_Dominion::Connectors N_A;
 public:

 static ChTR_Relae_Frame& instance();

};


_AQNS(Chasm_TR)

#endif
