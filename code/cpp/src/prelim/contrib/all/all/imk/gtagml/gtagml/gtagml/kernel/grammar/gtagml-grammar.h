
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_GRAMMAR__H
#define GTAGML_GRAMMAR__H

#include "relae-graph/relae-grammar.h"

#include "kans.h"

KANS_(GTagML)

class GTagML_Graph;
class GTagML_Parser;
class GTagML_Graph_Build;

class GTagML_Grammar : public Relae_Grammar<GTagML_Graph, GTagML_Parser>
{
public:

 GTagML_Grammar();

 void init(GTagML_Parser& p, GTagML_Graph& g,
           GTagML_Graph_Build& graph_build);


};

_KANS(GTagML)

#endif // GTAGML_GRAMMAR__H
