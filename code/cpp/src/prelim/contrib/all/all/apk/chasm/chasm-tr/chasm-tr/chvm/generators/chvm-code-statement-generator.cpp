

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

 auto lambda_channel = [this, &cvcs](ChTR_Channel_Object& cco)
 {  
  QString ln = enter_channel("lambda");

  auto dissolve = [this, &ln, &cvcs]()
  {
   statement_line(&ln);
   cvcs.add_code_line(ln);
  };

  dissolve();

  for(ChTR_Carrier* car : cco.carriers())
  {
   car->check_literal();
   ln = car->symbol();
   dissolve();
  }

 };

 auto proc_channel = [this](ChTR_Channel_Object& cco)
 {
  qDebug() << cco.channel_kind();
 };


 ccp->all_channel_objects({
   {"l", lambda_channel},
   {"p", proc_channel},
  });

// QVector<ChTR_Channel_Object*> ccos;
// ccp->get_channel_objects(ccos);
// for(ChTR_Channel_Object* cco : ccos)
// {

// }

}


