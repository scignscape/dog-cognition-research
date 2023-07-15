
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chgr-mempad.h"

#include <cstdlib>

#include <QFileInfo>


ChGr_Mempad::ChGr_Mempad(u4 id, u4 size)
  :  id_(id), size_(size)
{

}

void ChGr_Mempad::init()
{
 raw_memory_ = (u1*) std::malloc(size_);
}


