
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef METATYPE_OBJECT__H
#define METATYPE_OBJECT__H

#include <QString>
#include <QMap>

#include <QList>


#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include "kans.h"


//KANS_(GTagML)


class Metatype_Object
{
 QString local_name_;
 QString full_name_;

 typedef std::function<n8(QVector<n8>)> guard_fn_type;

 QMap<QString, QList<guard_fn_type>> guard_fns_;

public:

 Metatype_Object(QString local_name);

 ACCESSORS(QString ,local_name)
 ACCESSORS(QString ,full_name)

 void register_guard_fn(QString key, guard_fn_type fn);

 QString get_full_name();

 guard_fn_type check_single_guard_fn(QString key);



};

// _KANS(GTagML)

#endif // METATYPE_OBJECT__H
