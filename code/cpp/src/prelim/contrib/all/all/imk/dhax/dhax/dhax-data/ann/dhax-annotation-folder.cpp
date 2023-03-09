

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-annotation-folder.h"

#include <QDataStream>
#include <QDirIterator>



DHAX_Annotation_Folder::DHAX_Annotation_Folder()
{

}

void DHAX_Annotation_Folder::read_image_path(QString path,
  QStringList extensions)
{
 read_path(path, extensions, image_files_);
}

void DHAX_Annotation_Folder::read_data_path(QString path,
  QStringList extensions)
{
 read_path(path, extensions, data_files_);
}

void DHAX_Annotation_Folder::read_path(QString path,
  QStringList extensions, QStringList& target)
{
 path_ = path;

 QStringList exts;
 std::transform(extensions.begin(), extensions.end(), std::back_inserter(exts),
   [](QString s) {return "*." + s;});

 QDirIterator qdi(path, exts);

 while(qdi.hasNext())
 {
  qdi.next();
  target << qdi.fileInfo().canonicalFilePath();
 }
}

void DHAX_Annotation_Folder::supply_data(QByteArray& qba)
{
 QDataStream qds(&qba, QIODevice::WriteOnly);
// qds << a_string_ << a_number_;


#define TEMP_MACRO(cast, type ,name) << cast name##_
// qds _Demo_Class_fm(TEMP_MACRO);
#undef TEMP_MACRO


}

void DHAX_Annotation_Folder::absorb_data(const QByteArray& qba)
{
 QDataStream qds(qba);
// qds >> a_string_ >> a_number_;


#define TEMP_MACRO(cast, type ,name) >> cast name##_
// qds _Demo_Class_fm(TEMP_MACRO);
#undef TEMP_MACRO
}



