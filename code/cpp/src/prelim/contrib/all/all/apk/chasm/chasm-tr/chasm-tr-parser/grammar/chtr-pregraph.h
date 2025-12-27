
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ChTR_PREGRAPH__H
#define ChTR_PREGRAPH__H

#include "flags.h"

#include "accessors.h"

#include "global-types.h"

#include "grammar/chtr-parse-context.h"

#include "kernel/graph/chtr-graph.h"

#include <QStack>


#include "aqns.h"
AQNS_(Chasm_TR)

class ChTR_Graph;
class ChTR_Node;
class ChTR_Document;
class ChTR_Parser;
class ChTR_Graph;
class ChTR_Grammar;

class ChTR_Relae_Frame;
class ChTR_Relae_Query;


class ChTR_Source_Type;
class ChTR_Source_File;

class ChTR_Channel_Package;
class ChTR_Channel_Object;
class ChTR_Code_Statement;


class ChTR_Pregraph
{

public:

 flags_(1)
  bool active_run_call:1;
  bool infix_mode:1;
  bool active_statement:1;
  bool active_expression:1;

//  bool discard_acc:1;
//  bool split_acc:1;
//  bool array_field:1;
//  bool numeric_acc:1;
//  bool replace_acc:1;
//  bool wildcard_acc:1;
//  bool define_replacement:1;
  //bool expecting_field:1;
 _flags

 typedef ChTR_Graph::hypernode_type hypernode_type;
 typedef ChTR_Graph::numeric_index_type numeric_index_type;

private:

 //QString

 QString acc_;

 QTextStream acc;

// void acc(QString text);


 ChTR_Parse_Context parse_context_;


 ChTR_Document* document_;
 ChTR_Parser& parser_;
 ChTR_Graph& graph_;

 ChTR_Grammar* grammar_;

 ChTR_Relae_Frame& fr_;
 const ChTR_Relae_Query& qy_;

 QStringList acc_lines_;

 enum class Carrier_Handoff_States {
   N_A, Implicit_Return_to_Lambda, Return_to_Lambda, Return_to_Sigma
 };

 QStack<Carrier_Handoff_States> current_handoff_states_;
 Carrier_Handoff_States declared_handoff_state_;

 QStack<QString> proc_names_;

 QStack<QPair<s4, s4>> infix_line_indices_;

 u1 infix_count_;
 u1 expression_nesting_count_;

 u4 last_line_number_written_;
 u4 current_line_number_;


public:

 ChTR_Pregraph(ChTR_Document* d, ChTR_Parser& p, ChTR_Graph& g);

 ACCESSORS__RGET(ChTR_Parse_Context ,parse_context)

 ACCESSORS(ChTR_Grammar* ,grammar)

 void check_resolve_statement();
 void reenter_statement_level();
 void temp_reenter_statement_level();

 void enter_expression();

 void leave_expression();


 void check_lines(QString text);

 void check_write_handoff();

 void check_write_line_number();

 void init();

 void cut();

 void check_enter_infix_mode();

 void non_anchored_call(QString proc_name);

 void anchor_or_pin(QString symbol, QString tween, QString token);

 void symbol_token(QString token);

 QString pregraph_code();

 void enter_statement_body();

 void prepare_carrier_declaration(QString symbol,
   QString tween, QString type_token);

 void prepare_carrier_declarations(QStringList symbols,
   QStringList tweens, QString type_token);


 void resolve_source_file();

// void enter_channel_body();
// void leave_channel_body();

// void read_channel_string(QString channel_string);
// void read_carrier_string(QString carrier_string);


};

_AQNS(Chasm_TR)

#endif // ChTR_PREGRAPH__H

