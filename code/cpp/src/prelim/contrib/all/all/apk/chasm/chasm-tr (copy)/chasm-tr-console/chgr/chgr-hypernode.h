
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHGR_HYPERNODE__H
#define CHGR_HYPERNODE__H


#include "accessors.h"

#include "global-types.h"


class ChGr_Hypernode
{ 
 u4 id_;

public:

 ChGr_Hypernode(u4 id);

 ACCESSORS(u4 ,id)



};

#endif // CHGR_HYPERNODE__H
