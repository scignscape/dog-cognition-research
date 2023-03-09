
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_OUTPUT_BLOCKS__H
#define GTAGML_OUTPUT_BLOCKS__H

#include <QTextStream>


#include "gtagml-output-base.h"

#include "gtagml-output-event-handler.h"


#include "global-types.h"

#include "kans.h"

//KANS_CLASS_DECLARE(HTXN, HTXN_Node_Detail)
//USING_KANS(HTXN)

#include "kans.h"

class GH_Block_Writer;
class GH_Block_Base;

KANS_(GTagML)

class GTagML_Graph;
class GTagML_Document;

//class GTagML_HTXN_Node;

class GTagML_Attribute_Tile;
class GTagML_Tile;

class GTagML_Output_Infoset;

class GTagML_Project_Info;


class GTagML_Output_Blocks : public GTagML_Output_Base, private GTagML_Output_Event_Handler
{
 QMap<QString, caon_ptr<GTagML_Tag_Command_Callback>> callbacks_;
 void init_callbacks();

 GH_Block_Writer* block_writer_;

 QString htxn_acc_;
 QTextStream htxn_qts_;

 QString summary_;

 QString ws_acc_;
 QTextStream ws_qts_;

//? QMap<HTXN_Node_Detail*, QString> region_end_names_;

 caon_ptr<tNode> suppress_node_;

 u1 active_gap_code_;

 GTagML_Output_Infoset* infoset_;

 //caon_ptr<GTagML_Tag_Command>

 QMap<u4, QMap<caon_ptr<GTagML_Tag_Command>,
   QPair<GH_Prenode*, QPair<u4, u4>>>> ref_ranges_;

 u4 last_ref_enter_;
 u4 last_ref_leave_;

 QVector<u4> special_flag_marks_;

 QVector<QMap<u4, QPair<QString, u4>>*> marks_by_mode_;

 GH_Prenode* local_last_prenode_;

// GTagML_Project_Info* project_info_;

 void mark_citation(QTextStream& qts,
   caon_ptr<tNode> node, caon_ptr<tNode> prior_node,
   caon_ptr<tNode> parent_of_siblings);

// QMap<QString, QPair<QString, u4>> main_block_text_commands_;


public:


 GTagML_Output_Blocks(GTagML_Document& document, GH_Block_Writer* block_writer);

 ACCESSORS(GTagML_Output_Infoset* ,infoset)

 ~GTagML_Output_Blocks();

 void export_blocks(QString path = "..blocks-summary.txt");
 void write_block_output(QMap<QString, QString>& block_output);

 QString export_main_block(QString path = "..htxn.txt");

 QString export_marks(QString path = "..marks-summary.txt");

 void load_marks(QString path);

 void generate(QTextStream& qts) Q_DECL_OVERRIDE;

 GH_Block_Base* get_current_mandatory_argument_block();

 void init_standard_8bit();

 void reset_active_gap_code()
 {
  active_gap_code_ = 0;
 }

 u1 get_ws_gap_code();
 u1 get_ws_gap_code(const QString& str);

 void check_reconcile_gap(const GTagML_Output_Bundle& b, u1 new_code);
 void check_reconcile_gap(const GTagML_Output_Bundle& b, 
   u1 new_code, u1& result);

 void check_generate_tag_command_argument(const GTagML_Output_Bundle& b,
   GTagML_Tag_Command& ntc);

// void generate_tag_command_argument(const GTagML_Output_Bundle& b,
//   GTagML_HTXN_Node& nhn);

// void check_generate_whitespace(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn);

 void parse_main_block_text_commands(caon_ptr<GTagML_Node> node);

 void check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc) Q_DECL_OVERRIDE;
 void check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tile> tile) Q_DECL_OVERRIDE;
 void check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Paralex_Tile> tile) Q_DECL_OVERRIDE;

 void generate_tag_command_entry(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc) Q_DECL_OVERRIDE;

//? void generate_tag_command_entry(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn);

 void generate_tag_command_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc) Q_DECL_OVERRIDE;
//? void generate_tag_command_leave(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn);

 void generate_tag_body_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc) Q_DECL_OVERRIDE;
//? void generate_tag_body_leave(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn);

  void generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Paralex_Tile> tile) Q_DECL_OVERRIDE;

 void generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tile> tile) Q_DECL_OVERRIDE;
 void generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Attribute_Tile> tile) Q_DECL_OVERRIDE;
// void generate_tile_via_htxn(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn) Q_DECL_OVERRIDE;

 void handle_annotation(caon_ptr<GTagML_Tile> tile, caon_ptr<GTagML_Annotation_Tile> atile) Q_DECL_OVERRIDE;

 caon_ptr<GTagML_Tag_Command_Callback> check_command_callback(caon_ptr<GTagML_Tag_Command> ntc)  Q_DECL_OVERRIDE;

 
};

_KANS(GTagML)


#endif
