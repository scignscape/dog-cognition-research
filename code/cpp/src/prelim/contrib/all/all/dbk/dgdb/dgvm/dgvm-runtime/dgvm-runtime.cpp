
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include <QDebug>

#include <QFileInfo>
#include <QDirIterator>

#include <QString>
#include <QDataStream>


#include "dgvm-runtime.h"



#include "tkrzw_dbm_hash.h"

#include "dgdb/dh-location-structure.h"

using namespace _class_DH_Location_Structure;

#include "dgdb/dgdb-database-instance.h"

#include "dgdb/dtb/sv-wrapper.h"

#include "dgdb/types/stage/dh-stage-code.h"
#include "dgdb/dh-stage-value.h"

#include "dgdb-demo/queue-demo-class.h"

#include "dgdb/dgdb-hypernode.h"

#include "dgdb/conversions.h"

#include "dgdb/types/dh-type-system.h"
#include "dgdb/types/dh-type.h"

#include "dgdb/graph/dh-frame.h"
#include "dgdb/graph/dh-dominion.h"
#include "dgdb/dh-instance.h"

#include "macro-ladder.h"


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#include <string>
#include <vector>
#include <iostream>



USING_KANS(DGVM)

DGVM_Runtime::DGVM_Runtime()
  :  database_(nullptr)
{

}

DgDb_Hypernode* DGVM_Runtime::new_hypernode()
{
 DgDb_Hypernode* result = database_->new_hypernode();
 return result;
}

//u1 DGVM_Runtime::_get_ptr_tag(n8 raw_value)
//{
// mz::tagged_ptr<void**> tptr;
// tptr.set_raw_value(raw_value);
// return tptr.tag();
//}


void DGVM_Runtime::init_database(QString folder, const QVector<QString>& known_flags)
{
 database_ = new DgDb_Database_Instance(folder);

#define CURRENT_KNOWN_FLAGS(macro_name) macro_name(\
   scratch_mode, local_scratch_mode, auto_stage, auto_commit, avoid_record_pointers, \
   temp_reinit, reset_tkrzw, whitedb_auto_commit, tkrzw_auto_commit \
 )

// bool scratch_mode:1;
// bool local_scratch_mode:1;
// bool auto_stage:1;
// bool auto_commit:1;
// bool avoid_record_pointers:1;
// bool :1;
// bool reset_tkrzw:1;
// bool whitedb_auto_commit:1;
// bool tkrzw_auto_commit:1;



 #define _TEMP_MACRO_LADDER(num ,_f) static const u1 f_##_f = num;
 CURRENT_KNOWN_FLAGS(TEMP_MACRO_LADDER)
 #undef _TEMP_MACRO_LADDER

 static QMap<QString, u1> flags_map {{
    #define _TEMP_MACRO_LADDER(num ,_f) {#_f, f_##_f},
    CURRENT_KNOWN_FLAGS(TEMP_MACRO_LADDER)
    #undef _TEMP_MACRO_LADDER
   }};

 for(QString f : known_flags)
 {
  switch(flags_map.value(f))
  {
  case 0: break;

  #define _TEMP_MACRO_LADDER(num ,_f) \
  case f_##_f: database_->Config.flags._f = f_##_f; break;
  CURRENT_KNOWN_FLAGS(TEMP_MACRO_LADDER)
  #undef _TEMP_MACRO_LADDER
  }
 }

 database_->init_dtb_package();
 database_->init_type_system();
 database_->check_construct_files();
 database_->check_interns_dbm();
 database_->check_nodes_dbm();
 database_->init_indices();
 database_->read_hypernode_count_status();
 database_->read_interns_count_status();
 database_->init_dwb_blocks();


}


//void DGVM_Runtime::init_flags(QString flags_list)
//{
//#if defined(QT5_MODE)
// known_flags_ = flags_list.split(";", Qt::SkipEmptyParts).toVector();
//#elif defined(QT6_MODE)
// known_flags_ = flags_list.split(";", Qt::SkipEmptyParts);
//#endif

// std::for_each(known_flags_.begin(), known_flags_.end(),
//   [](QString& s) { s = s.trimmed(); } );
//}


//using namespace tkrzw;


