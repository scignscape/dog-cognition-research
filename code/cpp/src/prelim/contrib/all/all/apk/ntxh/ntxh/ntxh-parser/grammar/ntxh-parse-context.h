
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NTXH_PARSE_CONTEXT__H
#define NTXH_PARSE_CONTEXT__H

#include "relae-graph/relae-parser.h"

#include "flags.h"

#include "kans.h"
KANS_(HGDMCore)


class NTXH_Graph;
class NTXH_Node;

class NTXH_Parse_Context
{
 typedef NTXH_Node tNode;

public:
 flags_(1)
  flag_(1, inside_comment)
  flag_(2, multiline_field)
  flag_(3, active_type_decl)
  flag_(4, expecting_field)
 _flags_

 NTXH_Parse_Context();

};

_KANS(HGDMCore)

#endif
