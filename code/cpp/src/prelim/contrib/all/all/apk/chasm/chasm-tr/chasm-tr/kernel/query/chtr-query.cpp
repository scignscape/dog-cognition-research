
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-query.h"

#include "aqns.h"


USING_AQNS(Chasm_TR)


ChTR_Query::ChTR_Query()
 : node_query<ChTR_Dominion>()
  #define DOMINION_CONNECTOR(name, label) \
    ,name(ChTR_Connectors(ChTR_Connectors_Case_Labels::name, label))
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

const ChTR_Query& ChTR_Query::instance()
{
 static ChTR_Query* the_instance = nullptr;
 if(!the_instance)
  the_instance = new ChTR_Query;
 return *the_instance;
}
