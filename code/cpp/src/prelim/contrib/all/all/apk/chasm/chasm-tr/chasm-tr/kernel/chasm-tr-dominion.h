
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_TR_DOMINION__H
#define CHASM_TR_DOMINION__H


#include "relae-graph/relae-node-ptr.h"
#include "relae-graph/relae-caon-ptr.h"


#define DOMINION_HIDE_NO_NAMESPACE
#define DOMINION_TYPE DOMINION_TYPE_DECLARE
#include "dominion/types.h"
#undef DOMINION_TYPE
#undef DOMINION_HIDE_NO_NAMESPACE

#include "aqns.h"

AQNS_(ChasmTR)

struct Qh_CPP_Galaxy;
class Qh_CPP_Node;
class Qh_CPP_Connectors;
class Qh_CPP_Connection;
class Qh_CPP_Annotated_Connectors;
class Qh_CPP_Frame;
class Qh_CPP_Document;
class Qh_CPP_Graph;
class Qh_CPP_Root;
class Qh_CPP_Token;

struct Qh_CPP_Dominion
{
 typedef Qh_CPP_Galaxy Galaxy_type;
 typedef Qh_CPP_Node Node_type;
 typedef Qh_CPP_Frame Frame_type;
 typedef Qh_CPP_Connectors Connectors_type;
 typedef Qh_CPP_Connection Connection_type;
 typedef Qh_CPP_Annotated_Connectors Annotated_Connectors_type;
 typedef Qh_CPP_Document Document_type;
 typedef Qh_CPP_Graph Graph_type;
 typedef Qh_CPP_Root Root_type;

 enum class Type_Codes { N_A,
  #define DOMINION_TYPE DOMINION_TYPE_ENUM
  #include "dominion/types.h"
  #undef DOMINION_TYPE
 };

 template<typename T>
 Type_Codes get_type_code()
 {
  return (Type_Codes) 0;
 }

};



struct Qh_CPP_Galaxy : Node_Ptr_Default_Galaxy<Qh_CPP_Dominion>
{
 typedef Qh_CPP_Token Qh_CPP_Token_type;

};

enum class Qh_CPP_Connectors_Case_Labels
{
 #define DOMINION_CONNECTOR(name, label) \
  name,
 #include "kernel/dominion/connectors.h"
 #undef DOMINION_CONNECTOR
};

struct Qh_CPP_Connectors : node_connectors<Qh_CPP_Dominion>
{
  Qh_CPP_Connectors(Qh_CPP_Connectors_Case_Labels cl = Qh_CPP_Connectors_Case_Labels::N_A,
    QString label = QString())
   : node_connectors<Qh_CPP_Dominion>(label), case_label(cl),
     priority(0), order(0){}
  Qh_CPP_Connectors_Case_Labels case_label;
  int priority;
  int order;
  bool operator<(const Qh_CPP_Connectors& rhs) const
  {
   return order < rhs.order;
  }
  operator bool() const
  {
   return order > 0;
  }
};

struct Qh_CPP_Annotated_Connectors :
  node_annotated_connectors<Qh_CPP_Dominion>
{
 Qh_CPP_Annotated_Connectors(const Qh_CPP_Connectors& conn,
   caon_ptr<Qh_CPP_Connection> cion)
   : node_annotated_connectors<Qh_CPP_Dominion>{conn, cion} {}

};

_AQNS(ChasmTR)

#endif
