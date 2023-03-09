
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_MESHLAB_INTEGRATION_CONTROLLER__H
#define DHAX_MESHLAB_INTEGRATION_CONTROLLER__H

#include "global-types.h"
#include "accessors.h"

#include "integration/dhax-integration-controller.h"

#include <QQuaternion>


class DHAX_Meshlab_Integration_Data;
class DHAX_Application_Controller;

class DHAX_Meshlab_Integration_Controller : public DHAX_Integration_Controller
{
 DHAX_Meshlab_Integration_Data* integration_data_;
 DHAX_Application_Controller* application_controller_;

public:

 DHAX_Meshlab_Integration_Controller();

 ACCESSORS(DHAX_Meshlab_Integration_Data* ,integration_data)
 ACCESSORS(DHAX_Application_Controller* ,application_controller)

 void read_datagram(QString text) Q_DECL_OVERRIDE;

};


#endif //  DHAX_MESHLAB_INTEGRATION_DATA__H


