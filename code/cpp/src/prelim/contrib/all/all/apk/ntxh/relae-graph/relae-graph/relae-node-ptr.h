
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_NODE_PTR__H
#define RZ_NODE_PTR__H

#include "relae-caon-ptr.h"

#include "accessors.h"


#include <QMultiMap>
#include <QMapIterator>
#include <QString>
#include <QList>
#include <QPair>

#ifndef MACRO_PASTE
#define MACRO_PASTE(...) __VA_ARGS__
#endif

#ifndef ACCESSORS__GET
#define ACCESSORS__GET(type ,name) \
 type name() const { return name##_; }
#endif

#ifndef ACCESSORS__SET
#define ACCESSORS__SET(type ,name) \
 void set_##name(type t) { name##_ = t; }
#endif

#ifndef ACCESSORS
#define ACCESSORS(type ,name) \
  ACCESSORS__GET(MACRO_PASTE(type) ,name) \
  ACCESSORS__SET(MACRO_PASTE(type) ,name)
#endif

#ifdef RELAE_LABEL_NODES
#define RELAE_SET_NODE_LABEL(node, label) \
 node->set_label(label);
#else
#define RELAE_SET_NODE_LABEL(node, label)
#endif


struct Node_Ptr_Basic_Galaxy
{
 typedef QString tString;
 struct Root_Void {};
 typedef caon_ptr<Root_Void> Root_Vertex_type;
 typedef Root_Void Root_Void_type;
};


template<typename DOMINION, typename T>
typename DOMINION::Type_Codes dominion_get_type_code();


template<typename DOMINION>
struct Node_Ptr_Default_Galaxy : Node_Ptr_Basic_Galaxy
{
 typedef typename DOMINION::Connectors_type Connectors_type;
 typedef typename DOMINION::Annotated_Connectors_type Annotated_Connectors_type;
 typedef typename DOMINION::Connection_type Connection_type;
 typedef typename DOMINION::Type_Codes Type_Codes_type;
 typedef typename DOMINION::Node_type Node_type;
 typedef typename DOMINION::Frame_type Frame_type;
 typedef typename DOMINION::Graph_type Graph_type;
 typedef typename DOMINION::Document_type Document_type;
 typedef typename DOMINION::Root_type Root_type;
 typedef caon_ptr<Connectors_type> Connectors_Caon_type;
 typedef caon_ptr<Annotated_Connectors_type> Annotated_Connectors_Caon_type;
 typedef caon_ptr<Connection_type> Connection_Caon_type;
 typedef caon_ptr<Node_type> Node_Caon_type;
 typedef caon_ptr<Root_type> Root_Caon_type;
};

template<typename DOMINION_Type,
   typename GALAXY_Type>
class node_annotated_connectors;

template<typename DOMINION_Type,
   typename GALAXY_Type = typename DOMINION_Type::Galaxy_type>
class node_connectors
{
 typedef typename GALAXY_Type::tString tString;
 typedef typename GALAXY_Type::Node_type Node_type;
 typedef typename GALAXY_Type::Node_Caon_type Node_Caon_type;
 typedef typename GALAXY_Type::Connectors_type Connectors_type;
 typedef typename GALAXY_Type::Connectors_Caon_type Connectors_Caon_type;
 typedef typename GALAXY_Type::Connection_type Connection_type;
 typedef typename GALAXY_Type::Connection_Caon_type Connection_Caon_type;
 typedef typename GALAXY_Type::Annotated_Connectors_type Annotated_Connectors_type;

 typedef node_connectors<DOMINION_Type, GALAXY_Type> self_type;

 tString label_;

 struct Node_With_Write_Connection
 {
  const self_type* _this;
  Connection_Caon_type& write_connection;
  Node_Caon_type operator()(Node_Caon_type node) const
  {
   const Connectors_type* cast = static_cast<const Connectors_type*>(_this);
   return node->retrieve(write_connection, *cast);
  }
 };

public:

 node_connectors(tString label) : label_(label) {}

 tString label() const
 {
  return label_;
 }
 Node_Caon_type operator()(Node_Caon_type node) const
 {
  const Connectors_type* cast = static_cast<const Connectors_type*>(this);
  return node->retrieve(*cast);
 }

 Node_With_Write_Connection operator[](Connection_Caon_type& cion) const
 {
  return {this, cion};
 }

 Annotated_Connectors_type operator()(Connection_Caon_type cion) const
 {
  const Connectors_type* cast = static_cast<const Connectors_type*>(this);
  return Annotated_Connectors_type(*cast, cion);
 }

 bool operator()(Node_Caon_type n, Node_Caon_type target) const
 {
  const Connectors_type* cast = static_cast<const Connectors_type*>(this);
  return n->match_relation(*cast, target);
 }
};


template<typename DOMINION_Type,
   typename GALAXY_Type = typename DOMINION_Type::Galaxy_type>
struct node_annotated_connectors
{
 typedef typename GALAXY_Type::Connectors_type Connectors_type;
 typedef typename GALAXY_Type::Connection_Caon_type Connection_Caon_type;

 const Connectors_type& connector;
 Connection_Caon_type connection;

};



template<typename DOMINION_Type,
   typename GALAXY_Type = typename DOMINION_Type::Galaxy_type>
class node_query
{
protected:
 typedef typename GALAXY_Type::tString tString;
 typedef typename GALAXY_Type::Connectors_type Connectors_type;
};


template<typename DOMINION_Type,
   typename GALAXY_Type = typename DOMINION_Type::Galaxy_type>
class node_graph
{
 typedef typename GALAXY_Type::Root_Caon_type Root_Caon_type;
 typedef typename GALAXY_Type::Node_Caon_type Node_Caon_type;

protected:
 Node_Caon_type root_node_;

public:
 node_graph(Node_Caon_type root_node) : root_node_(root_node){}

 ACCESSORS(Node_Caon_type ,root_node)
 Root_Caon_type root(){ return root_node_->template as<Root_Caon_type>(); }

};

template<typename DOMINION_Type,
   typename GALAXY_Type = typename DOMINION_Type::Galaxy_type>
class node_frame
{
 typedef node_frame<DOMINION_Type, GALAXY_Type> self;
 typedef typename GALAXY_Type::Frame_type Frame_type;
 typedef typename GALAXY_Type::Node_Caon_type Node_Caon_type;
 typedef typename GALAXY_Type::Connectors_type Connectors_type;
 typedef typename GALAXY_Type::Connectors_Caon_type Connectors_Caon_type;
 typedef typename GALAXY_Type::Connection_type Connection_type;
 typedef typename GALAXY_Type::Connection_Caon_type Connection_Caon_type;
 typedef typename GALAXY_Type::Annotated_Connectors_type Annotated_Connectors_type;

public:
 struct Frame_With_Connector
 {
  Frame_type& frame;
  const Connectors_type& connector;
 };

 struct Frame_With_Annotated_Connector
 {
  Frame_type& frame;
  const Annotated_Connectors_type& annotated_connector;
 };

 friend Frame_With_Connector operator /(Frame_type& frame,
  const Connectors_type& connector)
 {
  return {frame, connector};
 }

 friend Frame_With_Annotated_Connector operator /(Frame_type& frame,
  const Annotated_Connectors_type& annotated_connector)
 {
  return {frame, annotated_connector};
 }

 void connect(Node_Caon_type node,
   const Connectors_type& connector, Node_Caon_type target)
 {
  node->connect(connector, target);
 }

 void connect(Node_Caon_type node,
   const Annotated_Connectors_type& annotated_connector, Node_Caon_type target)
 {
  node->connect(annotated_connector.connector, annotated_connector.connection, target);
 }

};

template<typename DOMINION_Type,
   typename GALAXY_Type = typename DOMINION_Type::Galaxy_type,
   typename VERTEX_Type = typename GALAXY_Type::Root_Vertex_type>
class node_ptr
{
 typedef node_ptr<DOMINION_Type, GALAXY_Type> self;

protected:

 typedef self node_ptr_base_type;

 typedef typename GALAXY_Type::tString tString;
 typedef typename GALAXY_Type::Connectors_type Connectors_type;
 typedef typename GALAXY_Type::Type_Codes_type Type_Codes_type;
 typedef typename GALAXY_Type::Node_Caon_type Node_Caon_type;
 typedef typename GALAXY_Type::Connectors_Caon_type Connectors_Caon_type;
 typedef typename GALAXY_Type::Annotated_Connectors_Caon_type Annotated_Connectors_Caon_type;
 typedef typename GALAXY_Type::Connection_Caon_type Connection_Caon_type;
 typedef typename GALAXY_Type::Frame_type Frame_type;

 typedef typename GALAXY_Type::Root_Void_type Root_Void_type;

 Type_Codes_type type_code_;

 QMultiMap<Connectors_Caon_type, Node_Caon_type> targets_;

 QMultiMap<Connectors_Caon_type, QPair<Connection_Caon_type, Node_Caon_type>> annotated_targets_;

 typedef QMapIterator<Connectors_Caon_type, Node_Caon_type> targets_iterator_type;
 typedef QMapIterator<Connectors_Caon_type, QPair<Connection_Caon_type, Node_Caon_type>> annotated_targets_iterator_type;

 VERTEX_Type vertex_;

#ifdef RELAE_LABEL_NODES
 tString label_;
#endif


#ifdef NO_CAON
 template<typename T>
 node_ptr(T* v) :
  type_code_(dominion_get_type_code<DOMINION_Type, T>()),
  vertex_(
   (VERTEX_Type) v
   )
 {
 }
#else //NO_CAON
 template<typename T>
 node_ptr(caon_ptr<T> v) :
  type_code_(dominion_get_type_code<DOMINION_Type, T>()),
  vertex_(
   v.template caon_cast<VERTEX_Type>()
   )
 {
 }
#endif

public:

 struct Node_With_Connector {
  Node_Caon_type node;
  typename Frame_type::Frame_With_Connector frame_with_connector;
  friend void operator >>(const Node_With_Connector& lhs, Node_Caon_type rhs)
  {
   lhs.frame_with_connector.frame.connect(lhs.node,
     lhs.frame_with_connector.connector, rhs);
  }
 };

 struct Node_With_Annotated_Connector {
  Node_Caon_type node;
  typename Frame_type::Frame_With_Annotated_Connector frame_with_annotated_connector;
  friend void operator >>(const Node_With_Annotated_Connector& lhs,
    Node_Caon_type rhs)
  {
   lhs.frame_with_annotated_connector.frame.connect(lhs.node,
     lhs.frame_with_annotated_connector.annotated_connector, rhs);
  }
 };

public:

 ACCESSORS(Type_Codes_type ,type_code)
 ACCESSORS(VERTEX_Type ,vertex)

 #ifdef RELAE_LABEL_NODES
  ACCESSORS(tString ,label)
 #else
  static void set_label(tString){}
  static tString label(){ return tString(); }
 #endif


 typedef DOMINION_Type Dominion_type;
 typedef GALAXY_Type Galaxy_type;

 void connect(const Connectors_type& connector, Node_Caon_type target)
 {
  targets_.insert(caon_ptr<Connectors_type>(&connector), target);
 }

 void connect(const Connectors_type& connector, Connection_Caon_type connection, Node_Caon_type target)
 {
  annotated_targets_.insert(caon_ptr<Connectors_type>(&connector), {connection, target});
 }


 Node_Caon_type retrieve(const Connectors_type& connector)
 {
  return targets_.value(caon_ptr<Connectors_type>(&connector));
 }

 Node_Caon_type retrieve(Connection_Caon_type& connection, const Connectors_type& connector)
 {
  if(annotated_targets_.contains(caon_ptr<Connectors_type>(&connector)))
  {
   auto result = annotated_targets_.value(caon_ptr<Connectors_type>(&connector));
   connection = result.first;
   return result.second;
  }
  // // fall back to unannotated ...
  return retrieve(connector);
 }

 void match_relation(const Connectors_type& connector, QList<Node_Caon_type>& target_nodes)
 {
  targets_iterator_type it(targets_);
  while(it.hasNext())
  {
   it.next();
   Connectors_Caon_type con = it.key();
   if(con == caon_ptr<Connectors_type>(&connector))
   {
    // //  The question here is whether a single relations
    //    can appear multiple times in the list or
    //    just once with a list of targets.
    target_nodes.push_back(it.value());
   }
  }
 }

 bool match_relation(const Connectors_type& connector, Node_Caon_type target)
 {
  targets_iterator_type it(targets_);
  while(it.hasNext())
  {
   it.next();
   Connectors_Caon_type con = it.key();
   if(con == caon_ptr<Connectors_type>(&connector))
   {
    if(it.value() == target)
     return true;
   }
  }
  return false;
 }



 template<typename T>
 caon_ptr<T> as()
 {
  return vertex_.template as<T>();
 }

 friend Node_With_Connector operator<<(Node_Caon_type lhs, typename Frame_type::Frame_With_Connector rhs)
 {
  return {lhs, rhs};
 }

 friend Node_With_Annotated_Connector operator<<(Node_Caon_type lhs, typename Frame_type::Frame_With_Annotated_Connector rhs) //? Frame_With_Connector& rhs
 {
  return {lhs, rhs};
 }

};


#endif //RELAE_NODE_PTR__H
