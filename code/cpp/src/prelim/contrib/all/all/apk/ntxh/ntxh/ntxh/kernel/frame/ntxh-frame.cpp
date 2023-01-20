
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ntxh-frame.h"

#include "kernel/graph/ntxh-node.h"

#include "kans.h"

#include <QDebug>


USING_KANS(HGDMCore)

NTXH_Frame::NTXH_Frame()
 : node_frame<NTXH_Dominion>()
{


}

NTXH_Frame& NTXH_Frame::instance()
{
 static NTXH_Frame* the_instance = nullptr;
 if(!the_instance)
  the_instance = new NTXH_Frame;
 return *the_instance;
}
