//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dw-query-layer.h"

#include "wdb-manager.h"
#include "dw-instance.h"

USING_KANS(DGDB)


DW_Query_Layer::DW_Query_Layer(DW_Instance& dw)
  :  dw_(dw)
{

} 

void DW_Query_Layer::single_field_query(QString key, DW_Stage_Value& dwsv,
  std::function<n8(DW_Record)> fn)
{
 qDebug() << "key = " << key;

 QPair<u4, u4> range;

 u1 key_col, val_col, ref_col;

 WDB_Manager* wdbm = dw_.make_single_indexed_query_basis(range, key_col, val_col, ref_col);

 WDB_Manager::Query_Iterator* qi = wdbm->new_single_index_query_iterator(key, range.first, range.second,
   key_col, val_col, dwsv, ref_col);

 n8 brake = 0;

 u4 count = 0;
 while(brake == 0)
 {
  void* rec = wdbm->cycle_query(qi);
  if(rec)
  {
   ++count;
   DW_Record dwr = wdbm->resolve_ref(qi);
   if(dwr.id())
     fn(dwr);
  }
  else brake = 1;
 }

}
