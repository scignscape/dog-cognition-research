
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dhax-meshlab-integration-data.h"


DHAX_Meshlab_Integration_Data::DHAX_Meshlab_Integration_Data()
  :  meshlab_import_count_(nullptr)
{

}

void DHAX_Meshlab_Integration_Data::init_import_count()
{
 if(meshlab_import_count_)
 {
  qDebug() << "Re-initializing meshlab import count!";
 }
 static u4 static_u4 = 0;
 meshlab_import_count_ = &static_u4;
}
