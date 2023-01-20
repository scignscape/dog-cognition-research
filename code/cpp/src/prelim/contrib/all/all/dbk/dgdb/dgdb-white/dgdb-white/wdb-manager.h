
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef WDB_MANAGER__H
#define WDB_MANAGER__H

#include <QMap>
#include <QString>

#include "global-types.h"

#include "accessors.h"

#include "kans.h"

#include "dw-record.h"


KANS_(DGDB)

class WDB_Instance;
class DW_Instance;

class DW_Stage_Value;

class WDB_Manager
{
 DW_Instance* dw_instance_;

 u2 max_num_code_;
 n8 default_mem_size_;

 QMap<u2, WDB_Instance*> whites_;
 QMap<QString, WDB_Instance*> whites_by_name_;

 WDB_Instance* current_white_;  
 
 WDB_Instance* first_new_white_;
 WDB_Instance* last_new_white_;

 QString db_root_folder_;

 void to_ntxh(QString& result);
 void update_ntxh();


public:

 WDB_Manager(DW_Instance* dw_instance);

 ACCESSORS(n8 ,default_mem_size)

 ACCESSORS(WDB_Instance* ,current_white)
 ACCESSORS(QString ,db_root_folder)


 ACCESSORS(WDB_Instance* ,first_new_white)
 ACCESSORS(WDB_Instance* ,last_new_white)


 struct Query_Iterator;

 void* cycle_query(Query_Iterator* qi);
 void get_hypernode_payload(Query_Iterator* qi, QByteArray& qba, u4 qba_index = 1);

 void init_from_ntxh();

 QString get_restore_file();

 WDB_Instance* check_reinit();
 WDB_Instance* get_current_white();
 WDB_Instance* get_white(QString name);

 WDB_Instance* new_white(u2 num_code = 0, n8 mem = 0, QString name = {});
 WDB_Instance* new_white(QString name)
 {
  return new_white(0, 0, name);
 }
 WDB_Instance* new_white(u2 num_code, QString name)
 {
  return new_white(num_code, 0, name);
 }

 Query_Iterator* new_query_iterator(QString criterion, 
   u4 id_low, u4 id_high, u4 col, u4 id_col = 0);

 Query_Iterator* new_free_form_query_iterator(u4 threshold = 0x1000, u4 id_col = 0);

 DW_Record resolve_ref(Query_Iterator* qi);

 Query_Iterator* new_single_index_query_iterator(QString key,
   u4 id_low, u4 id_high, u4 key_col, u4 val_col,
   DW_Stage_Value& dwsv, u4 ref_col, u4 id_col = 0);

};


_KANS(DGDB)


#endif // WDB_MANAGER__H


