
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_FORGE_CONTROLLER__H
#define DHAX_FORGE_CONTROLLER__H

#include "global-types.h"

#include <QVector>


class Forge_Session;
class Forge_API_Workflow;


class DHAX_Forge_Controller
{
 Forge_Session* forge_session_;

 QString forge_client_id_;
 QString forge_client_secret_;

 QString libcrypto_file_name_;
 QString libssl_file_name_;

public:

 DHAX_Forge_Controller();

 void parse_default_workflow(Forge_API_Workflow& fw);
 void run_workflow();
 void init_ssl();

};


#endif //  DHAX_FORGE_CONTROLLER__H


