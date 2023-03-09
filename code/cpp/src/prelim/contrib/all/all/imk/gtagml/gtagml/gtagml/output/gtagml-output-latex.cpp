
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-output-latex.h"

#include "gtagml-output-event-generator.h"
#include "kernel/document/gtagml-document.h"
#include "kernel/output/gtagml-output-bundle.h"
#include "tag-command/gtagml-tag-command.h"
#include "tile/gtagml-paralex-tile.h"

#include "tile/gtagml-tile.h"

#include "tag-command/gtagml-tag-command-callback.h"

#include "kernel/graph/gtagml-node.h"

#include "gh/gh-prenode.h"

#include "gh/gh-block-base.h"

#include "sdi/gh-sdi-document.h"
#include "gtagml-output-sdi-infoset.h"

#include "gh/gh-block-writer.h"

//?#include "ngml-htxn/ngml-htxn-node.h"


//#include "htxn/htxn-document-8b.h"
//#include "htxn/glyph-layer-8b.h"
//#include "htxn/infoset/sdi-callback-8b.h"


//?#include "gtagml-output-infoset.h"
//?#include "gtagml-output-htxn.h"

#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>


#include <QDebug>

#include "kans.h"
USING_KANS(GTagML)

//struct _SDI_Callback : public SDI_Callback_8b
//{
// GTagML_Output_Infoset& infoset;
// u4 target_layer_id;
// _SDI_Callback(GTagML_Output_Infoset& noi, u4 u);
// void pre_write(Glyph_Layer_8b& gl, u4 pos,
//   Glyph_Argument_Package& gap, u8& skip_flag,
//   QString& pre_insert, QString& post_insert) Q_DECL_OVERRIDE;
//};

//_SDI_Callback::_SDI_Callback(GTagML_Output_Infoset& noi, u4 u)
//  :  infoset(noi), target_layer_id(u)
//{

//}

void GTagML_Output_Latex::set_held_ref(QTextStream& qts, caon_ptr<tNode> node)
{
 CAON_PTR_DEBUG(tNode ,node)
 if(caon_ptr<GTagML_Tag_Command> ntc = node->GTagML_tag_command())
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
  held_ref_ = ntc->argument();
 }
}


void GTagML_Output_Latex::check_discourse_markup(QTextStream& qts,
  caon_ptr<tNode> node, QString mode)
{
 CAON_PTR_DEBUG(tNode ,node)
 if(caon_ptr<GTagML_Tag_Command> ntc = node->GTagML_tag_command())
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
  //

  QString ref;
  if(!held_ref_.isEmpty())
  {
   ref = held_ref_;
   held_ref_.clear();
  }

  GTagML_Output_SDI_Infoset* gsi = sdi_document_->sdi_infoset_output(); //sdi_document_->block_writer();

  GH_Block_Base* bl = gsi->block_writer()->current_mandatory_argument_block();

  QString post_processing_code = QString("discourse-markup=%1:%2:%3:%4-%5")
    .arg(mode).arg(ref).arg(bl->layer_code()).arg(ntc->ref_enter()).arg(ntc->ref_leave());

  gsi->add_post_processing_code(post_processing_code);
  //  block_writer_->current_mandatory_argument_block();

//  ntc->each_arg_prenode([](GH_Prenode* ghp)
//  {

//  });
 }
}



GTagML_Output_Latex::GTagML_Output_Latex(GTagML_Document& document,
  GH_SDI_Document* sdi_document)
  :  GTagML_Output_Base(document), active_gap_code_(0), 
     suppress_node_(nullptr), sdi_document_(sdi_document)
{
 htxn_qts_.setString(&htxn_acc_);
 ws_qts_.setString(&ws_acc_);
 init_callbacks();
}

GTagML_Output_Latex::~GTagML_Output_Latex()
{
 qDebug() << "del GTagML_Output_Latex";
}


void GTagML_Output_Latex::init_callbacks()
{
 #include "gtagml-output-callbacks-common.h"

 #include "gtagml-output-latex.callbacks.h"
}

void GTagML_Output_Latex::generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Attribute_Tile> tile)
{
}


void GTagML_Output_Latex::write_latex_output(QString& latex_output)
{
 QTextStream qts(&latex_output);
 generate(qts);
 latex_output.replace(QRegularExpression("\\n{2,}"), "\n\n");
}

void GTagML_Output_Latex::generate(QTextStream& qts)
{
 GTagML_Output_Event_Generator events(*this, *this);
 events.generate(qts);
}

void GTagML_Output_Latex::export_latex(QString path)
{
 if(path.startsWith(".."))
 {
  path.remove(0, 1);
  path.prepend(document_.local_or_info_path());
 }
 else if(path.startsWith('.'))
 {
  QFileInfo qfi(document_.local_or_info_path());
  path.prepend(qfi.absolutePath() + '/' + qfi.completeBaseName());
 }
 QString latex_output;
 write_latex_output(latex_output);

 // //temp
 latex_output.replace("@@", "%%");
 latex_output.replace("#{", "\\scaps{");
 latex_output.replace("}#", "}");

 QFile outfile(path);
 if(outfile.open(QFile::WriteOnly | QIODevice::Text))
 {
  outfile.write(latex_output.toLatin1());
  outfile.close();
 }
}

void GTagML_Output_Latex::handle_annotation(caon_ptr<GTagML_Tile> tile, caon_ptr<GTagML_Annotation_Tile> atile)
{
//? document_.tag_command_annotation(tile, atile);
}

void GTagML_Output_Latex::check_reconcile_gap(const GTagML_Output_Bundle& b, u1 new_code)
{
 check_reconcile_gap(b, new_code, active_gap_code_);
}

void GTagML_Output_Latex::check_reconcile_gap(const GTagML_Output_Bundle& b, u1 new_code, u1& result)
{
 u2 code = (active_gap_code_ * 100) + new_code;

 switch(code)
 {
 case 2020:
  result = 20; break;
 case 2121: 
  result = 21; break;
 case 2120:
  result = 21; break;
 case 2010:
  result = 20; break;
 case 2111:
  result = 21; break;
 case 2110:
  result = 21; break;
 case 1010:
  result = 10; break;
 case 1111:
  result = 11; break;
 case 1110:
  result = 11; break;
 case 2101:
  result = 21; break;
 case 1101:
  result = 11; break;
 case 1011:
  b.qts << ' '; result = 11; break;
 case 2021:
  b.qts << ' '; result = 21; break;
 case 1001:
  b.qts << ' '; result = 11; break;
 case 2001:
  b.qts << ' '; result = 21; break;
 case 1:
  b.qts << ' '; result = 1; break;
 case 1020:
  b.qts << '\n'; result = 20; break;
 case 1120:
  b.qts << '\n'; result = 20; break;
 case 10:
  b.qts << '\n'; result = 10; break;
 case 1021:
  b.qts << "\n "; result = 21; break;
 case 1121:
  b.qts << "\n "; result = 21; break;
 case 11:
  b.qts << "\n "; result = 11; break;
 case 21:
  b.qts << "\n\n "; result = 21; break;
 case 20:
  b.qts << "\n\n"; result = 20; break;
 default: break;
 }
}

void GTagML_Output_Latex::generate_tile_via_gh(const GTagML_Output_Bundle& b, GH_Prenode& ghp)
{
 if(GH_Block_Base* ghb = ghp.get_block())
 {
  b.qts << ghb->get_latex_out(ghp.range());
 }
}


void GTagML_Output_Latex::generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Paralex_Tile> tile)
{
 tile->write_latex(b.qts);
 check_generate_whitespace(b, tile);
 reset_active_gap_code();
}


//void GTagML_Output_Latex::generate_tag_command_entry(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
//{
// HTXN_Node_Detail* nd = nhn.get_node_detail(htxn_document_);
// Glyph_Layer_8b* gl = nd->get_layer();

// if(nd->flags.pre_line_double_gap)
//   check_reconcile_gap(b, 20);  //? b.qts << "\n\n";
// else if(nd->flags.pre_line_gap)
//   check_reconcile_gap(b, 10);  //? b.qts << '\n';
// else if(nd->flags.pre_space_gap)
//   check_reconcile_gap(b, 1);  //? b.qts << ' ';

// if(nd->flags.is_ghosted)
// {
//  if(nd->flags.region_main_preempts_wrap)
//  {
//   if(nd->flags.block_environment_marked_main)
//     check_reconcile_gap(b, 10);  //? b.qts << '\n';
//  }
//  else if(nd->flags.optional)
//  {
//   b.qts << '[';
//   reset_active_gap_code();
//  }
//  else
//  {
//   b.qts << '{';
//   reset_active_gap_code();
//  }
// }
// else
// {
//  htxn_document_->write_minimal_latex_out(gl, nd->enter,
//    nd->leave, htxn_qts_);

////  if(nd->flags.ref_preempts_wrap)
////    b.qts << '\\' << htxn_acc_;
//  if(nd->flags.region)
//  {
//   b.qts << "\\begin{" << htxn_acc_;// << '}';
//   region_end_names_[nd] = htxn_acc_;
//  }
//  else if(nd->flags.wmi_left)
//  {
//   if(nd->flags.wmi_with_space)
//     b.qts << "{\\" << htxn_acc_ << ' ';
//   else
//     b.qts << "{\\" << htxn_acc_;
//  }
//  else
//    b.qts << '\\' << htxn_acc_;// << '{';
//  htxn_acc_.clear();
//  htxn_qts_.reset();
// }
//}

//void _SDI_Callback::pre_write(Glyph_Layer_8b& gl, u4 pos,
//  Glyph_Argument_Package& gap, u8& skip_flag,
//  QString& pre_insert, QString& post_insert)
//{
// if(gl.id() != target_layer_id)
//   return;
// QString pre_result;
// QString post_result;
// u8 inserts = infoset.check_sdi_latex_insert(&gl, pos,
//   pre_result, post_result);

// if(inserts)
// {
//  pre_insert = pre_result;
//  post_insert = post_result;
// }
//}

//void GTagML_Output_Latex::generate_tile_via_htxn(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
//{
// if(infoset_)
// {
//  u4 id = infoset_->GTagML_output_htxn()->main_gl()->id();
//  _SDI_Callback cb(*infoset_, id);
//  htxn_document_->write_minimal_latex_out(nhn.layer_code(), nhn.range(), b.qts, &cb);
// }
// else
//   htxn_document_->write_minimal_latex_out(nhn.layer_code(), nhn.range(), b.qts);
// reset_active_gap_code();
//}

//void GTagML_Output_Latex::generate_tag_command_argument(const GTagML_Output_Bundle& b,
//  GTagML_HTXN_Node& nhn)
//{
// HTXN_Node_Detail* nd = nhn.get_node_detail(htxn_document_);
// b.qts << (nd->flags.optional? '[' : '{');
// htxn_document_->write_minimal_latex_out(nd->get_layer(), nd->enter, nd->leave, b.qts);
// b.qts << (nd->flags.optional? ']' : '}');
//}

void GTagML_Output_Latex::check_generate_tag_command_argument(const GTagML_Output_Bundle& b,
  GTagML_Tag_Command& gtc)
{
// if(GTagML_HTXN_Node* nhn = gtc.arg_GTagML_htxn_node())
//   generate_tag_command_argument(b, *nhn);

// gtc.each_arg_GTagML_htxn_node([&b, this](GTagML_HTXN_Node* nhn)
// {
//  generate_tag_command_argument(b, *nhn);
// });

 gtc.each_arg_prenode([&b, this, gtc](GH_Prenode* ghp)
 {
  if(gtc.flags.force_opt_split)
    b.qts << ((ghp->get_block()->layer_code() == 2) ? '[' : '{');
  generate_tag_command_argument(b, *ghp);
  if(gtc.flags.force_opt_split)
    b.qts << ((ghp->get_block()->layer_code() == 2) ? ']' : '}');
 });

 // {
 //  generate_tag_command_argument(b, *nhn);
 // });

}

void GTagML_Output_Latex::generate_tag_command_argument(const GTagML_Output_Bundle& b,
  GH_Prenode& ghp)
{
 if(GH_Block_Base* ghb = ghp.get_block())
 {
  b.qts << ghb->get_latex_out(ghp.range());
 }
}



void GTagML_Output_Latex::generate_tag_command_entry(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> gtc)
{
 CAON_PTR_B_DEBUG(GTagML_Node ,node)
 CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)

 caon_ptr<GTagML_Tag_Command_Callback> cb = b.cb;

 // inh?
 if(caon_ptr<GTagML_Node> pn = b.prior_node)
 {
  if(pn->type_code() != GTagML_Dominion::Type_Codes::GTagML_Tile)
    gtc->write_inherited_whitespace(b.qts);
 }
 else
   gtc->write_inherited_whitespace(b.qts);

 caon_ptr<GTagML_Node> parent_of_siblings = nullptr;

 switch(b.connection_descriptor)
 {
 case GTagML_Connection_Descriptor::Tag_Command_Cross_From_Blank:
 case GTagML_Connection_Descriptor::Tag_Command_Cross:
  // maybe set parent_of_siblings?

 case GTagML_Connection_Descriptor::Tag_Command_Entry:
  if(cb)
  {
   CAON_PTR_DEBUG(GTagML_Tag_Command_Callback ,cb)

   // if its Tag_Command_Entry definitely parent_of_siblings == nullptr

   if(cb->flags.has_around_callback)
   {
    cb->around_callback(b.qts, b.node, b.prior_node, parent_of_siblings, b.index, b.cb);
    break;
   }

   if(cb->flags.has_pre_callback)
    cb->pre_callback(b.qts, b.node, b.prior_node, parent_of_siblings, b.index, b.cb);
   if(!cb->flags.pre_fallthrough)
    break;
  }

//  if(htxn_document_)
//  {
//   if(GTagML_HTXN_Node* nhn = gtc->GTagML_htxn_node())
//   {
//    generate_tag_command_entry(b, *nhn);
//    check_generate_tag_command_argument(b, *gtc);
//    reset_active_gap_code();
//    break;
//   }
//  }

  if(gtc->flags.is_multi_mandatory)
  {
  }
  else if(gtc->flags.is_multi_optional)
  {
  }
  else
  {
   QString name;
   if(gtc->flags.command_name_written_to_main)
   {
    qDebug() << "to Main: " << gtc->latex_name();
   }
   if(GH_Prenode* ghp = gtc->name_prenode())
   {
    if(GH_Block_Base* ghb = ghp->get_block())
    {
     name = ghb->get_latex_out(ghp->range());
     name = GTagML_Tag_Command::latex_name(name);
    }
    else
    {
     // something's wrong ...
    }
   }
   else
     name = gtc->latex_name();
   if(gtc->flags.is_region)
    b.qts << "\\begin{" << name;
   else
     b.qts << '\\' << name;
  }
  reset_active_gap_code();
  break;
 }

 if(caon_ptr<tNode> n = qry_.Tag_Command_Annotation(b.node))
 {
  if(caon_ptr<tNode> mt = qry_.Tag_Command_Main_Tile(b.node))
  {
   if(caon_ptr<GTagML_Tile> nt = mt->GTagML_tile())
    tag_command_annotation(nt, n);
  }
 }

// check_generate_tag_command_argument(b, *gtc);
}

//void GTagML_Output_Latex::generate_tag_command_leave(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
//{
// HTXN_Node_Detail* nd = nhn.get_node_detail(htxn_document_);

// if(nd->flags.is_ghosted)
// {
//  if(nd->flags.region_main_preempts_wrap)
//    ; // nothing ...
//  else if(nd->flags.optional)
//  {
//   b.qts << ']';
//   reset_active_gap_code();
//  }
//  else
//  {
//   b.qts << '}';
//   reset_active_gap_code();
//  }
// }
// else if(nd->flags.ref_preempts_wrap)
// {
//  if(nd->flags.region)
//  {
//    // // should be some sort of whitespace flag ...
//   check_reconcile_gap(b, 10);  //? b.qts << '\n';
//   b.qts << "\\end{" << region_end_names_.take(nd) << '}';
//   reset_active_gap_code();
//  }
// }
// else if(nd->flags.region)
// {
//  if(nd->flags.main_only_block_environment)
//    check_reconcile_gap(b, 10);  //? b.qts << '\n';
//  b.qts << "\\end{" << region_end_names_.take(nd) << '}';
//  reset_active_gap_code();
// }
// else if(nd->flags.wmi_none)
//   ; // nothing
// else
// {
//  b.qts << '}';
//  reset_active_gap_code();
// }

// if(nd->flags.post_line_double_gap)
//   check_reconcile_gap(b, 20);  //? b.qts << "\n\n";
// else if(nd->flags.post_line_gap)
//   check_reconcile_gap(b, 10);  //? b.qts << '\n';
// else if(nd->flags.post_space_gap)
//   check_reconcile_gap(b, 1);  //? b.qts << ' ';
//}


void GTagML_Output_Latex::generate_tag_command_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> gtc)
{
 CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)

 if(b.cb)
 {
  if(b.cb->flags.has_post_callback)
  {
   b.cb->post_callback(b.qts, b.node,
     // // is b.prior_node different than before?
     b.prior_node, nullptr, b.index, b.cb);
  }
  if(!b.cb->flags.post_fallthrough)
   return;
 }

// if(htxn_document_)
// {
//  if(GTagML_HTXN_Node* nhn = gtc->GTagML_htxn_node())
//  {
//   generate_tag_command_leave(b, *nhn);
//   return;
//  }
// }

 if(gtc->flags.force_opt_split)
   ;
 else if(gtc->flags.is_non_wrapped)
   ;
 else if(gtc->flags.is_multi_optional
   || gtc->flags.is_layer_optional || gtc->flags.is_layer_main_optional)
   b.qts << ']';
 else if(gtc->flags.is_multi_mandatory)
   b.qts << '}';
 else if(gtc->flags.is_multi_parent)
   ;
 else if(gtc->flags.is_region)
   b.qts << "\\end{" << gtc->latex_name() << '}';
 else
   b.qts << '}';

 if(tile_whitespace_defers_.contains(gtc))
 {
  b.qts << tile_whitespace_defers_.take(gtc);
 }

 reset_active_gap_code();
}

void GTagML_Output_Latex::check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tile> tile)
{
 if(caon_ptr<tNode> wd = (tNode*) tile->whitespace_defer())
 {
  if(caon_ptr<GTagML_Tag_Command> gtc = wd->GTagML_tag_command())
  {
   GTagML_Output_Event_Handler::check_generate_whitespace(b.with(ws_qts_), tile);
   tile_whitespace_defers_[gtc] += ws_acc_;
   ws_acc_.clear();
   ws_qts_.reset();
  }
 }
 else
   GTagML_Output_Event_Handler::check_generate_whitespace(b, tile);
}

void GTagML_Output_Latex::check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Paralex_Tile> tile)
{
 GTagML_Output_Event_Handler::check_generate_whitespace(b, tile);
}

u1 GTagML_Output_Latex::get_ws_gap_code()
{
 return get_ws_gap_code(ws_acc_);
}

u1 GTagML_Output_Latex::get_ws_gap_code(const QString& str)
{
 if(str.endsWith("\n\n"))
   return 20;
 if(str.endsWith("\n"))
   return 10;
 if(str.endsWith("\n\n "))
   return 21;
 if(str.endsWith("\n "))
   return 11;
 if(str.endsWith(' '))
   return 1;
 return 0;
}


//void GTagML_Output_Latex::check_generate_whitespace(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
//{
// HTXN_Node_Detail* nd = nhn.get_node_detail(htxn_document_);
// if(!nd)
//   return;
// if(nd->flags.wmi_none)
//   return;
//  // // or take ws from the node detail?

// nhn.write_whitespace(ws_qts_); //b.qts);

// if(ws_acc_.isEmpty())
// {
//  ws_qts_.reset();
//  return;
// }

// u1 wsgc = get_ws_gap_code();

// if(active_gap_code_ == 0)
// {
//  active_gap_code_ = wsgc;
//  b.qts << ws_acc_;
//  ws_acc_.clear();
//  ws_qts_.reset();
//  return;
// }
// if(wsgc == 0)
// {
//  b.qts << ws_acc_;
//  ws_acc_.clear();
//  ws_qts_.reset();
//  reset_active_gap_code();
//  return;
// }

// u2 code = (active_gap_code_ * 100) + wsgc;

// switch (code)
// {
// case 2121:
//   ws_acc_.chop(3); break;
// case 2020:
// case 1111:
//   ws_acc_.chop(2); break;
// case 1010:
// case 101:
//   ws_acc_.chop(1); break;
// case 2010:
//   ws_acc_.chop(1); break;
// case 1020:
//   ws_acc_.chop(1); active_gap_code_ = 20; break;
// case 2110:
//   active_gap_code_ = 10; break;
// case 2120:
//   active_gap_code_ = 20; break;
// case 2111:
//   ws_acc_.chop(2); break;
// case 2101:
//   ws_acc_.chop(1); break;
// case 110:
//  active_gap_code_ = 10; break;
// case 111:
//  active_gap_code_ = 11; break;
// case 120:
//  active_gap_code_ = 20; break;
// case 121:
//  active_gap_code_ = 21; break;
// default:
//  reset_active_gap_code();
// }

// b.qts << ws_acc_;
// ws_acc_.clear();
// ws_qts_.reset();
//}

void GTagML_Output_Latex::check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> gtc)
{
 CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)
// if(htxn_document_)
// {
//  if(GTagML_HTXN_Node* nhn = gtc->GTagML_htxn_node())
//  {
//   check_generate_whitespace(b, *nhn);
//   return;
//  }
// }
 GTagML_Output_Event_Handler::check_generate_whitespace(b, gtc);
 //gtc->write_whitespace(b.qts);
}

//void GTagML_Output_Latex::generate_tag_body_leave(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
//{
// HTXN_Node_Detail* nd = nhn.get_node_detail(htxn_document_);

// if(nd->flags.is_ghosted)
//   ; // nothing
// else if(nd->flags.wmi_left)
//   ; // nothing
// else if(nd->flags.wmi_none)
// {
//   ; // nothing
// }
// else if(nd->flags.ref_preempts_wrap)
// {
//  if(nd->flags.region)
//  {
//   b.qts << '}';
//   reset_active_gap_code();
//  }
// }
// else if(nd->flags.region)
// {
//  b.qts << '}';
//  if(nd->flags.main_only_block_environment)
//  {
//    //?check_reconcile_gap(b, 10);  //?
//   b.qts << '\n';
//   active_gap_code_ = 10;
//  }
//  reset_active_gap_code();
// }
// else
// {
//  b.qts << '{';
//  reset_active_gap_code();
// }
//}

void GTagML_Output_Latex::generate_tag_body_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> gtc)
{
 CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)

// if(htxn_document_)
// {
//  if(GTagML_HTXN_Node* nhn = gtc->GTagML_htxn_node())
//  {
//   generate_tag_body_leave(b, *nhn);
//   return;
//  }
// }

 if(gtc->flags.force_opt_split)
   ;
 else if(gtc->flags.is_non_wrapped)
   ;
 else if(gtc->flags.is_multi_optional ||
   gtc->flags.is_layer_optional || gtc->flags.is_layer_main_optional)
   b.qts << '[';
 else if(gtc->flags.is_multi_mandatory)
   b.qts << '{';
 else if(gtc->flags.is_multi_parent)
   ;
 else if(gtc->flags.is_region)
   b.qts << '}';
 else
   b.qts << '{';

//?
 if(gtc->flags.tile_is_quasi_fiat)
   b.qts << '\\';

  // here?
 check_generate_tag_command_argument(b, *gtc);

 reset_active_gap_code();
}

caon_ptr<GTagML_Tag_Command_Callback> GTagML_Output_Latex::check_command_callback(caon_ptr<GTagML_Tag_Command> gtc)
{
 QString name = gtc->name();
 return callbacks_.value(name, caon_ptr<GTagML_Tag_Command_Callback> ( nullptr ));
}

