
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_CPP_SOURCE_FILE__H
#define QH_CPP_SOURCE_FILE__H


#include "accessors.h"

#include "kans.h"

#include "flags.h"

#include <QFile>
#include <QVector>

#include "tsl/ordered_map.h"

#include "global-types.h"

KANS_(Qh)


class Qh_CPP_Source_Type;

class Qh_CPP_Source_File
{

private:

 QString path_;

 tsl::ordered_map<QString, Qh_CPP_Source_Type*> declared_types_;
 tsl::ordered_map<QString, Qh_CPP_Source_Type*> defined_types_;


public:


 Qh_CPP_Source_File(QString path = {});

 ACCESSORS(QString ,path)

 ACCESSORS(MACRO_PASTE(tsl::ordered_map<QString, Qh_CPP_Source_Type*>) ,declared_types)
 ACCESSORS(MACRO_PASTE(tsl::ordered_map<QString, Qh_CPP_Source_Type*>) ,defined_types)

 void add_source_type(Qh_CPP_Source_Type* sty);

};

_KANS(Qh)


#endif // QH_CPP_SOURCE_FILE__H

