
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHGR_ENVIRONMENT__H
#define CHGR_ENVIRONMENT__H


#include "accessors.h"

#include "global-types.h"

#include <QMap>

class ChGr_Hypernode;
class ChGr_Mempad;

class ChGr_Environment
{ 
 QMap<u4, ChGr_Hypernode*> hypernodes_by_id_;
 QMap<u4, ChGr_Mempad*> mempads_by_id_;

public:

 ChGr_Environment();

 static ChGr_Environment* instance();
 static void allocate_new_hypernode(u4& id);
 static void allocate_new_mempad(u4& id, u4 size);

 ACCESSORS(QMap<u4, ChGr_Hypernode*> ,hypernodes_by_id)
 ACCESSORS(QMap<u4, ChGr_Mempad*> ,mempads_by_id)



};

#endif // CHGR_ENVIRONMENT__H
