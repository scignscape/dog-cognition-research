
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-graph-build.h"

#include "tile/gtagml-tile.h"
#include "kernel/graph/gtagml-graph.h"
#include "tag-command/gtagml-tag-command.h"
#include "whitespace/gtagml-whitespace.h"
#include "kernel/gtagml-root.h"
#include "tile/gtagml-attribute-tile.h"
#include "tile/gtagml-paralex-tile.h"
#include "tile/gtagml-raw-tile.h"

#include "annotation/gtagml-annotation-tile.h"

#include "kernel/document/gtagml-document-info.h"
//#include "kernel/document/gtagml-document-light-xml.h"

#include "kans.h"

#include <QDebug>


USING_KANS(GTagML)

GTagML_Graph_Build::GTagML_Graph_Build(GTagML_Graph& g, GTagML_Document_Info& document_info)
 : Flags(0), markup_position_(g.root_node()), acc_mode_(Acc_Mode::Main_Tile), document_info_(document_info),
   current_parsing_mode_(GTagML_Parsing_Modes::GTagML), //?current_annotation_tile_(nullptr),
   tile_acc_length_adjustment_(0),
   tile_acc_qts_(&tile_acc_), string_literal_acc_qts_(&string_literal_acc_),
   current_raw_format_("latex"), held_semantic_mark_mode_(0)
{

}


void GTagML_Graph_Build::init()
{

}


void GTagML_Graph_Build::enter_multiline_comment(QString semis, QString tildes)
{
 markup_position_.enter_multiline_comment(cutmax(semis.length()), cutmax(tildes.length()));
 parse_context_.flags.inside_multiline_comment = true;
}

void GTagML_Graph_Build::check_leave_multiline_comment(QString semis, QString tildes)
{
 if(markup_position_.check_leave_multiline_comment(cutmax(tildes.length()),
  cutmax(tildes.length())));
 parse_context_.flags.inside_multiline_comment = false;
}

void GTagML_Graph_Build::tile_acc(QString str)
{
 tile_acc_qts_ << str;
}

//void GTagML_Graph_Build::spm_acc(QString str)
//{
// spm_acc_qts_ << str;
//}


void GTagML_Graph_Build::tag_command_annotation(QString annotation)
{
 //?
 // current_annotation_tile_ = new GTagML_Annotation_Tile("");
 // current_annotation_tile_->set_connector(annotation);
 // caon_ptr<tNode> node = make_new_node(current_annotation_tile_);
 // markup_position_.tag_command_annotation(node);
}

void GTagML_Graph_Build::annotation_entry(QString flag, QString text, QString rel, QString tile, QString follow)
{
 check_tile_acc();

 QString annotation_text = text;
 if(flag == "*")
 {
  annotation_text.prepend("*:");
 }

 caon_ptr<GTagML_Tile> ntile = new GTagML_Tile(annotation_text);
 caon_ptr<GTagML_Annotation_Tile> atile = new GTagML_Annotation_Tile;
 //atile->set_subject(text);
 caon_ptr<tNode> node = make_new_node(ntile);
 caon_ptr<tNode> anode = make_new_node(atile);
 CAON_PTR_DEBUG(tNode ,node)
 if(rel.isEmpty())
 {
  markup_position_.annotation_entry(node, anode);
  flags.active_annotation_entry = true;
  if(!tile.isEmpty())
  {
   atile->set_tile(tile);
  }
  if(follow == ";")
  {
   markup_position_.close_annotation();
   flags.active_annotation_entry = false;
  }
  else
   flags.active_annotation_tile = true;
 }
 else
 {
  atile->set_connector(rel);
  //?current_annotation_tile_->set_connector(rel);
  markup_position_.annotation_entry(node, anode);
  if(!tile.isEmpty())
  {
   atile->set_tile(tile);
   //?current_annotation_tile_->set_tile(tile);
  }
  if(follow == ";")
  {
   markup_position_.close_annotation();
   flags.active_annotation_entry = false;
  }
  else
   flags.active_annotation_tile = true;
 }
}

void GTagML_Graph_Build::check_tile_acc(Acc_Mode new_mode)
{
 if(tile_acc_.isEmpty())
 {
  acc_mode_ = new_mode;
  return;
 }

 QString trim = tile_acc_.trimmed();

 if(trim.isEmpty())
 {
  attach_whitespace(tile_acc_);
  tile_acc_qts_.reset();
  tile_acc_.clear();
  acc_mode_ = new_mode;
  return;
 }

 caon_ptr<tNode> ws_defer_node = nullptr;

 if(trim == "%-%" || trim == "---")
   trim.clear();

 else if(trim.endsWith("-."))
 {
  trim.chop(2);
  trim = trim.trimmed();
  ws_defer_node = markup_position_.current_tag_command_node();

 }

 caon_ptr<GTagML_Tile> new_tile = nullptr;

 switch(acc_mode_)
 {
 case Acc_Mode::Main_Tile:
  attach_left_whitespace();
  check_add_words();
  if(new_mode == Acc_Mode::Raw)
  {
   new_tile = add_tile(trim + "\n");
  }
  else
  {
   new_tile = add_tile(trim);
   attach_right_whitespace();
  }
  tile_acc_length_adjustment_ = 0;
  tile_acc_qts_.reset();
  tile_acc_.clear();

  break;

 case Acc_Mode::Arg_Tile:
  attach_left_whitespace();
  new_tile = add_tile(trim);
  attach_right_whitespace();
  tile_acc_length_adjustment_ = 0;
  tile_acc_qts_.reset();
  tile_acc_.clear();
  break;

 case Acc_Mode::Attribute:
  add_attribute_tile(tile_acc_);
  tile_acc_length_adjustment_ = 0;
  tile_acc_qts_.reset();
  tile_acc_.clear();
  break;

 case Acc_Mode::Raw:
  add_raw_tile(tile_acc_);
  tile_acc_length_adjustment_ = 0;
  tile_acc_qts_.reset();
  tile_acc_.clear();
  break;


 default: break;
 }

 if(new_tile)
   new_tile->set_whitespace_defer(ws_defer_node.raw_pointer());

 acc_mode_ = new_mode;
}

void GTagML_Graph_Build::check_add_words()
{
 QStringList strings = tile_acc_.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);
 for(QString s : strings)
 {
  QRegularExpression rx_start("\\A\\$(\\w+)\\$");
  QRegularExpressionMatch rxm_start = rx_start.match(s);

  QRegularExpression rx_end("\\$(\\w+)\\$\\W*\\Z");
  QRegularExpressionMatch rxm_end = rx_end.match(s);

  if(rxm_start.hasMatch())
  {
   QString key = rxm_start.captured(1);
   s = s.mid(rxm_start.capturedEnd());
   if(key == "LDQ")
   {
    quote_acc_ += s + " ";
   }
  }
  else if(rxm_end.hasMatch())
  {
   QString key = rxm_end.captured(1);
   s = s.mid(0, rxm_end.capturedStart());
   if(key == "RDQ")
   {
    quote_acc_ += s;
    document_info_.add_quote(quote_acc_);
    quote_acc_.clear();
   }
  }
  else if(!quote_acc_.isEmpty())
  {
   quote_acc_ += s + " ";
  }


  if(s.contains('@'))
   continue;
  if(s.contains("//"))
   continue;
  if(s.count('.') > 1)
   continue;
  if(s.contains('/') && s.contains('.'))
   continue;

  if(s.contains(QRegularExpression("\\d")))
   continue;

  s.replace("&apos;", "");
  s.replace(QRegularExpression("&\\w+;"), "");
  s.replace(QRegularExpression("[^\\w']"), "");
  if(!s.isEmpty())
  {
   document_info_.add_word(s);
  }
 }
}


void GTagML_Graph_Build::mark_attribute_tile()
{
 check_tile_acc(Acc_Mode::Attribute);
}



void GTagML_Graph_Build::attach_left_whitespace()
{
 if(get_light_xml())
 {
  return;
 }
 int index = tile_acc_.indexOf(QRegularExpression("\\S"));

 if(index > 0)
 {
  // // is this hackneyed?
  if(index < 2)
    markup_position_.check_flag_right_whitespace();

  attach_whitespace(tile_acc_.left(index));
 }
}

void GTagML_Graph_Build::attach_right_whitespace()
{
 if(get_light_xml())
 {
  return;
 }

 int index = tile_acc_.lastIndexOf(QRegularExpression("\\S\\s+\\Z"));
 if(index != -1)
 {
  attach_whitespace(tile_acc_.mid(index + 1));
 }
}


void GTagML_Graph_Build::attach_whitespace(QString whitespace)
{
 if(get_light_xml())
 {
  return;
 }
#ifndef NO_CAON
 if(caon_ptr<tNode> node = markup_position_.current_node())
 {
  CAON_PTR_DEBUG(tNode ,node)
  caon_ptr<GTagML_Whitespace_Holder> nwh = node->as<GTagML_Whitespace_Holder>();
  nwh->attach_whitespace(whitespace);
 }
#endif //NO_CAON
}

#ifdef HIDE
void GTagML_Graph_Build::end_khif_tile(QString connector_prefix, QString connectors)
{
 end_khif_tile();

 bool string_follow = (connector_prefix.startsWith('+'));
 bool subject_claim = (connector_prefix.endsWith('['));
 markup_position_.load_khif_connectors(connectors);

 parse_context_.flags.inside_khif_tile = true;

}

void GTagML_Graph_Build::attach_khif_tile()
{
 if(!khif_tile_.isEmpty())
 {
  QString kt = khif_tile_.trimmed();
  if(!kt.isEmpty())
  {
   if(markup_position_.expecting_khif_attribute_tile())
   {
    QRegularExpression rx("(\\S+)\\s*(\\S*)");
    QRegularExpressionMatch match = rx.match(kt);
    QString attribute = match.captured(1);
    QString value = match.captured(2);
    caon_ptr<GTagML_Attribute_Tile> tile = make_new_attribute_tile(attribute, value);
    khif_tile_.clear();
    CAON_PTR_DEBUG(GTagML_Attribute_Tile ,tile)
    caon_ptr<tNode> node = make_new_node(tile);
    markup_position_.add_khif_tile_node(node);
   }
   else
   {
    caon_ptr<GTagML_Tile> tile = make_new_tile(kt);
    CAON_PTR_DEBUG(GTagML_Tile ,tile)
    khif_tile_.clear();
    caon_ptr<tNode> node = make_new_node(tile);
    markup_position_.add_khif_tile_node(node);
   }
  }
 }
}

void GTagML_Graph_Build::end_khif_tile()
{
 //? parse_context.flags.inside_khif_tile = false;
 attach_khif_tile();
 markup_position_.khif_tag_command_leave();
}
#endif //def HIDE


void GTagML_Graph_Build::enter_tag_command_with_predicate_vector(QString tag_command,
 QString connector_prefix, QString connectors)
{
 bool string_follow = (connector_prefix.startsWith('+'));
 bool subject_claim = (connector_prefix.endsWith('['));

 caon_ptr<GTagML_Tag_Command> gtc = make_new_tag_command(tag_command, {});
 caon_ptr<tNode> node = make_new_node(gtc);

 markup_position_.tag_command_entry(node);

 markup_position_.load_khif_connectors(connectors);

 parse_context_.flags.inside_khif_tile = true;

}


//void GTagML_Graph_Build::khif_tile_acc(QString m)
//{
// khif_tile_ += m;
//}

void GTagML_Graph_Build::attach_predicate_vector(QString connector_prefix, QString connectors)
{
// attach_khif_tile();
 bool string_follow = (connector_prefix.startsWith('+'));
 bool subject_claim = (connector_prefix.endsWith('['));
 markup_position_.load_khif_connectors(connectors);
}


caon_ptr<GTagML_Tag_Command> GTagML_Graph_Build::html_tag_instruction(QString prefix,
 QString tag_command, QString argument)
{
 check_tile_acc();

 caon_ptr<GTagML_Tag_Command> gtc = make_new_tag_command(tag_command, {});
 if(prefix == "!")
  gtc->flags.is_tag_assertion = true;
 else if(prefix == "?")
  gtc->flags.is_tag_query = true;

 gtc->flags.is_html = true;
 gtc->flags.is_understood_auto_closed = true;

 caon_ptr<tNode> node = make_new_node(gtc);

 caon_ptr<tNode> current_node = markup_position_.tag_command_instruction(node);
 tag_body_leave();
 tile_acc(argument);
 check_tile_acc();
 markup_position_.restore_current_node(current_node);

 return gtc;

}



caon_ptr<GTagML_Tag_Command> GTagML_Graph_Build::html_tag_command_entry(QString prefix, QString tag_command)
{
 check_tile_acc();

 if(get_light_xml())
 {
  // get_light_xml()->tag_entry(tag_command);
  parse_context_.flags.inside_html_tag_body = true;
  return nullptr;
 }

 caon_ptr<GTagML_Tag_Command> gtc = make_new_tag_command(tag_command, {});
 caon_ptr<tNode> node = make_new_node(gtc);

 markup_position_.tag_command_entry(node);
 parse_context_.flags.inside_html_tag_body = true;
 gtc->flags.is_html = true;

 return gtc;

}

void GTagML_Graph_Build::check_non_or_left_wrapped(QString wmi, caon_ptr<GTagML_Tag_Command> gtc)
{
 if(wmi.startsWith(':'))
 {
  if(wmi.startsWith("::"))
    gtc->flags.is_non_wrapped = true;
  else
    gtc->flags.is_left_wrapped = true;
 }
 if(wmi.endsWith('.'))
 {
  gtc->flags.has_non_wrapped_space = true;
 } 
}

caon_ptr<GTagML_Tag_Command> GTagML_Graph_Build::tag_command_entry(QString wmi, 
  QString prefix, QString tag_command, QString argument, QString parent_tag_type)
{
 if(held_semantic_mark_mode_)
 {
  document_info_.marks()[held_semantic_mark_mode_].last() += tag_command;
  held_semantic_mark_mode_ = 0;
 }

 check_tile_acc();
 caon_ptr<GTagML_Tag_Command> gtc = make_new_tag_command(tag_command,
   argument, parent_tag_type);

 check_non_or_left_wrapped(wmi, gtc);

//?
// if(prefix == "/")
//   gtc->flags.is_environment = true;

 caon_ptr<tNode> node = make_new_node(gtc);

 RELAE_SET_NODE_LABEL(node, tag_command);
 markup_position_.tag_command_entry(node);
 parse_context_.flags.inside_tag_body = true;

 return gtc;
}


void GTagML_Graph_Build::html_tag_command_attribute_entry(QString pre_space,
 QString attribute, QString s_or_d)
{
 current_html_attribute_ = attribute;
//? if(s_or_d == "'")
//?  parse_context_.flags.inside_html_tag_attribute_single_quote = true;
//? else if(s_or_d == "\"")
//?  parse_context_.flags.inside_html_tag_attribute_double_quote = true;
}

void GTagML_Graph_Build::html_tag_command_attribute_acc(QString str)
{
 tile_acc_ += str;
}

caon_ptr<GTagML_Attribute_Tile> GTagML_Graph_Build::complete_html_tag_command_attribute()
{
 if(get_light_xml())
 {
  // get_light_xml()->add_attribute_tile(current_html_attribute_, tile_acc_);
  tile_acc_.clear();
  current_html_attribute_.clear();
  document_info_.check_light_xml_href();
 }


 caon_ptr<GTagML_Attribute_Tile> tile =  make_new_attribute_tile(current_html_attribute_, tile_acc_);

 CAON_PTR_DEBUG(GTagML_Attribute_Tile ,tile)
 if(tile->key() == "href")
 {
  QString tag = markup_position_.current_tag_command_name();
  document_info_.add_href(tag, tile->value());
 }
 caon_ptr<tNode> node = make_new_node(tile);
 markup_position_.add_attribute_tile_node(node);

 current_html_attribute_ = QString();
 tile_acc_ = QString();

//? parse_context_.flags.inside_html_tag_attribute_double_quote = false;
//? parse_context_.flags.inside_html_tag_attribute_single_quote = false;
 parse_context_.flags.inside_html_tag_body = true;

 return tile;

}

GTagML_Document_Light_Xml* GTagML_Graph_Build::get_light_xml()
{
 return nullptr;
 //return document_info_.light_xml();
}

void GTagML_Graph_Build::multi_arg_transition_to_main_tile()
{
 multi_arg_transition({}, {}, {}, "-->", "=>");
  // // need to mark as main tile somehow ...
}

void GTagML_Graph_Build::multi_arg_transition(QString wmi, QString inner_wmi,
  QString fiat, QString arg_marker, QString carried_arg_marker)
{
 if(flags.active_attribute_sequence)
 {
  flags.active_attribute_sequence = false;
  if(caon_ptr<tNode> cn = markup_position_.current_node())
  {
   if(caon_ptr<GTagML_Tag_Command> gtc = cn->GTagML_tag_command())
   {
    CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)
    check_tile_acc();
    markup_position_.attribute_sequence_leave();
    gtc->flags.is_multi_parent = true;

    //if(gtc->flags.is_provisional_multi_parent_semis)
    //?gtc->flags.is_multi_parent_semis = true;
    if(gtc->flags.anticipate_semis)
      parse_context_.flags.inside_multi_parent_semis = true;
    else
      parse_context_.flags.inside_multi_parent = true;
    tag_command_entry_inside_multi(wmi, {}, fiat, gtc->name(),
      arg_marker);
    return;
   }
  }
 }
 tag_command_leave();
 QString tag_command = markup_position_.current_tag_command_name();
 tag_command_entry_inside_multi(wmi, inner_wmi, fiat, tag_command,
   arg_marker, &carried_arg_marker);
}

void GTagML_Graph_Build::tag_command_entry_with_layer(QString tag_command, QString layer_marker)
{
 caon_ptr<GTagML_Tag_Command> gtc = tag_command_entry({}, {}, tag_command, {});
   //make_new_tag_command(tag_command, {});

 if(layer_marker == "->>")
 {
  gtc->flags.is_layer_optional = true;
 }
 else if(layer_marker == "-->")
 {
  gtc->flags.is_layer_mandatory = true;
 }
 else if(layer_marker == "->")
 {
  gtc->flags.is_layer_main_mandatory = true;
 }
 else if(layer_marker == "-->>")
 {
  gtc->flags.is_layer_main_optional = true;
 }

 tag_body_leave();
}

void GTagML_Graph_Build::tag_command_entry_inside_multi(QString wmi,
  QString inner_wmi,
  QString fiat,
  QString tag_command, QString arg_marker, 
  QString* carried_arg_marker, QString argument, QString name)
{
 QString nn = name;
 if(nn.isEmpty())
   // //  this "name" will never appear but it's a placeholder 
    //    for debugging ...
   nn = QString("%1 %2").arg(tag_command).arg(arg_marker);

 caon_ptr<GTagML_Tag_Command> gtc = make_new_tag_command(nn, argument);
 if(name.isEmpty())
   gtc->flags.autogen_multi_name = true;

 if(carried_arg_marker && (*carried_arg_marker == "=>"))
   gtc->flags.marked_main = true;

 check_non_or_left_wrapped(wmi, gtc);

 if(fiat == '=')
 {
  gtc->flags.is_fiat = true;
  if(!gtc->flags.is_left_wrapped)
    gtc->flags.is_non_wrapped = true;
 }

 if(inner_wmi == ".")
   gtc->flags.tile_is_quasi_fiat = true;

 caon_ptr<tNode> node = make_new_node(gtc);

 if(arg_marker == "->>")
 {
  gtc->flags.is_multi_optional = true;
  gtc->flags.multi_arg_layer = true;
  markup_position_.await_optional(node);
  acc_mode_ = Acc_Mode::Arg_Tile;
 }
 else if(arg_marker == "-->")
 {
  gtc->flags.is_multi_mandatory = true;
  gtc->flags.multi_main_layer = true;
  markup_position_.await_mandatory(node);
  acc_mode_ = Acc_Mode::Main_Tile;
 }
 else if(arg_marker == "->")
 {
  gtc->flags.is_multi_mandatory = true;
  gtc->flags.multi_arg_layer = true;
  markup_position_.await_mandatory(node);
  acc_mode_ = Acc_Mode::Arg_Tile;
 }
 else if(arg_marker == "-->>")
 {
  gtc->flags.is_multi_optional = true;
  gtc->flags.multi_main_layer = true;
  markup_position_.await_optional(node);
  acc_mode_ = Acc_Mode::Main_Tile;
 }
}

void GTagML_Graph_Build::tag_command_entry_multi(QString wmi,
  QString inner_wmi, QString tag_command,
  QString tag_body_follow, QString fiat, QString first_arg_wmi, QString first_arg_marker)
{
 Tag_Body_Follow_Mode m = tag_body_follow.isEmpty() ? Normal
   : parse_tag_body_follow(tag_body_follow);

 caon_ptr<GTagML_Tag_Command> gtc = tag_command_entry(wmi, {},
   tag_command, {});

 if(m == Region)
   gtc->flags.is_region = true;

 gtc->flags.has_entry = true;


 tag_body_leave();

 if(tag_body_follow.isEmpty())
   gtc->flags.anticipate_semis = true;

 if(first_arg_marker == "@")
 {
  gtc->flags.is_provisional_multi_parent = true;
  markup_position_.prepare_attribute_sequence();
  parse_context_.flags.inside_attribute_sequence = true;
  parse_context_.flags.inside_multi_generic = true;
  flags.active_attribute_sequence = true;
  acc_mode_ = Acc_Mode::Attribute;
 }
 else
 {
  gtc->flags.is_multi_parent = true;
  tag_command_entry_inside_multi(first_arg_wmi, inner_wmi, fiat, tag_command, first_arg_marker);

  parse_context_.flags.inside_multi_generic = true;
  if(tag_body_follow.isEmpty())
    parse_context_.flags.inside_multi_parent_semis = true;
  else
    parse_context_.flags.inside_multi_parent = true;
 }
}

void GTagML_Graph_Build::tag_command_entry_inline(QString wmi,
  QString inner_wmi, QString fiat, QString tag_command,
  QString tag_body_follow, QString argument)
{
 Tag_Body_Follow_Mode m = parse_tag_body_follow(tag_body_follow);
 QString prefix;

 caon_ptr<GTagML_Tag_Command> gtc = tag_command_entry(wmi, prefix,
   tag_command, argument);

 CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)

 if(fiat == "=")
   gtc->flags.is_fiat = true;

// if(inner_wmi == ".")
//   gtc->flags.tile_is_quasi_fiat = true;


//?
// else if(fiat == "==")
//   gtc->flags.is_fiat_inherited = true;

 switch(m)
 {
 case Normal:
  tag_body_leave();
  break;
 case Region:
  gtc->flags.is_region = true;
  tag_body_leave();
  break;
 case Empty:
  gtc->flags.is_self_closed = true;
  tag_body_leave();
  tag_command_leave(); break;
 }
}

void GTagML_Graph_Build::gtag_command_entry_inline(QString tag_command,
 QString tag_body_follow)
{
 Tag_Body_Follow_Mode m = parse_tag_body_follow(tag_body_follow);
 QString prefix;

 caon_ptr<GTagML_Tag_Command> gtc = tag_command_entry({}, prefix,
   tag_command, {});

 switch(m)
 {
 case Normal:
  tag_body_leave();
  break;
 case Region:
  gtc->flags.is_region = true;
  tag_body_leave();
  break;
 case Empty:
  gtc->flags.is_self_closed = true;
  tag_body_leave();
  tag_command_leave(); break;
 }
}


caon_ptr<GTagML_Tag_Command> GTagML_Graph_Build::make_new_tag_command(QString name, QString argument, QString parent_tag_type)
{
 GTagML_Tag_Command* result;

 QString opt;
 if(argument.startsWith('%'))
   argument = argument.mid(1);
 else
 {
  argument = argument.trimmed();
  if(argument.startsWith('['))
  {
   int be = argument.indexOf(']');
   opt = argument.mid(1, be - 1).trimmed();
   argument = argument.mid(be + 1).trimmed();
  }
  else if(argument.startsWith('('))
  {
   int be = argument.indexOf(')');
   opt = argument.mid(1, be - 1).trimmed();
   opt.prepend('(');
   opt.append(')');
   argument = argument.mid(be + 1).trimmed();
  }
 }

 if(name.startsWith('='))
 {
  result = new GTagML_Tag_Command(name.mid(1), argument, parent_tag_type);
  result->flags.is_fiat = true;
  result->flags.is_non_wrapped = true;
 }
 else
   result = new GTagML_Tag_Command(name, argument, parent_tag_type);

 if(!opt.isEmpty())
   result->set_opt_argument(opt);
   
 return result;
}


caon_ptr<GTagML_Tile> GTagML_Graph_Build::add_tile(QString tile_str)
{
 if(get_light_xml())
 {
  // get_light_xml()->add_tile(tile_str);
  return nullptr;
 }

 caon_ptr<GTagML_Tile> tile = make_new_tile(tile_str);
 tile->set_length_adjustment(tile_acc_length_adjustment_);
 caon_ptr<tNode> node = make_new_node(tile);
 //?
 markup_position_.add_tile_node(node);
 return tile;
}

caon_ptr<GTagML_Raw_Tile> GTagML_Graph_Build::add_raw_tile(QString tile_str)
{
  // // current latex is the only raw format ...
 caon_ptr<GTagML_Raw_Tile> tile = make_new_raw_tile(current_raw_format_, tile_str);
 CAON_PTR_DEBUG(GTagML_Raw_Tile ,tile)
 caon_ptr<tNode> node = make_new_node(tile);
 markup_position_.add_raw_tile_node(node);
 return tile;
}

caon_ptr<GTagML_Attribute_Tile> GTagML_Graph_Build::add_attribute_tile(QString tile_str)
{
 if(get_light_xml())
 {
  // get_light_xml()->add_attribute_tile(tile_str);
  return nullptr;
 }

 caon_ptr<GTagML_Attribute_Tile> tile = make_new_attribute_tile(tile_str);
 CAON_PTR_DEBUG(GTagML_Attribute_Tile ,tile)
 caon_ptr<tNode> node = make_new_node(tile);
 markup_position_.add_attribute_tile_node(node);
 return tile;
}


void GTagML_Graph_Build::add_string_literal_tile(QString str)
{
 //? caon_ptr<GTagML_Tile> tile = add_tile(str);
 //? tile->flags.is_string_literal = true;
}

void GTagML_Graph_Build::tag_command_leave(QString connector_to_load, QString tag_command)
{

}

void GTagML_Graph_Build::block_gtag_command_leave()
{
 if(caon_ptr<tNode> node = markup_position_.tag_command_leave())
 {
  CAON_PTR_DEBUG(tNode ,node)
  check_tile_acc();
  markup_position_.confirm_tag_command_leave(node);
  check_multi_parent_reset();
 }
}

void GTagML_Graph_Build::inline_tag_command_leave()
{
 if(caon_ptr<tNode> node = markup_position_.tag_command_leave())
 {
  CAON_PTR_DEBUG(tNode ,node)
  check_tile_acc();
  markup_position_.confirm_tag_command_leave(node);
  check_multi_parent_reset();
 }
}

void GTagML_Graph_Build::tag_command_leave_multi(QString tag_command)
{
 if(caon_ptr<tNode> node = markup_position_.tag_command_leave())
 {
  CAON_PTR_DEBUG(tNode ,node)
  check_tile_acc();
  markup_position_.confirm_tag_command_leave(node);

  if(caon_ptr<GTagML_Tag_Command> gtc = node->GTagML_tag_command())
  {
   CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)

   if( (gtc->flags.is_multi_optional) || (gtc->flags.is_multi_mandatory) )
   {
     // //  two leaves here because the first is an arg ...
    if(caon_ptr<tNode> node1 = markup_position_.tag_command_leave())
    {
     markup_position_.confirm_tag_command_leave(node1);
//?
//     check_multi_parent_reset();
//     return;
    }
   }
  }
  check_multi_parent_reset();
 }
}

void GTagML_Graph_Build::tag_command_leave()
{
 if(caon_ptr<tNode> node = markup_position_.tag_command_leave())
 {
  CAON_PTR_DEBUG(tNode ,node)
  check_tile_acc();
  markup_position_.confirm_tag_command_leave(node);
  check_multi_parent_reset();
 }
}

void GTagML_Graph_Build::tag_command_instruction_leave(caon_ptr<tNode> node)
{
 check_tile_acc();
 markup_position_.restore_current_node(node);
}

void GTagML_Graph_Build::check_html_tag_command_leave(QString tag_command, QString match_text)
{
 check_tile_acc();

 if(get_light_xml())
 {
  // get_light_xml()->tag_leave(tag_command);
  return;
 }

 markup_position_.rewind_tag_command_leave(tag_command);
}

void GTagML_Graph_Build::check_multi_parent_reset()
{
 if(caon_ptr<GTagML_Tag_Command> gtc = markup_position_.get_current_tag_command())
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)
  if(gtc->flags.is_multi_parent || gtc->flags.is_multi_parent_inherited)
  {
   parse_context_.flags.inside_multi_generic = true;
   if(gtc->flags.anticipate_semis)
     parse_context_.flags.inside_multi_parent_semis = true;
   else
     parse_context_.flags.inside_multi_parent = true;
  }
  else
  {
   parse_context_.flags.inside_multi_generic = false;
   parse_context_.flags.inside_multi_parent = false;
   parse_context_.flags.inside_multi_parent_semis = false;
  }
 }
 else
 {
  parse_context_.flags.inside_multi_generic = false;
  parse_context_.flags.inside_multi_parent = false;
  parse_context_.flags.inside_multi_parent_semis = false;
 }
}

void GTagML_Graph_Build::check_tag_command_leave(QString tag_command, QString match_text)
{
 // //  If the tag command does not match the current node, treat the whole match
  //    as just text to accumulate
 if(caon_ptr<tNode> node = markup_position_.check_tag_command_leave(tag_command))
 {
  CAON_PTR_DEBUG(tNode ,node)
  check_tile_acc();
  markup_position_.confirm_tag_command_leave(node);
  check_multi_parent_reset();
 }
 else
 {
  tile_acc(match_text);
 }
}

//void GTagML_Graph_Build::add_string_literal_tile()
//{
// if(!tile_acc_.isEmpty())
// {
//  // //  This will happen if a string literal is preceeded by a
//  //     string without whitespace; that could be used to create
//  //     special kinds of string literals.
//  //     This could be a spot for a callback which takes the
//  //     tile_acc_ string before clearing it.
//  tile_acc_.clear();
//  tile_acc_qts_.reset();
// }
// add_string_literal_tile(string_literal_acc_);
// string_literal_acc_.clear();
// qts_string_literal_acc_.reset();
//}

caon_ptr<GTagML_Attribute_Tile> GTagML_Graph_Build::make_new_attribute_tile(QString tile)
{
 QRegularExpression rx("(\\S+)\\s+(.+)", QRegularExpression::DotMatchesEverythingOption);
 QRegularExpressionMatch rxm = rx.match(tile);
 if(rxm.hasMatch())
 {
  return caon_ptr<GTagML_Attribute_Tile>(
   new GTagML_Attribute_Tile(rxm.captured(1), rxm.captured(2)) );
 }
}

caon_ptr<GTagML_Attribute_Tile> GTagML_Graph_Build::make_new_attribute_tile(QString key, QString value)
{
 return caon_ptr<GTagML_Attribute_Tile>(
   new GTagML_Attribute_Tile(key, value) );
}

caon_ptr<GTagML_Raw_Tile> GTagML_Graph_Build::make_new_raw_tile(QString format, QString value)
{
 return caon_ptr<GTagML_Raw_Tile>(
   new GTagML_Raw_Tile(format, value) );
}

caon_ptr<GTagML_Tile> GTagML_Graph_Build::make_new_tile(QString tile)
{
 return caon_ptr<GTagML_Tile>( new GTagML_Tile(tile) );
}


caon_ptr<GTagML_Paralex_Tile> GTagML_Graph_Build::make_new_paralex_tile(QString tile,
  u1 kind, u1 w_or_a)
{
 return caon_ptr<GTagML_Paralex_Tile>( new GTagML_Paralex_Tile(tile, 
   (GTagML_Paralex_Tile::Kind) kind, w_or_a) );
}


caon_ptr<GTagML_Graph_Build::tNode> GTagML_Graph_Build::make_new_node(caon_ptr<GTagML_Tile> tile)
{
 CAON_PTR_DEBUG(GTagML_Tile ,tile)
 caon_ptr<tNode> result = caon_ptr<tNode>( new tNode(tile) );
 #ifdef RELAE_LABEL_NODES
 result->set_label(tile->thumbnail());
 #endif
 return result;
}

caon_ptr<GTagML_Graph_Build::tNode> GTagML_Graph_Build::make_new_node(caon_ptr<GTagML_Raw_Tile> tile)
{
 CAON_PTR_DEBUG(GTagML_Raw_Tile ,tile)
 caon_ptr<tNode> result = caon_ptr<tNode>( new tNode(tile) );
 #ifdef RELAE_LABEL_NODES
 result->set_label(tile->thumbnail());
 #endif
 return result;
}

void GTagML_Graph_Build::check_nonstandard_special_character_sequence
  (QString match_text, QString& esc, u1& mode, QString& sup_text)
{
 static QMap<QString, std::pair<QString, u1>> static_map {
  {"%--", {"-", 2}},
  {"%_", {"_", 1}},
  {"%#", {"#", 1}},
  {"->-", {"/", 2}},
  {"%..", {"...", 2}},
  {"%...", {"...", 2}},
 };

 static QMap<QString, QString> supp_map {
  {"%...", "."},
 };

 auto it = static_map.find(match_text);
 if(it != static_map.end())
 {
  std::tie(esc, mode) = it.value();
  sup_text = supp_map.value(match_text);
//  esc = it.value().first;
//  mode = it.value().second;
 }
}

void GTagML_Graph_Build::semantic_mark(QString match_text, QString sem, u1 mode)
{
 QString acc;

 int ix = sem.indexOf("-/");
 if(ix == -1)
 {
  acc = sem;
 }
 else
 {
  acc = sem.mid(0, ix);
  sem = sem.mid(ix + 2);
 }

 if(sem.endsWith("/+"))
 {
  // //  Signals that the following tag-command should be added to the mark ...
  sem.chop(2);
  acc = sem;
  held_semantic_mark_mode_ = mode;
 }

 QString text = QString("%1%2^").arg(mode).arg(acc) + "%9";
 text.prepend("^%");
 tile_acc(text);
 document_info_.marks()[mode].push_back(sem);
}



void GTagML_Graph_Build::special_character_sequence(QString match_text, 
  QString esc, u1 mode)
{
 QString sup_text;
 check_nonstandard_special_character_sequence(match_text, esc, mode, sup_text);

 QString text;
 GTagML_Paralex_Tile::Kind k = GTagML_Paralex_Tile::N_A;
 u1 w = 0;

 switch (mode)
 {
 case 0: text = match_text; 
  break;
 case 1: 
 case 2: 
 case 3: 
 case 4: 
  text = esc;
  w = mode;
  k = GTagML_Paralex_Tile::Alt_Interpretation;
  break;  
 case 5:
  if(match_text == "||")
  {
    // // preserve the escape?
   tile_acc("||");
   ++tile_acc_length_adjustment_;
   return;
  }
  text = esc; 
  k = GTagML_Paralex_Tile::Pipe_Escape;
  if( (text[0] == '>') || (text[0] == '+') )
    w = 2;
  else if(text[0] == '&') 
    w = 3;
  else
    w = 1;
  break;
 }

 int adj = 0;
 // // maybe we just acc everything ...
 switch(k)
 {
 case GTagML_Paralex_Tile::Alt_Interpretation:
  //?tile_acc_length_adjustment_ += (text.size() + 3) - w;
  //?adj = text.size();
  //?adj += 2;
  tile_acc_length_adjustment_ += 3;
  switch (mode)
  {
  case 1:
   tile_acc(QString("`(%1)%2").arg(text).arg(sup_text));
   return;
  case 2:
   tile_acc(QString("`{%1}%2").arg(text).arg(sup_text));
   return;
  case 3:
   tile_acc(QString("`[%1]%2").arg(text).arg(sup_text));
   return;
  case 4:
   tile_acc(QString("`<%1>%2").arg(text).arg(sup_text));
   return;
  }
  break;
 case GTagML_Paralex_Tile::Pipe_Escape:
  tile_acc_length_adjustment_ += (text.size() + 1) - w;
  tile_acc(QString("|%1").arg(text));
  return; 
 default:
  break;
 }

 check_tile_acc();
 
 caon_ptr<GTagML_Paralex_Tile> xtile = make_new_paralex_tile(text, k, w);
 caon_ptr<tNode> node = make_new_node(xtile);
 markup_position_.add_tile_node(node);
}

caon_ptr<GTagML_Graph_Build::tNode> GTagML_Graph_Build::make_new_node(caon_ptr<GTagML_Annotation_Tile> tile)
{
 caon_ptr<tNode> result = new tNode(tile);
 result->set_label(tile->thumbnail());
 return result;
}

caon_ptr<GTagML_Graph_Build::tNode> GTagML_Graph_Build::make_new_node(caon_ptr<GTagML_Annotation_Tile> tile, QString label)
{
 caon_ptr<tNode> result = new tNode(tile);
 result->set_label(label);
 return result;
}

caon_ptr<GTagML_Graph_Build::tNode> GTagML_Graph_Build::make_new_node(caon_ptr<GTagML_Attribute_Tile> tile)
{
 CAON_PTR_DEBUG(GTagML_Attribute_Tile ,tile)
 caon_ptr<tNode> result = caon_ptr<tNode>( new tNode(tile) );
 #ifdef RELAE_LABEL_NODES
 result->set_label(tile->thumbnail());
 #endif
 return result;
}

caon_ptr<GTagML_Graph_Build::tNode> GTagML_Graph_Build::make_new_node(caon_ptr<GTagML_Paralex_Tile> tile)
{
 CAON_PTR_DEBUG(GTagML_Paralex_Tile ,tile)
 caon_ptr<tNode> result = caon_ptr<tNode>( new tNode(tile) );
 #ifdef RELAE_LABEL_NODES
 result->set_label(tile->thumbnail());
 #endif
 return result;
}

caon_ptr<GTagML_Graph_Build::tNode> GTagML_Graph_Build::make_new_node(caon_ptr<GTagML_Tag_Command> gtc)
{
 CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)
 caon_ptr<tNode> result = caon_ptr<tNode>( new tNode(gtc) );
 #ifdef RELAE_LABEL_NODES
 result->set_label(gtc->name());
 #endif
 return result;
}

void GTagML_Graph_Build::attribute_sequence_leave()
{
 check_tile_acc();
 parse_context_.flags.inside_attribute_sequence = false;
 parse_context_.flags.inside_multi_generic = false;
 markup_position_.attribute_sequence_leave();
}

void GTagML_Graph_Build::tag_body_leave(QString match)
{
 check_tile_acc();
 markup_position_.tag_body_leave();
 parse_context_.flags.inside_tag_body = false;
 if(match == "/>")
  tag_command_leave();
}

void GTagML_Graph_Build::enter_special_parse_mode(QString spm)
{
 if(spm.startsWith("raw-"))
 {
  current_raw_format_ = spm.mid(4);
 }
 else if(spm != "raw")
 {
  // // no other spm current recognized ...
  return;
 }

 prior_parsing_modes_.push({current_parsing_mode_, acc_mode_});
 check_tile_acc(Acc_Mode::Raw);
 current_parsing_mode_ = GTagML_Parsing_Modes::Raw;
}

void GTagML_Graph_Build::leave_special_parse_mode(QString spm)
{
 if(prior_parsing_modes_.isEmpty())
   current_parsing_mode_ = GTagML_Parsing_Modes::Parse_Error;
 else
 {
  current_parsing_mode_ = prior_parsing_modes_.top().first;
  check_tile_acc(prior_parsing_modes_.pop().second);
 }
}

void GTagML_Graph_Build::special_parse_mode_acc(QString text)
{
 tile_acc(text);
}

void GTagML_Graph_Build::html_tag_body_leave(QString prefix)
{

 if(get_light_xml())
 {
  // get_light_xml()->tag_body_leave(prefix);
  parse_context_.flags.inside_html_tag_body = false;
  return;
 }

 markup_position_.tag_body_leave();
 parse_context_.flags.inside_html_tag_body = false;
 if(prefix == "/")
  tag_command_leave();
}

