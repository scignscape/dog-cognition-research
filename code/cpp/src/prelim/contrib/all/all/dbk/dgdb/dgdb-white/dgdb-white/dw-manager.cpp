
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dw-manager.h"
#include "dw-instance.h"

#include "wdb-manager.h"



#include <QDebug>

#include "kans.h"
#include "textio.h"


USING_KANS(TextIO)

extern "C" {
#include "whitedb/_whitedb.h"
}


USING_KANS(DGDB)


DW_Manager::DW_Manager(WDB_Manager* wdb_manager)
  :  dw_instance_(nullptr), wdb_manager_(wdb_manager) 
{

}

DW_Manager::DW_Manager(DW_Instance* dw_instance)
  :  dw_instance_(dw_instance), wdb_manager_(dw_instance->wdb_manager())
{
 
}


template<typename PROC_Type>
inline void _run_fn(PROC_Type fn, QByteArray& qba, u4 count);

template<typename PROC_Type>
inline void _run_fn(PROC_Type fn, void* rec, u4 count);

template<>
void _run_fn<std::function<void(void*, u4)>>(
  std::function<void(void*, u4)> fn, void* rec, u4 count)
{
 fn(rec, count);
}

template<>
void _run_fn<std::function<void(void*)>>(
  std::function<void(void*)> fn, void* rec, u4 count)
{
 fn(rec);
}


template<>
void _run_fn<std::function<void(QByteArray&, u4)>>(
  std::function<void(QByteArray&, u4)> fn, QByteArray& qba, u4 count)
{
 fn(qba, count);
}

template<>
void _run_fn<std::function<void(QByteArray&)>>(
  std::function<void(QByteArray&)> fn, QByteArray& qba, u4 count)
{
 fn(qba);
}



template<typename PROC_Type>
void DW_Manager::query_free_form_records(PROC_Type fn)
{
 WDB_Manager::Query_Iterator* qi = wdb_manager_->new_free_form_query_iterator();
 n8 brake = 0;
 u4 count = 0;
 while(brake == 0)
 {
  void* rec = wdb_manager_->cycle_query(qi);
  if(rec)
  {
   ++count;
   _run_fn(fn, rec, count);
  }
  else break;
 }
}


void DW_Manager::With_All_Free_Form_Records_Package::operator<<
  (std::function<void(void*)> fn)
{
 _this->query_free_form_records(fn);
}

void DW_Manager::With_All_Free_Form_Records_Package::operator<<
  (std::function<void(void*, u4)> fn)
{
 _this->query_free_form_records(fn);
}



template<typename PROC_Type>
void DW_Manager::query_tagged_records(QString tag, 
  PROC_Type fn)
{
 QPair<u4, u4> range = DW_Instance::hypernodes_id_range();

  // //  column 3 is the tag column ...
 WDB_Manager::Query_Iterator* qi = wdb_manager_->new_query_iterator(tag, 
   range.first, range.second, 3, 0);

 n8 brake = 0;

 u4 count = 0;
 while(brake == 0)
 {
  void* rec = wdb_manager_->cycle_query(qi);
  if(rec)
  {
   ++count;
   QByteArray qba;
   wdb_manager_->get_hypernode_payload(qi, qba);
   _run_fn(fn, qba, count);
  }
 }
}


void DW_Manager::With_All_Tagged_Records_Package::operator<<
  (std::function<void(QByteArray&)> fn)
{
 _this->query_tagged_records(tag, fn);

}

void DW_Manager::With_All_Tagged_Records_Package::operator<<
  (std::function<void(QByteArray&, u4)> fn)
{
 _this->query_tagged_records(tag, fn);
}


void DW_Manager::With_Check_Create_Package::operator<<
  (std::function<void()> fn)
{
 _this->check_create(fn);
}

void DW_Manager::With_Check_Create_Package::operator<<
  (std::function<void(QString)> fn)
{
 _this->check_create(fn);
}


void DW_Manager::check_create(std::function<void()> fn)
{
 dw_instance_->init();
 WDB_Instance* wdbi = wdb_manager_->first_new_white();
 if(wdbi)
   fn();
}

void DW_Manager::check_create(std::function<void(QString)> fn)
{
 dw_instance_->init(); 
 WDB_Instance* wdbi = wdb_manager_->first_new_white();
 if(wdbi)
   fn({});
}

u4 DW_Manager::get_tagged_record_count(QString tag)
{
 return 0;
}




/*
void DW_Manager::query_tagged_records(QString tag, 
  std::function<void(QByteArray&)> fn)
{
 QPair<u4, u4> range = DW_Instance::hypernodes_id_range();

  // //  column 3 is the tag column ...
 WDB_Manager::Query_Iterator* qi = wdb_manager_->new_query_iterator(tag, 
   range.first, range.second, 3);

 n8 brake = 0;

 while(brake == 0)
 {
  void* rec = wdb_manager_->cycle_query(qi);
  if(rec)
  {
   QByteArray qba;
   wdb_manager_->get_hypernode_payload(qi, qba);
   fn(qba);
  }
 }
}

void DW_Manager::query_tagged_records(QString tag, 
  std::function<void(QByteArray&, u4)> fn)
{
 QPair<u4, u4> range = DW_Instance::hypernodes_id_range();

  // //  column 3 is the tag column ...
 WDB_Manager::Query_Iterator* qi = wdb_manager_->new_query_iterator(tag, 
   range.first, range.second, 3);

 n8 brake = 0;

 u4 count = 0;
 while(brake == 0)
 {
  void* rec = wdb_manager_->cycle_query(qi);
  if(rec)
  {
   ++count;
   QByteArray qba;
   wdb_manager_->get_hypernode_payload(qi, qba);
   fn(qba, count);
  }
 }
}


*/

