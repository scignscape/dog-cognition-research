
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_PARSE_CONTEXT__H
#define CHTR_PARSE_CONTEXT__H

#include "relae-graph/relae-parser.h"

#include "flags.h"

#include "aqns.h"
AQNS_(Chasm_TR)


class ChTR_Graph;
class ChTR_Node;

class ChTR_Parse_Context
{
 typedef ChTR_Node tNode;

public:
 flags_(1)
  flag_(1, open_channel_declaration)
  flag_(2, active_channel)
  flag_(3, open_channel_body)
  flag_(4, awaiting_statement_body)
 _flags_

 ChTR_Parse_Context();

};

_AQNS(Chasm_TR)

#endif
