
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rdsc-runtime/qhr/qh-runtime.h"

#include "rdsc-runtime/json/qh-json-file-reader.h"
#include "rdsc-runtime/json/pseudo-jpath.h"

#include <QJsonDocument>

USING_KANS(RdSC)

QString folder = "/quasihome/nlevisrael/zola-git/regit/labs-zola";

//"$>lev:t1 t2 t3;"

int main(int argc, char *argv[])
{
 Qh_Runtime qhr;
 Qh_Type_System* qht = qhr.type_system();

 Qh_Json_File_Reader qjfr(folder);

 QJsonDocument jsond;
 qjfr.json_document(jsond, ".ember-cli");
 //qjfr.json_document(jsond, "test.js");

 Pseudo_JPath jp(jsond);
 QVariant qvar = jp.evaluate("$:port;");

 qDebug() << "qvar = " << qvar;

 return 0;
}


/*
 *
{
 "port": 4202,
 "key1": {
  "key2":  ["key3", "ok"]
 }
}

{
 "port": 4202,
 "key1": ["key2", "ok"]
}


{
 "port": 4202,
 "key1": {
  "key2":  {
   "key3": "ok"
  }
 }
}
*/

