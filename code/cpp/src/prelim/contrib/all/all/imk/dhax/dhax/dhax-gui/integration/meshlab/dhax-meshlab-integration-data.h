
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_MESHLAB_INTEGRATION_DATA__H
#define DHAX_MESHLAB_INTEGRATION_DATA__H

#include "global-types.h"
#include "accessors.h"

#include <QQuaternion>

class DHAX_Meshlab_Integration_Data
{
 friend class DHAX_Meshlab_Integration_Controller;

 QQuaternion meshlab_track_info_;
 r4 meshlab_scale_info_;
 QVector3D meshlab_center_position_;
 QString meshlab_file_path_;
 QString mesh_file_path_;
 u4* meshlab_import_count_;


public:

 DHAX_Meshlab_Integration_Data();

 ACCESSORS(u4* ,meshlab_import_count)

 ACCESSORS__RGET(QQuaternion ,meshlab_track_info)
 ACCESSORS(r4 ,meshlab_scale_info)
 ACCESSORS__RGET(QVector3D ,meshlab_center_position)
 ACCESSORS(QString ,meshlab_file_path)
 ACCESSORS(QString ,mesh_file_path)

 void init_import_count();

};


#endif //  DHAX_MESHLAB_INTEGRATION_DATA__H


