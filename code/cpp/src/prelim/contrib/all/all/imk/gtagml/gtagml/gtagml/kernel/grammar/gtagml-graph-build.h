
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_GRAPH_BUILD__H
#define GTAGML_GRAPH_BUILD__H

#include "kernel/graph/gtagml-markup-position.h"
#include "kernel/grammar/gtagml-parse-context.h"

#include "kernel/gtagml-dominion.h"

#include "kernel/grammar/gtagml-parsing-mode.h"

#include "global-types.h"

#include "accessors.h"

#include "kans.h"

KANS_(GTagML)

class GTagML_Parser;
class GTagML_Tag_Command;
class GTagML_Attribute_Tile;
class GTagML_Paralex_Tile;
class GTagML_Raw_Tile;
class GTagML_Document_Info;
class GTagML_Annotation_Tile;

class GTagML_Document_Light_Xml;


class GTagML_Graph_Build
{
 flags_(1)
  bool math_mode:1;
  bool skip_command_node_insert:1;
  bool active_annotation_entry:1;
  bool active_annotation_tile:1;
  bool active_attribute_sequence:1;
 _flags

 enum class Acc_Mode {
  Main_Tile, Attribute, Math, Arg_Tile, Raw
 };

 Acc_Mode acc_mode_;

 enum Tag_Body_Follow_Mode {
  Tag_Body_Follow_Mode_Not_Recognized, Normal, Region, Empty
 };

 static Tag_Body_Follow_Mode parse_tag_body_follow(QString str)
 {
  static QMap<QString, Tag_Body_Follow_Mode> static_map {{
   {".",  Normal}, {",",  Region}, {";", Empty},
    // for gtags ...
    {">", Normal}
  }};
  return static_map.value(str, Tag_Body_Follow_Mode_Not_Recognized);
 }

 GTagML_Parsing_Modes current_parsing_mode_;

 QStack<QPair<GTagML_Parsing_Modes, Acc_Mode>> prior_parsing_modes_;

 GTagML_Parse_Context parse_context_;

 GTagML_Markup_Position markup_position_;

 QString current_raw_format_;


 static inline int cutmax(int x)
 {
  if(x > 6)
   return 6;
  return x;
 }

 typedef GTagML_Node tNode;

 u4 tile_acc_length_adjustment_;
 QString tile_acc_;
 QTextStream tile_acc_qts_;

 QString string_literal_acc_;
 QTextStream string_literal_acc_qts_;

 QString current_html_attribute_;

//? QString khif_tile_;

 GTagML_Document_Info& document_info_;

 caon_ptr<GTagML_Tile> add_tile(QString tile_str);
 caon_ptr<GTagML_Attribute_Tile> add_attribute_tile(QString tile_str);
 caon_ptr<GTagML_Raw_Tile> add_raw_tile(QString tile_str);

 void add_string_literal_tile();

 GTagML_Document_Light_Xml* get_light_xml();

 QString quote_acc_;

 u1 held_semantic_mark_mode_;

public:


 ACCESSORS__RGET(GTagML_Parse_Context ,parse_context)
 ACCESSORS(GTagML_Parsing_Modes ,current_parsing_mode)

 GTagML_Graph_Build(GTagML_Graph& g, GTagML_Document_Info& document_info);

 void init();

 void add_string_literal_tile(QString str);
 void enter_multiline_comment(QString semis, QString tildes);
 void check_leave_multiline_comment(QString semis, QString tildes);

 void tag_command_leave();
 void tag_command_leave_multi(QString tag_command);

 void inline_tag_command_leave();
 void block_gtag_command_leave();


 caon_ptr<GTagML_Tag_Command> tag_command_entry(QString wmi, QString prefix, QString tag_command, QString argument, QString parent_tag_type = QString());
 void tag_command_instruction_leave(caon_ptr<tNode> node);

 void attribute_sequence_leave();
 void tag_body_leave(QString match = QString());

 void call_leave();

 void tile_acc(QString str);
 void check_tile_acc(Acc_Mode new_mode = Acc_Mode::Main_Tile);

 void check_non_or_left_wrapped(QString wmi, caon_ptr<GTagML_Tag_Command> ntc);

 void html_tag_body_leave(QString prefix);

 void enter_special_parse_mode(QString spm);
 void leave_special_parse_mode(QString spm);
 void special_parse_mode_acc(QString spm);

//? void khif_tile_acc(QString m);

 caon_ptr<GTagML_Tag_Command> html_tag_command_entry(QString prefix, QString tag_command);

 void attach_whitespace(QString whitespace);
 void attach_left_whitespace();
 void attach_right_whitespace();

//? void end_khif_tile(QString connector_prefix, QString connectors);
//? void end_khif_tile();
//? void attach_khif_tile();

 void attach_predicate_vector(QString connector_prefix, QString connectors);

 void tag_command_leave(QString connector_to_load, QString tag_command);

 void check_tag_command_leave(QString tag_command, QString match_text);
 void check_html_tag_command_leave(QString tag_command, QString match_text);

 void html_tag_command_attribute_acc(QString str);

 void html_tag_command_attribute_entry(QString pre_space, QString attribute, QString s_or_d);

 void check_add_words();

 void enter_tag_command_with_predicate_vector(QString tag_command,
  QString connector_prefix, QString connectors);

 caon_ptr<GTagML_Tag_Command> html_tag_instruction(QString prefix,
  QString tag_command, QString argument);

 void tag_command_annotation(QString annotation);

 void annotation_entry(QString flag, QString text, QString rel, QString tile, QString follow);

 void check_multi_parent_reset();

 void multi_arg_transition_to_main_tile();

 void multi_arg_transition(QString wmi, QString inner_wmi, QString fiat,
   QString arg_marker, QString carried_arg_marker = {});

 caon_ptr<GTagML_Attribute_Tile> complete_html_tag_command_attribute();

 caon_ptr<GTagML_Attribute_Tile> make_new_attribute_tile(QString key, QString value);

 caon_ptr<GTagML_Raw_Tile> make_new_raw_tile(QString format, QString value);

 void tag_command_entry_with_layer(QString tag_command, QString layer_marker);

 void tag_command_entry_multi(QString wmi,
   QString inner_wmi, QString tag_command,
   QString tag_body_follow, QString fiat, QString first_arg_wmi, QString first_arg_marker);

 void tag_command_entry_inside_multi(QString wmi, QString inner_wmi,
   QString fiat,  QString tag_command, QString arg_marker,
   QString* carried_arg_marker = nullptr, QString argument = QString(), QString name = QString());

 void tag_command_entry_inline(QString wmi, QString inner_wmi,
   QString fiat, QString tag_command,
   QString tag_body_follow, QString argument = QString());

 void gtag_command_entry_inline(QString tag_command,
   QString tag_body_follow);



 void mark_attribute_tile();

 void special_character_sequence(QString match_text, QString esc, u1 mode);

 void semantic_mark(QString match_text, QString esc, u1 mode);

 void check_nonstandard_special_character_sequence(QString match_text, QString& esc,
   u1& mode, QString& sup_text);

   //QString bq_trig, QString bq_esc, QString pipe);

 caon_ptr<GTagML_Attribute_Tile> make_new_attribute_tile(QString tile);
 caon_ptr<GTagML_Tile> make_new_tile(QString tile);
 caon_ptr<GTagML_Tag_Command> make_new_tag_command(QString name, 
QString argument, QString parent_tag_type = QString());
 caon_ptr<GTagML_Paralex_Tile> make_new_paralex_tile(QString tile, 
   u1 kind, u1 w_or_a);

 caon_ptr<tNode> make_new_node(caon_ptr<GTagML_Attribute_Tile> tile);

 caon_ptr<tNode> make_new_node(caon_ptr<GTagML_Raw_Tile> tile);

 caon_ptr<tNode> make_new_node(caon_ptr<GTagML_Tile> tile);
 caon_ptr<tNode> make_new_node(caon_ptr<GTagML_Tag_Command> ntc);
 caon_ptr<tNode> make_new_node(caon_ptr<GTagML_Paralex_Tile> tile);

 caon_ptr<tNode> make_new_node(caon_ptr<GTagML_Annotation_Tile> tile);
 caon_ptr<tNode> make_new_node(caon_ptr<GTagML_Annotation_Tile> tile, QString label);


};

_KANS(GTagML)

#endif
