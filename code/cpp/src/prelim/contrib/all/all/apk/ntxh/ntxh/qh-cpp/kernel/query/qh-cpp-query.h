
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_CPP_QUERY__H
#define QH_CPP_QUERY__H

#include "kernel/qh-cpp-dominion.h"

#include "relae-graph/relae-node-ptr.h"

#include "kans.h"

KANS_(Qh)

class Qh_CPP_Query : public node_query<Qh_CPP_Dominion>
{
 Qh_CPP_Query();

public:
  #define DOMINION_CONNECTOR(name, label) \
   Qh_CPP_Connectors name;
  #include "kernel/dominion/connectors.h"
  #undef DOMINION_CONNECTOR

 static const Qh_CPP_Query& instance();
};

_KANS(Qh)

#endif
