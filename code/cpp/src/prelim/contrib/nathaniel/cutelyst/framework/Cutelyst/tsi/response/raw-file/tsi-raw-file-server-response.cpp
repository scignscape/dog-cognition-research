
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "tsi-raw-file-server-response.h"

#include "../tsi-server-response.h"

#include "../../tsi-global-types.h"

#include "../../tsi-resource-info.h"

#include <QDebug>

#include <QFile>
#include <QDir>

#include <QDateTime>

#include <syslog.h>



#define DEFAULT_FOLDER_BRANCH "public"_qt

TSI_Raw_File_Server_Response::TSI_Raw_File_Server_Response(TSI_Server_Response* main_response,
  QString format, QString url_path, s1 response_mode, QString folder_branch)
  :  main_response_(main_response),
     format_(format), url_path_(url_path), response_mode_(response_mode) //, binary_content_(nullptr)
{
 if(folder_branch.isEmpty())
   folder_branch_ = DEFAULT_FOLDER_BRANCH;
 else
   folder_branch_ = folder_branch;
}


void TSI_Raw_File_Server_Response::check_rename(QString& path, QString prepend)
{
 // //  we know path starts with "/~" ...



 s2 index = path.indexOf(QChar::fromLatin1('~'), 2);
 if(index == -1)
   return;

 QString mid = path[0] + path.mid(2, index - 2);
 QString pmid = prepend + mid;

 QString rename_modification, rename_pattern;

 static QMap<QString, QStringList> rename_options;

//? auto it = rename_options.find(pmid);
 auto it = rename_options.find(mid);

 if(it == rename_options.end())
 {
  QDir qd(pmid);

  if(qd.exists("rename"_qt))
  {
   QString rename_file_string = qd.absoluteFilePath("rename"_qt);
   QFile rename_file(rename_file_string);
   if(rename_file.open(QIODevice::Text | QIODevice::ReadOnly))
   {
    QString rename = QString::fromLatin1(rename_file.readAll())
      .simplified().replace(QChar::fromLatin1(' '), ""_qt);
    QStringList qsl = rename.split(QChar::fromLatin1(':'));
    if(qsl.length() >= 2)
    {
     rename_options[mid] = qsl;
     rename_modification = qsl[0];
     rename_pattern = qsl[1];
    }

    qDebug() << "Using rename file " << rename_file;

   }
  }
  else
    rename_options[pmid] = QStringList {};
 }
 else
 {
  if(it->empty())
    return;

  rename_modification = (*it)[0];
  rename_pattern = (*it)[1];
 }

 if(rename_modification.isEmpty())
   return;

 if(rename_modification == "cut"_qt)
 {
  QString after_pattern = path.mid(index + 1);
  path = mid + rename_pattern + after_pattern;

  main_response_->log_or_debug("resetting path: %1\n"_qt.arg(path));
 }
}

void TSI_Raw_File_Server_Response::check_rewrite_nonexistent_path(QString& path)
{
 QFileInfo qfi(path);
 if(qfi.exists())
   return;

 path = QString::fromLatin1(PREFERRED_SERVER_FILES_FOLDER DEFAULT_NO_IMAGE_PATH);
}

void TSI_Raw_File_Server_Response::proceed(Cutelyst::Context* c, QString& response_file, QString prepend)
{
 QStringList paths = main_response_->path_components();
 if(paths.isEmpty())
   return;
 response_file = paths.first();

 add_extension(response_file);
}

void TSI_Raw_File_Server_Response::add_extension(QString& response_file)
{
 static QMap<QString, QString> static_map {{
   "h"_qt, ".html"_qt,
 }};

 auto it = static_map.find(format_);

 if(it == static_map.end())
   return;

 response_file += it.value();
}

void TSI_Raw_File_Server_Response::proceed(QString prepend)
{
 QString path = url_path_;

 //?QString implicit_request_path;

 if(path.startsWith(QChar::fromLatin1('/')))
 {
  QString full_prepend = "%1/%2"_qt
    .arg(prepend.isEmpty()?
     QString::fromLatin1(PREFERRED_SERVER_FILES_FOLDER) : prepend)
    .arg(folder_branch_);

  if(path.startsWith("/~"_qt))
    check_rename(path, full_prepend);

  path.prepend(full_prepend);
 }

 if(!format_.isEmpty())
 {
  QString extra = (non_lowercase_flag_.isNull()? format_.toLower() : format_).prepend(QChar::fromLatin1('.'));
  path += extra;
 }


 //TSI_Server_Response::Response_Modes rm {response_mode_};

 switch ((TSI_Server_Response::Response_Modes) response_mode_)
 {
 case TSI_Server_Response::Response_Modes::N_A:
   main_response_->text_html_utf8_error(); break;
 case TSI_Server_Response::Response_Modes::Checked_Show:
   check_rewrite_nonexistent_path(path);
   [[fallthrough]];
 case TSI_Server_Response::Response_Modes::Show:
   main_response_->init_content_file_with_type(format_, path);
   break;
 case TSI_Server_Response::Response_Modes::Info:
   main_response_->text_html_utf8("Request format: %1, path: %2"_qt
     .arg(format_).arg(path));
   break;
 case TSI_Server_Response::Response_Modes::Qt_Serialized_Info:
   {
    u4 size = (u4) -1;
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
     size = file.size();  //when file does open.
     file.close();
     qDebug() << "file = " << file << " size = " << size;
    }

    TSI_Resource_Info qri(url_path_, path, size);
    main_response_->init_resource_info_content(qri);
   }
   break;
 }

}

