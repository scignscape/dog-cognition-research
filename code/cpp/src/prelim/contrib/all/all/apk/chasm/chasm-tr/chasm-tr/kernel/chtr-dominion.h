
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_DOMINION__H
#define CHTR_DOMINION__H


#include "relae-graph/relae-node-ptr.h"
#include "relae-graph/relae-caon-ptr.h"


#define DOMINION_HIDE_NO_NAMESPACE
#define DOMINION_TYPE DOMINION_TYPE_DECLARE
#include "dominion/types.h"
#undef DOMINION_TYPE
#undef DOMINION_HIDE_NO_NAMESPACE

#include "aqns.h"

AQNS_(Chasm_TR)

struct ChTR_Galaxy;
class ChTR_Node;
class ChTR_Connectors;
class ChTR_Connection;
class ChTR_Annotated_Connectors;
class ChTR_Relae_Frame;
class ChTR_Document;
class ChTR_Graph;
class ChTR_Root;
class ChTR_Token;

struct ChTR_Dominion
{
 typedef ChTR_Galaxy Galaxy_type;
 typedef ChTR_Node Node_type;
 typedef ChTR_Relae_Frame Frame_type;
 typedef ChTR_Connectors Connectors_type;
 typedef ChTR_Connection Connection_type;
 typedef ChTR_Annotated_Connectors Annotated_Connectors_type;
 typedef ChTR_Document Document_type;
 typedef ChTR_Graph Graph_type;
 typedef ChTR_Root Root_type;

 enum class Type_Codes { N_A,
  #define DOMINION_TYPE DOMINION_TYPE_ENUM
  #include "kernel/dominion/types.h"
  #undef DOMINION_TYPE
 };

 template<typename T>
 Type_Codes get_type_code()
 {
  return (Type_Codes) 0;
 }

};



struct ChTR_Galaxy : Node_Ptr_Default_Galaxy<ChTR_Dominion>
{
 typedef ChTR_Token ChTR_Token_type;

};

enum class ChTR_Connectors_Case_Labels
{
 #define DOMINION_CONNECTOR(name, label) \
  name,
 #include "kernel/dominion/connectors.h"
 #undef DOMINION_CONNECTOR
};

struct ChTR_Connectors : node_connectors<ChTR_Dominion>
{
  ChTR_Connectors(ChTR_Connectors_Case_Labels cl = ChTR_Connectors_Case_Labels::N_A,
    QString label = QString())
   : node_connectors<ChTR_Dominion>(label), case_label(cl),
     priority(0), order(0){}
  ChTR_Connectors_Case_Labels case_label;
  int priority;
  int order;
  bool operator<(const ChTR_Connectors& rhs) const
  {
   return order < rhs.order;
  }
  operator bool() const
  {
   return order > 0;
  }
};

struct ChTR_Annotated_Connectors :
  node_annotated_connectors<ChTR_Dominion>
{
 ChTR_Annotated_Connectors(const ChTR_Connectors& conn,
   caon_ptr<ChTR_Connection> cion)
   : node_annotated_connectors<ChTR_Dominion>{conn, cion} {}

};

_AQNS(Chasm_TR)

#endif
