
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-frame.h"

#include "kernel/graph/chtr-node.h"

#include "aqns.h"

#include <QDebug>


USING_AQNS(Chasm_TR)

ChTR_Relae_Frame::ChTR_Relae_Frame()
 : node_frame<ChTR_Dominion>()
{


}

ChTR_Relae_Frame& ChTR_Relae_Frame::instance()
{
 static ChTR_Relae_Frame* the_instance = nullptr;
 if(!the_instance)
  the_instance = new ChTR_Relae_Frame;
 return *the_instance;
}
