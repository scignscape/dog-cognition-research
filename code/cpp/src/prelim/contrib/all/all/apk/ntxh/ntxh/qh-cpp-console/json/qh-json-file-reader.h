
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_JSON_FILE_READER__H
#define QH_JSON_FILE_READER__H

#include <QByteArray>

#include <functional>

#include "global-types.h"

#include "accessors.h"

class QJsonDocument;
class QJsonParseError;

#include "kans.h"


KANS_(RdSC)

class Qh_Type;
class Qh_Type_System;

class Qh_Json_File_Reader
{
 QString folder_;

public:

 explicit Qh_Json_File_Reader(QString folder);

 ACCESSORS(QString ,folder)

 void json_document(QString file_name, QJsonDocument& result, QJsonParseError* error = nullptr);
 void json_document(QJsonDocument& result, QString file_name, QJsonParseError* error = nullptr)
 {
  json_document(file_name, result, error);
 }

 void strip_comments(QByteArray& json, s4 start = 0);

};

_KANS(RdSC)


#endif // QH_JSON_FILE_READER__H


