
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DHAX_ANNOTATION_ENVIRONMENT__H
#define DHAX_ANNOTATION_ENVIRONMENT__H

#include "accessors.h"

#include "global-types.h"


#include <QString>
#include <QByteArray>

#include <QDateTime>



 // //  defines the serialization order ...
#define _Demo_Class_fm(field      )field(,\
 QString ,string_in_record        )field(,\
 QString ,string_for_query        )field(,\
 QString ,string_encoded          )field(,\
 u4 ,u4_in_block                  )field(,\
 u4 ,u4_for_query                 )field(,\
 s1 ,s1_in_block                  )field(,\
 s2 ,s2_for_query                 )field(,\
 QDateTime ,datetime_in_block     )field(,\
 QDateTime ,datetime_for_query    )field(,\
 QTime ,time_in_block             )field(,\
 QTime ,time_for_query            )field(,\
 QDate ,date_in_block             )field(,\
 QDate ,date_for_query            )field(,\
 Demo_Class::Test_Enum ,test_enum             )field(,\
 Demo_Class::Test_Enum_Flags ,test_enum_flags )\


//(u1&), Test_Enum ,test_enum    )field(,\
//(u1&), Test_Enum_Flags ,test_enum_flags)

class AXFI_Annotation_Environment;


#include "kans.h"

KANS_CLASS_DECLARE(DGDB ,DgDb_Database_Instance)

USING_KANS(DGDB)

class DHAX_Annotation_Folder;
class DHAX_Annotation_Group;


class DHAX_Annotation_Environment
{
 DgDb_Database_Instance* dgdb_;

 QMap<QString, DHAX_Annotation_Folder*> data_folders_;
 QMap<QString, DHAX_Annotation_Folder*> image_folders_;
 //AXFI_Annotation_Group* axfi_annotation_group_;

 QStringList data_file_extensions_;
 QStringList image_file_extensions_;


public:

 DHAX_Annotation_Environment();

 ACCESSORS(DgDb_Database_Instance* ,dgdb)

 DHAX_Annotation_Folder* add_data_folder(QString path);
 DHAX_Annotation_Folder* add_image_folder(QString path);

 DHAX_Annotation_Group* add_annotation_group(QString path);

 void default_extensions();

 void supply_data(QByteArray& qba);
 void absorb_data(const QByteArray& qba);

 DgDb_Database_Instance* dgdb(QString path);

 void init_database();
};



#endif // DHAX_ANNOTATION_ENVIRONMENT__H
