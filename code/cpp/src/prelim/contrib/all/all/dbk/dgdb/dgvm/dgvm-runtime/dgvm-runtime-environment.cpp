
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include <QDebug>

#include <QFileInfo>
#include <QDirIterator>

#include <QString>
#include <QDataStream>


#include "dgvm-runtime-environment.h"

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

DGVM_Runtime_Environment::DGVM_Runtime_Environment(DGVM_Runtime* dgr)
  :  dgr_(dgr), database_(dgr->database())
{

}

DGVM_Runtime_Environment::DGVM_Runtime_Environment()
  :  dgr_(nullptr), database_(nullptr)
{

}

DGVM_Runtime_Environment::DGVM_Runtime_Environment(DgDb_Database_Instance* db)
  :  dgr_(new DGVM_Runtime), database_(db)
{
 dgr_->set_database(database_);
}

void DGVM_Runtime_Environment::init_runtime()
{
 dgr_ = new DGVM_Runtime;
}


void DGVM_Runtime_Environment::push_byte_value(u1 value)
{
 one_byte_deque_.push(value);
}

void DGVM_Runtime_Environment::push_opt_byte_value(u1 value)
{
 one_byte_deque_.push_opt(value);
}

u1 DGVM_Runtime_Environment::pull_byte_value()
{
 return one_byte_deque_.pull();
}

void DGVM_Runtime_Environment::new_hypernode()
{
 DgDb_Hypernode* result = dgr_->new_hypernode();

 push_ptr_value(result);
}

void DGVM_Runtime_Environment::init_database(QString folder)
{
 dgr_->init_database(folder, known_flags_);
 database_ = dgr_->database();
}


void DGVM_Runtime_Environment::init_flags(QString flags_list)
{
#if defined(QT5_MODE)
 known_flags_ = flags_list.split(";", Qt::SkipEmptyParts).toVector();
#elif defined(QT6_MODE)
 known_flags_ = flags_list.split(";", Qt::SkipEmptyParts);
#endif

 std::for_each(known_flags_.begin(), known_flags_.end(),
   [](QString& s) { s = s.trimmed(); } );
}


//using namespace tkrzw;


