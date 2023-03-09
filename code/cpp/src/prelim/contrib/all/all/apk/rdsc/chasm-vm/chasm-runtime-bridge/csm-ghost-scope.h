
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CSM_GHOST_SCOPE__H
#define CSM_GHOST_SCOPE__H

#include <QString>

#include <QStack>
#include <QVariant>

#include <QDebug>

#include "chasm/chasm-carrier.h"


#include "accessors.h"
#include "flags.h"

#include "global-types.h"
#include "kans.h"


class Chasm_Runtime;

class Chasm_Runtime_Bridge;

class CSM_Ghost_Scope
{
 QVector<Chasm_Carrier> carriers_;

public:

 CSM_Ghost_Scope();

 void add_carrier(const Chasm_Carrier& cc);
 void clear_carrier(Chasm_Carrier& cc);

 void clear_all();

// ACCESSORS__GET(QString ,last_source_proc_name)


};

// _KANS(GTagML)

#endif // CSM_GHOST_SCOPE__H
