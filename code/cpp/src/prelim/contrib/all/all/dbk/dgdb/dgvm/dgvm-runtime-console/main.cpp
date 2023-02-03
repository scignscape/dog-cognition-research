
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include <QDebug>

#include <QFileInfo>
#include <QDirIterator>

#include <QString>
#include <QDataStream>


#include "dgvm-runtime/dgvm-runtime.h"

USING_KANS(DGVM)


int main(int argc, char *argv[])
{
 DGVM_Runtime dgr;

 dgr.init_flags("avoid_record_pointers; tkrzw_auto_commit; scratch_mode; reset_tkrzw");

 dgr.init_database();


// DgDb_Database_Instance ddi(DEFAULT_DEV_DGDB_FOLDER "/t1");

// ddi.Config.flags.avoid_record_pointers = true;
// ddi.Config.flags.tkrzw_auto_commit = true;
// //ddi.Config.flags.local_scratch_mode = true;
// ddi.Config.flags.scratch_mode = true;
// ddi.Config.flags.reset_tkrzw = true;

// ddi.init_dtb_package();
// ddi.init_type_system();
// ddi.check_construct_files();
// ddi.check_interns_dbm();
// ddi.check_nodes_dbm();
// ddi.init_indices();
// ddi.read_hypernode_count_status();
// ddi.read_interns_count_status();
// ddi.init_dwb_blocks();

// qDebug() << "blocks ftok key: " << ddi.ftok_key("blocks");

// DgDb_Hypernode* dh = ddi.new_hypernode();

// DH_Location_Structure dls = ddi (dh)-> property_site("test"); //(ddi/dh) //sigma(ddi, dh)

// ddi (dh)-> set_property("test", QVariant(34));
// u1 ch = ddi (dh)-> get_property<u1>("test"); //.value<u1>();


// qDebug() << "ch = " << ch;

}





//#include "tkrzw_dbm_hash.h"

//#include "dgdb/dh-location-structure.h"

//using namespace _class_DH_Location_Structure;

//#include "dgdb/dgdb-database-instance.h"

//#include "dgdb/dtb/sv-wrapper.h"

//#include "dgdb/types/stage/dh-stage-code.h"
//#include "dgdb/dh-stage-value.h"

//#include "dgdb-demo/queue-demo-class.h"

//#include "dgdb/dgdb-hypernode.h"

//#include "dgdb/conversions.h"

//#include "dgdb/types/dh-type-system.h"
//#include "dgdb/types/dh-type.h"

//#include "dgdb/graph/dh-frame.h"
//#include "dgdb/graph/dh-dominion.h"
//#include "dgdb/dh-instance.h"


//#include <sys/types.h>
//#include <sys/ipc.h>
//#include <sys/shm.h>


////extern "C" {
////#include "whitedb/_whitedb.h"
////}

//#include "dgdb-demo/test-class.h"
//#include "dgdb-demo/demo-class.h"

//using namespace tkrzw;


