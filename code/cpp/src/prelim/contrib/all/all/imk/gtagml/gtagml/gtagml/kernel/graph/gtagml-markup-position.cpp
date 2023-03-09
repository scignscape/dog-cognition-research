
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-markup-position.h"

#include "tag-command/gtagml-tag-command.h"

#include <QStringList>
#include <QRegularExpression>

#include <QDebug>

#include "kans.h"

USING_KANS(GTagML)


GTagML_Markup_Position::GTagML_Markup_Position(caon_ptr<tNode> current_node)
 :  current_node_(current_node), current_attribute_node_(nullptr),
   comment_semis_(0), comment_tildes_(0),
   fr_(GTagML_Frame::instance()), qry_(GTagML_Query::instance()),
   position_state_(Root), held_position_state_(Held_Empty), current_khif_connector_(Khif_Connectors::Khif_N_A)
{
}

void GTagML_Markup_Position::prepare_attribute_sequence()
{
 position_state_ = Tag_Body_Leave_Awaiting_Attributes;
}

caon_ptr<GTagML_Markup_Position::tNode>
  GTagML_Markup_Position::current_tag_command_node()
{
 if(tag_commands_.isEmpty())
   return nullptr;

 return tag_commands_.top();
}

QString GTagML_Markup_Position::current_tag_command_name()
{
 QString result;
 if(!tag_commands_.isEmpty())
 {
  if(caon_ptr<GTagML_Tag_Command> ntc = tag_commands_.top()->GTagML_tag_command())
  {
   result = ntc->name();
  }
 }
 return result;
}

void GTagML_Markup_Position::tag_command_annotation(caon_ptr<tNode> node)
{
 switch(position_state_)
 {
  case Tag_Command_Entry:
   current_node_ << fr_/qry_.Tag_Command_Annotation >> node;
   break;
  default:
   break;
 }
}

void GTagML_Markup_Position::close_annotation()
{
 position_state_ = Annotation_Close;
}


void GTagML_Markup_Position::annotation_entry(caon_ptr<tNode> node, caon_ptr<tNode> anode)
{
 CAON_PTR_DEBUG(tNode ,node)
 CAON_PTR_DEBUG(tNode ,current_node_)

 node << fr_/qry_.Tile_Annotation >> anode;

 switch(position_state_)
 {
   // //?  Is this part right?
 case Tag_Command_Entry:
   //
 case Tag_Body_Leave:
  current_node_ << fr_/qry_.Tag_Command_Main_Tile >> node;
  current_node_ = node;
  break;
 case Tag_Command_Leave:
  current_node_ << fr_/qry_.Tag_Command_Continue >> node;
  current_node_ = node;
  break;
 default:
  current_node_ << fr_/qry_.Annotation_Tile_Sequence >> node;
  current_node_ = node;
 }
}


void GTagML_Markup_Position::enter_multiline_comment(int semis, int tildes)
{
 comment_semis_ = semis;
 comment_tildes_ = tildes;
}

bool GTagML_Markup_Position::check_leave_multiline_comment(int semis, int tildes)
{
 if(comment_semis_ == semis && comment_tildes_ == tildes)
 {
  comment_semis_ = 0;
  comment_tildes_ = 0;
  return true;
 }
 return false;
}

void GTagML_Markup_Position::merge_multi_parent_inherited(GTagML_Tag_Command& parent,
  GTagML_Tag_Command& ntc)
{
 ntc.flags.is_multi_parent_inherited = parent.flags.is_multi_parent_inherited
   || parent.flags.is_multi_parent;
 ntc.flags.anticipate_semis_inherited =
   parent.flags.anticipate_semis_inherited || parent.flags.anticipate_semis;
// ntc.flags.is_multi_parent_semis_inherited = parent.flags.is_multi_parent_semis_inherited
//   || parent.flags.is_multi_parent_semis;

 ntc.flags.multi_arg_layer_inherited = parent.flags.multi_arg_layer
   || parent.flags.multi_arg_layer_inherited;
 ntc.flags.multi_main_layer_inherited = parent.flags.multi_main_layer
   || parent.flags.multi_main_layer_inherited;
}

void GTagML_Markup_Position::merge_multi_parent_sequence(GTagML_Tag_Command& parent,
  GTagML_Tag_Command& ntc)
{
 ntc.flags.is_multi_parent_inherited = parent.flags.is_multi_parent_inherited;
 ntc.flags.anticipate_semis_inherited = parent.flags.anticipate_semis_inherited;

 ntc.flags.multi_arg_layer_inherited = parent.flags.multi_arg_layer_inherited;
 ntc.flags.multi_main_layer_inherited = parent.flags.multi_main_layer_inherited;
}

void GTagML_Markup_Position::merge_multi_parent_inherited(GTagML_Tile& parent,
  GTagML_Tag_Command& ntc)
{
 if(caon_ptr<GTagML_Tag_Command> pntc = get_current_tag_command())
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command ,pntc)
  ntc.flags.is_multi_parent_inherited = pntc->flags.is_multi_parent_inherited
    || pntc->flags.is_multi_parent;
  ntc.flags.anticipate_semis_inherited = pntc->flags.anticipate_semis_inherited
    || pntc->flags.anticipate_semis;

  ntc.flags.multi_arg_layer_inherited = pntc->flags.multi_arg_layer
    || pntc->flags.multi_arg_layer_inherited;
  ntc.flags.multi_main_layer_inherited = pntc->flags.multi_main_layer
    || pntc->flags.multi_main_layer_inherited;
 }
}


void GTagML_Markup_Position::merge_multi_parent_inherited(caon_ptr<tNode> parent,
  caon_ptr<tNode> node)
{
 if(caon_ptr<GTagML_Tag_Command> ntc = parent->GTagML_tag_command())
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
  if(caon_ptr<GTagML_Tag_Command> ntc1 = node->GTagML_tag_command())
  {
   CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc1)
   merge_multi_parent_inherited(*ntc, *ntc1);
  }
 }
 else if(caon_ptr<GTagML_Tile> tile = parent->GTagML_tile())
 {
  CAON_PTR_DEBUG(GTagML_Tile ,tile)
  if(caon_ptr<GTagML_Tag_Command> ntc1 = node->GTagML_tag_command())
  {
   CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc1)
   merge_multi_parent_inherited(*tile, *ntc1);
  }
 }
}

void GTagML_Markup_Position::merge_multi_parent_sequence(caon_ptr<tNode> prior, caon_ptr<tNode> node)
{
 if(caon_ptr<GTagML_Tag_Command> ntc = prior->GTagML_tag_command())
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
  if(caon_ptr<GTagML_Tag_Command> ntc1 = node->GTagML_tag_command())
  {
   CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc1)
   merge_multi_parent_sequence(*ntc, *ntc1);  }
 }
}

void GTagML_Markup_Position::await_mandatory_or_optional(caon_ptr<tNode> node)
{
 if(caon_ptr<GTagML_Tag_Command> ntc = current_node_->GTagML_tag_command())
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
  CAON_DEBUG_NOOP
 }
 switch(position_state_)
 {
//? case Tag_Command_Entry:
 case Tag_Body_Leave:
  current_node_ << fr_/qry_.Tag_Command_Entry >> node;
  merge_multi_parent_inherited(current_node_, node);
  break;
 case Tag_Command_Leave:
  current_node_ << fr_/qry_.Tag_Command_Cross >> node;
  merge_multi_parent_sequence(current_node_, node);
  break;
 default:
   // // any others?
   break;
 }
 current_node_ = node;
 tag_commands_.push(node);

 position_state_ = Tag_Body_Leave;
}

void GTagML_Markup_Position::await_optional(caon_ptr<tNode> node)
{
// position_state_ = Await_Optional;
 await_mandatory_or_optional(node);
}

void GTagML_Markup_Position::await_mandatory(caon_ptr<tNode> node)
{
// position_state_ = Await_Mandatory;
 await_mandatory_or_optional(node);
}

void GTagML_Markup_Position::tag_command_entry(caon_ptr<GTagML_Node> node)
{
 CAON_PTR_DEBUG(tNode ,current_node_)
 CAON_PTR_DEBUG(tNode ,node)

 current_attribute_node_ = caon_ptr<tNode>( nullptr );
 switch(position_state_)
 {
 case Tag_Body_Leave:
  {
   if(caon_ptr<GTagML_Tag_Command> ntc = current_node_->GTagML_tag_command())
   {
    CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
    ntc->flags.has_entry = true;
   }
  }

  // fallthrough
 case Root:
 case Tile_Sequence:
   node->wsh()->inherit_whitespace(current_node_->wsh());

  [[clang::fallthrough]];
  // // what about inherit_whitespace for Annotation_Close?
 case Annotation_Close:
  current_node_ << fr_/qry_.Tag_Command_Entry >> node;
  merge_multi_parent_inherited(current_node_, node);
  position_state_ = Tag_Command_Entry;
  break;

 case Tag_Command_Leave:
  current_node_ << fr_/qry_.Tag_Command_Cross >> node;
  merge_multi_parent_sequence(current_node_, node);
  position_state_ = Tag_Command_Entry;
  break;

 case Active_Khif_Connector:
  attach_khif_tag_command_node(node);
  break;

default:
  //  likely syntax error
  break;
 }

 current_node_ = node;
 tag_commands_.push(node);
}


void GTagML_Markup_Position::load_khif_connectors(QString connectors)
{
 current_connectors_ = connectors;

 QStringList cs = connectors.split(QRegularExpression("\\s+"));
 for(QString c : cs)
 {
  Khif_Connectors kc = parse_khif_connector(c);
  if(kc != Khif_Connectors::Khif_N_A)
  {
   current_khif_connector_ = kc;
  }
 }

 position_state_ = Position_States::Active_Khif_Connector;

}

void GTagML_Markup_Position::attach_khif_tag_command_node(caon_ptr<GTagML_Node> node)
{
 CAON_PTR_DEBUG(GTagML_Node ,node)
 switch(current_khif_connector_)
 {
 case Khif_Connectors::Khif_N_A:
  break;

 case Khif_Connectors::Khif_Entry:
  current_node_ << fr_/qry_.Tag_Command_Entry >> node;
  break;

 case Khif_Connectors::Khif_Cross:
  current_node_ << fr_/qry_.Tag_Command_Cross >> node;
  break;

 case Khif_Connectors::Khif_Continue:
  current_node_ << fr_/qry_.Tag_Command_Continue >> node;
  break;

 case Khif_Connectors::Khif_Attribute:
  //? error...
  break;

 case Khif_Connectors::Khif_Main_Tile:
  //? error...
  break;

 default:
  //? error...
  break;
 }

}

void GTagML_Markup_Position::add_khif_tile_node(caon_ptr<tNode> node)
{
 CAON_PTR_DEBUG(tNode ,node)
 CAON_PTR_DEBUG(tNode ,current_node_)
 switch(current_khif_connector_)
 {
 case Khif_Connectors::Khif_N_A:
  break;

 case Khif_Connectors::Khif_Entry:
   if(caon_ptr<GTagML_Tag_Command> ntc = node->GTagML_tag_command())
   {
    ntc->flags.has_entry = true;
   }
  current_attribute_node_ = caon_ptr<tNode>( nullptr );
  current_node_ << fr_/qry_.Tile_Sequence >> node;
  break;

 case Khif_Connectors::Khif_Cross:
  current_attribute_node_ = caon_ptr<tNode>( nullptr );
  current_node_ << fr_/qry_.Tag_Command_Cross >> node;
  break;

 case Khif_Connectors::Khif_Continue:
  current_attribute_node_ = caon_ptr<tNode>( nullptr );
  current_node_ << fr_/qry_.Tag_Command_Continue >> node;
  break;

 case Khif_Connectors::Khif_Attribute:
  if(current_attribute_node_)
  {
   current_attribute_node_ << fr_/qry_.Tile_Sequence >> node;
  }
  else
  {
   if(caon_ptr<GTagML_Tag_Command> ntc = current_node_->GTagML_tag_command())
   {
    ntc->flags.has_attribute_tile = true;
   }
   current_node_ << fr_/qry_.Tag_Command_Attribute_Tile >> node;
  }
  current_attribute_node_ = node;
  break;

 case Khif_Connectors::Khif_Space:
 case Khif_Connectors::Khif_Main_Tile:
  {
   current_attribute_node_ = caon_ptr<tNode>( nullptr );
   if(caon_ptr<GTagML_Tag_Command> ntc = current_node_->GTagML_tag_command())
   {
    ntc->flags.has_main_tile = true;
   }
   current_node_ << fr_/qry_.Tag_Command_Main_Tile >> node;
   current_node_ = node;
  }
  //? error...
  break;

 default:
  //? error...
  break;
 }
}

void GTagML_Markup_Position::khif_tag_command_leave()
{
 current_attribute_node_ = caon_ptr<tNode>( nullptr );
 if(tag_commands_.isEmpty())
 {
  if(caon_ptr<GTagML_Tag_Command> ntc = current_node_->GTagML_tag_command())
  {
   CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
   qDebug() << "Too far closing: " <<  ntc->name();
  }
  return;
  //throw(nullptr);
 }
 current_node_ = tag_commands_.pop();
 position_state_ = Khif_Tag_Command_Leave;
 if(caon_ptr<GTagML_Tag_Command> ntc = current_node_->GTagML_tag_command())
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
  ntc->flags.is_closed = true;
 }

}

void GTagML_Markup_Position::tag_body_leave()
{
 position_state_ = Tag_Body_Leave;
 current_node_ = tag_commands_.top();
}


void GTagML_Markup_Position::attribute_sequence_leave()
{
 position_state_ = Tag_Body_Leave;
}


caon_ptr<GTagML_Markup_Position::tNode> GTagML_Markup_Position::check_tag_command_leave(QString tag_command)
{
 if(tag_commands_.isEmpty())
   return caon_ptr<tNode>( nullptr );
 current_attribute_node_ = caon_ptr<tNode>( nullptr );
 caon_ptr<tNode> result = tag_commands_.top();
 CAON_PTR_DEBUG(GTagML_Node ,result)
 if(caon_ptr<GTagML_Tag_Command> ntc = result->GTagML_tag_command())
 {
  if(ntc->name() == tag_command)
  {
   return result;
  }
 }
 return caon_ptr<tNode>( nullptr );
}

void GTagML_Markup_Position::rewind_tag_command_leave(QString tag_command)
{
 if(tag_commands_.isEmpty())
   return;
 current_attribute_node_ = caon_ptr<tNode>( nullptr );
 caon_ptr<tNode> result = tag_commands_.pop();
 CAON_PTR_DEBUG(GTagML_Node ,result)
 if(caon_ptr<GTagML_Tag_Command> ntc = result->GTagML_tag_command())
 {
  if(ntc->name() == tag_command)
  {
   position_state_ = Tag_Command_Leave;
   current_node_ = result;
   ntc->flags.is_closed = true;
  }
  else
  {
   //?ntc->flags.is_closed = true;
   rewind_tag_command_leave(tag_command);
  }
 }
}

caon_ptr<GTagML_Markup_Position::tNode> GTagML_Markup_Position::tag_command_leave()
{
 if(tag_commands_.isEmpty())
   return caon_ptr<tNode>( nullptr );
 current_attribute_node_ = caon_ptr<tNode>( nullptr );
 caon_ptr<tNode> result = tag_commands_.top();
 CAON_PTR_DEBUG(GTagML_Node ,result)
 if(caon_ptr<GTagML_Tag_Command> ntc = result->GTagML_tag_command())
 {
  //confirm_tag_command_leave(result);
  return result;
 }
 return caon_ptr<tNode>( nullptr );
}


void GTagML_Markup_Position::confirm_tag_command_leave(caon_ptr<tNode> node)
{
 CAON_PTR_DEBUG(tNode ,node)
 tag_commands_.pop();
 position_state_ = Tag_Command_Leave;
 current_node_ = node;
  // //  check if current parent command is multi

#ifdef HIDE
 if(caon_ptr<GTagML_Tag_Command> ntc = node->GTagML_tag_command())
 {
  ntc->flags.is_closed = true;
  parse_context_.flags.inside_multi_parent = 
    (ntc->flags.is_multi_mandatory || ntc->flags.is_multi_optional);
 }
#endif HIDE
#ifdef HIDE
 if(tag_commands_.isEmpty())
   parse_context_.flags.inside_multi_parent = false;
 else
 {
  caon_ptr<tNode> tnode = tag_commands_.top();
  if(caon_ptr<GTagML_Tag_Command> tntc = tnode->GTagML_tag_command())
  {
   parse_context_.flags.inside_multi_parent = tntc->flags.is_multi_parent;
  }
 }
#endif HIDE
}

caon_ptr<GTagML_Tag_Command> GTagML_Markup_Position::get_current_tag_command()
{
 if(tag_commands_.isEmpty())
   return nullptr;

 return tag_commands_.top()->GTagML_tag_command();
}


caon_ptr<GTagML_Tag_Command> GTagML_Markup_Position::check_flag_right_whitespace()
{
 CAON_PTR_DEBUG(GTagML_Node ,current_node_)
 if(caon_ptr<GTagML_Tag_Command> ntc = current_node_->GTagML_tag_command())
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
  ntc->flags.has_boundary_white_whitespace = true;
  return ntc;
 }
 return nullptr;
}


void GTagML_Markup_Position::restore_current_node(caon_ptr<tNode> node)
{
 position_state_ = held_position_state_;
 held_position_state_ = Held_Empty;
 current_node_ = node;
}

void GTagML_Markup_Position::add_attribute_tile_node(caon_ptr<GTagML_Node> node)
{
 CAON_PTR_DEBUG(GTagML_Node ,node)
 CAON_PTR_DEBUG(GTagML_Node ,current_node_)
 CAON_PTR_DEBUG(GTagML_Node ,current_attribute_node_)

 switch(position_state_)
 {
 case Tag_Command_Entry:
 case Tag_Body_Leave:
  {
   if(caon_ptr<GTagML_Tag_Command> ntc = current_node_->GTagML_tag_command())
   {
    ntc->flags.has_attribute_tile = true;
   }
   current_node_ << fr_/qry_.Tag_Command_Attribute_Tile >> node;
  }
  break;
 case Tile_Sequence:
  current_attribute_node_ << fr_/qry_.Tile_Sequence >> node;
  break;
 }
 current_attribute_node_ = node;
 position_state_ = Tile_Sequence;
}




caon_ptr<GTagML_Markup_Position::tNode> GTagML_Markup_Position::tag_command_instruction(caon_ptr<tNode> node)
{
 held_position_state_ = position_state_;
 caon_ptr<tNode> result = current_node_;
 current_node_ << fr_/qry_.Tag_Command_Instruction >> node;
 current_node_ = node;
 tag_commands_.push(node);
 return result;
}


void GTagML_Markup_Position::add_tile_node(caon_ptr<GTagML_Node> node)
{
 CAON_PTR_DEBUG(GTagML_Node ,node)
 CAON_PTR_DEBUG(GTagML_Node ,current_node_)

 switch(position_state_)
 {
 case Root:
  current_node_ << fr_/qry_.Tile_Sequence >> node;
  break;
 case Tag_Command_Entry:
  {
   if(caon_ptr<GTagML_Tag_Command> ntc = current_node_->GTagML_tag_command())
   {
    ntc->flags.has_entry = true;
   }
   current_node_ << fr_/qry_.Tag_Command_Entry >> node;
  }
  break;
 case Tag_Body_Leave:
  {
   if(caon_ptr<GTagML_Tag_Command> ntc = current_node_->GTagML_tag_command())
   {
    ntc->flags.has_main_tile = true;
   }
  }
  current_node_ << fr_/qry_.Tag_Command_Main_Tile >> node;
  break;
 case Tag_Command_Leave:
  current_node_ << fr_/qry_.Tag_Command_Continue >> node;
  break;
 case Tile_Sequence:
  current_node_ << fr_/qry_.Tile_Sequence >> node;
  break;

 case Annotation_Close:
  current_node_ << fr_/qry_.Tile_Sequence >> node;
  break;
 }
 current_node_ = node;
 position_state_ = Tile_Sequence;
}

void GTagML_Markup_Position::add_raw_tile_node(caon_ptr<GTagML_Node> node)
{
 add_tile_node(node);
// CAON_PTR_DEBUG(GTagML_Node ,node)
// CAON_PTR_DEBUG(GTagML_Node ,current_node_)

// switch(position_state_)
// {
// case Tag_Command_Entry:
// case Tag_Body_Leave:
//   current_node_ << fr_/qry_.Tag_Command_Raw_Tile >> node;
//  }
//  break;
// case Tag_Command_Leave:
//  current_attribute_node_ << fr_/qry_.Tile_Sequence >> node;
//  break;
// }
//? current_attribute_node_ = node;
//? position_state_ = Tile_Sequence;
}
