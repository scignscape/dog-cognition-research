

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-annotation-environment.h"

#include <QDataStream>


#include "dgdb/dgdb-database-instance.h"

#include "dhax-annotation-folder.h"
#include "dhax-annotation-group.h"


#define DDI DgDb_Database_Instance& ddi = *dgdb_;

DHAX_Annotation_Environment::DHAX_Annotation_Environment()
  :  dgdb_(nullptr) //new DgDb_Database_Instance)
{

}

void DHAX_Annotation_Environment::default_extensions()
{
 data_file_extensions_ << "xml";
 image_file_extensions_ << "png" << "jpg" << "jpeg"; // etc.
}


DHAX_Annotation_Folder* DHAX_Annotation_Environment::add_data_folder(QString path)
{
 DHAX_Annotation_Folder* result = new DHAX_Annotation_Folder;
 result->read_data_path(path, data_file_extensions_);
 data_folders_[path] = result;
 return result;
}

DHAX_Annotation_Folder* DHAX_Annotation_Environment::add_image_folder(QString path)
{
 DHAX_Annotation_Folder* result = new DHAX_Annotation_Folder;
 result->read_image_path(path, image_file_extensions_);
 image_folders_[path] = result;
 return result;
}


DHAX_Annotation_Group* DHAX_Annotation_Environment::add_annotation_group(QString path)
{
 DHAX_Annotation_Group* result = new DHAX_Annotation_Group;
 result->set_target_path(path);
 return result;
}


DgDb_Database_Instance* DHAX_Annotation_Environment::dgdb(QString path)
{
// dgdb_->set_private_folder_path(path);
// return dgdb_;
}


//void DHAX_Annotation_Environment::init_database()
//{
// DDI
// ddi.init_dtb_package();
// ddi.init_type_system();
// ddi.check_construct_files();
// ddi.check_interns_dbm();
// ddi.check_nodes_dbm();
// ddi.init_indices();
// ddi.read_hypernode_count_status();
// ddi.read_interns_count_status();
// ddi.init_dwb_blocks();
//}


void DHAX_Annotation_Environment::supply_data(QByteArray& qba)
{
 QDataStream qds(&qba, QIODevice::WriteOnly);
// qds << a_string_ << a_number_;


#define TEMP_MACRO(cast, type ,name) << cast name##_
// qds _Demo_Class_fm(TEMP_MACRO);
#undef TEMP_MACRO


}

void DHAX_Annotation_Environment::absorb_data(const QByteArray& qba)
{
 QDataStream qds(qba);
// qds >> a_string_ >> a_number_;


#define TEMP_MACRO(cast, type ,name) >> cast name##_
// qds _Demo_Class_fm(TEMP_MACRO);
#undef TEMP_MACRO
}



