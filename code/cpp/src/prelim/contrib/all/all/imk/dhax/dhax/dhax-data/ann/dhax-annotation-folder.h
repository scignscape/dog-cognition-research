
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DHAX_ANNOTATION_FOLDER__H
#define DHAX_ANNOTATION_FOLDER__H

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

class DHAX_Annotation_Group;
class DHAX_Annotation_Folder;

class DHAX_Annotation_Folder
{
 QString path_;

 QStringList image_files_;
 QStringList data_files_;

public:

 DHAX_Annotation_Folder();

 ACCESSORS(QString ,path)
 ACCESSORS__CONST_RGET(QStringList ,data_files)
 ACCESSORS__CONST_RGET(QStringList ,image_files)

 bool data_is_empty() { return data_files_.isEmpty(); }
 bool images_is_empty() { return image_files_.isEmpty(); }

 void read_image_path(QString path, QStringList extensions);
 void read_data_path(QString path, QStringList extensions);
 void read_path(QString path, QStringList extensions, QStringList& target);

 void supply_data(QByteArray& qba);
 void absorb_data(const QByteArray& qba);


};



#endif // DHAX_ANNOTATION_ENVIRONMENT__H
