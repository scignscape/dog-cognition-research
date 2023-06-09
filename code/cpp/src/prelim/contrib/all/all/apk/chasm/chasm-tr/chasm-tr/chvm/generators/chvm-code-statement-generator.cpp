

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "chvm-code-statement-generator.h"

#include "kernel/graph/chtr-node.h"
#include "kernel/graph/chtr-graph.h"
#include "kernel/query/chtr-query.h"

#include "chtr-code-statement.h"

#include "chtr-channel-package.h"

#include "chtr-channel-object.h"

#include "chvm/chvm-code-statement.h"
#include "chtr-carrier.h"

#include <QDebug>


USING_AQNS(Chasm_TR)


ChVM_Code_Statement_Generator::ChVM_Code_Statement_Generator(ChVM_Code_Generator& gen,
  ChTR_Code_Statement& ccs)  :  gen_(gen), ccs_(ccs)
{

}



void ChVM_Code_Statement_Generator::graph_to_chvm(ChVM_Code_Statement& cvcs)
{
 ChTR_Channel_Package* ccp = ccs_.channel_package();

 auto blank = [&cvcs]()
 {
  cvcs.add_blank_line();
 };

 blank();

 QString ln = " .; statement";

 auto dissolve = [this, &ln, &cvcs](QVector<QString> new_lns = {})
 {
  if(new_lns.isEmpty())
  {
   statement_line(&ln);
   cvcs.add_code_line(ln);
  }
  else
  {
   for(QString new_ln : new_lns)
   {
    statement_line(&new_ln);
    cvcs.add_code_line(new_ln);
   }
  }
 };

 dissolve(); 
 blank();

 dissolve({"init_new_ghost_scope", "push_carrier_deque"});
 blank();

 dissolve({"new_call_package"});


 auto lambda_channel = [this, dissolve, blank, &ln](ChTR_Channel_Object& cco)
 {
  blank();

  ln = enter_channel("lambda");
  dissolve();

  for(ChTR_Carrier* car : cco.carriers())
  {
   car->check_literal();
   QPair<QString, QString> lit = car->literal_info_string();

   // type pointer ...

   if(car->literal_info.flags.known_symbol)
    ln = "load_symbol $ %1 %2"_qt.arg(lit.first).arg(lit.second);
   else
    ln = "load_symbol_%1 $ %2"_qt.arg(lit.first).arg(lit.second);
   dissolve();


   //if(type_pointer)
   dissolve({"gen_carrier_lsr"});

  }

  blank();
  dissolve({"add_carriers"});

 };

 auto proc_channel = [this, &ln, dissolve, blank](ChTR_Channel_Object& cco)
 {
  blank();
  ln = enter_channel("proc");
  dissolve();

  QString pn = cco.get_proc_name();

  if(pn.isEmpty())
  {
   // what here?
  }

  ln = "load_proc_name $ %1"_qt.arg(pn);
  dissolve();
 };


 ccp->all_channel_objects({
   {"l", lambda_channel},
   {"p", proc_channel},
  });


// ln = "run_proc_eval";
 blank();
 dissolve({"run_proc_eval"});
 blank();
 dissolve({"reset_carrier_deque", "clear_current_ghost_scope"});
 blank();

// QVector<ChTR_Channel_Object*> ccos;
// ccp->get_channel_objects(ccos);
// for(ChTR_Channel_Object* cco : ccos)
// {

// }

}


