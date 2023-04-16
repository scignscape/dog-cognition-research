
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-tr-frame.h"

#include "kernel/graph/chasm-tr-node.h"

#include "aqns.h"

#include <QDebug>


USING_AQNS(ChasmTR)

Chasm_TR_Frame::Chasm_TR_Frame()
 : node_frame<Chasm_TR_Dominion>()
{


}

Chasm_TR_Frame& Chasm_TR_Frame::instance()
{
 static Chasm_TR_Frame* the_instance = nullptr;
 if(!the_instance)
  the_instance = new Chasm_TR_Frame;
 return *the_instance;
}
