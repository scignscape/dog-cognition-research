
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_NODE_FRAME__H
#define QH_NODE_FRAME__H

#include <QByteArray>

#include <QVariant>

#include <functional>

#include "global-types.h"

//class Qh_Bundle_Code;

#include "qh-pack-code.h"

#include "qh-hyperedge-dominion.h"

KANS_(RdSC)

class Qh_Hypernode;
class Qh_Hyperedge;

class Qh_Hyperedge_Dominion;

class Qh_Node_Data;


class Qh_Node_Frame
{
 QMap<Qh_Hypernode*, Qh_Node_Data*> proxy_data_;

 Qh_Hypernode* start_node_;

 QMap<QString, QList<Qh_Hyperedge*>> hyperedges_;

 //QVector<QPair<u4, u4>> offsets_;

public:

 Qh_Node_Frame(Qh_Hypernode* start_node = nullptr);

 void add_hypernode(Qh_Hypernode* qhn, Qh_Node_Data* proxy_data = nullptr);

 void add_proxy_to_start_node(Qh_Hypernode* added_qhn);

 void add_hyperedge(Qh_Hyperedge* qhe);
 Qh_Hyperedge* add_hyperedge(Qh_Hyperedge_Dominion::Label lbl);

 void add_hyperedge_class(Qh_Hyperedge* qhe);
};

inline Qh_Node_Frame& operator >>= (Qh_Node_Frame& lhs, Qh_Hypernode* rhs)
{
 lhs.add_proxy_to_start_node(rhs);
 return lhs;
}

inline Qh_Hyperedge& operator/(Qh_Node_Frame& lhs, Qh_Hyperedge& rhs)
{
 lhs.add_hyperedge(&rhs);
 return rhs;
}

inline Qh_Hyperedge& operator/(Qh_Node_Frame& lhs, Qh_Hyperedge_Dominion::Label rhs)
{
 Qh_Hyperedge* qhe = lhs.add_hyperedge(rhs);
 return *qhe;
}

_KANS(RdSC)

#endif // QH_NODE_FRAME__H
