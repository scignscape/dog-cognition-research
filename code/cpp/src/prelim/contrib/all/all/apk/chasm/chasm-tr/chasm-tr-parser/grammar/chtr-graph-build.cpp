
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-graph-build.h"

#include "kernel/frame/chtr-frame.h"

#include "kernel/graph/chtr-graph.h"

#include "kernel/query/chtr-query.h"


#include "chtr-source-file.h"

#include <QMap>

#include "global-types.h"

#include "chasm-tr/chtr-channel-object.h"
#include "chasm-tr/chtr-channel-package.h"
#include "chasm-tr/chtr-code-statement.h"

#include "chasm-tr/types/chtr-type-object.h"

#include "chtr-node-factory.h"

#include "chasm-tr/chtr-source-token.h"

#include "relae-graph/relae-caon-ptr.h"
#include "relae-graph/relae-node-ptr.h"

#include "chtr-document.h"

#include "textio.h"
USING_KANS(TextIO)


//?#include "chasm-tr/kernel/dominion/types.h"


USING_AQNS(Chasm_TR)


ChTR_Graph_Build::ChTR_Graph_Build(ChTR_Document* d, ChTR_Parser& p, ChTR_Graph& g)
 : Flags(0)
   ,document_(d)
   ,graph_(g)
   ,parser_(p)
   ,Sf(ChTR_Relae_Frame::instance())
   ,Qy(ChTR_Relae_Query::instance())
   ,node_factory_(ChTR_Node_Factory::instance())
   ,source_file_index_(0)
   ,held_line_number_(0)
   ,current_context_code_(0)
   ,current_source_type_(nullptr)
   ,current_channel_package_(nullptr)
   ,current_channel_object_(nullptr)
   ,current_code_statement_(nullptr)
   ,current_statement_level_node_(nullptr)
   ,current_line_number_(0)
   ,current_channel_state_(Channel_States::N_A)
   ,current_expression_state_(Expression_States::N_A)
{
 current_lexical_scope_ = &file_lexical_scope_;

 current_source_file_ = new ChTR_Source_File;
 // acc << "\n"; cut();

}


QString ChTR_Graph_Build::chvm_code()
{
 QString result;
 gen.chvm_code(result);
 return result;
}


void ChTR_Graph_Build::parse_line_number(QString text)
{
 current_line_number_ = text.mid(1).trimmed().toUInt();
}

void ChTR_Graph_Build::cut()
{
 gen.cut();
}

void ChTR_Graph_Build::read_graph_build_program(QString lines)
{
 s4 pos = 0;
 s4 end = lines.length();

 while(pos < end)
 {
  s4 np = lines.indexOf(";.\n", pos);
  if(np == -1)
    np = lines.indexOf("\n.\n", pos);
  if(np == -1)
    break;
  QString l = lines.mid(pos, np - pos).trimmed();
  if(l.startsWith(".;"))
  {
   pos = np + 3;
   continue;
  }
  if(l.startsWith("# "))
  {
   line_ops_.push_back({l, fn_u{.fn1 = &ChTR_Graph_Build::parse_line_number}});
   //parse_line_number(l);
   pos = np + 3;
   continue;
  }

//  bool reread = false;
  int mp = l.indexOf(" $");
//  if(mp == -1)
//  {
//   mp = l.indexOf(" @");
//   reread = true;
//  }
  if(mp != -1)
  {
   QString l1 = l.mid(0, mp).trimmed();
   QString l2 = l.mid(mp + 2, np - mp - 2).trimmed();
//   if(reread)
//     reread_substitute(l2);
   read_line(l1, l2);
  }
  else
  {
   read_line(l.trimmed());
  }
  pos = np + 3;
 }

 run_lines();
}

void ChTR_Graph_Build::run_lines()
{

// const QVector<QPair<QString*, fn_u>>& lines = it.value();
 for(auto& pr: line_ops_)
 {
  if(pr.first.isEmpty())
    (this->*(pr.second.fn0))();
  else
    (this->*(pr.second.fn1))(pr.first);
 }
}

void ChTR_Graph_Build::source_file(QString file_path)
{
 ++source_file_index_;

 gen
   .blank()
   << "@sf " << file_path; cut();
 gen
   .blank()
   << "init-source-file-lexical-scope"; cut();

 gen
   .blank()
   << "source-file-index $ " << source_file_index_; cut();

 gen.blank();
}


void ChTR_Graph_Build::scoped_symbol_decl(QString symbol)
{
 ChTR_Source_Token* token = new ChTR_Source_Token(symbol);
 current_parse_node_ = node_factory_.make_new_node(token);
 current_expression_state_ = Expression_States::Held_Declare_Point_Token;
}

void ChTR_Graph_Build::type_expression_token(QString token)
{
 ChTR_Type_Object* cto = type_system_.find_type(token);

 if(!cto)
 {
  // //  error?
  return;
 }

 caon_ptr<ChTR_Node> type_node = node_factory_.make_new_node(cto);

 switch (current_expression_state_)
 {
 case Expression_States::Held_Declare_Point_Token:
  {
   caon_ptr<ChTR_Source_Token> source_token = current_parse_node_->source_token();
   QString text = source_token->text();

   current_lexical_scope_->add_symbol(text, cto);

   gen
     .blank()
     .preamble_comment("statement-level declaration");
   //preamble()

//   gen_.blank();

   if(cto->flags.built_in)
     gen << "load-type-" << cto->name();
   else
     gen << "load-type-object $ " << token;
   cut();

   gen << "declare-lexical-typed-symbol $ " << text; cut();

   current_parse_node_ << Sf/Qy.Symbol_to_Type_Object >> type_node;

  }
  break;
 default:
  break;
 }
}

void ChTR_Graph_Build::scoped_symbol_pin(QString symbol)
{
 gen
   .blank()
   .preamble_comment("statement-level pin")
   << "single-init-pin $ " << symbol; cut();
}

void ChTR_Graph_Build::proc_name(QString token)
{
 gen
   .dissolve({"add-new-channel $ proc"})
   << "load-proc-name $ " << token;

 cut();
 gen.blank();

 current_channel_state_ = Channel_States::Implicit_Lambda;
}

void ChTR_Graph_Build::symbol_token(QString token)
{
 switch(current_channel_state_)
 {
 case Channel_States::Implicit_Lambda:
   gen.dissolve({"add-new-channel $ lambda"}).blank();
   current_channel_state_ = Channel_States::Explicit_Lambda;
   // //  fall through
 case Channel_States::Explicit_Lambda:
  {
   QString symbol_name = current_lexical_scope_->get_symbol_name(token);

   if(symbol_name.isEmpty())
   {
    bool negative = false;
    bool positive = false;
    bool fp = false;
    if(token[0] == '-')
    {
     negative = true;
     token = token.mid(1);
    }
    if(token[0] == '+')
    {
     positive = true;
     token = token.mid(1);
    }
    if(token[0] == '.')
    {
     fp = true;
     token = token.mid(1);
    }

    if(token[0].isDigit())
    {
     QString base;
     QString signed_or_not;
     QString generic_or_literal;
     QString int_or_float;
     if(token[0] == '0')
     {
      if(token.size() == 1)
      {
       generic_or_literal = "generic";
      }
      else if(token[1].isDigit())
        base = "_0";
      else
        base = token.mid(0, 2).prepend("_");
     }

     if(negative)
       signed_or_not = "signed-negative";
     else if(positive)
       signed_or_not = "signed-positive";
     else
       signed_or_not = "unsigned";

     if(generic_or_literal.isEmpty())
       generic_or_literal = "literal";
     if(fp)
       int_or_float = "float";
     else
       int_or_float = "int";
     gen << "load-" << signed_or_not << "-" << generic_or_literal
         << "-" << int_or_float << " $ " << token; cut();
    }
    return;
   }

   gen << "load-carrier-symbol-lxs $ " << symbol_name; cut();
  }
 }

}

void ChTR_Graph_Build::pin_value_literal(QString token)
{
 gen
   .blank()
   << "load-value-literal $ " << token;
   cut();
 gen << "resolve-pins"; cut();
}

void ChTR_Graph_Build::check_resolve_statement()
{
// switch(current_channel_state_)
// {
// case Channel_States::Implicit_Lambda:
// case Channel_States::Explicit_Lambda:

//  gen
//    .blank()
//    .dissolve({"add-carriers", "run-proc-eval"})
//    .blank()
//    .dissolve({"reset-carrier-deque", "clear-current-ghost-scope"})
//    .blank();
// }
}


void ChTR_Graph_Build::source_file_end()
{
 check_resolve_statement();
 gen.blank().dissolve({"@sfe"});
}

void ChTR_Graph_Build::write_handoff_rtl()
{
 gen.blank().dissolve({"resolve-handoffs $ retv lambda"});
}

void ChTR_Graph_Build::write_handoff_rts()
{

}

void ChTR_Graph_Build::resolve_expression()
{
 switch(current_channel_state_)
 {
 case Channel_States::Implicit_Lambda:
 case Channel_States::Explicit_Lambda:

  gen
    .blank()
    .dissolve({"add-carriers", "run-proc-eval"})
    .blank()
    .dissolve({"reset-carrier-deque", "clear-current-ghost-scope"})
    .blank();
 }

}

void ChTR_Graph_Build::expression_to_statement()
{
 current_expression_state_ = Expression_States::Expression_Return;

 gen
   .blank()
   .dissolve({"pop-proc-name", "pull-call-package"});
//   .blank()
//   .dissolve("run-proc-eval");
}

void ChTR_Graph_Build::expression_to_expression()
{
 gen
   .blank()
   .dissolve({"pop-proc-name", "pull-call-package"});
}

void ChTR_Graph_Build::resolve_statement()
{
 switch(current_channel_state_)
 {
 case Channel_States::Implicit_Lambda:
 case Channel_States::Explicit_Lambda:
  if(current_expression_state_ != Expression_States::Expression_Return)
   gen
     .blank()
     .dissolve({"add-carriers", "run-proc-eval"});
  else
   gen
     .blank()
     .dissolve({"run-proc-eval"});
  gen
    .blank()
    .dissolve({"reset-carrier-deque", "clear-current-ghost-scope"})
    .blank();
 }

}

void ChTR_Graph_Build::enter_expression()
{
 gen
   .blank()
   .preamble_comment("expression")
   << "statement-line-number $ " << current_line_number_; cut();

// .dissolve({"init-new-ghost-scope", "push-carrier-deque"})

 gen
  .dissolve({"push-carrier-deque"})
  .blank()
  .dissolve({"new-call-package", "gen-return-channels"})
  .blank();
}

void ChTR_Graph_Build::enter_statement()
{
 gen
   .blank()
   .preamble_comment("statement")
   << "statement-line-number $ " << current_line_number_; cut();

 gen
  .dissolve({"init-new-ghost-scope", "push-carrier-deque"})
  .blank()
  .dissolve({"new-call-package"})
  .blank(); //?cut();

}



void ChTR_Graph_Build::read_line(QString fn, QString arg)
{
 static QMap<QString, void(ChTR_Graph_Build::*)(QString)> static_map {{
   { ".source-file", &ChTR_Graph_Build::source_file },
   { ".scoped-symbol-decl", &ChTR_Graph_Build::scoped_symbol_decl },
   { ".type-expression-token", &ChTR_Graph_Build::type_expression_token },
   { ".scoped-symbol-pin", &ChTR_Graph_Build::scoped_symbol_pin },
   { ".pin-value-literal", &ChTR_Graph_Build::pin_value_literal },
   { ".proc-name", &ChTR_Graph_Build::proc_name },
   { ".symbol-token", &ChTR_Graph_Build::symbol_token },
 }};

 auto it = static_map.find(fn);
 if(it != static_map.end())
 {
//  QString* a = new QString(arg);
  line_ops_.push_back({arg, fn_u{.fn1=it.value()}});
 }

}

void ChTR_Graph_Build::read_line(QString fn)
{
 static QMap<QString, void(ChTR_Graph_Build::*)()> static_map {{
   { ".source-file-end", &ChTR_Graph_Build::source_file_end },

   { ".write-handoff-rtl", &ChTR_Graph_Build::write_handoff_rtl },
   { ".write-handoff-rts", &ChTR_Graph_Build::write_handoff_rts },
   { ".enter-expression", &ChTR_Graph_Build::enter_expression },
   { ".enter-statement", &ChTR_Graph_Build::enter_statement },
   { ".resolve-expression", &ChTR_Graph_Build::resolve_expression },
   { ".resolve-statement", &ChTR_Graph_Build::resolve_statement },
   { ".expression-to-expression", &ChTR_Graph_Build::expression_to_expression },
   { ".expression-to-statement", &ChTR_Graph_Build::expression_to_statement },

 }};

 auto it = static_map.find(fn);
 if(it != static_map.end())
 {
//  QString* a = new QString(arg);
  line_ops_.push_back({{}, fn_u{.fn0=it.value()}});
 }

}


void ChTR_Graph_Build::load_pregraph(QString file_path)
{
 QString lines;
 load_file(file_path, lines);
 read_graph_build_program(lines);
}




//void ChTR_Graph_Build::acc(QString contents)
//{
// acc << contents;
//}




// // // //

void ChTR_Graph_Build::init()
{
 ChTR_Channel_Package::set_channel_object_encoder([](ChTR_Channel_Object* cco)
 {
  //caon_ptr<ChTR_Channel_Object> pcco(cco);
  ChTR_Node* node = new ChTR_Node(caon_ptr<ChTR_Channel_Object>(cco));
  return (void*) node;
 });

 ChTR_Channel_Package::set_channel_object_decoder([](void* pv)//  -> ChTR_Channel_Object*
 {
  //caon_ptr<ChTR_Channel_Object> pcco(cco);
  ChTR_Node* node = (ChTR_Node*) pv;
  return node->channel_object().raw_pointer();
 });

 ChTR_Source_File* root_file = new ChTR_Source_File(document_->local_path());

 ChTR_Node* root_node = new ChTR_Node(root_file);

 graph_.set_root_node(root_node);
 current_statement_level_node_ = root_node;

 //graph_.set
}


void ChTR_Graph_Build::read_channel_string(QString channel_string)
{
 ChTR_Channel_Object* cco = new ChTR_Channel_Object(channel_string);

 if(!current_channel_package_)
 {
  current_channel_package_ = new ChTR_Channel_Package;
 }

 if(parse_context_.flags.awaiting_statement_body)
 {
  parse_context_.flags.awaiting_statement_body = false;
  current_code_statement_->set_channel_package(current_channel_package_);
 }

 current_channel_package_->add_channel_object(cco);
 current_channel_object_ = cco;

 parse_context_.flags.active_channel = true;
}

void ChTR_Graph_Build::enter_statement_body()
{
 ChTR_Code_Statement* ccs = new ChTR_Code_Statement;

 current_code_statement_ = ccs;
 parse_context_.flags.awaiting_statement_body = true;

 if(current_statement_level_node_ == graph_.root_node())
 {
  ChTR_Node* n = new ChTR_Node(ccs);
  current_statement_level_node_ << Sf/Qy.Root_Sequence >> n;
 }
}

void ChTR_Graph_Build::enter_channel_body()
{
 parse_context_.flags.open_channel_body = true;
}

void ChTR_Graph_Build::leave_channel_body()
{
 parse_context_.flags.open_channel_body = false;
}

void ChTR_Graph_Build::read_carrier_string(QString carrier_string)
{
 current_channel_object_->add_carrier(carrier_string);
}
