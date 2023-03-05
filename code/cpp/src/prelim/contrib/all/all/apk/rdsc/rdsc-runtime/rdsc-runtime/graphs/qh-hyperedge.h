
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_HYPEREDGE__H
#define QH_HYPEREDGE__H

#include <QByteArray>

#include <QVariant>

#include <functional>

#include "global-types.h"

#include "accessors.h"
//class Qh_Bundle_Code;

#include "qh-pack-code.h"

KANS_(RdSC)

class Qh_Hypernode;
class Qh_Node_Frame;
class Qh_Node_Data;

class Qh_Hyperedge
{
 Qh_Hypernode* source_;
 Qh_Hypernode* target_;
 Qh_Hypernode* annotation_;

 QString description_;

 n8 supplement_;

public:

 Qh_Hyperedge(QString description);

 ACCESSORS(Qh_Hypernode* ,source)
 ACCESSORS(Qh_Hypernode* ,target)
 ACCESSORS(Qh_Hypernode* ,annotation)
 ACCESSORS(QString ,description)

 ACCESSORS(n8 ,supplement)

 static QPair<Qh_Hypernode*, Qh_Node_Data*> new_hypernode_from_proxy(Qh_Hypernode* proxied);
 static Qh_Node_Frame* new_node_frame(Qh_Hypernode* start_node, Qh_Node_Data* proxy_data);

};

inline Qh_Hyperedge& operator << (Qh_Hypernode* lhs, Qh_Hyperedge& rhs)
{
 rhs.set_source(lhs);
 return rhs;
}

inline Qh_Hyperedge& operator >> (Qh_Hyperedge& lhs, Qh_Hypernode* rhs)
{
 if(lhs.target())
 {
  Qh_Hyperedge* result = new Qh_Hyperedge(lhs.description());
  result->set_source(lhs.target());
  result->set_target(rhs);
  return *result;
 }
 lhs.set_target(rhs);
 return lhs;
}

inline Qh_Node_Frame& operator >>= (Qh_Hyperedge& lhs, Qh_Hypernode* rhs)
{
 if(lhs.target())
 {
  //lhs.target()
 }
 else
 {
  QPair<Qh_Hypernode*, Qh_Node_Data*> target = Qh_Hyperedge::new_hypernode_from_proxy(rhs);
  return *Qh_Hyperedge::new_node_frame(target.first, target.second);
 }
 //lhs.set_target(rhs);
 // return lhs;
}

_KANS(RdSC)

#endif // QH_HYPEREDGE__H


