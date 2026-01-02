
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-pregraph.h"

#include "kernel/frame/chtr-frame.h"

#include "kernel/graph/chtr-graph.h"

#include "chtr-grammar.h"

#include "kernel/query/chtr-query.h"


#include "chtr-source-file.h"

#include <QMap>

#include "global-types.h"

#include "chasm-tr/chtr-channel-object.h"
#include "chasm-tr/chtr-channel-package.h"
#include "chasm-tr/chtr-code-statement.h"

#include "relae-graph/relae-caon-ptr.h"
#include "relae-graph/relae-node-ptr.h"

#include "chtr-document.h"

//?#include "chasm-tr/kernel/dominion/types.h"


USING_AQNS(Chasm_TR)


ChTR_Pregraph::ChTR_Pregraph(ChTR_Document* d,
  ChTR_Parser& p, ChTR_Graph& g)
 : Flags(0)
   ,document_(d)
   ,graph_(g)
   ,parser_(p)
   ,fr_(ChTR_Relae_Frame::instance())
   ,qy_(ChTR_Relae_Query::instance())
   ,acc(&acc_)
   ,declared_handoff_state_(Carrier_Handoff_States::N_A)
   ,last_line_number_written_(0)
   ,current_line_number_(1)
   ,expression_nesting_count_(0)
   ,infix_count_(0)
{
 acc << "\n"; cut();
 acc << ".source-file $ " << d->local_path(); cut();
 acc << "\n"; cut();
}

//void ChTR_Pregraph::acc(QString contents)
//{
// acc << contents;
//}

void ChTR_Pregraph::enter_expression()
{
 flags.active_expression = true;
 ++expression_nesting_count_;
 acc << ".enter-expression"; cut();

 current_handoff_states_.push(Carrier_Handoff_States::Implicit_Return_to_Lambda);
}

void ChTR_Pregraph::leave_expression()
{
 acc << ".resolve-expression"; cut();
 check_write_handoff();
//? flags.active_expression = false;

//? acc << ".leave-expression"; cut();
 --expression_nesting_count_;
 if(expression_nesting_count_ == 0)
 {
  flags.active_expression = false;
  acc << ".expression-to-statement"; cut();
 }
 else
 {
  acc << ".expression-to-expression"; cut();

//  acc << ".resolve-expression"; cut();
//   ;.
//  pull-call-package ;.
 }

}

void ChTR_Pregraph::reenter_statement_level()
{
 temp_reenter_statement_level();
 grammar_->activate_context("statement-level-context");
}

void ChTR_Pregraph::temp_reenter_statement_level()
{
 if(flags.active_run_call)
 {
  check_resolve_statement();
  //  acc << ".resolve-symbol"; cut();
  flags.active_run_call = false;
 }
}


void ChTR_Pregraph::check_write_handoff()
{
 if(current_handoff_states_.isEmpty())
   return;

 switch (current_handoff_states_.pop())
 {
 case Carrier_Handoff_States::Implicit_Return_to_Lambda:
 case Carrier_Handoff_States::Return_to_Lambda:
  acc << ".write-handoff-rtl"; cut();
  break;

 case Carrier_Handoff_States::Return_to_Sigma:
  acc << ".write-handoff-rts"; cut();
  break;

 default:
  break;
 }

// current_handoff_state_ = Carrier_Handoff_States::N_A;
}

void ChTR_Pregraph::check_resolve_statement()
{
 while(flags.active_expression)
 {
  leave_expression();
 }

 if(flags.active_statement)
 {
  acc << ".resolve-statement"; cut();

 }

}

void ChTR_Pregraph::check_write_line_number()
{
 if(current_line_number_ != last_line_number_written_)
 {
  acc << "# " << current_line_number_; cut();
  last_line_number_written_ = current_line_number_;
 }
}

void ChTR_Pregraph::check_lines(QString text)
{
 u2 count = text.count(QLatin1Char('\n'));
 if(count > 0)
 {
  // //  we're probably not doing anything right here
  current_line_number_ += count;
 }
}


void ChTR_Pregraph::symbol_token(QString token)
{
 if(flags.infix_mode)
 {
  ++infix_count_;
  if(infix_count_ % 2)
  {
   acc << ".symbol-token $ " << token; cut();
  }
  else
  {
   auto ix = infix_line_indices_.pop();
   acc_lines_[ix.first].insert(ix.second, token);
  }
 }
 else
 {
  acc << ".symbol-token $ " << token; cut();
 }
}

void ChTR_Pregraph::prepare_carrier_declarations(QStringList symbols,
  QStringList tweens, QString type_token)
{
 check_resolve_statement();
 check_write_line_number();

 for(QString symbol : symbols)
 {
  acc << ".scoped-symbol-decl $ " << symbol; cut();

  check_lines(tweens.takeFirst());
  check_write_line_number();
 }

 acc << ".type-expression-token $ " << type_token; cut();
}

void ChTR_Pregraph::prepare_carrier_declaration(QString symbol,
  QString tween, QString type_token)
{
 check_resolve_statement();
 check_write_line_number();

 acc << ".scoped-symbol-decl $ " << symbol; cut();

 check_lines(tween);
 check_write_line_number();

 acc << ".type-expression-token $ " << type_token; cut();
}

void ChTR_Pregraph::resolve_source_file()
{
 check_resolve_statement();
 check_write_line_number();

 acc << ".source-file-end"; cut();
}


QString ChTR_Pregraph::pregraph_code()
{
 return acc_lines_.join("\n") + "\n\n .; end of source file ;. \n";
}

void ChTR_Pregraph::cut()
{
 if(acc_.trimmed().isEmpty())
   return;

 acc << " ;.";
 acc_lines_.push_back(acc_);
 acc_.clear();
}

void ChTR_Pregraph::check_enter_infix_mode()
{
 check_write_line_number();

 infix_count_ = 0;

 if(flags.infix_mode)
 {
  flags.infix_mode = false;

 }
 else
 {
  flags.infix_mode = true;
  acc << ".enter-infix-mode"; cut();

  enter_expression();

  acc << ".proc-name $ ";
  u4 acc_size = acc_.size();
  cut();

  infix_line_indices_.push({acc_lines_.size() - 1, acc_size});
 }
}

void ChTR_Pregraph::non_anchored_call(QString proc_name)
{
 check_write_line_number();

 proc_names_.push_back(proc_name);

 if(flags.active_expression)
 {
  acc << ".enter-expression"; cut();
 }
 else if(flags.active_statement)
 {
  acc << ".enter-expression"; cut();
  flags.active_expression = true;
 }
 else
 {
  acc << ".enter-statement"; cut();
  flags.active_statement = true;
 }

 acc << ".proc-name $ " << proc_name; cut();

 grammar_->activate_context("run-call-context");
 flags.active_run_call = true;
}

void ChTR_Pregraph::anchor_or_pin(QString symbol, QString tween, QString token)
{
 check_resolve_statement();
 check_lines(tween);
 check_write_line_number();

 if(token.isEmpty())
 {

 }
 else
 {
  acc << ".scoped-symbol-pin $ " << symbol; cut();

  check_lines(tween);
  check_write_line_number();

  if(token.startsWith("$"))
  {
   acc << ".pin-value-symbol $ " << token.mid(1); cut();
  }
  else if(token[0].isDigit())
  {
   acc << ".pin-value-literal $ " << token; cut();
  }
 }
}

// // // //

void ChTR_Pregraph::init()
{
}


//void ChTR_Pregraph::enter_statement_body()
//{
//}

//void ChTR_Pregraph::enter_channel_body()
//{
// parse_context_.flags.open_channel_body = true;
//}

//void ChTR_Pregraph::leave_channel_body()
//{
// parse_context_.flags.open_channel_body = false;
//}

//void ChTR_Pregraph::read_carrier_string(QString carrier_string)
//{
//// current_channel_object_->add_carrier(carrier_string);
//}
