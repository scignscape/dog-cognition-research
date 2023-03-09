
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-output-blocks.h"

#include "gtagml-output-event-generator.h"
#include "kernel/document/gtagml-document.h"
#include "kernel/output/gtagml-output-bundle.h"
#include "tag-command/gtagml-tag-command.h"
#include "tile/gtagml-paralex-tile.h"

#include "tile/gtagml-tile.h"

#include "tag-command/gtagml-tag-command-callback.h"

#include "kernel/graph/gtagml-node.h"

#include "gh/gh-block-writer.h"

#include "gh/gh-prenode.h"
#include "gh/gh-block-base.h"


#include "textio.h"

USING_KANS(TextIO)

//?#include "ngml-htxn/ngml-htxn-node.h"


//#include "htxn/htxn-document-8b.h"
//#include "htxn/glyph-layer-8b.h"
//#include "htxn/infoset/sdi-callback-8b.h"


//?#include "gtagml-output-infoset.h"
//?#include "gtagml-output-htxn.h"

#include "gtagml/kernel/document/gtagml-project-info.h"

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


GTagML_Output_Blocks::GTagML_Output_Blocks(GTagML_Document& document, GH_Block_Writer* block_writer)
  :  GTagML_Output_Base(document), active_gap_code_(0), 
     suppress_node_(nullptr), infoset_(nullptr),
     last_ref_enter_(0), last_ref_leave_(0),
     block_writer_(block_writer), local_last_prenode_(nullptr)
{
 htxn_qts_.setString(&htxn_acc_);
 ws_qts_.setString(&ws_acc_);
 init_callbacks();

 // // two copies of the first ...
 marks_by_mode_.push_back(new QMap<u4, QPair<QString, u4>>);
 marks_by_mode_.push_back(marks_by_mode_.first());

 marks_by_mode_.push_back(new QMap<u4, QPair<QString, u4>>);
 marks_by_mode_.push_back(new QMap<u4, QPair<QString, u4>>);
 marks_by_mode_.push_back(new QMap<u4, QPair<QString, u4>>);
}

void GTagML_Output_Blocks::init_standard_8bit()
{
 block_writer_->init_standard_8bit();
 if(document_.divert())
   block_writer_->current_main_text_block()->
   set_divert_mode(GH_Block_Base::Divert_Sentence_Boundaries);
}

void GTagML_Output_Blocks::init_callbacks()
{
 #include "gtagml-output-callbacks-common.h"

 #include "gtagml-output-blocks.callbacks.h"
}

void GTagML_Output_Blocks::parse_main_block_text_commands(caon_ptr<GTagML_Node> node)
{
 auto& main_block_text_commands = document_.project_info()->main_block_text_commands();

 CAON_PTR_DEBUG(GTagML_Node ,node)
 if(caon_ptr<GTagML_Tag_Command> ntc = node->GTagML_tag_command())
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command ,ntc)
  QString value = ntc->argument();
  if(value.startsWith('@'))
    value = value.mid(1).prepend(document_.project_info()->root_folder());

  document_.project_info()->set_main_block_text_commands_file(value);

  QString lines;
  load_file(value, lines);
  QStringList qsl = lines.split('\n');
  for(QString line : qsl)
  {
   line = line.trimmed();
   if(line.isEmpty())
     continue;

   int ix = line.indexOf(" === ");
   if(ix == -1)
   {
    main_block_text_commands.insert(line, {{}, 0});
   }
   else
   {
    QString cmd = line.mid(0, ix);
    QString val = line.mid(ix + 5);
    main_block_text_commands.insert(cmd, {val, 0});
   }
  }
  //project_info_->add();
 }


}



GH_Block_Base* GTagML_Output_Blocks::get_current_mandatory_argument_block()
{
 return block_writer_->current_mandatory_argument_block();
}

void GTagML_Output_Blocks::mark_citation(QTextStream& qts, caon_ptr<tNode> node,
  caon_ptr<tNode> prior_node, caon_ptr<tNode> parent_of_siblings)
{
 GH_Prenode* pre = nullptr;

 // //? always?
 if(prior_node)
 {
  CAON_PTR_DEBUG(tNode ,prior_node)
  if(caon_ptr<GTagML_Tile> tile = prior_node->GTagML_tile())
  {
   CAON_PTR_DEBUG(GTagML_Tile ,tile)
   pre = tile->prenode();
  }
 }
 else if(parent_of_siblings)
 {
  CAON_PTR_DEBUG(tNode ,parent_of_siblings)
  if(caon_ptr<GTagML_Tag_Command> gtc = parent_of_siblings->GTagML_tag_command())
  {
   CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)
   pre = gtc->last_tile_prenode();
  }
 }

 if(!pre)
   return;

 QString citation_text;
 QString opt_text;

 if(caon_ptr<GTagML_Tag_Command> gtc = node->GTagML_tag_command())
 {
  CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)
  citation_text = gtc->argument();
  if(citation_text.isEmpty())
    return;

  opt_text = gtc->opt_argument();
 }

 document_.document_info().citations()[citation_text].push_back({opt_text, pre});

}



void GTagML_Output_Blocks::generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Attribute_Tile> tile)
{
}


void GTagML_Output_Blocks::write_block_output(QMap<QString, QString>& block_output)
{
 QTextStream qts(&summary_);
 generate(qts);
 //latex_output.replace(QRegularExpression("\\n{2,}"), "\n\n");
}

void GTagML_Output_Blocks::generate(QTextStream& qts)
{
 GTagML_Output_Event_Generator events(*this, *this);
 events.generate(qts);
}

void GTagML_Output_Blocks::load_marks(QString path)
{
 u4 current_index = 0;
 u1 current_mode = 0;
 u4 last_index = 0;
 u1 last_mode = 0;

 QMultiMap<QString, QString> info_params;

 QMap<QString, QStringList> citations;

 TextIO::load_file(path, [this, &info_params, &citations, &current_index,
   &current_mode, &last_index, &last_mode](QString& line) -> int
 {
  if(line.isEmpty())
    return 0;

  if(line.startsWith("$$ "))
  {
   if(line.endsWith(';'))
     line.chop(1);
   QStringList qsl = line.mid(3).trimmed().split(" := ", Qt::KeepEmptyParts);
   QString key = qsl.takeFirst();
   for(QString v : qsl)
     info_params.insert(key, v);
   return 0;
  }

  if(line.startsWith("$& "))
  {
   QStringList qsl = line.mid(3).trimmed().split(' ', Qt::SkipEmptyParts);
   QString citation_text = qsl.takeFirst();
   citation_text.replace("%%", " ");
   QString optarg = qsl.takeFirst();
   if(optarg == "%%")
     optarg.clear();
   optarg.prepend('[');
   optarg.append(']');
   if(qsl.size() >= 3)
   {
    QString layer_code = qsl.takeFirst();
    int index = layer_code.startsWith('(')? 1 : 0;
    QString summary = QString("%1=%2:%4-%3").arg(optarg)
      .arg(layer_code.mid(index, 1)).arg(qsl.takeFirst()).arg(qsl.takeFirst());
    citations[citation_text].push_back(summary);
   }
   return 0;
  }


  if(line.startsWith("= "))
  {
   line = line.mid(2).trimmed();
   if(line.endsWith(':'))
   {
    line.chop(1);
    last_index = current_index;
    current_index = line.toUInt();
   }
   else
   {
    last_mode = current_mode;
    current_mode = line.toUInt();
    if(current_mode == 9)
    {
     (*marks_by_mode_[last_mode])[last_index].second = current_index;
    }
   }
  }
  else
  {
   (*marks_by_mode_[current_mode])[current_index] = {line, 0};
  }
  return 0;
 });
}

QString GTagML_Output_Blocks::export_marks(QString path)
{
 QVector<QStringList>& marks = document_.document_info().marks();
 QMap<QString, QString>& params = document_.document_info().info_params();

 QMap<QString, QVector<QPair<QString, void*>>>& citations = document_.document_info().citations();

 u4 indices [5] {0,0,0,0,0};

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

 QFile outfile(path);
 if(outfile.open(QFile::WriteOnly | QIODevice::Text))
 {
  QTextStream qts(&outfile);

  {
   QMapIterator<QString, QString> it(params);
   while(it.hasNext())
   {
    it.next();
    qts << QString("$$ %1 := %2\n").arg(it.key()).arg(it.value());
   }
  }
  qts << "\n";
  {
   QMapIterator<QString, QVector<QPair<QString, void*>>> it(citations);
   while(it.hasNext())
   {
    it.next();
    for(QPair<QString, void*> pr : it.value())
    {
     GH_Prenode* pre = (GH_Prenode*) pr.second;
     QString k = it.key();
     k.replace(' ', "%%");
     QString opt = pr.first;
     if(opt.isEmpty())
       opt = "%%";
     else
       opt.replace(' ', "%%");

     qts << QString("$& %1 %2 %3\n").arg(k).arg(opt)
       .arg(pre->get_summary());

    }
   }
  }
  qts << "\n";
  for(u4 uu : special_flag_marks_)
  {
   if( (uu & 0x80000000) > 0 )
   {
    qts << QString("\n= %1:\n").arg(uu & 0x7FFFFFFF);
   }
   else
   {
    qts << QString("= %1\n").arg(uu);
    if(uu < 5)
    {
     qts << marks[uu][indices[uu]] << "\n";
     ++indices[uu];
    }
   }
  }
  return path;
 }

 return {};
}

QString GTagML_Output_Blocks::export_main_block(QString path)
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

 GH_Block_Base* gbb = block_writer_->current_main_text_block();

 gbb->write_to_file(path);

 return path;
}

void GTagML_Output_Blocks::export_blocks(QString path)
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

 QMap<QString, QString> _output;
 write_block_output(_output);

 // //temp
// latex_output.replace("@@", "%%");
// latex_output.replace("#{", "\\scaps{");
// latex_output.replace("}#", "}");

 QFile outfile(path);
 if(outfile.open(QFile::WriteOnly | QIODevice::Text))
 {
  outfile.write(summary_.toLatin1());
  outfile.close();
 }
}

void GTagML_Output_Blocks::handle_annotation(caon_ptr<GTagML_Tile> tile, caon_ptr<GTagML_Annotation_Tile> atile)
{
//? document_.tag_command_annotation(tile, atile);
}

void GTagML_Output_Blocks::check_reconcile_gap(const GTagML_Output_Bundle& b, u1 new_code)
{
 check_reconcile_gap(b, new_code, active_gap_code_);
}

void GTagML_Output_Blocks::check_reconcile_gap(const GTagML_Output_Bundle& b, u1 new_code, u1& result)
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


void GTagML_Output_Blocks::generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Paralex_Tile> tile)
{
// tile->write_latex(b.qts);
// check_generate_whitespace(b, tile);
// reset_active_gap_code();
}


//void GTagML_Output_Blocks::generate_tag_command_entry(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
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

//void GTagML_Output_Blocks::generate_tile_via_htxn(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
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

//void GTagML_Output_Blocks::generate_tag_command_argument(const GTagML_Output_Bundle& b,
//  GTagML_HTXN_Node& nhn)
//{
// HTXN_Node_Detail* nd = nhn.get_node_detail(htxn_document_);
// b.qts << (nd->flags.optional? '[' : '{');
// htxn_document_->write_minimal_latex_out(nd->get_layer(), nd->enter, nd->leave, b.qts);
// b.qts << (nd->flags.optional? ']' : '}');
//}

void GTagML_Output_Blocks::check_generate_tag_command_argument(const GTagML_Output_Bundle& b,
  GTagML_Tag_Command& gtc)
{
 if(!gtc.opt_argument().isEmpty())
 {
  QPair<u4, u4> pr;
  GH_Block_Base* bl =  block_writer_->write_optional_argument(gtc.opt_argument(), pr);//  write
  gtc.add_arg_prenode(bl, pr.first, pr.second);
 }
 if(!gtc.argument().isEmpty())
 {
  QPair<u4, u4> pr;
  GH_Block_Base* bl =  block_writer_->write_mandatory_argument(gtc.argument(), pr);//  write
  gtc.add_arg_prenode(bl, pr.first, pr.second);
 }
  // gtc.each_arg_GTagML_htxn_node(
// if(GTagML_HTXN_Node* nhn = gtc.arg_GTagML_htxn_node())
//   generate_tag_command_argument(b, *nhn);

// gtc.each_arg_GTagML_htxn_node([&b, this](GTagML_HTXN_Node* nhn)
// {
//  generate_tag_command_argument(b, *nhn);
// });
}

GTagML_Output_Blocks::~GTagML_Output_Blocks()
{
// qDebug() << "del GTagML_Output_Blocks";
}


void GTagML_Output_Blocks::generate_tile(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tile> tile)
{
 CAON_PTR_DEBUG(GTagML_Tile ,tile)
 QString rt = tile->raw_text();
 QPair<u4, u4> pr;

 QString bws = tile->get_block_whitespace();

 GH_Block_Base* bl =  block_writer_->write_tile(rt, bws, pr, &special_flag_marks_);//  write
 GH_Prenode* ghp = tile->init_prenode(bl, pr.first, pr.second);

 u4 layer_code = bl->layer_code();

 QMutableMapIterator<caon_ptr<GTagML_Tag_Command>,
   QPair<GH_Prenode*, QPair<u4, u4>>> it (ref_ranges_[layer_code]);

 while (it.hasNext())
 {
  it.next();
  if(it.value().second.first == 0)
    it.value().second.first = pr.first;
  it.value().second.second = pr.second;
  it.value().first = ghp;
 }


 if(last_ref_enter_ == 0)
   last_ref_enter_ = pr.first;
 last_ref_leave_ = pr.second;
}


void GTagML_Output_Blocks::generate_tag_command_entry(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> gtc)
{
 CAON_PTR_B_DEBUG(GTagML_Node ,node)
 CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)

 //QMap<QString, QPair<QString, u4>>*
 auto& main_block_text_commands = document_.project_info()->main_block_text_commands();

 caon_ptr<GTagML_Tag_Command_Callback> cb = b.cb;

 caon_ptr<GTagML_Node> parent_of_siblings = nullptr;

 switch(b.connection_descriptor)
 {
 case GTagML_Connection_Descriptor::Tag_Command_Cross_From_Blank:
 case GTagML_Connection_Descriptor::Tag_Command_Cross:
  // maybe set parent_of_siblings?
   parent_of_siblings = b.prior_cross_node;
   {
    if(parent_of_siblings)
    {
     if(caon_ptr<GTagML_Tag_Command> gtc = parent_of_siblings->GTagML_tag_command())
     {
      CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)
      CAON_DEBUG_NOOP
     }
    }
   }
   // fallthrough ...
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

  u4 layer_code = 0;

  if(gtc->flags.is_multi_mandatory)
  {
   if(gtc->flags.multi_main_layer)
     layer_code = block_writer_->push_main();
   else
     block_writer_->push_mandatory();
  }
  else if(gtc->flags.is_multi_optional)
  {
   layer_code = block_writer_->push_optional();
  }
  else
  {
   if(gtc->flags.is_layer_mandatory)
     layer_code = block_writer_->current_mandatory_argument_block()->layer_code();
   else if(gtc->flags.is_layer_optional)
     layer_code = block_writer_->current_optional_argument_block()->layer_code();
   else
     layer_code = block_writer_->current_main_text_block()->layer_code();

   QPair<u4, u4> pr;
   QString name = (cb && !cb->rename_tag().isEmpty())? cb->rename_tag() : gtc->name();

   auto it = main_block_text_commands.find(name);

   GH_Block_Base* bl;
   if(it == main_block_text_commands.end())
   {
    bl = block_writer_->write_tag_command_name(name, pr);//  write
   }
   else
   {
    QPair<QString, u4>& vpr = it.value();
    if(vpr.first.isEmpty())
    {
     bl = block_writer_->write_tag_command_name_as_main_text(name, pr);//  write
     gtc->flags.command_name_written_to_main = true;
     ++vpr.second;
    }
    else
    {
     bl = block_writer_->write_tag_command_name(name, pr);//  write
     // //  the text goes in the main block but is outside any tile/prenode
      //    so it's not visible anywhere in the PDF/etc. output ...
      //    just from transcriptions of the main block itself ...
     block_writer_->write_to_main(vpr.first);
    }

   }
   gtc->init_name_prenode(bl, pr);

  }

  check_generate_tag_command_argument(b, *gtc);

  if(!gtc->flags.is_self_closed)
    ref_ranges_[layer_code].insert(gtc, {nullptr, {0, 0}});

  reset_active_gap_code();

  if(gtc->flags.is_layer_optional)
    block_writer_->push_optional();
  else if(gtc->flags.is_layer_mandatory)
    block_writer_->push_mandatory();

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
}

//void GTagML_Output_Blocks::generate_tag_command_leave(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
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


void GTagML_Output_Blocks::generate_tag_command_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> gtc)
{
 CAON_PTR_DEBUG(GTagML_Tag_Command ,gtc)

 if(gtc->flags.has_boundary_white_whitespace)
   block_writer_->write_boundary_whitespace(" ");


 u4 expected_layer_code = 1;

 if(gtc->flags.is_layer_optional)
   expected_layer_code = 2;

 else if(gtc->flags.is_layer_mandatory)
   expected_layer_code = 3;

 if(ref_ranges_[expected_layer_code].contains(gtc))
 {
  QPair<GH_Prenode*, QPair<u4, u4>> pr = ref_ranges_[expected_layer_code].take(gtc);
  gtc->set_ref_enter(pr.second.first);
  gtc->set_ref_leave(pr.second.second);
  gtc->set_last_tile_prenode(pr.first);
 }

 if(gtc->flags.is_multi_optional)
   block_writer_->pop_optional();
 else if(gtc->flags.is_multi_mandatory)
 {
  if(gtc->flags.multi_main_layer)
    block_writer_->pop_main();
  else
    block_writer_->pop_mandatory();
 }

 if(gtc->flags.is_layer_optional)
   block_writer_->pop_optional();

 else if(gtc->flags.is_layer_mandatory)
   block_writer_->pop_mandatory();


 if(b.cb)
 {
  if(b.cb->flags.has_post_callback)
  {
   // prior_node changed?
   b.cb->post_callback(b.qts, b.node, b.prior_node, nullptr, b.index, b.cb);
  }
  if(!b.cb->flags.post_fallthrough)
   return;
 }

// if(htxn_document_)
// {
//  if(GTagML_HTXN_Node* nhn = gtc->GTagML_HTXN_Node())
//  {
//   generate_tag_command_leave(b, *nhn);
//   return;
//  }
// }

 reset_active_gap_code();
}

void GTagML_Output_Blocks::check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tile> tile)
{
 GTagML_Output_Event_Handler::check_generate_whitespace(b, tile);
}

void GTagML_Output_Blocks::check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Paralex_Tile> tile)
{
 GTagML_Output_Event_Handler::check_generate_whitespace(b, tile);
}

u1 GTagML_Output_Blocks::get_ws_gap_code()
{
 return get_ws_gap_code(ws_acc_);
}

u1 GTagML_Output_Blocks::get_ws_gap_code(const QString& str)
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


//void GTagML_Output_Blocks::check_generate_whitespace(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
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

void GTagML_Output_Blocks::check_generate_whitespace(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> gtc)
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


//?   GTagML_Output_Event_Handler::check_generate_whitespace(b, gtc);
 //gtc->write_whitespace(b.qts);
}

//void GTagML_Output_Blocks::generate_tag_body_leave(const GTagML_Output_Bundle& b, GTagML_HTXN_Node& nhn)
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

void GTagML_Output_Blocks::generate_tag_body_leave(const GTagML_Output_Bundle& b, caon_ptr<GTagML_Tag_Command> gtc)
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

// if(gtc->flags.is_region)
//   b.qts << '}';
// else
//  b.qts << '{';

 reset_active_gap_code();
}

caon_ptr<GTagML_Tag_Command_Callback> GTagML_Output_Blocks::check_command_callback(caon_ptr<GTagML_Tag_Command> gtc)
{
 QString name = gtc->name();
 return callbacks_.value(name, caon_ptr<GTagML_Tag_Command_Callback> ( nullptr ));
}

