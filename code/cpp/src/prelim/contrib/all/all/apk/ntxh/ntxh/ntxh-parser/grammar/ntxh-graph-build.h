
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NTXH_GRAPH_BUILD__H
#define NTXH_GRAPH_BUILD__H

#include "flags.h"

#include "accessors.h"

#include "grammar/ntxh-parse-context.h"

#include "kernel/graph/ntxh-graph.h"

#include <QStack>


#include "kans.h"
KANS_(HGDMCore)

class NTXH_Graph;
class NTXH_Node;
class NTXH_Document;
class NTXH_Parser;
class NTXH_Graph;
class NTXH_Frame;

class NTXH_Graph_Build
{
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

 typedef NTXH_Graph::hypernode_type hypernode_type;
 typedef NTXH_Graph::numeric_index_type numeric_index_type;

private:


 QString acc_;

 NTXH_Parse_Context parse_context_;


 NTXH_Document* document_;
 NTXH_Parser& parser_;
 NTXH_Graph& graph_;

 NTXH_Frame& fr_;

 int current_field_number_;
 QString current_field_name_;
 QString current_type_name_;

 int current_type_field_index_;

 hypernode_type* current_hypernode_;
 hypernode_type* last_hypernode_;
 hypernode_type* held_current_hypernode_;

 QStack<hypernode_type*> parent_hypernodes_;

 QVector<hypernode_type*> top_level_hypernodes_;

 QMap<QString, QString> replacements_;

 void check_reset_current_type_name();

public:

 NTXH_Graph_Build(NTXH_Document* d, NTXH_Parser& p, NTXH_Graph& g);

 ACCESSORS__RGET(NTXH_Parse_Context ,parse_context)
 ACCESSORS__RGET(QVector<hypernode_type*> ,top_level_hypernodes)


 void init();

 void array_append();
 void add_read_token(QString text);
 void add_numeric_read_token(numeric_index_type val);

 void top_level_append();

 void prepare_field_read(QString prefix, QString field, QString suffix);
 void read_acc(QString s);
 void end_field();

 void read_command(QString prefix, QString cmd, QString suffix);
 void leave_read_command(QString prefix, QString cmd, QString suffix);

 void add_type(QString name, QString length);

 void add_type_field_index(QString name, int code = 0);

 void start_sample(QString ty);
 void end_sample();

 void add_coda_data_line(QString qs);
};

_KANS(HGDMCore)

#endif

