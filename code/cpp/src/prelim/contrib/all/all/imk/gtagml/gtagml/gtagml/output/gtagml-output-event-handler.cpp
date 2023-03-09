
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-output-event-handler.h"

#include "kernel/document/gtagml-document.h"
#include "kernel/graph/gtagml-node.h"
#include "tile/gtagml-token.h"
#include "kernel/output/gtagml-output-bundle.h"

#include "tile/gtagml-tile.h"
#include "tile/gtagml-attribute-tile.h"
#include "tile/gtagml-raw-tile.h"

#include "tag-command/gtagml-tag-command.h"
#include "tile/gtagml-paralex-tile.h"

#include "annotation/gtagml-annotation-tile.h"

//?#include "ngml-htxn/ngml-htxn-node.h"

#include <QFile>
#include <QFileInfo>

#include "kans.h"

USING_KANS(GTagML)


GTagML_Output_Event_Handler::GTagML_Output_Event_Handler()
{

}

caon_ptr<GTagML_Tag_Command_Callback>
 GTagML_Output_Event_Handler::check_command_callback(const GTagML_Output_Bundle& b)
{
 if(caon_ptr<GTagML_Tag_Command> ntc = b.node->GTagML_tag_command())
 {
  return check_command_callback(ntc);
 }
}

caon_ptr<GTagML_Tag_Command_Callback>
 GTagML_Output_Event_Handler::check_command_callback(caon_ptr<GTagML_Tag_Command> ntc)
{
 CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
 return caon_ptr<GTagML_Tag_Command_Callback>( nullptr );
}

void GTagML_Output_Event_Handler::generate_root(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Root> nr)
{
}

caon_ptr<GTagML_Tag_Command> GTagML_Output_Event_Handler::generate_tag_command_entry(const GTagML_Output_Bundle& b)
{
 caon_ptr<GTagML_Tag_Command_Callback> cb = check_command_callback(b);
 if(caon_ptr<GTagML_Tag_Command> ntc = b.node->GTagML_tag_command())
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
  generate_tag_command_entry(b.with_callback(cb), ntc);

   // // ? wha ?
  if(ntc->flags.is_closed)
  {
   return ntc;
  }
 }
 return caon_ptr<GTagML_Tag_Command>( nullptr );
}

void GTagML_Output_Event_Handler::generate_tag_command_entry(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc)
{
}

void GTagML_Output_Event_Handler::generate_tag_command_leave(const GTagML_Output_Bundle& b)
{
 if(caon_ptr<GTagML_Tag_Command> ntc = b.node->GTagML_tag_command())
 {
  generate_tag_command_leave(b, ntc);
  check_generate_whitespace(b, ntc);
 }
}


void GTagML_Output_Event_Handler::tag_command_annotation(caon_ptr<GTagML_Tile> nt, caon_ptr<tNode> node)
{
 if(caon_ptr<GTagML_Annotation_Tile> tile = node->GTagML_annotation_tile())
  tag_command_annotation(nt, tile);
}

void GTagML_Output_Event_Handler::tag_command_annotation(caon_ptr<GTagML_Tile> nt,
  caon_ptr<GTagML_Annotation_Tile> tile)
{

}

void GTagML_Output_Event_Handler::generate_tag_command_auto_leave(const GTagML_Output_Bundle& b)
{
 if(caon_ptr<GTagML_Tag_Command> ntc = b.node->GTagML_tag_command())
 {
  generate_tag_command_auto_leave(b, ntc);
  check_generate_whitespace(b, ntc);
 }
}

void GTagML_Output_Event_Handler::generate_tag_command_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc)
{
}

void GTagML_Output_Event_Handler::generate_tag_command_auto_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc)
{
 generate_tag_command_leave(b, ntc);
}


void GTagML_Output_Event_Handler::generate_tag_body_leave(const GTagML_Output_Bundle& b)
{
 if(caon_ptr<GTagML_Tag_Command> ntc = b.node->GTagML_tag_command())
 {
  generate_tag_body_leave(b, ntc);
 }
}

void GTagML_Output_Event_Handler::generate_tag_command_entry_connector(const GTagML_Output_Bundle& b)
{

}

void GTagML_Output_Event_Handler::generate_tag_body_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc)
{
}


void GTagML_Output_Event_Handler::generate_tile(const GTagML_Output_Bundle& b)
{
 if(caon_ptr<GTagML_Tile> tile = b.node->GTagML_tile())
 {
  generate_tile(b, tile);
 }
 else if(caon_ptr<GTagML_Attribute_Tile> tile = b.node->GTagML_attribute_tile())
 {
  generate_tile(b, tile);
 }
 else if(caon_ptr<GTagML_Paralex_Tile> tile = b.node->GTagML_paralex_tile())
 {
  generate_tile(b, tile);
 }
 else if(caon_ptr<GTagML_Raw_Tile> tile = b.node->GTagML_raw_tile())
 {
  generate_tile(b, tile);
 }

}

void GTagML_Output_Event_Handler::check_update_index(const GTagML_Output_Bundle& b,
  GTagML_Tile& tile)
{
 b.index += tile.raw_text().length();
}

//void GTagML_Output_Event_Handler::generate_tile_via_htxn(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
//{

//}

//void GTagML_Output_Event_Handler::generate_attribute_tile_via_htxn(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
//{

//}

//void GTagML_Output_Event_Handler::generate_parelex_tile_via_htxn(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
//{

//}

//void GTagML_Output_Event_Handler::generate_annotation_tile_via_htxn(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
//{

//}

void GTagML_Output_Event_Handler::generate_tile_via_gh(const GTagML_Output_Bundle& b, GH_Prenode& ghn)
{

}

void GTagML_Output_Event_Handler::generate_tile(const GTagML_Output_Bundle& b,
  caon_ptr<GTagML_Raw_Tile> tile)
{
 CAON_PTR_DEBUG(GTagML_Raw_Tile ,tile)

 b.qts << tile->text();
}

void GTagML_Output_Event_Handler::generate_tile(const GTagML_Output_Bundle& b,
  caon_ptr<GTagML_Tile> tile)
{
 CAON_PTR_DEBUG(GTagML_Tile ,tile)

 if(GH_Prenode* ghp = tile->prenode())
 {
  generate_tile_via_gh(b, *ghp);
   // // here?
   //? check_generate_whitespace(b, *ghn);
  check_generate_whitespace(b, tile);
  return;
 }

 QString rt = tile->raw_text();

 if(!rt.startsWith("*:"))
 {
  b.qts << tile->raw_text();
  check_update_index(b, *tile);
 }
 check_generate_whitespace(b, tile);
}

void GTagML_Output_Event_Handler::generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Attribute_Tile> tile)
{
 tile->write_html(b.qts);
}

void GTagML_Output_Event_Handler::generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Annotation_Tile> tile)
{
}

void GTagML_Output_Event_Handler::handle_annotation(caon_ptr<GTagML_Tile> tile, caon_ptr<GTagML_Annotation_Tile> atile)
{

}

void GTagML_Output_Event_Handler::handle_annotation(caon_ptr<GTagML_Tile> tile, caon_ptr<tNode> node)
{
 if(caon_ptr<GTagML_Annotation_Tile> atile = node->GTagML_annotation_tile())
 {
  handle_annotation(tile, atile);
 }
}

void GTagML_Output_Event_Handler::generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Paralex_Tile> tile)
{
 tile->write_html(b.qts);
 check_generate_whitespace(b, tile);
}

//void GTagML_Output_Event_Handler::check_generate_whitespace(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
//{
// nhn.write_whitespace(b.qts);
//}


void GTagML_Output_Event_Handler::check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc)
{
 CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
 ntc->write_whitespace(b.qts);
 //? check_update_index_after_whitespace(b, ntc);
}

void GTagML_Output_Event_Handler::check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Paralex_Tile> tile)
{
 tile->write_whitespace(b.qts);
}

void GTagML_Output_Event_Handler::check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tile> tile)
{
 tile->write_whitespace(b.qts);
 check_update_index_after_whitespace(b, *tile);
}

void GTagML_Output_Event_Handler::check_update_index_after_whitespace(const GTagML_Output_Bundle& b,
  GTagML_Tile& tile)
{
 b.index += tile.ws().get_length();
}

void GTagML_Output_Event_Handler::check_update_index_after_whitespace(const GTagML_Output_Bundle& b,
  GTagML_Tag_Command& ntc)
{
 b.index += ntc.ws().get_length();
}

