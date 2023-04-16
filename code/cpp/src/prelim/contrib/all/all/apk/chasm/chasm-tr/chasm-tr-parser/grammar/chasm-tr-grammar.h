
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_TR_GRAMMAR__H
#define CHASM_TR_GRAMMAR__H

#include "relae-graph/relae-grammar.h"

#include "aqns.h"


AQNS_(ChasmTR)

class Chasm_TR_Graph;
class Chasm_TR_Graph_Build;
class Chasm_TR_Parser;

class Chasm_TR_Grammar : public Relae_Grammar<Chasm_TR_Graph, Chasm_TR_Parser>
{

public:

 Chasm_TR_Grammar();



 void init(Chasm_TR_Parser& p, Chasm_TR_Graph& g,
           Chasm_TR_Graph_Build& graph_build);


};

_AQNS(ChasmTR)


#endif // CHASM_TR_GRAMMAR__H
