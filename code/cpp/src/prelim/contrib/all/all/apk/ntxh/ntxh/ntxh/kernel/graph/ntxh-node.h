
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NTXH_NODE__H
#define NTXH_NODE__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/ntxh-dominion.h"

#include "kernel/frame/ntxh-frame.h"

#include "phaong/phaong.h"
#include "phaong/phaong-types.h"


#include <functional>

#include "kans.h"

KANS_(HGDMCore)


class NTXH_Node : public node_ptr<NTXH_Dominion>
{
public:
 #define DOMINION_TYPE DOMINION_NODE_CONSTRUCTOR
 #include "kernel/dominion/types.h"
 #undef DOMINION_TYPE

};

_KANS(HGDMCore)

#endif
