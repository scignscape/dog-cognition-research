
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qh-json-file-reader.h"

#include <QJsonDocument>

#include "textio.h"

USING_KANS(RdSC)
USING_KANS(TextIO)


Qh_Json_File_Reader::Qh_Json_File_Reader(QString folder)
  :  folder_(folder)
{

}

void Qh_Json_File_Reader::strip_comments(QByteArray& json, s4 start)
{
 s4 ix = json.indexOf("/*", start);
 if(ix == -1)
   return;

 s4 end = json.indexOf("*/", ix);
 if(end == -1)
   end += json.size();
 else
   end += 2;

 json.replace(ix, end - ix, "");

 if(ix < json.size())
   strip_comments(json, ix);
}

void Qh_Json_File_Reader::json_document(QString file_name, QJsonDocument& result, QJsonParseError* error)
{
 QByteArray json;

 QDir qdir(folder_);

 load_file(qdir.filePath(file_name), json);

 strip_comments(json);

 qDebug() << "json = " << json;

 result = QJsonDocument::fromJson(json, error);
}
