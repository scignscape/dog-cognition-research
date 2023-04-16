
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_TR_GRAPH_BUILD__H
#define CHASM_TR_GRAPH_BUILD__H

#include "flags.h"

#include "accessors.h"

#include "global-types.h"

#include "grammar/chasm-tr-parse-context.h"

#include "kernel/graph/chasm-tr-graph.h"

#include <QStack>


#include "aqns.h"
AQNS_(ChasmTR)

class Chasm_TR_Graph;
class Chasm_TR_Node;
class Chasm_TR_Document;
class Chasm_TR_Parser;
class Chasm_TR_Graph;
class Chasm_TR_Frame;

class Chasm_TR_Source_Type;
class Chasm_TR_Source_File;

class Chasm_TR_Graph_Build
{
 static constexpr u1 qj_enum_def = 1;
 static constexpr u1 qj_enum_ops = 2;
 static constexpr u1 qj_enum_str = 3;
 static constexpr u1 qj_accessors = 4;

public:

 flags_(1)
  bool discard_acc:1;
  bool split_acc:1;
  bool array_field:1;
  bool numeric_acc:1;
  bool replace_acc:1;
  bool wildcard_acc:1;
  bool define_replacement:1;
  //bool expecting_field:1;
 _flags

 typedef Chasm_TR_Graph::hypernode_type hypernode_type;
 typedef Chasm_TR_Graph::numeric_index_type numeric_index_type;

private:


 QString acc_;

 Chasm_TR_Parse_Context parse_context_;


 Chasm_TR_Document* document_;
 Chasm_TR_Parser& parser_;
 Chasm_TR_Graph& graph_;

 Chasm_TR_Frame& fr_;


 QVector<hypernode_type*> top_level_hypernodes_;

 u2 held_line_number_;
 u1 current_context_code_;

 Chasm_TR_Source_Type* current_source_type_;

 Chasm_TR_Source_File* current_source_file_;

public:

 Chasm_TR_Graph_Build(Chasm_TR_Document* d, Chasm_TR_Parser& p, Chasm_TR_Graph& g);

 ACCESSORS__RGET(Chasm_TR_Parse_Context ,parse_context)
 ACCESSORS__RGET(QVector<hypernode_type*> ,top_level_hypernodes)


 void init();

 void hold_line_number(u2 line_number);
 void enter_qj_context(u2 line_number, QString context_name);
 void leave_qj_context(u2 line_number, QString s);

 void note_enum_def(QString label, QString value);

};

_AQNS(ChasmTR)

#endif

