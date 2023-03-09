
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_DSMAIN__H
#define CHASM_DSMAIN__H

#include <QString>

#include <QStack>
#include <QVariant>

#include <QDebug>



#include "accessors.h"
#include "flags.h"

#include "global-types.h"
#include "kans.h"


class Chasm_Runtime;

class Chasm_Runtime_Bridge;


class Chasm_DSMain
{
 QString current_paper_name_;

public:

 Chasm_DSMain();

 void load_dataset(QString paper_name);
 void setup_sdifolder(QString paper_name);


};

// _KANS(GTagML)

#endif // CHASM_DSMAIN__H
