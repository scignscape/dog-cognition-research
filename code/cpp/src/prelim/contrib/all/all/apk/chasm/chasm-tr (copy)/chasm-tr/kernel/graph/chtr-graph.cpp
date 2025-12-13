
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-graph.h"

#include "aqns.h"

USING_AQNS(Chasm_TR)


ChTR_Graph::ChTR_Graph(ChTR_Node* root_node)
  :  root_node_(root_node)
{
 set_user_data(&hypernodes_);
 set_node_add_function([](phaong<pg_t>& _pg, phaong<pg_t>::Hypernode* hn)
 {
  QVector<hypernode_type*>* hh = _pg.user_data_as<QVector<hypernode_type*>>();
  hh->push_back(hn);
 });
}

