
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_INTEGRATION_CONTROLLER__H
#define DHAX_INTEGRATION_CONTROLLER__H

#include "global-types.h"
#include "accessors.h"

#include <QQuaternion>



class DHAX_Integration_Controller
{

public:

 DHAX_Integration_Controller();

 virtual void read_datagram(QString text) = 0;

// ACCESSORS(DHAX_Meshlab_Integration_Data* ,integration_data)

};


#endif //  DHAX_MESHLAB_INTEGRATION_DATA__H


