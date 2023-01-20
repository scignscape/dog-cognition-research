
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NTXH_GRAMMAR__H
#define NTXH_GRAMMAR__H

#include "relae-graph/relae-grammar.h"

#include "kans.h"


KANS_(HGDMCore)

class NTXH_Graph;
class NTXH_Graph_Build;
class NTXH_Parser;

class NTXH_Grammar : public Relae_Grammar<NTXH_Graph, NTXH_Parser>
{

public:

 NTXH_Grammar();



 void init(NTXH_Parser& p, NTXH_Graph& g,
           NTXH_Graph_Build& graph_build);


};

_KANS(HGDMCore)


#endif // NTXH_GRAMMAR__H
