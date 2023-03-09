
#ifndef GTAGML_GRAPH__H
#define GTAGML_GRAPH__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/gtagml-dominion.h"

#include "kans.h"

KANS_(GTagML)


class GTagML_Graph : public node_graph<GTagML_Dominion>
{
 public:
  GTagML_Graph(caon_ptr<GTagML_Node> root_node = caon_ptr<GTagML_Node>(nullptr) );

};

_KANS(GTagML)


#endif
