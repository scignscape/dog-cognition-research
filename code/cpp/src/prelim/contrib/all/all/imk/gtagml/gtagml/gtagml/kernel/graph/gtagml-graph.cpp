
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-graph.h"
#include "gtagml-node.h"

#include "kans.h"

USING_KANS(GTagML)

GTagML_Graph::GTagML_Graph(caon_ptr<GTagML_Node> root_node)
 : node_graph<GTagML_Dominion>(root_node)
{

}
