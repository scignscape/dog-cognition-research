
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_CPP_GRAMMAR__H
#define QH_CPP_GRAMMAR__H

#include "relae-graph/relae-grammar.h"

#include "kans.h"


KANS_(Qh)

class Qh_CPP_Graph;
class Qh_CPP_Graph_Build;
class Qh_CPP_Parser;

class Qh_CPP_Grammar : public Relae_Grammar<Qh_CPP_Graph, Qh_CPP_Parser>
{

public:

 Qh_CPP_Grammar();



 void init(Qh_CPP_Parser& p, Qh_CPP_Graph& g,
           Qh_CPP_Graph_Build& graph_build);


};

_KANS(Qh)


#endif // Qh_CPP_GRAMMAR__H
