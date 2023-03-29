
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_CPP_DOCUMENT__H
#define QH_CPP_DOCUMENT__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/qh-cpp-dominion.h"

#include "accessors.h"

#include "kans.h"

#include <QFile>
#include <QTextStream>

#include "kernel/graph/qh-cpp-graph.h"

KANS_(Qh)


class Qh_CPP_Parser;
class Qh_CPP_Grammar;
class Qh_CPP_Graph_Build;
//?class Qh_CPP_Word_Entry_List;
class Qh_CPP_Graph;


class Qh_CPP_Document
{
 Qh_CPP_Graph* graph_;
 Qh_CPP_Parser* parser_;
 Qh_CPP_Graph_Build* graph_build_;
 Qh_CPP_Grammar* grammar_;

 QString local_path_;
 QString raw_text_;

 QString local_directory_;


 void preprocess_raw_text();

public:

 ACCESSORS(QString ,local_path)
 ACCESSORS(QString ,raw_text)
 ACCESSORS(QString ,local_directory)
 ACCESSORS(Qh_CPP_Graph* ,graph)
 ACCESSORS__GET(Qh_CPP_Grammar* ,grammar)

 ACCESSORS(Qh_CPP_Graph_Build* ,graph_build)

 Qh_CPP_Document(QString path);

 ~Qh_CPP_Document();

 QVector<Qh_CPP_Graph::hypernode_type*>& top_level_hypernodes();

 void load_file(QString path);
 void report_graph(QString path);

 QString Qh_CPP_path_handlers();

 void resolve_report_path(QString& path);

 void write_report(QString path);

 void set_grammar(Qh_CPP_Grammar* grammar = nullptr);

 void parse(int start_position = 0, int end_position = -1);

 void surround(QString divider, QString text);
};

_KANS(Qh)


#endif // QH_CPP_DOCUMENT__H

