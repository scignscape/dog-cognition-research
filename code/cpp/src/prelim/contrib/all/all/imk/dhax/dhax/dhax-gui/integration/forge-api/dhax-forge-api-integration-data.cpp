
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-forge-api-integration-data.h"



#include <QApplication>

#include "iat-forge/forge-session.h"
#include "iat-forge/forge-runtime.h"
#include "iat-forge/forge-api-workflow.h"

#include <QFileDialog>

#include <QProcessEnvironment>
#include <QFileDialog>

#define VALUE2(x) value(#x, #x)



DHAX_FORGE_API_Integration_Data::DHAX_FORGE_API_Integration_Data()
  :  forge_session_(nullptr)
{

}
