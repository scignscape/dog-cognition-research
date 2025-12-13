
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chgr-environment.h"

#include "chgr-hypernode.h"
#include "chgr-mempad.h"

#include <QFileInfo>


ChGr_Environment::ChGr_Environment()
{

}

void ChGr_Environment::allocate_new_hypernode(u4& id)
{
 if(ChGr_Hypernode* cgh = new ChGr_Hypernode(id))
   instance()->hypernodes_by_id()[id] = cgh;
 else
   id = 0;
}

void ChGr_Environment::allocate_new_mempad(u4& id, u4 size)
{
 if(ChGr_Mempad* cgm = new ChGr_Mempad(id, size))
 {
  cgm->init();
  if(cgm->raw_memory())
  {
   instance()->mempads_by_id()[id] = cgm;
   return;
  }
  // // chance to cite the cause of the error?
  delete cgm;
 }
 id = 0;
}

ChGr_Environment* ChGr_Environment::instance()
{
 static ChGr_Environment* result = nullptr;
 if(!result)
   result = new ChGr_Environment;

 return result;
}
