
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_TR_QUERY__H
#define CHASM_TR_QUERY__H

#include "kernel/chasm-tr-dominion.h"

#include "relae-graph/relae-node-ptr.h"

#include "aqns.h"

AQNS_(ChasmTR)

class Chasm_TR_Query : public node_query<Chasm_TR_Dominion>
{
 Chasm_TR_Query();

public:
  #define DOMINION_CONNECTOR(name, label) \
   Chasm_TR_Connectors name;
  #include "kernel/dominion/connectors.h"
  #undef DOMINION_CONNECTOR

 static const Chasm_TR_Query& instance();
};

_AQNS(ChasmTR)

#endif
