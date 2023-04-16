
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_SOURCE_FILE__H
#define CHTR_SOURCE_FILE__H


#include "accessors.h"

#include "aqns.h"

#include "flags.h"

#include <QFile>
#include <QVector>

//?#include "tsl/ordered_map.h"

#include "global-types.h"

AQNS_(Chasm_TR)


class ChTR_Source_File
{

private:

 QString path_;

// tsl::ordered_map<QString, ChTR_Source_Type*> declared_types_;
// tsl::ordered_map<QString, ChTR_Source_Type*> defined_types_;


public:


 ChTR_Source_File(QString path = {});

 ACCESSORS(QString ,path)

// ACCESSORS(MACRO_PASTE(tsl::ordered_map<QString, ChTR_Source_Type*>) ,declared_types)
// ACCESSORS(MACRO_PASTE(tsl::ordered_map<QString, ChTR_Source_Type*>) ,defined_types)


};

_AQNS(Chasm_TR)


#endif // CHTR_SOURCE_FILE__H

