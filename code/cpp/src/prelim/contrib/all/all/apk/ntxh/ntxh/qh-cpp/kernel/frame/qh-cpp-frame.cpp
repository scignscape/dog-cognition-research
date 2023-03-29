
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-cpp-frame.h"

#include "kernel/graph/qh-cpp-node.h"

#include "kans.h"

#include <QDebug>


USING_KANS(Qh)

Qh_CPP_Frame::Qh_CPP_Frame()
 : node_frame<Qh_CPP_Dominion>()
{


}

Qh_CPP_Frame& Qh_CPP_Frame::instance()
{
 static Qh_CPP_Frame* the_instance = nullptr;
 if(!the_instance)
  the_instance = new Qh_CPP_Frame;
 return *the_instance;
}
