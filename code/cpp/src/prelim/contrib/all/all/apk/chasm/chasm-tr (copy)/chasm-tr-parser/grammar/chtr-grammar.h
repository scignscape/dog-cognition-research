
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_GRAMMAR__H
#define CHTR_GRAMMAR__H

#include "relae-graph/relae-grammar.h"

#include "aqns.h"


AQNS_(Chasm_TR)

class ChTR_Graph;
class ChTR_Graph_Build;
class ChTR_Parser;

class ChTR_Grammar : public Relae_Grammar<ChTR_Graph, ChTR_Parser>
{

public:

 ChTR_Grammar();



 void init(ChTR_Parser& p, ChTR_Graph& g,
           ChTR_Graph_Build& graph_build);


};

_AQNS(Chasm_TR)


#endif // CHTR_GRAMMAR__H
