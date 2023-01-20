
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NTXH_DOMINION__H
#define NTXH_DOMINION__H


#include "relae-graph/relae-node-ptr.h"
#include "relae-graph/relae-caon-ptr.h"


#define DOMINION_HIDE_NO_NAMESPACE
#define DOMINION_TYPE DOMINION_TYPE_DECLARE
#include "dominion/types.h"
#undef DOMINION_TYPE
#undef DOMINION_HIDE_NO_NAMESPACE

#include "kans.h"

KANS_(HGDMCore)

struct NTXH_Galaxy;
class NTXH_Node;
class NTXH_Connectors;
class NTXH_Connection;
class NTXH_Annotated_Connectors;
class NTXH_Frame;
class NTXH_Document;
class NTXH_Graph;
class NTXH_Root;
class NTXH_Token;

struct NTXH_Dominion
{
 typedef NTXH_Galaxy Galaxy_type;
 typedef NTXH_Node Node_type;
 typedef NTXH_Frame Frame_type;
 typedef NTXH_Connectors Connectors_type;
 typedef NTXH_Connection Connection_type;
 typedef NTXH_Annotated_Connectors Annotated_Connectors_type;
 typedef NTXH_Document Document_type;
 typedef NTXH_Graph Graph_type;
 typedef NTXH_Root Root_type;

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



struct NTXH_Galaxy : Node_Ptr_Default_Galaxy<NTXH_Dominion>
{
 typedef NTXH_Token NTXH_Token_type;

};

enum class NTXH_Connectors_Case_Labels
{
 #define DOMINION_CONNECTOR(name, label) \
  name,
 #include "kernel/dominion/connectors.h"
 #undef DOMINION_CONNECTOR
};

struct NTXH_Connectors : node_connectors<NTXH_Dominion>
{
  NTXH_Connectors(NTXH_Connectors_Case_Labels cl = NTXH_Connectors_Case_Labels::N_A,
    QString label = QString())
   : node_connectors<NTXH_Dominion>(label), case_label(cl),
     priority(0), order(0){}
  NTXH_Connectors_Case_Labels case_label;
  int priority;
  int order;
  bool operator<(const NTXH_Connectors& rhs) const
  {
   return order < rhs.order;
  }
  operator bool() const
  {
   return order > 0;
  }
};

struct NTXH_Annotated_Connectors :
  node_annotated_connectors<NTXH_Dominion>
{
 NTXH_Annotated_Connectors(const NTXH_Connectors& conn,
   caon_ptr<NTXH_Connection> cion)
   : node_annotated_connectors<NTXH_Dominion>{conn, cion} {}

};

_KANS(HGDMCore)

#endif
