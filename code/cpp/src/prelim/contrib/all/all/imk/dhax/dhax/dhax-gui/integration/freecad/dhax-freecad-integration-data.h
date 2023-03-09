
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_FREECAD_INTEGRATION_DATA__H
#define DHAX_FREECAD_INTEGRATION_DATA__H

#include "accessors.h"
#include "global-types.h"

#include <QVector>



class DHAX_FreeCAD_Integration_Data
{
 friend class DHAX_FreeCAD_Integration_Controller;

 QString freecad_file_path_;

 QVector<r8> freecad_position_data_;
 u4* freecad_import_count_;


public:

 DHAX_FreeCAD_Integration_Data();

 ACCESSORS(u4* ,freecad_import_count)
 ACCESSORS__RGET(QVector<r8> ,freecad_position_data)
 ACCESSORS(QString ,freecad_file_path)

 void init_import_count();

};


#endif //  DHAX_FREECAD_INTEGRATION_DATA__H


