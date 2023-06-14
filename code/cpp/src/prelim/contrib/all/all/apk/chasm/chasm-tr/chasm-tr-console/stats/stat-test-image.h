
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef STAT_TEST_IMAGE__H
#define STAT_TEST_IMAGE__H

#include <QString>

#include "accessors.h"


class Stat_Test_Image
{ 
 QString file_path_;

public:

 Stat_Test_Image(QString file_path = {});

 ACCESSORS(QString ,file_path)

 QString file_path_with_presuffix(QString pres, QString subdir = {});
 QString file_path_with_name_addon(QString addon, QString subdir = {});


};

#endif // STAT_TEST_IMAGE__H
