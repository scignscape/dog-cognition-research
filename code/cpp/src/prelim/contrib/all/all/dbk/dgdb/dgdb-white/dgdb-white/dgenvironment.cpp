
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dgenvironment.h"

#include "dw-instance.h"

KANS_(DGDB)

DW_Instance* DGEnvironment(QString path)
{
 DW_Instance* result = new DW_Instance;
 result->set_db_root_folder(path);
 return result; 
}

_KANS(DGDB)


