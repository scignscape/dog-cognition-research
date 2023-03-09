
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_OUTPUT_SDI_INFOSET__H
#define GTAGML_OUTPUT_SDI_INFOSET__H

#include <QStack>
#include <QTextStream>
#include <QSet>

#include <QMultiMap>

#include "gtagml-output-base.h"
#include "gtagml-output-event-handler.h"

//#include "htxn/infoset/htxn-infoset-8b.h"

#include "global-types.h"

#include "kans.h"

//?KANS_CLASS_DECLARE(HTXN, HTXN_Node_Detail)
//USING_KANS(HTXN)

//#include "rzns.h"

class GH_Block_Base;
class GH_Block_Writer;

KANS_CLASS_DECLARE(SDI, GH_SDI_Document)
USING_KANS(SDI)

KANS_(GTagML)


class GTagML_Graph;
class GTagML_Document;
class GTagML_Tag_Command_Callback;

class GTagML_HTXN_Node;
class GTagML_Output_HTXN;
//class GTagML_Output_SDI_Infoset

class GTagML_Output_SDI_Infoset : public GTagML_Output_Base, private GTagML_Output_Event_Handler
{
// HTXN_Infoset_8b* infoset_;

 QStack<caon_ptr<GTagML_Node>> chiefs_;

 caon_ptr<tNode> suppress_node_;

 QMap<u4, QPair<caon_ptr<tNode>, u4>> marked_sentence_starts_;
 QMap<u4, QPair<caon_ptr<tNode>, u4>> marked_sentence_ends_; // the other u4 is the space ...

 QMultiMap<caon_ptr<tNode>, u4> widowed_sentence_starts_;
 QMultiMap<caon_ptr<tNode>, u4> widowed_sentence_ends_;

 QMultiMap<caon_ptr<tNode>, u4> declared_sentence_starts_;
 QMultiMap<caon_ptr<tNode>, u4> declared_sentence_ends_;


 QMap<u4, QPair<caon_ptr<tNode>, u4>> marked_paragraph_starts_;
 QMap<u4, caon_ptr<tNode>> marked_paragraph_ends_;

 QMap<u4, QPair<QString, caon_ptr<tNode>>> sdi_marks_;
 QMap<u4, QPair<QString, caon_ptr<tNode>>> sdi_secondary_marks_;
 u4 held_sdi_sentence_end_index_;
 u4 canceled_sdi_sentence_start_index_;
 caon_ptr<tNode> held_sdi_sentence_end_node_;

 QMap<QString, caon_ptr<GTagML_Tag_Command_Callback>> callbacks_;
 void init_callbacks();

 GTagML_Output_HTXN* gh_output_htxn_;

 QString review_;
 QTextStream review_qts_;

 GH_Block_Writer* block_writer_;
 GH_SDI_Document* sdi_document_;

 QString copy_path_;
 QString raw_copy_path_;

 QString setup_path_;
 QString raw_setup_path_;

 QString file_job_name_;

 QStringList post_processing_codes_;

 void generate_sdi_mark(caon_ptr<GTagML_Tag_Command> ntc,
   const GTagML_Output_Bundle& b,  GH_Prenode& ghp);
 
 void check_post_callback(QTextStream& qts,
   caon_ptr<GTagML_Tag_Command_Callback> cb, caon_ptr<tNode> node, u4 index);

 caon_ptr<GTagML_Tag_Command_Callback> check_command_callback(caon_ptr<GTagML_Tag_Command> ntc) Q_DECL_OVERRIDE;

 void check_sentence_boundaries(QTextStream& qts, caon_ptr<tNode> node);
 void check_sentence_boundaries(QTextStream& qts, caon_ptr<tNode> node,
   GH_Block_Base& bl, //   GTagML_HTXN_Node& nhn,
                                u4 enter, u4 leave);

 void mark_sentence(QTextStream& qts, caon_ptr<tNode> node, u4 
   enter, u4 leave, u4 sp);

 u4 write_ntxh_sentences(QTextStream& qts, u4 id,  u4 s, u4 e, u4 sentence_id);


 void set_copy(QTextStream& qts, caon_ptr<tNode> node);
 void set_setup(QTextStream& qts, caon_ptr<tNode> node);

 void set_path(QTextStream& qts, caon_ptr<tNode> node, QString* path, QString* raw);

 void set_info_param(QTextStream& qts, QString key, caon_ptr<tNode> node);

public:

 GTagML_Output_SDI_Infoset(GTagML_Document& document, GH_Block_Writer* block_writer);//, HTXN_Infoset_8b* infoset);

 //ACCESSORS(GTagML_Output_HTXN* ,gh_output_htxn)
 ACCESSORS(GH_SDI_Document* ,sdi_document)

 ACCESSORS(QString ,copy_path)
 ACCESSORS(QString ,raw_copy_path)

 ACCESSORS(QString ,setup_path)
 ACCESSORS(QString ,raw_setup_path)

 ACCESSORS(QString ,file_job_name)

 ACCESSORS(GH_Block_Writer* ,block_writer)

 ACCESSORS__RGET(QStringList ,post_processing_codes)

 void add_post_processing_code(QString ppc);

 void write_ntxh(QTextStream& qts);

 void finalize_sentence_boundaries(GH_Block_Base& bl);
 void finalize_paragraph_boundaries(GH_Block_Base& bl);
 void finalize_widowed_sentence_boundaries(GH_Block_Base& bl);

 void finalize_post_processing_codes();


 n8 check_sdi_latex_insert(GH_Block_Base* bl, u4 index,
   QString& pre_result, QString& post_result);

 QVector<caon_ptr<tNode>> get_sdi_latex_insert_nodes(GH_Block_Base* bl, u4 index, QString& pre_result, QString& post_result);

 void write_infoset_output(QString& output);
 void export_infoset(QString path);
 void export_infoset_review(QString path);

 void generate(QTextStream& qts);

 void generate_root(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Root> nr) Q_DECL_OVERRIDE;

 void generate_tag_command_entry(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc) Q_DECL_OVERRIDE;
 void generate_tag_command_entry(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn);

 void generate_tag_command_argument(const GTagML_Output_Bundle& b,
   GTagML_HTXN_Node& nhn);
 void check_generate_tag_command_argument(const GTagML_Output_Bundle& b,
   GTagML_Tag_Command& ntc);

 void generate_tag_command_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc) Q_DECL_OVERRIDE;
 void generate_tag_command_leave(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn);

 void generate_tag_body_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc) Q_DECL_OVERRIDE;
 void generate_tag_body_leave(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn);

 void generate_tag_command_auto_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> ntc) Q_DECL_OVERRIDE;

//? void generate_tile_via_htxn(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn) Q_DECL_OVERRIDE;

};

_KANS(GTagML)


#endif // GTAGML_OUTPUT_INFOSET__H
