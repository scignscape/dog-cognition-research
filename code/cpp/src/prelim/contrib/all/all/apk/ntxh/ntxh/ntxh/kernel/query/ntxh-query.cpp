
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ntxh-query.h"

#include "kans.h"


USING_KANS(HGDMCore)


NTXH_Query::NTXH_Query()
 : node_query<NTXH_Dominion>()
  #define DOMINION_CONNECTOR(name, label) \
    ,name(NTXH_Connectors(NTXH_Connectors_Case_Labels::name, label))
  #include "kernel/dominion/connectors.h"
  #undef DOMINION_CONNECTOR
{
 int order = 0;
 #define DOMINION_CONNECTOR(name, label) \
  name.order = order; \
  ++order;
 #include "kernel/dominion/connectors.h"
 #undef DOMINION_CONNECTOR
}

const NTXH_Query& NTXH_Query::instance()
{
 static NTXH_Query* the_instance = nullptr;
 if(!the_instance)
  the_instance = new NTXH_Query;
 return *the_instance;
}
