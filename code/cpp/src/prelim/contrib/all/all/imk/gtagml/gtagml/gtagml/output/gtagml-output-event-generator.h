
#ifndef GTAGML_OUTPUT_EVENT_GENERATOR__H
#define GTAGML_OUTPUT_EVENT_GENERATOR__H

#include "relae-graph/relae-node-ptr.h"
#include "kernel/gtagml-dominion.h"
#include "kernel/query/gtagml-query.h"
#include "output/gtagml-output-base.h"
#include "kernel/output/gtagml-connection-descriptor.h"

#include "accessors.h"

#include "kans.h"

#include "kans.h"

KANS_(GTagML)

class GTagML_Graph;
class GTagML_Document;
class GTagML_Node;
class GTagML_Token;
class GTagML_Root;
class GTagML_Output_Base;
class GTagML_Output_Event_Handler;
class GTagML_Output_Bundle;

class GTagML_Output_Event_Generator : GTagML_Output_Base
{
 GTagML_Output_Event_Handler& handler_;

 HTXN_Document_8b* htxn_document_;

protected:

 typedef GTagML_Node tNode;

public:

 GTagML_Output_Event_Generator(GTagML_Output_Base& base, GTagML_Output_Event_Handler& handler);

 ACCESSORS(HTXN_Document_8b* ,htxn_document)

 ~GTagML_Output_Event_Generator();

 void generate(QTextStream& qts);

 void generate_tag_command_entry(const GTagML_Output_Bundle& b);
 void generate_tag_command_leave(const GTagML_Output_Bundle& b);

 void generate_attribute_tile(const GTagML_Output_Bundle& b);
 void generate_tile(const GTagML_Output_Bundle& b);
 void generate_tile_sequence(const GTagML_Output_Bundle& b);
 void check_tile_follow(const GTagML_Output_Bundle& b);

// void generate_tag_command_sequence(const const GTagML_Output_Bundle& b);

// void check_generate_token(const const GTagML_Output_Bundle& b);

 caon_ptr<tNode> check_tag_command_entry_connectors(const GTagML_Output_Bundle& b,
  bool write_connector = false);
 caon_ptr<tNode> check_closed_tag_command_entry_connectors(const GTagML_Output_Bundle& b);

 void check_tag_body_connectors(const GTagML_Output_Bundle& b);
 void check_connectors_on_root(const GTagML_Output_Bundle& b);


 void check_closed_tag_command_cross_connectors(const GTagML_Output_Bundle& b);

 void check_closed_tag_command_tile_connectors(const GTagML_Output_Bundle& b);

 void check_tag_command_tile_connectors(const GTagML_Output_Bundle& b);
 void check_tag_command_cross_connectors(const GTagML_Output_Bundle& b);

 // void check_cross_connectors(const const GTagML_Output_Bundle& b);
// void check_call_connectors(const const GTagML_Output_Bundle& b);

};

_KANS(GTagML)


#endif
