
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_DOCUMENT__H
#define CHTR_DOCUMENT__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/chtr-dominion.h"

#include "accessors.h"

#include "aqns.h"

#include <QFile>
#include <QTextStream>

#include "kernel/graph/chtr-graph.h"

AQNS_(Chasm_TR)


class ChTR_Parser;
class ChTR_Grammar;
class ChTR_Graph_Build;
//?class ChTR_Word_Entry_List;
class ChTR_Graph;


class ChTR_Document
{
 ChTR_Graph* graph_;
 ChTR_Parser* parser_;
 ChTR_Graph_Build* graph_build_;
 ChTR_Grammar* grammar_;

 QString local_path_;
 QString raw_text_;

 QString local_directory_;


 void preprocess_raw_text();

public:

 ACCESSORS(QString ,local_path)
 ACCESSORS(QString ,raw_text)
 ACCESSORS(QString ,local_directory)
 ACCESSORS(ChTR_Graph* ,graph)
 ACCESSORS__GET(ChTR_Grammar* ,grammar)

 ACCESSORS(ChTR_Graph_Build* ,graph_build)

 ChTR_Document(QString path);

 ~ChTR_Document();

 QVector<ChTR_Graph::hypernode_type*>& top_level_hypernodes();

 void load_file(QString path);
 void report_graph(QString path);

 QString ChTR_path_handlers();

 void resolve_report_path(QString& path);

 void write_report(QString path);

 void set_grammar(ChTR_Grammar* grammar = nullptr);

 void parse(int start_position = 0, int end_position = -1);

 void surround(QString divider, QString text);
};

_AQNS(Chasm_TR)


#endif // CHTR_DOCUMENT__H

