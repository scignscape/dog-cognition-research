
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NTXH_DOCUMENT__H
#define NTXH_DOCUMENT__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/ntxh-dominion.h"

#include "accessors.h"

#include "kans.h"

#include <QFile>
#include <QTextStream>

#include "kernel/graph/ntxh-graph.h"

KANS_(HGDMCore)


class NTXH_Parser;
class NTXH_Grammar;
class NTXH_Graph_Build;
//?class NTXH_Word_Entry_List;
class NTXH_Graph;


class NTXH_Document
{
 NTXH_Graph* graph_;
 NTXH_Parser* parser_;
 NTXH_Graph_Build* graph_build_;
 NTXH_Grammar* grammar_;

 QString local_path_;
 QString raw_text_;

 QString local_directory_;


 void preprocess_raw_text();

public:

 ACCESSORS(QString ,local_path)
 ACCESSORS(QString ,raw_text)
 ACCESSORS(QString ,local_directory)
 ACCESSORS(NTXH_Graph* ,graph)
 ACCESSORS__GET(NTXH_Grammar* ,grammar)

 ACCESSORS(NTXH_Graph_Build* ,graph_build)

 NTXH_Document(QString path);

 ~NTXH_Document();

 QVector<NTXH_Graph::hypernode_type*>& top_level_hypernodes();

 void load_file(QString path);
 void report_graph(QString path);

 QString NTXH_path_handlers();

 void resolve_report_path(QString& path);

 void write_report(QString path);

 void set_grammar(NTXH_Grammar* grammar = nullptr);

 void parse(int start_position = 0, int end_position = -1);

 void surround(QString divider, QString text);
};

_KANS(HGDMCore)


#endif // NTXH_DOCUMENT__H

