
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHASM_TR_SOURCE_FILE__H
#define CHASM_TR_SOURCE_FILE__H


#include "accessors.h"

#include "aqns.h"

#include "flags.h"

#include <QFile>
#include <QVector>

//?#include "tsl/ordered_map.h"

#include "global-types.h"

AQNS_(ChasmTR)


class Chasm_TR_Source_File
{

private:

 QString path_;

// tsl::ordered_map<QString, Chasm_TR_Source_Type*> declared_types_;
// tsl::ordered_map<QString, Chasm_TR_Source_Type*> defined_types_;


public:


 Chasm_TR_Source_File(QString path = {});

 ACCESSORS(QString ,path)

// ACCESSORS(MACRO_PASTE(tsl::ordered_map<QString, Chasm_TR_Source_Type*>) ,declared_types)
// ACCESSORS(MACRO_PASTE(tsl::ordered_map<QString, Chasm_TR_Source_Type*>) ,defined_types)


};

_AQNS(ChasmTR)


#endif // CHASM_TR_SOURCE_FILE__H

