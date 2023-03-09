
#ifndef GTAGML_OUTPUT_EVENT_HANDLER__H
#define GTAGML_OUTPUT_EVENT_HANDLER__H

#include <QTextStream>

#include "relae-graph/relae-node-ptr.h"
#include "kernel/gtagml-dominion.h"
#include "kernel/query/gtagml-query.h"
#include "kernel/output/gtagml-connection-descriptor.h"
#include "accessors.h"
#include "kans.h"

KANS_(GTagML)

class GTagML_Graph;
class GTagML_Document;
class GTagML_Node;
class GTagML_Tag_Command;
class GTagML_Root;
class GTagML_Annotation_Tile;
class GTagML_Output_Bundle;
class GTagML_Tag_Command_Callback;

class GH_Prenode;

class GTagML_Output_Event_Handler
{
protected:

 typedef GTagML_Node tNode;

 GTagML_Output_Event_Handler();

public:

 virtual caon_ptr<GTagML_Tag_Command_Callback> check_command_callback(const GTagML_Output_Bundle& b);
 virtual caon_ptr<GTagML_Tag_Command_Callback> check_command_callback(caon_ptr<GTagML_Tag_Command> ntc);


 virtual caon_ptr<GTagML_Tag_Command> generate_tag_command_entry(const GTagML_Output_Bundle& b);
 virtual void generate_tag_command_entry(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc);

 virtual void check_update_index(const GTagML_Output_Bundle& b, GTagML_Tile& tile);
 virtual void check_update_index_after_whitespace(const GTagML_Output_Bundle& b,
   GTagML_Tile& tile);
 virtual void check_update_index_after_whitespace(const GTagML_Output_Bundle& b,
   GTagML_Tag_Command& ntc);


 virtual void generate_tag_command_leave(const GTagML_Output_Bundle& b);
 virtual void generate_tag_command_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc);

 virtual void generate_tag_command_entry_connector(const GTagML_Output_Bundle& b);

 virtual void generate_tag_command_auto_leave(const GTagML_Output_Bundle& b);
 virtual void generate_tag_command_auto_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc);

 virtual void generate_tag_body_leave(const GTagML_Output_Bundle& b);
 virtual void generate_tag_body_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc);

 virtual void generate_tile(const GTagML_Output_Bundle& b);
 virtual void generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tile> tile);
 virtual void generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Attribute_Tile> tile);
 virtual void generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Paralex_Tile> tile);
 virtual void generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Annotation_Tile> tile);
 virtual void generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Raw_Tile> tile);

 virtual void generate_tile_via_gh(const GTagML_Output_Bundle& b, GH_Prenode& ghp);

// virtual void generate_tile_via_htxn(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn);
// virtual void generate_attribute_tile_via_htxn(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn);
// virtual void generate_parelex_tile_via_htxn(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn);
// virtual void generate_annotation_tile_via_htxn(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn);


 virtual void handle_annotation(caon_ptr<GTagML_Tile> tile, caon_ptr<GTagML_Annotation_Tile> atile);
 virtual void handle_annotation(caon_ptr<GTagML_Tile> tile, caon_ptr<tNode> node);


// virtual void check_generate_whitespace(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn);

 virtual void check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tile> tile);
 virtual void check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Paralex_Tile> tile);
 virtual void check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc);

 virtual void tag_command_annotation(caon_ptr<GTagML_Tile> nt, caon_ptr<tNode> node);
 virtual void tag_command_annotation(caon_ptr<GTagML_Tile> nt, caon_ptr<GTagML_Annotation_Tile> tile);

 virtual void generate_root(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Root> nr);



};

_KANS(GTagML)


#endif
