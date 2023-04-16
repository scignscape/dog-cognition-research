
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-tr-query.h"

#include "aqns.h"


USING_AQNS(ChasmTR)


Chasm_TR_Query::Chasm_TR_Query()
 : node_query<Chasm_TR_Dominion>()
  #define DOMINION_CONNECTOR(name, label) \
    ,name(Chasm_TR_Connectors(Chasm_TR_Connectors_Case_Labels::name, label))
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

const Chasm_TR_Query& Chasm_TR_Query::instance()
{
 static Chasm_TR_Query* the_instance = nullptr;
 if(!the_instance)
  the_instance = new Chasm_TR_Query;
 return *the_instance;
}
