
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rdsc-runtime/qhr/qh-runtime.h"

#include "rdsc-runtime/json/qh-json-file-reader.h"
#include "rdsc-runtime/json/pseudo-jpath.h"

#include <QJsonDocument>

USING_KANS(RdSC)

//
#include "scoping-if.h"

//"$>lev:t1 t2 t3;"

int main(int argc, char *argv[])
{

 QString uri = "abc~~def";

 qDebug() << "uri = " << uri;

 _if(<QString> ix = uri.mid(2))
 {
  qDebug() << "ix = " << ix;
 }

 _if(<QStringRef> ix = uri.midRef(2))
 {
  qDebug() << "ix = " << ix;
 }

 QStringView sv = uri;

 _if(<QStringView> ix = sv.mid(2))
 {
  qDebug() << "ix = " << ix;
 }

 _if(<u4> ix = uri.indexOf("~~"))
 {
  uri = uri.mid(ix + 2);
 }

 qDebug() << "uri = " << uri;

 return 0;

}

QString folder = "/quasihome/nlevisrael/zola-git/regit/labs-zola";

int main1(int argc, char *argv[])
{ 
 Qh_Runtime qhr;
 Qh_Type_System* qht = qhr.type_system();

 Qh_Json_File_Reader qjfr(folder);

 QJsonDocument jsond;
 qjfr.json_document(jsond, ".ember-cli");
 //qjfr.json_document(jsond, "test.js");

 Pseudo_JPath jp(jsond);
 u4 port = jp.evaluate("$:port;").value<u4>();


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

