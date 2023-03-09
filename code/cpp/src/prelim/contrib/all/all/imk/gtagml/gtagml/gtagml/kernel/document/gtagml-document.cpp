
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-document.h"

#include "relae-graph/relae-parser.templates.h"


#include "kans.h"

#include "kernel/grammar/gtagml-grammar.h"
#include "kernel/gtagml-root.h"
#include "kernel/graph/gtagml-node.h"
#include "kernel/graph/gtagml-graph.h"
#include "kernel/grammar/gtagml-parser.h"
#include "kernel/grammar/gtagml-graph-build.h"

#include "tile/gtagml-tile.h"
//#include "annotation/gtagml-annotation-tile.h"

#include "tag-command/gtagml-tag-command.h"

#include "gtagml-project-info.h"

#include <QFileInfo>

#include <QtAlgorithms>

#include "textio.h"

#include <QDir>


#include "kans.h"
USING_KANS(GTagML)


GTagML_Document::GTagML_Document()
 : parsing_mode_(GTagML_Parsing_Modes::GTagML),
   graph_(nullptr), grammar_(nullptr),
   annotations_(nullptr), divert_(nullptr),
   project_info_(nullptr)
{

}

GTagML_Document::GTagML_Document(GTagML_Project_Info* gpi)
 : parsing_mode_(GTagML_Parsing_Modes::GTagML),
   graph_(nullptr), grammar_(nullptr),
   annotations_(nullptr), divert_(nullptr),
   project_info_(gpi)
{

}


GTagML_Project_Info* GTagML_Document::init_project_info(QString folder)
{
 project_info_ = new GTagML_Project_Info(folder);
 return project_info_;
}


QString GTagML_Document::use_info_path()
{
 QFileInfo qfi(local_path_);

 info_path_ = qfi.absolutePath() + "/info/" + qfi.fileName();

 return qfi.absolutePath() + "/info";
}

QString GTagML_Document::local_or_info_path()
{
 return info_path_.isEmpty()? local_path_ : info_path_;
}


QString GTagML_Document::get_full_top_level_path()
{
 QFileInfo qfi(local_path_);

 return qfi.absolutePath() + "/" + top_level_path_;
}


QString GTagML_Document::get_path_root()
{
 if(!man_folder_path_.isEmpty())
   return man_folder_path_;

 if(local_path_.isEmpty())
   return {};
 QDir qd(local_path_);
 if(qd.exists(".gt-copy"))
 {
  QString text = TextIO::load_file(qd.absoluteFilePath(".gt-copy")).trimmed();
  if(!text.isEmpty())
    return text;
 }
 qd.cd(ROOT_FOLDER);
 qd.cdUp();
 return qd.absolutePath();
}


void GTagML_Document::write_annotations(QString path, QMap<QString, caon_ptr<GTagML_Annotation_Tile>>& annotations)
{
 qDebug() << "Writing to path: " << path;

 QString contents;

 contents = "<html><body><table>";

 QStringList qsl = annotations.keys();

 for(QString& qs : qsl)
 {
  if(qs.startsWith("*:"))
   qs = qs.mid(2);
 }


 qSort(qsl.begin(), qsl.end());

 for(QString qs : qsl)
 {
  QString key = qs.simplified();
  caon_ptr<GTagML_Annotation_Tile> tile = annotations[qs];

//  QString value = tile->tile().simplified();
//  contents += QString("\n<tr><td class='annotation-key'>%1</td>"
//                      "<td class='annotation-value'>%2</td></tr>").arg(key).arg(value);

 }

 contents += "\n</table></body></html>";

 save_file(path, contents);

}

void GTagML_Document::write_local_annotations(QString path)
{
 QString contents;

 QMapIterator<QString, caon_ptr<GTagML_Annotation_Tile> >
   it(local_annotations_);

 contents = "<html><body><table>";

 while(it.hasNext())
 {
  it.next();

  QString key = it.key().simplified();
  caon_ptr<GTagML_Annotation_Tile> tile = it.value();

//  QString value = tile->tile().simplified();
//  if(!value.isEmpty())
//  {
//   value.replace(0, 1, value[0].toUpper());
//  }

//  if(key.startsWith("*:"))
//  {
//   key = key.mid(2);
//  }

//  contents += QString("\n<tr><td>%1</td><td>%2</td></tr>").arg(key).arg(value);

 }

 contents += "\n</table></body></html>";

 save_file(path, contents);
}


QString GTagML_Document::escape_unicode(QString contents)
{
 QString result;
 QString isAcsii;
 QString tmp;
 for(QChar cr : contents)
 {
  int uni = cr.unicode();
  if(uni > 128)
  {
   tmp.setNum(uni);
   tmp.prepend("\\u");
   result += tmp;
  }
  else if(cr.toLatin1() != QChar(0))
  {
   isAcsii = static_cast<QString>(cr.toLatin1());
   result += isAcsii;
  }
  else
  {
   tmp.setNum(cr.unicode());
   tmp.prepend("\\u");
   result += tmp;
  }
 }
 return result;
}

void GTagML_Document::use_light_xml()
{
 document_info_.init_light_xml();
}

//void GTagML_Document::tag_command_annotation(caon_ptr<GTagML_Tile> nt, caon_ptr<GTagML_Annotation_Tile> tile)
//{
// QString key = nt->raw_text();
// if(annotations_)
// {
//  if(!annotations_->contains(key))
//  {
//   annotations_->insert(key, tile);
//  }
// }
// if(!local_annotations_.contains(key))
// {
//  local_annotations_.insert(key, tile);
// }
//}

void GTagML_Document::tag_command_annotation(caon_ptr<GTagML_Annotation_Tile> tile)
{
 QString key;// = tile->subject();
 if(annotations_)
 {
  if(!annotations_->contains(key))
  {
   annotations_->insert(key, tile);
  }
 }
 if(!local_annotations_.contains(key))
 {
  local_annotations_.insert(key, tile);
 }
}


QString GTagML_Document::save_hrefs()
{
 QString path = local_path_;
 path += ".hrefs";
 document_info_.save_hrefs(path);
 return path;
}


QString GTagML_Document::save_quotes()
{
 QString path = local_path_;
 path += ".quotes";
 document_info_.save_quotes(path);
 return path;
}

QString GTagML_Document::file_name()
{
 QFileInfo qfi(local_path_);
 return qfi.baseName();
}


QString GTagML_Document::save_light_xml()
{
 if(document_info_.light_xml())
 {
  QString path = local_path_;
  path += ".light.xml";
  document_info_.save_light_xml(path);
  return path;
 }
 else
 {
  return QString();
 }
}

QString GTagML_Document::save_word_count()
{
 QString path = local_path_;
 path += ".count";
 document_info_.save_word_count(path);
 return path;
}

QString GTagML_Document::save_word_stream()
{
 QString path = local_path_;
 path += ".stream";
 document_info_.save_word_stream(path);
 return path;
}

void GTagML_Document::save_file(QString path, QString contents)
{
 QFile file(path);
 if(file.open(QIODevice::WriteOnly | QIODevice::Text))
 {
  QTextStream out(&file);
  out << contents;
 }
}


void GTagML_Document::load_file(QString path)
{
 QFile file(path);
 if(file.open(QFile::ReadOnly | QIODevice::Text))
 {
  raw_text_ = file.readAll();
  local_path_ = path;
  QFileInfo qfi(path);
  local_file_name_ = qfi.fileName();
  file_job_name_ = qfi.fileName();
 }
}


void GTagML_Document::set_grammar(caon_ptr<GTagML_Grammar> grammar)
{
 if(grammar)
  grammar_ = grammar;
 else
  grammar_ = caon_ptr<GTagML_Grammar>( new GTagML_Grammar() );
}

void GTagML_Document::parse()
{
 caon_ptr<GTagML_Root> root = caon_ptr<GTagML_Root>( new GTagML_Root() );
 caon_ptr<GTagML_Node> node = caon_ptr<GTagML_Node>( new GTagML_Node(root) );
 graph_ = caon_ptr<GTagML_Graph> ( new GTagML_Graph(node) );
 parser_ = caon_ptr<GTagML_Parser> ( new GTagML_Parser(graph_) );

 graph_build_ = caon_ptr<GTagML_Graph_Build>(
  new GTagML_Graph_Build(*graph_, document_info_) );
 graph_build_->init();

 graph_build_->set_current_parsing_mode(parsing_mode_);

 grammar_->init(*parser_, *graph_, *graph_build_);

 grammar_->compile(*parser_, *graph_, raw_text_);
}


void GTagML_Document::check_sdi_tag_command_info()
{
 if(sdi_tag_command_info_path_.isEmpty())
 {
  GTagML_Tag_Command::set_needs_sdi_mark_check([](QString name) -> bool
  {
   static QStringList qsl {
    "cq-", "dq-", "qq-", "sq-"
   };

   for(const QString& qs : qsl)
   {
    if(name.startsWith(qs))
      return true;
   }
   
   return false;
  });
 }
}

void GTagML_Document::load_and_parse(QString path, caon_ptr<GTagML_Grammar> grammar)
{
 check_sdi_tag_command_info();
 load_file(path);
 set_grammar(grammar);
 parse();
}


GTagML_Document::~GTagML_Document()
{
 qDebug() << "del GTagML_Document";
}


// //  Quick cleanup of HTML documents being converted to XML
 //    -- not very reliable.
void GTagML_Document::clean_html(QString& str)
{
 QRegularExpression script_rx("<script.*?</script>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(script_rx, "");

 QRegularExpression script_rx_remaining("<script.*?/?>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(script_rx_remaining, "");

 QRegularExpression link_rx("<link.*?</link>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(link_rx, "");

 QRegularExpression link_rx_remaining("<link.*?/?>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(link_rx_remaining, "");

 QRegularExpression style_rx("<style.*?</style>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(style_rx, "");

 QRegularExpression style_rx_remaining("<style.*?/?>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(style_rx_remaining, "");

 QRegularExpression button_rx("<button.*?</button>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(button_rx, "");

 QRegularExpression button_rx_remaining("<button.*?/?>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(button_rx_remaining, "");



 QRegularExpression iframe_rx("<iframe.*?</iframe>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(iframe_rx, "");

 QRegularExpression iframe_rx_remaining("<iframe.*?/?>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(iframe_rx_remaining, "");

 QRegularExpression form_rx("<form.*?</form>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(form_rx, "");

 QRegularExpression form_rx_remaining("<form.*?/?>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(form_rx_remaining, "");

 QRegularExpression meta_rx("<meta.*?</meta>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(meta_rx, "");

 QRegularExpression meta_rx_remaining("<meta.*?/?>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(meta_rx_remaining, "");

 QRegularExpression img_rx("<img.*?</img>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(img_rx, "");

 QRegularExpression img_rx_remaining("<img.*?/?>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(img_rx_remaining, "");


 QRegularExpression video_rx("<video.*?</video>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(video_rx, "");

 QRegularExpression video_rx_remaining("<video.*?/?>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(video_rx_remaining, "");


 QRegularExpression object_rx("<object.*?</object>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(object_rx, "");

 QRegularExpression object_rx_remaining("<object.*?/?>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(object_rx_remaining, "");


 QRegularExpression param_rx("<param.*?</param>",
  QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(param_rx, "");

 QRegularExpression param_rx_remaining("<param.*?/?>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(param_rx_remaining, "");




 QRegularExpression base_rx("<base.*?</base>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(base_rx, "");

 QRegularExpression base_rx_remaining("<base.*?/?>", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(base_rx_remaining, "");



 QRegularExpression comment_rx("<!--.*?-->", QRegularExpression::DotMatchesEverythingOption | QRegularExpression::CaseInsensitiveOption);
 str.replace(comment_rx, "");

 str.replace(QRegularExpression("<![^>]+>"), "");


 str.replace("<br>", "");
 str.replace("<hr>", "");

 str.replace(QRegularExpression("\\n\\s*\\n"), "\n");

 str.replace(QRegularExpression("<html[^>]+>"), "<html>" );

 str.replace("&ndash;", "&#x2013;");
 str.replace("&mdash;", "&#x2014;");

 str.replace("&lsquo;", "&#x2018;");
 str.replace("&rsquo;", "&#x2019;");

 str.replace("&ldquo;", "&#x201C;");
 str.replace("&rdquo;", "&#x201D;");

 str.replace("&nbsp;", "");

 QRegularExpression eos_word_rx("([\\\\a-z]{2,}\\.(?=\\s))");
 str.replace(eos_word_rx, "\\1 ");

 QRegularExpression eos_caps_word_rx("([\\\\A-Z]{2,}\\.(?=\\s))");
 str.replace(eos_caps_word_rx, "\\1 ");

 str.replace("   ", "  ");

 str.replace(QRegularExpression("=\"([^\"]+)=\""), "=\"\\1$EQ$\"");

}



