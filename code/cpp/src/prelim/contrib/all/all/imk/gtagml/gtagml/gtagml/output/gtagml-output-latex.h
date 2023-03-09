
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_OUTPUT_LATEX__H
#define GTAGML_OUTPUT_LATEX__H

#include <QTextStream>


#include "gtagml-output-base.h"
#include "gtagml-output-event-handler.h"

#include "global-types.h"

#include "kans.h"

//KANS_CLASS_DECLARE(HTXN, HTXN_Node_Detail)
//USING_KANS(HTXN)

#include "kans.h"


KANS_CLASS_DECLARE(SDI, GH_SDI_Document)
USING_KANS(SDI)


KANS_(GTagML)

class GTagML_Graph;
class GTagML_Document;

//class GTagML_HTXN_Node;

class GTagML_Attribute_Tile;
class GTagML_Tile;
class GTagML_Tag_Command;

class GH_Prenode;

class GTagML_Output_Infoset;


class GTagML_Output_Latex : public GTagML_Output_Base, private GTagML_Output_Event_Handler
{
 QMap<QString, caon_ptr<GTagML_Tag_Command_Callback>> callbacks_;
 void init_callbacks();

 QString htxn_acc_;
 QTextStream htxn_qts_;

 QString ws_acc_;
 QTextStream ws_qts_;

//? QMap<HTXN_Node_Detail*, QString> region_end_names_;

 caon_ptr<tNode> suppress_node_;

 u1 active_gap_code_;

 //GTagML_Output_Infoset* infoset_;
 GH_SDI_Document* sdi_document_;

 QMap<caon_ptr<GTagML_Tag_Command>, QString> tile_whitespace_defers_;

 QString held_ref_;

public:


 GTagML_Output_Latex(GTagML_Document& document,
   GH_SDI_Document* sdi_document = nullptr);

// ACCESSORS(GTagML_Output_Infoset* ,infoset)

 ~GTagML_Output_Latex();

 void export_latex(QString path = "..tex");
 void write_latex_output(QString& latex_output);

 void set_held_ref(QTextStream& qts, caon_ptr<tNode> node);

 void generate(QTextStream& qts);

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
 void generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Attribute_Tile> tile) Q_DECL_OVERRIDE;
//
 void generate_tile_via_gh(const GTagML_Output_Bundle& b, GH_Prenode& ghp) Q_DECL_OVERRIDE;

 void handle_annotation(caon_ptr<GTagML_Tile> tile, caon_ptr<GTagML_Annotation_Tile> atile) Q_DECL_OVERRIDE;

 caon_ptr<GTagML_Tag_Command_Callback> check_command_callback(caon_ptr<GTagML_Tag_Command> ntc)  Q_DECL_OVERRIDE;

 void generate_tag_command_argument(const GTagML_Output_Bundle& b,
   GH_Prenode& ghp);
 
 void check_discourse_markup(QTextStream& qts, caon_ptr<tNode> node, QString mode);

};

_KANS(GTagML)


#endif
