

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "chvm-code-generator.h"

#include "kernel/graph/chtr-node.h"
#include "kernel/graph/chtr-graph.h"
#include "kernel/query/chtr-query.h"

#include "chtr-code-statement.h"

#include "generators/chvm-code-statement-generator.h"

#include "chvm/chvm-code-statement.h"


USING_AQNS(Chasm_TR)


ChVM_Code_Generator::ChVM_Code_Generator(ChTR_Graph* ir_graph)
  :  ir_graph_(ir_graph), qry_(ChTR_Relae_Query::instance())
{

}

ChVM_Code_Statement_Generator ChVM_Code_Generator::statement_generator(caon_ptr<ChTR_Code_Statement> ccs)
{
 return ChVM_Code_Statement_Generator(*this, *ccs);
}

void ChVM_Code_Generator::graph_to_chvm(QString& chvm)
{
 ChTR_Node* root_node = ir_graph_->root_node();
 if(caon_ptr<ChTR_Node> n = qry_.Root_Sequence(root_node))
 {
  if(caon_ptr<ChTR_Code_Statement> ccs = n->code_statement())
  {
   ChVM_Code_Statement cvcs;
   //QString statement_lines;
   statement_generator(ccs).graph_to_chvm(cvcs);

   chvm = cvcs.lines_to_chvm();
  // graph_to_chvm(chvm, ccs);
  }
 }
}


