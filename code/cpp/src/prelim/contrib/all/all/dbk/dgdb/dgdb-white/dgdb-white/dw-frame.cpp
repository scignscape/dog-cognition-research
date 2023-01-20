//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dw-frame.h"

#include "dw-instance.h"


USING_KANS(DGDB)


DW_Frame::DW_Frame(DW_Instance* dw_instance, u4 id)
  :  dw_instance_(dw_instance),  id_(id)
{

} 

QPair<u4, u4> DW_Frame::commit()
{
 return dw_instance_->commit_new_triples(new_string_label_triples_);
}

DW_Record* DW_Frame::register_new_triple(DW_Record* source, QString connector, DW_Record* target, 
  DW_Dominion* dom)
{
 // // not using dom here ...
 u1 property_kind = 0;

 if(target->id() < 1024)
 {
  if(target->id() < 1000)
    property_kind = 255; // error?  Would be ever connect to an index label?
  else
    property_kind = target->id() - 1000; 
 }
 new_string_label_triples_.push_back({source, connector, target, dom, property_kind});
 return source;
}


