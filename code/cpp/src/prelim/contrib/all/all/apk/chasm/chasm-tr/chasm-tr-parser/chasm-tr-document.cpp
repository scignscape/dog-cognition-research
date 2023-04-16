
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-tr-document.h"

#include "relae-graph/relae-parser.templates.h"

#include "kernel/graph/chasm-tr-graph.h"
#include "grammar/chasm-tr-grammar.h"
#include "grammar/chasm-tr-parser.h"
#include "grammar/chasm-tr-graph-build.h"

#include <QFileInfo>
#include <QDir>

USING_KANS(Qh)


Chasm_TR_Document::Chasm_TR_Document(QString path)
 : graph_(nullptr), grammar_(nullptr)
{
 if(!path.isEmpty())
   load_file(path);
}

void Chasm_TR_Document::surround(QString divider, QString text)
{
 int index = text.indexOf(divider);
 if(index == -1)
   raw_text_.append(text);
 else
 {
#ifdef USING_QT5
  raw_text_.prepend(text.midRef(0, index));
  raw_text_.append(text.midRef(index + divider.size()));
#endif

#ifdef USING_QT6
  raw_text_.prepend(QStringView(text).mid(0, index));
  raw_text_.append(QStringView(text).mid(index + divider.size()));
#endif

 }
}


QVector<Chasm_TR_Graph::hypernode_type*>& Chasm_TR_Document::top_level_hypernodes()
{
 static QVector<Chasm_TR_Graph::hypernode_type*> static_default;
 if(graph_build_)
   return graph_build_->top_level_hypernodes();
 return static_default;
}

void Chasm_TR_Document::load_file(QString path)
{
 QFile file(path);
 if(file.open(QFile::ReadOnly | QIODevice::Text))
 {
  raw_text_ = file.readAll();
  local_path_ = path;
  QFileInfo qfi(local_path_);
  local_directory_ = qfi.absoluteDir().absolutePath();
 }
}


void Chasm_TR_Document::resolve_report_path(QString& path)
{
 if(path.startsWith('.'))
 {
  path = path.mid(1);
  if(path.startsWith('.'))
  {
   path = local_path_ + path;
  }
  else
  {
//?   QFileInfo qfi(local_path_);
  }
 }
}

void Chasm_TR_Document::report_graph(QString path)
{
 resolve_report_path(path);
 QFile file(path);
 if(file.open(QFile::WriteOnly | QIODevice::Text))
 {
  QTextStream qts(&file);
 }
}

void Chasm_TR_Document::set_grammar(Chasm_TR_Grammar* grammar)
{
 if(grammar)
  grammar_ = grammar;
 else
  grammar_ = new Chasm_TR_Grammar();
}

void Chasm_TR_Document::parse(int start_position, int end_position)
{
 graph_ = new Chasm_TR_Graph();
 parser_ = new Chasm_TR_Parser(graph_);
 parser_->set_raw_text(raw_text_);

 graph_build_ = new Chasm_TR_Graph_Build(this, *parser_, *graph_);
 graph_build_->init();

 grammar_ = new Chasm_TR_Grammar;

 grammar_->init(*parser_, *graph_, *graph_build_);

 grammar_->compile(*parser_, *graph_, raw_text_, start_position);
}

Chasm_TR_Document::~Chasm_TR_Document()
{

}


