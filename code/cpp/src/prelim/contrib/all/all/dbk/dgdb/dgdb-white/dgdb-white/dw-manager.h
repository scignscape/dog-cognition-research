
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DW_MANAGER__H
#define DW_MANAGER__H

#include <QMap>
#include <QString>

#include "global-types.h"

#include "accessors.h"


#include "kans.h"

KANS_(DGDB)

class WDB_Manager;

class WDB_Instance;
class DW_Instance;

class DW_Manager
{
 WDB_Manager* wdb_manager_;
 DW_Instance* dw_instance_;

 struct With_Check_Create_Package
 {
  DW_Manager* _this;
  void operator <<
    (std::function<void()> fn);
  void operator <<
    (std::function<void(QString reinit_path)> fn);

 };

 struct With_All_Tagged_Records_Package
 {
  DW_Manager* _this;
  QString tag;
  void operator <<
    (std::function<void(QByteArray&)> fn);
  void operator <<
    (std::function<void(QByteArray&, u4)> fn);
 };

 struct With_All_Free_Form_Records_Package
 {
  DW_Manager* _this;
  void operator <<
    (std::function<void(void*)> fn);
  void operator <<
    (std::function<void(void*, u4)> fn);
 };


public:

 DW_Manager(WDB_Manager* wdb_manager);
 DW_Manager(DW_Instance* dw_instance);

 u4 get_tagged_record_count(QString tag);

// void update_tagged_record();

 template<typename PROC_Type>
 void query_tagged_records(QString tag, 
   PROC_Type fn);


 template<typename PROC_Type>
 void query_free_form_records(PROC_Type fn);


 void check_create(std::function<void()> fn);
 void check_create(std::function<void(QString)> fn);

//   std::function<void(QByteArray&)> fn);
// void query_tagged_records(QString tag, 
//   std::function<void(QByteArray&, u4)> fn);

 With_Check_Create_Package with_check_create()
 {
  return {this};
 }

 With_All_Tagged_Records_Package with_all_tagged_records(QString tag)
 {
  return {this, tag};
 }

 With_All_Free_Form_Records_Package with_all_free_form_records()
 {
  return {this};
 }

};


_KANS(DGDB)


#endif // DW_MANAGER__H


