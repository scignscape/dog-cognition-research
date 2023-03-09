
#ifndef GTAGML_DOMINION__H
#define GTAGML_DOMINION__H


#include "relae-graph/relae-node-ptr.h"
#include "relae-graph/relae-caon-ptr.h"

#include "kans.h"



#define DOMINION_TYPE DOMINION_TYPE_DECLARE
#include "dominion/types.h"
#undef DOMINION_TYPE

KANS_(GTagML)

struct GTagML_Galaxy;
class GTagML_Node;
class GTagML_Connectors;
class GTagML_Connection;
class GTagML_Annotated_Connectors;
class GTagML_Frame;
class GTagML_Root;
class GTagML_Graph;
class GTagML_Document;


struct GTagML_Dominion
{
 typedef GTagML_Galaxy Galaxy_type;
 typedef GTagML_Node Node_type;
 typedef GTagML_Frame Frame_type;
 typedef GTagML_Connectors Connectors_type;
 typedef GTagML_Connection Connection_type;
 typedef GTagML_Annotated_Connectors Annotated_Connectors_type;;
 typedef GTagML_Graph Graph_type;
 typedef GTagML_Document Document_type;
 typedef GTagML_Root Root_type;

 enum class Type_Codes {
  #define DOMINION_TYPE DOMINION_TYPE_ENUM
  #include "dominion/types.h"
  #undef DOMINION_TYPE
 };

 template<typename T>
 Type_Codes get_type_code()
 {
 }
};

struct GTagML_Galaxy : Node_Ptr_Default_Galaxy<GTagML_Dominion>
{
};

struct GTagML_Connectors : node_connectors<GTagML_Dominion> {
  GTagML_Connectors(QString label) : node_connectors<GTagML_Dominion>(label){}
};

_KANS(GTagML)


#endif
