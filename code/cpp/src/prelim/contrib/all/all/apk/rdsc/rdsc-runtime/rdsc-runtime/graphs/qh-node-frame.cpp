
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-node-frame.h"

#include "qh-node-data.h"

#include "qh-hyperedge.h"

#include "qh-hyperedge-dominion.h"

USING_KANS(RdSC)

Qh_Node_Frame::Qh_Node_Frame(Qh_Hypernode* start_node)
  :  start_node_(start_node)
{

}

void Qh_Node_Frame::add_hypernode(Qh_Hypernode* qhn, Qh_Node_Data* proxy_data)
{
 proxy_data_[qhn] = proxy_data;
}

void Qh_Node_Frame::add_hyperedge(Qh_Hyperedge* qhe)
{
 QString description = qhe->description();
 description.prepend(';');
 hyperedges_[description].push_back(qhe);
}


Qh_Hyperedge* Qh_Node_Frame::add_hyperedge(Qh_Hyperedge_Dominion::Label lbl)
{
 Qh_Hyperedge* qhe = new Qh_Hyperedge(lbl._label);
 QString description = QString("%1;%2").arg(lbl._this->description())
   .arg(lbl._label);
 hyperedges_[description].push_back(qhe);
 return qhe;
}


void Qh_Node_Frame::add_proxy_to_start_node(Qh_Hypernode* added_qhn)
{
 Qh_Node_Data* proxy_data = proxy_data_[start_node_];
 QPair<u4, u4> pr = proxy_data->get_last_offset();

 u1 gap = pr.first - pr.second;

 if(gap == 8)
 {
  proxy_data->add_pointer(added_qhn);


 }

}
