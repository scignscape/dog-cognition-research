
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-cpp-document.h"

#include "relae-graph/relae-parser.templates.h"

#include "kernel/graph/qh-cpp-graph.h"
#include "grammar/qh-cpp-grammar.h"
#include "grammar/qh-cpp-parser.h"
#include "grammar/qh-cpp-graph-build.h"

#include <QFileInfo>
#include <QDir>

USING_KANS(Qh)


Qh_CPP_Document::Qh_CPP_Document(QString path)
 : graph_(nullptr), grammar_(nullptr)
{
 if(!path.isEmpty())
   load_file(path);
}

void Qh_CPP_Document::surround(QString divider, QString text)
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


QVector<Qh_CPP_Graph::hypernode_type*>& Qh_CPP_Document::top_level_hypernodes()
{
 static QVector<Qh_CPP_Graph::hypernode_type*> static_default;
 if(graph_build_)
   return graph_build_->top_level_hypernodes();
 return static_default;
}

void Qh_CPP_Document::load_file(QString path)
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


void Qh_CPP_Document::resolve_report_path(QString& path)
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

void Qh_CPP_Document::report_graph(QString path)
{
 resolve_report_path(path);
 QFile file(path);
 if(file.open(QFile::WriteOnly | QIODevice::Text))
 {
  QTextStream qts(&file);
 }
}

void Qh_CPP_Document::set_grammar(Qh_CPP_Grammar* grammar)
{
 if(grammar)
  grammar_ = grammar;
 else
  grammar_ = new Qh_CPP_Grammar();
}

void Qh_CPP_Document::parse(int start_position, int end_position)
{
 graph_ = new Qh_CPP_Graph();
 parser_ = new Qh_CPP_Parser(graph_);
 parser_->set_raw_text(raw_text_);

 graph_build_ = new Qh_CPP_Graph_Build(this, *parser_, *graph_);
 graph_build_->init();

 grammar_ = new Qh_CPP_Grammar;

 grammar_->init(*parser_, *graph_, *graph_build_);

 grammar_->compile(*parser_, *graph_, raw_text_, start_position);
}

Qh_CPP_Document::~Qh_CPP_Document()
{

}


