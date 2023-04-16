
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_TR_DOCUMENT__H
#define CHASM_TR_DOCUMENT__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/chasm-tr-dominion.h"

#include "accessors.h"

#include "aqns.h"

#include <QFile>
#include <QTextStream>

#include "kernel/graph/chasm-tr-graph.h"

AQNS_(ChasmTR)


class Chasm_TR_Parser;
class Chasm_TR_Grammar;
class Chasm_TR_Graph_Build;
//?class Chasm_TR_Word_Entry_List;
class Chasm_TR_Graph;


class Chasm_TR_Document
{
 Chasm_TR_Graph* graph_;
 Chasm_TR_Parser* parser_;
 Chasm_TR_Graph_Build* graph_build_;
 Chasm_TR_Grammar* grammar_;

 QString local_path_;
 QString raw_text_;

 QString local_directory_;


 void preprocess_raw_text();

public:

 ACCESSORS(QString ,local_path)
 ACCESSORS(QString ,raw_text)
 ACCESSORS(QString ,local_directory)
 ACCESSORS(Chasm_TR_Graph* ,graph)
 ACCESSORS__GET(Chasm_TR_Grammar* ,grammar)

 ACCESSORS(Chasm_TR_Graph_Build* ,graph_build)

 Chasm_TR_Document(QString path);

 ~Chasm_TR_Document();

 QVector<Chasm_TR_Graph::hypernode_type*>& top_level_hypernodes();

 void load_file(QString path);
 void report_graph(QString path);

 QString Chasm_TR_path_handlers();

 void resolve_report_path(QString& path);

 void write_report(QString path);

 void set_grammar(Chasm_TR_Grammar* grammar = nullptr);

 void parse(int start_position = 0, int end_position = -1);

 void surround(QString divider, QString text);
};

_AQNS(ChasmTR)


#endif // CHASM_TR_DOCUMENT__H

