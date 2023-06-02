
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_DSMAIN_MODEL__H
#define CHASM_DSMAIN_MODEL__H

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
class Chasm_Procedure_Table;

class Chasm_DSMain_Model
{
 //Chasm_Runtime_Bridge* crb_;
 Chasm_Procedure_Table* proctable_;

public:

 Chasm_DSMain_Model(Chasm_Procedure_Table* proctable);

 void register_procedures();


};

// _KANS(GTagML)

#endif // CHASM_DSMAIN_MODEL__H
