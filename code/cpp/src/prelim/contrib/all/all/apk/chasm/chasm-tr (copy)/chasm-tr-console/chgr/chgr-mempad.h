
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHGR_MEMPAD__H
#define CHGR_MEMPAD__H


#include "accessors.h"

#include "global-types.h"

#include <QMap>

class ChGr_Hypernode;

class ChGr_Mempad
{ 
 u4 id_;
 u4 size_;

 u1* raw_memory_;

public:

 ChGr_Mempad(u4 id, u4 size);

 ACCESSORS(u1* ,raw_memory)

 void init();




};

#endif // CHGR_MEMPAD__H
