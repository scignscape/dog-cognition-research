
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-hyperedge.h"

#include "qh-node-frame.h"

#include "qh-pack-code.h"
#include "qh-pack-builder.h"

USING_KANS(RdSC)

Qh_Hyperedge::Qh_Hyperedge(QString description)
  :  source_(nullptr),
     target_(nullptr), annotation_(nullptr),
     description_(description), supplement_(0)
{

}

Qh_Node_Frame* Qh_Hyperedge::new_node_frame(Qh_Hypernode* start_node, Qh_Node_Data* proxy_data)
{
 Qh_Node_Frame* result = new Qh_Node_Frame(start_node);
 result->add_hypernode(start_node, proxy_data);
}


QPair<Qh_Hypernode*, Qh_Node_Data*> Qh_Hyperedge::new_hypernode_from_proxy(Qh_Hypernode* proxied)
{
 Qh_Pack_Code qpc;
 qpc.add_proxy(1);
 Qh_Pack_Builder qpb(qpc);
 qpb.init_proxy_data();
 qpb.add_array_proxy_value(proxied);
 Qh_Hypernode* result = qpb.as_hypernode();
 return {result, qpb.proxy_data()};
}
