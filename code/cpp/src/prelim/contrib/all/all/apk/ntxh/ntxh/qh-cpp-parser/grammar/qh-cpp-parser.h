
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_CPP_PARSER__H
#define QH_CPP_PARSER__H

#include "relae-graph/relae-parser.h"

#include "qh-cpp/kernel/qh-cpp-dominion.h"

#include "kans.h"
KANS_(Qh)

class Qh_CPP_Graph;

class Qh_CPP_Parser : public Relae_Parser<Qh_CPP_Galaxy>
{
 QString raw_text_;

public:

 ACCESSORS(QString ,raw_text)

 Qh_CPP_Parser(caon_ptr<Qh_CPP_Graph> g);

};

_KANS(Qh)


#endif
