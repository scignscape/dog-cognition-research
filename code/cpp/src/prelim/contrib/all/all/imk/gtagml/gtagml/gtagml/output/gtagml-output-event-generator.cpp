
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-output-event-generator.h"

#include <QDebug>

#include "gtagml-output-event-handler.h"
#include "kernel/output/gtagml-connection-descriptor.h"
#include "kernel/graph/gtagml-graph.h"
#include "kernel/graph/gtagml-node.h"
#include "kernel/output/gtagml-output-bundle.h"
#include "tag-command/gtagml-tag-command-callback.h"


#include "kans.h"
USING_KANS(GTagML)


GTagML_Output_Event_Generator::GTagML_Output_Event_Generator
 (GTagML_Output_Base& output_base, GTagML_Output_Event_Handler& handler)
 : GTagML_Output_Base(output_base), handler_(handler)
{

}

GTagML_Output_Event_Generator::~GTagML_Output_Event_Generator()
{
 //qDebug() << "del GTagML_Output_Event_Generator";
}

void GTagML_Output_Event_Generator::generate(QTextStream& qts)
{
 caon_ptr<tNode> root_node = graph_.root_node();
 CAON_PTR_DEBUG(tNode ,root_node)
 root_node->debug_connectors();
 u4 index = 2; // // assume `[//] ...
//? 

// const GTagML_Output_Bundle b& {qts, index, root_node};
// GTagML_Output_Bundle b {qts, index, root_node};

 GTagML_Output_Bundle b {.qts = qts, .index = index,
   .node = root_node };

 if(caon_ptr<GTagML_Root> nr = root_node->GTagML_root())
 {
  CAON_PTR_DEBUG(GTagML_Root ,nr)
  handler_.generate_root(b, nr);
 }
 check_connectors_on_root(b);
}

caon_ptr<GTagML_Output_Event_Generator::tNode>
 GTagML_Output_Event_Generator::check_tag_command_entry_connectors(const GTagML_Output_Bundle& b,
  bool write_connector)
{
 CAON_PTR_B_DEBUG(tNode ,node)
 if(caon_ptr<tNode> target_node = qry_.Tag_Command_Entry(b.node))
 {
  CAON_PTR_DEBUG(tNode ,target_node)
  if(write_connector)
  {
   handler_.generate_tag_command_entry_connector(b.with_node(target_node));
  }
  generate_tag_command_entry(b.with(b.node, target_node,
    GTagML_Connection_Descriptor::Tag_Command_Entry));
  return target_node;
 }
 return caon_ptr<tNode>( nullptr );
}


caon_ptr<GTagML_Output_Event_Generator::tNode>
 GTagML_Output_Event_Generator::check_closed_tag_command_entry_connectors(const GTagML_Output_Bundle& b)
{
 if(caon_ptr<tNode> target_node = qry_.Tag_Command_Entry(b.node))
 {
  CAON_PTR_DEBUG(tNode ,target_node)
  generate_tag_command_entry(b.with(target_node, GTagML_Connection_Descriptor::Tag_Command_Cross));
  return target_node;
 }
 return caon_ptr<tNode>( nullptr );
}


void GTagML_Output_Event_Generator::check_connectors_on_root(const GTagML_Output_Bundle& b)
{
 CAON_PTR_B_DEBUG(tNode ,node)

 if(caon_ptr<tNode> target_node = check_tag_command_entry_connectors(b))
 {
  CAON_PTR_DEBUG(tNode ,target_node)
 }
 else if(target_node = qry_.Tile_Sequence(b.node))
 {
  CAON_PTR_DEBUG(tNode ,target_node)
  generate_tile(b.with(target_node, GTagML_Connection_Descriptor::Tag_Command_Main_Tile));
  check_tile_follow(b.with_node(target_node));
 }
}

void GTagML_Output_Event_Generator::check_tag_body_connectors(//?const
  const GTagML_Output_Bundle& b)
{
 CAON_PTR_B_DEBUG(tNode ,node)

 if(caon_ptr<tNode> target_node = qry_.Tag_Command_Attribute_Tile(b.node))
 {
  CAON_PTR_DEBUG(tNode ,target_node)
  generate_attribute_tile(b.with(target_node, GTagML_Connection_Descriptor::Tag_Command_Attribute_Tile));
  check_tile_follow(b.with_node(target_node));
 }

}

void GTagML_Output_Event_Generator::generate_attribute_tile(const GTagML_Output_Bundle& b)
{
 CAON_PTR_B_DEBUG(tNode ,node)
 handler_.generate_tile(b);
}


void GTagML_Output_Event_Generator::check_tag_command_tile_connectors(//?const
  const GTagML_Output_Bundle& b)
{
 if(caon_ptr<tNode> target_node = qry_.Tag_Command_Main_Tile(b.node))
 {
  CAON_PTR_DEBUG(tNode ,target_node)
  generate_tile(b.with(target_node, GTagML_Connection_Descriptor::Tag_Command_Main_Tile));

  //  In case the main tile is (or starts with) an annotation
  if(caon_ptr<tNode> anode = qry_.Tile_Annotation(target_node))
  {
   CAON_PTR_DEBUG(tNode ,anode)
   if(caon_ptr<GTagML_Tile> tile = target_node->GTagML_tile())
   {
    handler_.handle_annotation(tile, anode);
    // tag_command_annotation(target_node, anode);
   }
  }

  check_tile_follow(b.with_node(target_node));
 }

}


void GTagML_Output_Event_Generator::check_closed_tag_command_tile_connectors(//?const
  const GTagML_Output_Bundle& b)
{
 if(caon_ptr<tNode> target_node = qry_.Tag_Command_Main_Tile(b.node))
 {
  CAON_PTR_DEBUG(tNode ,target_node)
  generate_tile(b.with(target_node, GTagML_Connection_Descriptor::Closed_Tag_Command_Main_Tile));
  check_tile_follow(b.with_node(target_node));
 }
}

void GTagML_Output_Event_Generator::generate_tile(const GTagML_Output_Bundle& b)
{
 CAON_PTR_B_DEBUG(tNode ,node)

 handler_.generate_tile(b);

}


void GTagML_Output_Event_Generator::check_tag_command_cross_connectors(//?const
  const GTagML_Output_Bundle& b)
{
 CAON_PTR_B_DEBUG(tNode ,node)
 bool node_was_blank = false;
 if(b.cb)
 {
  if(b.cb->flags.has_around_callback && !b.cb->flags.post_fallthrough)
  {
   node_was_blank = true;
  }
 }
 if(caon_ptr<tNode> target_node = qry_.Tag_Command_Cross(b.node))
 {
  CAON_PTR_DEBUG(tNode ,target_node)
  if(node_was_blank)
    generate_tag_command_entry(b.with(target_node, GTagML_Connection_Descriptor::Tag_Command_Cross_From_Blank));
  else
  {
   caon_ptr<tNode> pcn = b.node;
   generate_tag_command_entry(b.with(target_node, GTagML_Connection_Descriptor::Tag_Command_Cross, pcn));
  }
 }
 else if(target_node = qry_.Tag_Command_Continue(b.node))
 {
  if(node_was_blank)
   generate_tile(b.with(target_node, GTagML_Connection_Descriptor::Tag_Command_Continue_From_Blank));
  else
   generate_tile(b.with(target_node, GTagML_Connection_Descriptor::Tag_Command_Continue));
  check_tile_follow(b.with_node(target_node));
 }
}

void GTagML_Output_Event_Generator::check_closed_tag_command_cross_connectors(//?const
  const GTagML_Output_Bundle& b)
{
 CAON_PTR_B_DEBUG(tNode ,node)
 bool node_was_blank = false;
 if(b.cb)
 {
  if(b.cb->flags.has_around_callback && !b.cb->flags.post_fallthrough)
  {
   node_was_blank = true;
  }
 }
 if(caon_ptr<tNode> target_node = qry_.Tag_Command_Cross(b.node))
 {
  CAON_PTR_DEBUG(tNode ,target_node)
  if(node_was_blank)
   generate_tag_command_entry(b.with(target_node, GTagML_Connection_Descriptor::Tag_Command_Cross_From_Blank));
  else
   generate_tag_command_entry(b.with(target_node, GTagML_Connection_Descriptor::Tag_Command_Cross));
 }
 else if(target_node = qry_.Tag_Command_Continue(b.node))
 {
  if(node_was_blank)
   generate_tile(b.with(target_node, GTagML_Connection_Descriptor::Tag_Command_Continue_From_Blank));
  else
   generate_tile(b.with(target_node, GTagML_Connection_Descriptor::Tag_Command_Continue));
  check_tile_follow(b.with_node(target_node));
 }
}


void GTagML_Output_Event_Generator::check_tile_follow(//?const
  const GTagML_Output_Bundle& b)
{
 CAON_PTR_B_DEBUG(tNode ,node)
   b.node->debug_connectors();
 if(caon_ptr<tNode> target_node = check_tag_command_entry_connectors(b, true))
 {
  CAON_PTR_DEBUG(tNode ,target_node)
  CAON_DEBUG_NOOP
 }
 else if(target_node = qry_.Tile_Sequence(b.node))
 {
  generate_tile_sequence(b.with(target_node, GTagML_Connection_Descriptor::Tile_Sequence));
  check_tile_follow(b.with_node(target_node));
 }
 else if(target_node = qry_.Annotation_Tile_Sequence(b.node))
 { // Annotation_Tile_Sequence? ...
  generate_tile_sequence(b.with(target_node, GTagML_Connection_Descriptor::Tile_Sequence));
  check_tile_follow(b.with_node(target_node));
 }
}

void GTagML_Output_Event_Generator::generate_tile_sequence(const GTagML_Output_Bundle& b)
{
 CAON_PTR_B_DEBUG(tNode ,node)
 if(caon_ptr<GTagML_Tile> tile = b.node->GTagML_tile())
 {
  handler_.generate_tile(b, tile);
  if(caon_ptr<tNode> n = qry_.Tile_Annotation(b.node))
  {
   handler_.handle_annotation(tile, n);
  }
 }
 else if(caon_ptr<GTagML_Attribute_Tile> tile = b.node->GTagML_attribute_tile())
 {
  handler_.generate_tile(b, tile);
 }
 else if(caon_ptr<GTagML_Paralex_Tile> tile = b.node->GTagML_paralex_tile())
 {
  handler_.generate_tile(b, tile);
 }
 else if(caon_ptr<GTagML_Annotation_Tile> tile = b.node->GTagML_annotation_tile())
 {
  CAON_PTR_DEBUG(GTagML_Annotation_Tile ,tile)
  handler_.generate_tile(b, tile);
 }
 else if(caon_ptr<GTagML_Raw_Tile> tile = b.node->GTagML_raw_tile())
 {
  CAON_PTR_DEBUG(GTagML_Raw_Tile ,tile)
  handler_.generate_tile(b, tile);
 }

 //handler_.generate_tag_command_leave(b);
}


void GTagML_Output_Event_Generator::generate_tag_command_leave(const GTagML_Output_Bundle& b)
{
 CAON_PTR_B_DEBUG(tNode ,node)

 handler_.generate_tag_command_leave(b);
}


void GTagML_Output_Event_Generator::generate_tag_command_entry(const GTagML_Output_Bundle& b)
{
 CAON_PTR_B_DEBUG(tNode ,node)

 caon_ptr<GTagML_Tag_Command_Callback> cb = handler_.check_command_callback(b);

 const GTagML_Output_Bundle& bwc = b.with_callback(cb);
 caon_ptr<GTagML_Tag_Command> closed_tag_command = handler_.generate_tag_command_entry(bwc);

 check_tag_body_connectors(bwc);
 if(cb)
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command_Callback ,cb)
  if(cb->flags.pre_fallthrough)
  {
   if(closed_tag_command)
   {
    //? handler_.generate_tag_command_auto_leave(b);
   }
   else
   {
    handler_.generate_tag_body_leave(bwc);
   }
  }
 }
 else
 {
  if(closed_tag_command)
  {
   //? handler_.generate_tag_command_auto_leave(b);
  }
  else
  {
   handler_.generate_tag_body_leave(bwc);
  }
 }
 caon_ptr<tNode> target_node = caon_ptr<tNode>( nullptr );
 if(closed_tag_command)
 {
  handler_.generate_tag_command_auto_leave(bwc);
  target_node = check_closed_tag_command_entry_connectors(bwc);
 }
 else
 {
  target_node = check_tag_command_entry_connectors(bwc);
 }
 if(target_node)
 {
  CAON_PTR_DEBUG(tNode ,target_node)
  CAON_DEBUG_NOOP
 }
 else
 {
  bool ok_check_tag_command_tile_connectors = true;
  if(cb)
  {
   // //  Any flag affects this...?
   CAON_PTR_DEBUG(GTagML_Tag_Command_Callback ,cb)
   if(cb->flags.pre_fallthrough)
    ;
   else if(cb->flags.has_around_callback)
   {
    ok_check_tag_command_tile_connectors = false;
   }
  }
  if(ok_check_tag_command_tile_connectors)
  {
   if(closed_tag_command)
   {
    check_closed_tag_command_tile_connectors(bwc);
   }
   else
   {
    check_tag_command_tile_connectors(bwc);
   }
  }
 }

 if(closed_tag_command)
 {
  //?check_closed_tag_command_cross_connectors(bwc);
  //?handler_.generate_tag_command_auto_leave(bwc);
 }
 else
 {
  generate_tag_command_leave(bwc);
  check_tag_command_cross_connectors(bwc);
 }

}

