
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_CPP_GRAPH_BUILD__H
#define QH_CPP_GRAPH_BUILD__H

#include "flags.h"

#include "accessors.h"

#include "global-types.h"

#include "grammar/qh-cpp-parse-context.h"

#include "kernel/graph/qh-cpp-graph.h"

#include <QStack>


#include "kans.h"
KANS_(Qh)

class Qh_CPP_Graph;
class Qh_CPP_Node;
class Qh_CPP_Document;
class Qh_CPP_Parser;
class Qh_CPP_Graph;
class Qh_CPP_Frame;

class Qh_CPP_Source_Type;
class Qh_CPP_Source_File;

class Qh_CPP_Graph_Build
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

 typedef Qh_CPP_Graph::hypernode_type hypernode_type;
 typedef Qh_CPP_Graph::numeric_index_type numeric_index_type;

private:


 QString acc_;

 Qh_CPP_Parse_Context parse_context_;


 Qh_CPP_Document* document_;
 Qh_CPP_Parser& parser_;
 Qh_CPP_Graph& graph_;

 Qh_CPP_Frame& fr_;


 QVector<hypernode_type*> top_level_hypernodes_;

 u2 held_line_number_;
 u1 current_context_code_;

 Qh_CPP_Source_Type* current_source_type_;

 Qh_CPP_Source_File* current_source_file_;

public:

 Qh_CPP_Graph_Build(Qh_CPP_Document* d, Qh_CPP_Parser& p, Qh_CPP_Graph& g);

 ACCESSORS__RGET(Qh_CPP_Parse_Context ,parse_context)
 ACCESSORS__RGET(QVector<hypernode_type*> ,top_level_hypernodes)


 void init();

 void hold_line_number(u2 line_number);
 void enter_qj_context(u2 line_number, QString context_name);
 void leave_qj_context(u2 line_number, QString s);

 void note_enum_def(QString label, QString value);

};

_KANS(Qh)

#endif

