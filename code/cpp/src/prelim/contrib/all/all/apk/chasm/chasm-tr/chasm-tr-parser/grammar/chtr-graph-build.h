
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ChTR_GRAPH_BUILD__H
#define ChTR_GRAPH_BUILD__H

#include "flags.h"

#include "accessors.h"

#include "global-types.h"

#include "grammar/chtr-parse-context.h"

#include "kernel/graph/chtr-graph.h"

#include "types/chtr-type-system.h"

#include "codegen/chtr-chvm-generator.h"

#include <QStack>


#include "aqns.h"
AQNS_(Chasm_TR)

class ChTR_Graph;
class ChTR_Node;
class ChTR_Node_Factory;


class ChTR_Document;
class ChTR_Parser;
class ChTR_Graph;
class ChTR_Relae_Frame;
class ChTR_Relae_Query;


class ChTR_Source_Type;
class ChTR_Source_File;

class ChTR_Channel_Package;
class ChTR_Channel_Object;
class ChTR_Code_Statement;

class ChTR_Lexical_Scope
{
 QMap<QString, ChTR_Type_Object*> known_symbols_;

public:

 ChTR_Lexical_Scope() {}

 void add_symbol(QString token, ChTR_Type_Object* cto)
 {
  known_symbols_[token] = cto;
 }

 QString get_symbol_name(QString token)
 {
  if(known_symbols_.contains(token))
    return token;

  return {};
 }
};



class ChTR_Graph_Build
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

 typedef ChTR_Graph::hypernode_type hypernode_type;
 typedef ChTR_Graph::numeric_index_type numeric_index_type;

private:

 //QString


 ChTR_CHVM_Generator gen;

// void acc(QString text);


 ChTR_Parse_Context parse_context_;


 ChTR_Document* document_;
 ChTR_Parser& parser_;
 ChTR_Graph& graph_;

 ChTR_Relae_Frame& Sf;
 const ChTR_Relae_Query& Qy;

 ChTR_Node_Factory& node_factory_;


 QVector<hypernode_type*> top_level_hypernodes_;

 u2 held_line_number_;
 u1 current_context_code_;

 ChTR_Source_Type* current_source_type_;

 ChTR_Source_File* current_source_file_;

 ChTR_Channel_Package* current_channel_package_;
 ChTR_Channel_Object* current_channel_object_;
 ChTR_Code_Statement* current_code_statement_;

 ChTR_Node* current_statement_level_node_;

 ChTR_Type_System type_system_;

 u4 current_line_number_;

 QString current_channel_name_;

 u4 source_file_index_;

 void cut();

// QTextStream acc;


 typedef union {void(ChTR_Graph_Build::*fn0)();
   void(ChTR_Graph_Build::*fn1)(QString);} fn_u;

 QVector<QPair<QString, fn_u>> line_ops_;

 enum class Expression_States {

  N_A, Held_Declare_Point_Token, Held_Anchor_Token, Expression_Return

 };
 Expression_States current_expression_state_;

 enum class Channel_States : s2 {

  N_A, Implicit_Lambda = 1, Explicit_Lambda = 2, Named_Channel_Entered = 4, Named_Channel_Exited = 8,
  //Expression_Return = 256
 };

 Channel_States current_channel_state_;

 ChTR_Lexical_Scope* current_lexical_scope_;
 ChTR_Lexical_Scope file_lexical_scope_;


 caon_ptr<ChTR_Node> current_parse_node_;




public:

 ChTR_Graph_Build(ChTR_Document* d, ChTR_Parser& p, ChTR_Graph& g);

 ACCESSORS__RGET(ChTR_Parse_Context ,parse_context)
 ACCESSORS__RGET(QVector<hypernode_type*> ,top_level_hypernodes)

 void load_pregraph(QString file_path);

 void parse_line_number(QString text);

 void init();

 void read_line(QString fn, QString arg);
 void read_line(QString fn);

 void run_lines();

 void read_graph_build_program(QString lines);

 QString chvm_code();

 void source_file(QString file_path);

 void check_resolve_statement();

 void expression_to_statement();
 void expression_to_expression();

 void write_handoff_rtl();
 void write_handoff_rts();
 void resolve_expression();
 void resolve_statement();
 void enter_expression();
 void enter_statement();


 void scoped_symbol_decl(QString symbol);
 void type_expression_token(QString token);
 void scoped_symbol_pin(QString symbol);
 void proc_name(QString token);
 void symbol_token(QString token);
 void pin_value_literal(QString token);

 void source_file_end();

 void enter_statement_body();

 void prepare_carrier_declaration(QString symbol);

 void enter_channel_body();
 void leave_channel_body();

 void read_channel_string(QString channel_string);
 void read_carrier_string(QString carrier_string);



};

_AQNS(Chasm_TR)

#endif

