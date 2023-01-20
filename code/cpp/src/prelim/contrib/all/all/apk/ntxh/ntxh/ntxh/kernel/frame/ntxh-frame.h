
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NTXH_FRAME__H
#define NTXH_FRAME__H


#include "relae-graph/relae-node-ptr.h"

#include "kernel/ntxh-dominion.h"

#include "kans.h"

KANS_(HGDMCore)

class NTXH_Frame : public node_frame<NTXH_Dominion>
{
 NTXH_Frame();
 // SY_Dominion::Connectors N_A;
 public:

 static NTXH_Frame& instance();

};


_KANS(HGDMCore)

#endif
