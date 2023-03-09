
#include "gtagml-query.h"

#include "kans.h"

USING_KANS(GTagML)

GTagML_Query::GTagML_Query()
 : node_query<GTagML_Dominion>()
  #define DOMINION_CONNECTOR(name, label) \
    ,name(GTagML_Connectors(#label))
  #include "kernel/dominion/connectors.h"
  #undef DOMINION_CONNECTOR
{


}

const GTagML_Query& GTagML_Query::instance()
{
 static GTagML_Query* the_instance = nullptr;
 if(!the_instance)
  the_instance = new GTagML_Query;
 return *the_instance;
}
