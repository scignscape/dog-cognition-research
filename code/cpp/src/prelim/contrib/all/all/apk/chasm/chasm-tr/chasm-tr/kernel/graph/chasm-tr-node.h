
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_TR_NODE__H
#define CHASM_TR_NODE__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/chasm-tr-dominion.h"

#include "kernel/frame/chasm-tr-frame.h"

#include "phaong/phaong.h"
#include "phaong/phaong-types.h"


#include <functional>

#include "aqns.h"

AQNS_(ChasmTR)


class Chasm_TR_Node : public node_ptr<Chasm_TR_Dominion>
{
public:
 #define DOMINION_TYPE DOMINION_NODE_CONSTRUCTOR
 #include "kernel/dominion/types.h"
 #undef DOMINION_TYPE

};

_AQNS(ChasmTR)

#endif
