
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include <QDebug>

#include <QFileInfo>
#include <QDirIterator>

#include <QString>
#include <QDataStream>

#include "tkrzw_dbm_hash.h"

using namespace tkrzw;

int main(int argc, char *argv[])
{
 tkrzw::HashDBM dbm;
 dbm.Open(DEFAULT_DEV_TKRZW_FOLDER "/hello-world.tkh", true).OrDie();
 dbm.Set("hello", "world").OrDie();
 qDebug() << QString::fromStdString( dbm.GetSimple("hello") );
 dbm.Close().OrDie();

 // Opens a new database.
 dbm.Open(DEFAULT_DEV_TKRZW_FOLDER "/casket.tkh", true);

 // Stores records.
 dbm.Set("foo", "hop");
 dbm.Set("bar", "step");
 dbm.Set("baz", "jump");

 // Retrieves records.
 std::cout << dbm.GetSimple("foo", "*") << std::endl;
 std::cout << dbm.GetSimple("bar", "*") << std::endl;
 std::cout << dbm.GetSimple("baz", "*") << std::endl;
 std::cout << dbm.GetSimple("outlier", "*") << std::endl;

 // Traverses records.
 std::unique_ptr<DBM::Iterator> iter = dbm.MakeIterator();
 iter->First();

 std::string key, value;
 while (iter->Get(&key, &value) == Status::SUCCESS)
 {
  std::cout << key << ":" << value << std::endl;
  iter->Next();
 }

 // Closes the database.
 dbm.Close();
 return 0;

}
