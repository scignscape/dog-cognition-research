
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-cpp-query.h"

#include "kans.h"


USING_KANS(Qh)


Qh_CPP_Query::Qh_CPP_Query()
 : node_query<Qh_CPP_Dominion>()
  #define DOMINION_CONNECTOR(name, label) \
    ,name(Qh_CPP_Connectors(Qh_CPP_Connectors_Case_Labels::name, label))
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

const Qh_CPP_Query& Qh_CPP_Query::instance()
{
 static Qh_CPP_Query* the_instance = nullptr;
 if(!the_instance)
  the_instance = new Qh_CPP_Query;
 return *the_instance;
}
