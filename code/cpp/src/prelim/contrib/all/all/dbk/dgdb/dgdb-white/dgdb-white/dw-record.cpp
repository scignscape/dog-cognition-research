//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dw-record.h"


USING_KANS(DGDB)


DW_Record::DW_Record(u4 id, void* wg_record)
  :  id_(id), 
     wg_record_(wg_record) 
{

} 

DW_Record::DW_Record()
  :  id_(0), wg_record_(nullptr)
{

}




