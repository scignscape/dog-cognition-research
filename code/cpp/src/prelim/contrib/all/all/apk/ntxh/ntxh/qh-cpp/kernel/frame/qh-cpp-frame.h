
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_CPP_FRAME__H
#define QH_CPP_FRAME__H


#include "relae-graph/relae-node-ptr.h"

#include "kernel/qh-cpp-dominion.h"

#include "kans.h"

KANS_(Qh)

class Qh_CPP_Frame : public node_frame<Qh_CPP_Dominion>
{
 Qh_CPP_Frame();
 // SY_Dominion::Connectors N_A;
 public:

 static Qh_CPP_Frame& instance();

};


_KANS(Qh)

#endif
