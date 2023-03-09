
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ngml-sdi-document.h"

#include "ngml-sdi-element.h"
#include "ngml-sdi-page.h"

#include "ngml-sdi-paragraph.h"
#include "ngml-sdi-sentence.h"

//#include "ntxh-parser/ntxh-document.h"


#include "global-types.h"

#include "textio.h"

#ifdef USING_ZIP
#include "quazip/quazip.h"
#include "quazip/quazipfile.h"
#endif // def USING_ZIP

USING_KANS(TextIO)

#include "dgh-sdi/dgh-sdi-paragraph.h"
#include "dgh-sdi/dgh-sdi-sentence.h"


USING_KANS(DGH)

#include <QDir>

typedef NTXH_Graph::hypernode_type hypernode_type;

NGML_SDI_Document::NGML_SDI_Document(QString path, QString folder)
  :  path_(path), folder_(folder), global_base_line_skip_(12.), global_base_line_stretch_(1.),
     carried_paragraph_id_(0), carried_sentence_id_(0), current_parse_paragraph_(nullptr)
{
}


void NGML_SDI_Document::load_prelatex_files(QStringList paths)
{
 for(QString p : paths)
 {
  qDebug() << "Loading prelatex file: " << p;
  load_prelatex_file(p);
 }
}

void NGML_SDI_Document::load_prelatex_file(QString path)
{
 NTXH_Document doc(path);

 doc.parse();

 typedef NTXH_Graph::hypernode_type hypernode_type;

 NTXH_Graph& g = *doc.graph();
 const QVector<hypernode_type*>& v = g.hypernodes();

 qDebug() << "Parse: " << path << " -- " << v.size() << " nodes ...";

 u4 i = 0;

 prelatex_files_.push_back(path);
 u4 file_id = prelatex_files_.size();

 QFileInfo qfi(path);

 QString bn = qfi.completeBaseName();

 if(bn.endsWith(".sdi-prelatex"))
   bn.chop(13);

 prelatex_file_ids_[bn] = file_id;

 file_job_name_by_file_id_[file_id] = bn;

// n8 bls = 12; // default ...

 DGH_SDI_Paragraph* dsp;

 for(hypernode_type* h : v)
 {
  if(h->type_descriptor().first == "GH_SDI_Paragraph")
    g.get_sfsr(h, {{1, 4}}, [this, &dsp](QVector<QPair<QString, void*>>& prs)
    {
     u4 id = prs[0].first.toInt();
     QString j = prs[1].first;
     u4 s = prs[2].first.toInt();
     u4 e = prs[3].first.toInt();

     u4 fid = prelatex_file_ids_[j];
//     int ix = j.indexOf('-');
//     int jid = j.mid(ix).toInt();
//     j = j.left(ix);

     dsp = new DGH_SDI_Paragraph(fid, id);

     gh_sdi_paragraph_info_[dsp] = {s, e};
     dgh_paragraphs_[j][id] = dsp;
    });

  else if(h->type_descriptor().first == "GH_SDI_Sentence")
    g.get_sfsr(h, {{1, 4}}, [this, dsp](QVector<QPair<QString, void*>>& prs)
    {
     u4 id = prs[0].first.toInt();
     u4 p = prs[1].first.toInt();
     u4 s = prs[2].first.toInt();
     u4 e = prs[3].first.toInt();
     gh_sdi_sentence_info_[{dsp->file_id(), id}] = {{dsp, p}, {s, e}};
    });
 }

#ifdef HIDE
 load_file(path, [this](QString& line)
 {
  if(line.isEmpty())
    return 0;
  if(!line.startsWith('\\'))
  {
   prelatex_lines_.push_back(line.simplified());
   return 0;
  }
  const QChar qc = line.at(1);
  if(qc == '>')
  {
   prelatex_[';'].push_back(line.mid(3).toInt() - 1);
   prelatex_['+'].push_back(line.mid(3).toInt() + 2);
  }
  else
    prelatex_[qc].push_back(line.mid(3).toInt());
//  QStringList qsl = line.simplified().split(' ');
//  prelatex_[qsl.first] = qsl.value(1).toInt();
  return 0;
 }); 
#endif //def HIDE
}

NGML_SDI_Page* NGML_SDI_Document::get_page(u4 page)
{
 NGML_SDI_Page* result = pages_.value(page - 1);
 if(!result)
 {
  result = new NGML_SDI_Page(page);
  if(page >= pages_.size())
    pages_.resize(page);
  pages_[page - 1] = result;
 }
 return result;
}

r8 NGML_SDI_Document::ptstring_to_r8(QString str, r8 default_value)
{
 if(str.isEmpty())
   return default_value;
 if(str.endsWith("pt"))
   str.chop(2);
 bool ok = false;
 r8 result = str.toDouble(&ok);
 if(ok)
   return result;
 return default_value;
}

u4 NGML_SDI_Document::half_base_line_stretch()
{
 return half_base_line_stretch(global_base_line_skip_, global_base_line_stretch_);
}

u4 NGML_SDI_Document::half_base_line_stretch(n8 bls)
{
 return half_base_line_stretch(bls, global_base_line_stretch_);
}


u4 NGML_SDI_Document::half_base_line_stretch(n8 bls, r8 blt)
{
 return (u4) (( (r8) bls * blt) / 2);
}


void NGML_SDI_Document::parse_element_start_hypernode(NTXH_Graph& g, hypernode_type* hn)
{
 NGML_SDI_Element* nsel = new NGML_SDI_Element();
 g.get_sfsr(hn, {{2,10}}, [this, nsel](QVector<QPair<QString, void*>>& prs)
 {
  //:n:1 :i:2 :o:3 :c:4 :r:5 :k:6 :p:8 :x:9 :y:10 :b:7 ;
  u4 id = prs[0].first.toInt();
  
  QString line = prelatex_lines_.value(id - 1);
  QStringList qsl = line.split(' ');

  if(qsl.size() >= 2) // //  otherwise something's wrong
  {
   nsel->set_start_index(qsl[1].toInt());
   nsel->set_end_index(qsl[2].toInt());   
  }

  // // qsl[0] is name ...

//  QChar ccue = nsel->get_command_cue();
//  if(ccue == '@')
//  {
//   prelatex_lines_
//  }
//  else
//    nsel->set_start_index(prelatex_[ccue].value(id - 1));

  nsel->set_id(id);

  nsel->set_kind(prs[4].first);
  

  // //  assume that everything is in pts for now ...
  QString sx = prs[7].first;
  if(sx.endsWith("pt"))
    sx.chop(2);

  QString sy = prs[8].first;
  if(sy.endsWith("pt"))
    sy.chop(2);

  u4 start_x = (int) sx.toDouble();
  u4 start_y = (int) sy.toDouble();

  if(prs[5].first.isEmpty())
    start_y += half_base_line_stretch();
  else
  {
   QString bb = prs[5].first;
   qDebug() << "Using special skip: " << bb;
   QStringList qsl = bb.split(';');
   QString b = qsl.takeFirst();
   r8 bls = ptstring_to_r8(b, global_base_line_skip_);
   if(qsl.isEmpty())
     start_y += half_base_line_stretch(bls);
   else
     start_y += half_base_line_stretch(bls, ptstring_to_r8(qsl.first(), 1.));
  }    

  nsel->set_start_x(start_x);
  nsel->set_start_y(start_y);
 
  u4 pg = prs[6].first.toInt();

//  qDebug() << "on page ..." << pg;

  this->open_elements_[{"NGML_SDI_Element", id}] = {nsel, pg};


 });

// qDebug() << "parse_element_start_hypernode()";
}

void NGML_SDI_Document::parse_element_end_hypernode(NTXH_Graph& g, hypernode_type* hn)
{
 g.get_sfsr(hn, {{2,6}}, [this](QVector<QPair<QString, void*>>& prs)
 {
  //:i:2 :o:3 :p:4 :x:5 :y:6 ;
  u4 id = prs[0].first.toInt();

  void* pv = this->open_elements_.value({"NGML_SDI_Element", id}).first;

  u4 pg = this->open_elements_.value({"NGML_SDI_Element", id}).second;

  if(!pv)
    return;

  NGML_SDI_Element* nsel = static_cast<NGML_SDI_Element*>(pv);

//  QChar ccue = nsel->get_command_end_cue();
//  nsel->set_end_index(prelatex_[ccue].value(id - 1));

  // //  assume that everything is in pts for now ...
  QString ex = prs[3].first;
  if(ex.endsWith("pt"))
    ex.chop(2);

  QString ey = prs[4].first;
  if(ey.endsWith("pt"))
    ey.chop(2);

  u4 end_x = (int) ex.toDouble();
  u4 end_y = (int) ey.toDouble();
  nsel->set_end_x(end_x);
  nsel->set_end_y(end_y);

  NGML_SDI_Page* page = this->get_page(pg);
  page->add_page_element(nsel);

 });
// qDebug() << "parse_element_end_hypernode()";
}

template<typename T>
void generic_start(NGML_SDI_Document& nsd, T& obj, 
  QVector<QPair<QString, void*>>& prs, u1 xy_pos, u1 b_pos)
{
 QChar ccue = obj.get_command_cue();
 obj.set_start_index(nsd.review()[ccue].value(obj.id() - 1));

 // //  assume that everything is in pts for now ...
 QString sx = prs[xy_pos].first;
 if(sx.endsWith("pt"))
   sx.chop(2);

 QString sy = prs[xy_pos + 1].first;
 if(sy.endsWith("pt"))
   sy.chop(2);

 u4 start_x = (int) sx.toDouble();
 u4 start_y = (int) sy.toDouble();

 // //  go from bottom of line to top ...
 if(prs[b_pos].first.isEmpty())
    start_y += nsd.half_base_line_stretch();
 else
 {
  QString bb = prs[5].first;
  qDebug() << "Using special skip: " << bb;
  QStringList qsl = bb.split(';');

  QString b = qsl.takeFirst();
  r8 bls = nsd.ptstring_to_r8(b, nsd.global_base_line_skip());
  if(qsl.isEmpty())
    start_y += nsd.half_base_line_stretch(bls);
  else
    start_y += nsd.half_base_line_stretch(bls, nsd.ptstring_to_r8(qsl.first(), 1.));
 }    

 obj.set_start_x(start_x);
 obj.set_start_y(start_y);
}

void NGML_SDI_Document::review_dgh()
{
 QMapIterator<QString, QMap<u4, DGH_SDI_Paragraph*>> it (dgh_paragraphs_);
 while(it.hasNext())
 {
  it.next();
  QMapIterator<u4, DGH_SDI_Paragraph*> it1(it.value());
  while(it1.hasNext())
  {
   it1.next();
   qDebug() << it.key() << " (" << it1.key() << "):";
   qDebug() << " " << it1.value()->get_summary();
  }
 }

// for(DGH_SDI_Paragraph* dsp : dgh_paragraphs_)
// {
//  qDebug() << dsp->get_summary();
// }
}

void NGML_SDI_Document::output_dgh(QString path)
{
 QFile outfile(path);
 if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text))
   return;
 QTextStream outstream(&outfile);

 outstream << R"(

&type DGH_SDI_Paragraph {13}
  :i:1 :j:2 :p:3 :s:4 :e:5 :x:6 :y:7
  :ex:8 :ey:9 :o:10 :f:11 :d:12 ;

&type DGH_SDI_Sentence {10}
  :i:1 :p:2 :s:3 :e:4 :x:5 :y:6
  :ex:7 :ey:8 :f:9 :d:10 ;

&/
 )";

 QMapIterator<QString, QMap<u4, DGH_SDI_Paragraph*>> it (dgh_paragraphs_);
 while(it.hasNext())
 {
  it.next();
  QMapIterator<u4, DGH_SDI_Paragraph*> it1(it.value());
  while(it1.hasNext())
  {
   it1.next();

   DGH_SDI_Paragraph* dsp = it1.value();
   NGML_SDI_Paragraph* nsp = dsp->ngml();

   if(!nsp)
     continue;

   QString pf = file_job_name_by_file_id_.value(dsp->file_id());

   outstream << QString(R"(
!/ DGH_SDI_Paragraph
$i: %1
$j: %2
$p: %3
$s: %4
$e: %5
$x: %6
$y: %7
$ex: %8
$ey: %9)")
   .arg(nsp->id())
   .arg(pf)
   .arg(dsp->page())
   .arg(nsp->start_index())
   .arg(nsp->end_index())
   .arg(nsp->start_x())
   .arg(nsp->start_y())
   .arg(nsp->end_x())
   .arg(nsp->end_y())
  ;

  outstream << QString(R"(
$o: %1
$f: %2
$d: %3
/!
<+>

)").arg(dsp->order_in_page()).arg(dsp->in_file_id()).arg(dsp->file_id());


   QVector<DGH_SDI_Sentence*>& ss = sentences_[dsp];

   for(DGH_SDI_Sentence* dss : ss)
   {
    NGML_SDI_Sentence* nss = dss->ngml();
    outstream << QString(R"(
!/ DGH_SDI_Sentence
$i: %1
$p: %2
$s: %3
$e: %4
$x: %5
$y: %6
$ex: %7
$ey: %8)")
    .arg(nss->id())
    .arg(dss->page())
    .arg(nss->start_index())
    .arg(nss->end_index())
    .arg(nss->start_x())
    .arg(nss->start_y())
    .arg(nss->end_x())
    .arg(nss->end_y())
   ;

 outstream << QString(R"(
$f: %1
$d: %2
/!
<+>

)").arg(dss->in_file_id()).arg(dss->file_id());

   }

  } 
 }

 outstream << R"(

/&
)";

}

void NGML_SDI_Document::merge_dgh()
{
 QMapIterator<DGH_SDI_Paragraph*, QPair<u4, u4>> it(gh_sdi_paragraph_info_);

// u4 par_order = 0;
 while(it.hasNext())
 {
  it.next();

  DGH_SDI_Paragraph* dsp = it.key();

  NGML_SDI_Paragraph* nsp = dsp->ngml();

  if(nsp)
  {
   nsp->set_start_index(it.value().first);
   nsp->set_end_index(it.value().second);
   nsp->set_file_id(dsp->file_id());
   nsp->page_object()->check_add_file_id(nsp->current_jobname(), dsp->file_id());
  }

  QVector<DGH_SDI_Sentence*> ss = sentences_.value(dsp);

  for(DGH_SDI_Sentence* dss : ss)
  {
   NGML_SDI_Sentence* nss = dss->ngml();

   const QPair<QPair<DGH_SDI_Paragraph*, u4>, QPair<u4, u4>>& prpr =
     gh_sdi_sentence_info_.value({dss->file_id(), dss->in_file_id()});

//   if(prpr.first.first != current_parse_paragraph_)
//   {
//    qDebug() << "Mismatched paragraphs ...";
//    return;
//   }

   nss->set_start_index(prpr.second.first);
   nss->set_end_index(prpr.second.second);
  }
//  ++par_order;
 }
// for(DGH_SDI_Paragraph* dsp : dgh_paragraphs_)
// {
//  qDebug() << dsp->get_summary();
// }

  // // check for pages with no new paragraphs therefore no job name ...
 QString held_last_job_name = "?";
 u4 last_file_id = 0;
 for(NGML_SDI_Page* page_object : pages_)
 {
  u4 fid = 0;
  QString jn = page_object->last_job_name(fid);
  if(jn.isEmpty())
  {
   page_object->add_job_name(held_last_job_name, last_file_id);
   continue;
  }
  held_last_job_name = jn;
  last_file_id = fid;
 }
}


void NGML_SDI_Document::parse_paragraph_start_hypernode(NTXH_Graph& g, hypernode_type* hn)
{
 NGML_SDI_Paragraph* nsp = new NGML_SDI_Paragraph();
// DGH_SDI_Paragraph* dsp = new DGH_SDI_Paragraph(nsp);
// this->dgh_paragraphs_.push_back(dsp);

 g.get_sfsr(hn, {{2,9}}, [this, nsp](QVector<QPair<QString, void*>>& prs)
 {
  // :n:1 :i:2 :o:3 :p:5 :j:6 :x:7 :y:8 :b:4 ;
  u4 id = prs[0].first.toInt();
  nsp->set_id(id);

  generic_start(*this, *nsp, prs, 6, 2);

  u4 rank_in_pg = prs[1].first.toInt(); // prs[3] or [4] ?
  u4 pg = prs[3].first.toInt(); // prs[3] or [4] ?

  this->open_elements_[{"NGML_SDI_Paragraph", id}] = {nsp, pg};

  QString cj = prs[4].first; // prs[3] or [4] ?

  nsp->set_current_jobname(cj);
  //dsp->set_page()

  int jid = prs[5].first.toInt();

  //u4 file_id = prelatex_file_ids_.value(cj);

  //u4 jid = ++counts_by_file_job_name_[cj][0];

  current_parse_paragraph_ = dgh_paragraphs_[cj][jid];

  if(current_parse_paragraph_)
  {
   current_parse_paragraph_->set_ngml(nsp);
   current_parse_paragraph_->set_page(pg);
   current_parse_paragraph_->set_order_in_page(rank_in_pg);
  }
  else
  {
   qDebug() << "Failed to properly find dsp ...";
  }

  NGML_SDI_Page* page = this->get_page(pg);
  page->check_add_job_name(cj);
//?  page->add_page_element(nsp);
  nsp->set_page_object(page);

 });
 // // qDebug() << "parse_paragraph_start_hypernode()";
}

void NGML_SDI_Document::parse_sentence_start_hypernode(NTXH_Graph& g, NTXH_Graph::hypernode_type* hn)
{
 NGML_SDI_Sentence* nss = new NGML_SDI_Sentence();
 nss->set_file_id(current_parse_paragraph_->file_id());
 g.get_sfsr(hn, {{2,10}}, [this, nss](QVector<QPair<QString, void*>>& prs)
 {
  // :n:1 :i:2 :r:3 :c:4 :o:5 :p:7 :f:8 :x:9 :y:10 :b:6 ;
  u4 id = prs[0].first.toInt();
  nss->set_id(id);

  generic_start(*this, *nss, prs, 7, 4);

  u4 in_f_id = prs[6].first.toInt();
  u4 f_id = current_parse_paragraph_->file_id();


  u4 pg = prs[5].first.toInt();

  this->open_elements_[{"NGML_SDI_Sentence", id}] = {nss, pg};

  DGH_SDI_Sentence* dss = new DGH_SDI_Sentence(nss, in_f_id, f_id, pg);

  sentences_[current_parse_paragraph_].push_back(dss);

//  NGML_SDI_Page* page = this->get_page(pg);
//  page->add_page_element(nss);
 });
}


template<typename T>
void generic_end(NGML_SDI_Document& nsd, T& obj, 
  QVector<QPair<QString, void*>>& prs, u1 xy_pos)
{
 QChar ccue = obj.get_command_end_cue();
 obj.set_end_index(nsd.review()[ccue].value(obj.id() - 1));

 // //  assume that everything is in pts for now ...
 QString ex = prs[xy_pos].first;
 if(ex.endsWith("pt"))
   ex.chop(2);

 QString ey = prs[xy_pos + 1].first;
 if(ey.endsWith("pt"))
   ey.chop(2);

 u4 end_x = (int) ex.toDouble();
 u4 end_y = (int) ey.toDouble();
 obj.set_end_x(end_x);
 obj.set_end_y(end_y);
}

void NGML_SDI_Document::parse_sentence_end_hypernode(NTXH_Graph& g, NTXH_Graph::hypernode_type* hn)
{
 g.get_sfsr(hn, {{2,6}}, [this](QVector<QPair<QString, void*>>& prs)
 {
  // :n:1 :i:2 :o:3 :p:4 :x:5 :y:6 ;
  u4 id = prs[0].first.toInt();

  void* pv = this->open_elements_.value({"NGML_SDI_Sentence", id}).first;
  if(!pv)
    return;
  NGML_SDI_Sentence* nss = static_cast<NGML_SDI_Sentence*>(pv);

  generic_end(*this, *nss, prs, 3);//  QChar ccue = nsel->get_command_end_cue();

  u4 pg = this->open_elements_.value({"NGML_SDI_Sentence", id}).second;
  NGML_SDI_Page* page = this->get_page(pg);
  page->add_page_element(nss);

  // // clean up open elements?

 });
}


void NGML_SDI_Document::parse_paragraph_end_hypernode(NTXH_Graph& g, hypernode_type* hn)
{
 g.get_sfsr(hn, {{2,6}}, [this](QVector<QPair<QString, void*>>& prs)
 {
  //:i:2 :o:3 :p:4 :x:5 :y:6 ;
  u4 id = prs[0].first.toInt();

  void* pv = this->open_elements_.value({"NGML_SDI_Paragraph", id}).first;
  if(!pv)
    return;
  NGML_SDI_Paragraph* nsp = static_cast<NGML_SDI_Paragraph*>(pv);

  generic_end(*this, *nsp, prs, 3);//  QChar ccue = nsel->get_command_end_cue();

  u4 pg = this->open_elements_.value({"NGML_SDI_Paragraph", id}).second;
  NGML_SDI_Page* page = this->get_page(pg);
  page->add_page_element(nsp);

  // // clean up open elements?

 });
 // // qDebug() << "parse_paragraph_end_hypernode()";
}

void NGML_SDI_Document::parse_info_hypernode(NTXH_Graph& g, hypernode_type* hn)
{
 qDebug() << "parse_info_hypernode()";
 g.get_sfs(hn, {2,3}, [this](QVector<QPair<QString, void*>>& prs)
 {
  r8 bls = ptstring_to_r8(prs[0].first, global_base_line_skip_);
  global_base_line_skip_ = bls;
  r8 blt = ptstring_to_r8(prs[1].first, global_base_line_stretch_);
  global_base_line_stretch_ = blt;
 });
}


void NGML_SDI_Document::parse()
{
 QMap<QString, void(NGML_SDI_Document::*)(NTXH_Graph& g, hypernode_type*)> methods {
  {"Info", &NGML_SDI_Document::parse_info_hypernode},

  {"Paragraph:Start",
    &NGML_SDI_Document::parse_paragraph_start_hypernode},

  {"Paragraph:End",
    &NGML_SDI_Document::parse_paragraph_end_hypernode},


  {"Sentence:Start",
    &NGML_SDI_Document::parse_sentence_start_hypernode},

  {"Sentence:End",
    &NGML_SDI_Document::parse_sentence_end_hypernode},


  {"Element:Start",
    &NGML_SDI_Document::parse_element_start_hypernode},

  {"Element:End",
    &NGML_SDI_Document::parse_element_end_hypernode},

//"Sentence:Start"
//"Sentence:End"
//"Sentence:Start"
//"Sentence:End"
//"Paragraph:End"
 };

 NTXH_Document doc(path_);

 doc.parse();

 typedef NTXH_Graph::hypernode_type hypernode_type;

 NTXH_Graph& g = *doc.graph();
 const QVector<hypernode_type*>& v = g.hypernodes();

 qDebug() << "Parse: " << path_ << " -- " << v.size() << " nodes ...";

 u4 i = 0;

// n8 bls = 12; // default ... 

 for(hypernode_type* h : v)
 {
//  QString name;
  g.get_sf(h, 1, [this, &methods, &g, h](QPair<QString, void*>& pr)
  {
   auto it = methods.find(pr.first);
   if(it != methods.end())
   {
    (this->**it)(g, h);
   }
  });

//  g.get_sf(h, 2, [](QPair<QString, void*>& pr)
//  {
//   sent.set_corpus_name(pr.first);
//  });

#ifdef HIDE
  g.get_sf(h, 3, [](QPair<QString, void*>& pr)
  {
//   sent.set_sxp_text(pr.first);
  });

  g.get_sf(h, 4, [](QPair<QString, void*>& pr)
  {
//   sent.set_latex_out_file(pr.first);
  });

  g.get_sf(h, 5, [](QPair<QString, void*>& pr)
  {
//   qts << pr.first << "\n\n";
  });
#endif
 } 

//? output_pages();
}

void NGML_SDI_Document::output_pages(QStringList htxn_files, QStringList marks_files, QString mergefile)
{
 QDir qd(folder_);

 if(pages_folder_.isEmpty())
 {
  qd.mkdir("pages");
  qd.cd("pages");
  pages_folder_ = qd.absolutePath();
 }
 else
 {
  qd.mkpath(pages_folder_);
  qd.cd(pages_folder_);
 }


 QList<QPair<QString, QPair<QString, QString>>> files;

 for(NGML_SDI_Page* page : pages_)
 {
  QString fn = QString::number(page->number());
  fn.prepend('p');
  fn.append(".txt");
  QString ffn = qd.absoluteFilePath(fn);
  qDebug() << "Page file: " << ffn;
  QString contents;
  page->write(contents);
  save_file(ffn, contents);
  files.push_back({ffn, {qd.dirName() + "/" + fn, fn}});
 }

#ifdef USING_ZIP
 if(zip_path_.isEmpty())
   zip_path_ = pages_folder_ + ".sdi.zip";

 QFileInfo qfi(zip_path_);
 zip_path_ = qfi.absoluteFilePath();

 qDebug() << "Using zip path: " << zip_path_;

 if(!mergefile.isEmpty())
   files.push_back({mergefile, {"pages/sdi-merge.ntxh", "sdi-merge.ntxh"}});

 for(QString hf : htxn_files)
 {
  QFileInfo qfi(hf);
  QString hn = qfi.baseName() + ".htxn";
  files.push_back({hf, {"pages/" + hn, hn}});
 }

 for(QString mf : marks_files)
 {
  QFileInfo qfi(mf);
  QString mn = qfi.baseName() + ".marks.txt";
  files.push_back({mf, {"pages/" + mn, mn}});
 }


 QuaZip zip(zip_path_);
 zip.setFileNameCodec("IBM866");

 if (!zip.open(QuaZip::mdCreate)) 
 {
  qDebug() << "Zip open failed ...";
 }

 QFile inFile;
 QuaZipFile outFile(&zip);
 
 char c;
 int j = 0;
 
 for(QPair<QString, QPair<QString, QString>> pr : files)
 {
//  qDebug() << "PR: " << pr;

  inFile.setFileName(pr.first);
  if (!inFile.open(QIODevice::ReadOnly))
  {  
   qDebug() << "Infile open failed ...";
   continue;
  }

  QuaZipNewInfo qni = QuaZipNewInfo(pr.second.first, pr.second.second);
  qni.setFilePermissions(pr.first);

  if (!outFile.open(QIODevice::WriteOnly, qni))
  {
   qDebug() << "Outfile open failed ...";
   continue; 
  }
 
  while (inFile.getChar(&c))
    outFile.putChar(c);
 
  if (outFile.getZipError() != ZIP_OK)
  {
   qDebug() << "Outfile write failed ...";   
   continue;
  }
  outFile.close();
 
  if (outFile.getZipError() != ZIP_OK)
  {
   qDebug() << "Outfile close failed ...";   
   continue; 
  }

  inFile.close();
 }
 
 zip.close();
 
 if (zip.getZipError() != 0)
   qDebug() << "Zip failed ...";

#ifdef HIDE
 //QString copy_path_;// = folder_ + "/../../test/" + qd.dirName() + ".sdi.zip";
 QString unzip_path = folder_ + "/../../test/test";

 //qDebug() << new_path;

 if(!copy_path_.isEmpty())
 {
  if(QFile::exists(copy_path_))
  {
   QFile::remove(copy_path_);
  }
  qDebug() << "Copying ... " << zip_path_ << " to " << copy_path_;
  QFile::copy(zip_path_, copy_path_); 

  if(!unzip_test_path_.isEmpty())
    check_read_page(copy_path_, unzip_test_path_, qd.dirName(), 1);
 }
#endif // HIDE
#endif //def USING_ZIP
}

NGML_SDI_Page* NGML_SDI_Document::check_read_page(QString zip_file_path, 
  QString unzip_path, QString unzip_folder_name, u4 page_number)
{
 check_unzip_folder(zip_file_path, unzip_path, unzip_folder_name);
 QDir dir(*unzip_folder_);
 QString path = dir.absoluteFilePath(QString("p%1.txt").arg(page_number));
 NGML_SDI_Page* result = new NGML_SDI_Page(page_number);
 load_file(path, [result](QString& line) -> n8
 {
  if(line.isEmpty())
    return 0;
  QStringList nums = line.simplified().split(' ');
  if(nums.length() < 6)
    return 1; // malformed; stop reading
  result->read_page_element_from_strings(nums);   
 });

 return result;
 //qDebug() << "Text: " << text;
}

void NGML_SDI_Document::check_unzip_folder(QString zip_file_path, 
  QString unzip_path, QString unzip_folder_name)
{
 if(unzip_folder_)
   return;

#ifdef USING_ZIP
 QDir dir(unzip_path);
 dir.mkdir(unzip_folder_name);
 unzip_folder_ = new QString(dir.absoluteFilePath(unzip_folder_name));

 QuaZip zip(zip_file_path);

 if (!zip.open(QuaZip::mdUnzip)) 
 {
  qWarning("testRead(): zip.open(): %d", zip.getZipError());
  return;
 }

 zip.setFileNameCodec("IBM866");

 qWarning("%d entries\n", zip.getEntriesCount());
 qWarning("Global comment: %s\n", zip.getComment().toLocal8Bit().constData());

 QuaZipFileInfo info;

 QuaZipFile file(&zip);

 QFile out;
 QString name;
 char c;
 for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()) 
 {
  if (!zip.getCurrentFileInfo(&info)) 
  {
   qWarning("testRead(): getCurrentFileInfo(): %d\n", zip.getZipError());
  }
  if (!file.open(QIODevice::ReadOnly)) 
  {
   qWarning("testRead(): file.open(): %d", file.getZipError());
   return;
  }

  name = QString("%1/%2").arg(unzip_path).arg(file.getActualFileName());

  qDebug() << "Name: " << name;

  if (file.getZipError() != UNZ_OK) 
  {
   qWarning("testRead(): file.getFileName(): %d", file.getZipError());
   return;
  }

  //out.setFileName("out/" + name);
  out.setFileName(name);

  // this will fail if "name" contains subdirectories, but we don't mind that
  if(!out.open(QIODevice::WriteOnly))
    qDebug() << "Out failed ...";
  // Slow like hell (on GNU/Linux at least), but it is not my fault.
  // Not ZIP/UNZIP package's fault either.
  // The slowest thing here is out.putChar(c).
  while (file.getChar(&c)) out.putChar(c);

  out.close();

  if (file.getZipError() != UNZ_OK) 
  {
   qWarning("testRead(): file.getFileName(): %d", file.getZipError());
   return;
  }

  if (!file.atEnd()) 
  {
   qWarning("testRead(): read all but not EOF");
   return;
  }

  file.close();

  if (file.getZipError() != UNZ_OK) 
  { 
   qWarning("testRead(): file.close(): %d", file.getZipError());
   return;
  }
 }

 zip.close();

 if (zip.getZipError() != UNZ_OK) 
 {
  qWarning("testRead(): zip.close(): %d", zip.getZipError());
  return;
 }
#endif //def USING_ZIP
}

