
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
   ,last_line_number_written_(0)
   ,current_line_number_(1)
{
 acc << "\n"; cut();
 acc << ".source-file $ " << d->local_path(); cut();
 acc << "\n"; cut();
}

//void ChTR_Pregraph::acc(QString contents)
//{
// acc << contents;
//}

void ChTR_Pregraph::check_resolve_statement()
{
 if(flags.active_run_call)
 {
  acc << ".resolve-symbol"; cut();

  grammar_->activate_context("statement-level-context");
  flags.active_run_call = false;
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
 acc << ".symbol-token $ " << token; cut();
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

QString ChTR_Pregraph::pregraph_code()
{
 check_resolve_statement();
 check_write_line_number();

 acc << ".source-file-end"; cut();

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

void ChTR_Pregraph::non_anchored_call(QString proc_name)
{
 check_write_line_number();

 proc_names_.push_back(proc_name);

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
