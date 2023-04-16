
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-tr-parser.h"

USING_AQNS(ChasmTR)

Chasm_TR_Parser::Chasm_TR_Parser(caon_ptr<Chasm_TR_Graph> g)
 : Relae_Parser<Chasm_TR_Galaxy>(g)
{
}

