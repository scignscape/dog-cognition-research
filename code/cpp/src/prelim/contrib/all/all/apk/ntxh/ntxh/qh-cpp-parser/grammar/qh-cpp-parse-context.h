
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_CPP_PARSE_CONTEXT__H
#define QH_CPP_PARSE_CONTEXT__H

#include "relae-graph/relae-parser.h"

#include "flags.h"

#include "kans.h"
KANS_(Qh)


class Qh_CPP_Graph;
class Qh_CPP_Node;

class Qh_CPP_Parse_Context
{
 typedef Qh_CPP_Node tNode;

public:
 flags_(1)
  flag_(1, enum_def)
  flag_(2, enum_ops)
  flag_(3, enum_str)
  flag_(4, accessors)
 _flags_

 Qh_CPP_Parse_Context();

};

_KANS(Qh)

#endif
