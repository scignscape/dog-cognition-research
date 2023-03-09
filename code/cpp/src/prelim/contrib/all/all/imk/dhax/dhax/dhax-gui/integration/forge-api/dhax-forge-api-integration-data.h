
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_FORGE_API_INTEGRATION_DATA__H
#define DHAX_FORGE_API_INTEGRATION_DATA__H

#include "global-types.h"

#include <QVector>


class Forge_Session;
class Forge_API_Workflow;


class DHAX_FORGE_API_Integration_Data
{
 Forge_Session* forge_session_;

public:

 DHAX_FORGE_API_Integration_Data();

};


#endif //  DHAX_FORGE_API_INTEGRATION_DATA__H


