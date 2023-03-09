
#ifndef GTAGML_QUERY__H
#define GTAGML_QUERY__H

#include "kernel/gtagml-dominion.h"

#include "relae-graph/relae-node-ptr.h"

#include "kans.h"

KANS_(GTagML)


class GTagML_Query : public node_query<GTagML_Dominion>
{
 GTagML_Query();

 public:
  #define DOMINION_CONNECTOR(name, label) \
   GTagML_Connectors name;
  #include "kernel/dominion/connectors.h"
  #undef DOMINION_CONNECTOR

 static const GTagML_Query& instance();
};

_KANS(GTagML)

#endif
