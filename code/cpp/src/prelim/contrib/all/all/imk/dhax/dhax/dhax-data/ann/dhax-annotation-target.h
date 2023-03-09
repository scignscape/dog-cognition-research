
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_ANNOTATION_TARGET__H
#define DHAX_ANNOTATION_TARGET__H

#include <QString>
#include <QPoint>
#include <QVector>


#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include "location/dhax-location-2d.h"

#include <functional>

#include "kans.h"


//KANS_(GTagML)


class DHAX_Annotation_Target
{
 //QVector<n8> locations_;

 QString full_path_;

public:

 DHAX_Annotation_Target();

 ACCESSORS(QString ,full_path)

// ACCESSORS(QString ,shape_designation)
// ACCESSORS__RGET(QStringList ,scoped_identifiers)
// ACCESSORS(n8 ,opaque_shape_kind_code)
// ACCESSORS(QString ,comment)


// void absorb_shape_point(const QPoint& qp);
// QString to_compact_string();
// void locations_to_qpoints(QVector<QPoint>& result);

};

// _KANS(GTagML)


#endif  //  DHAX_ANNOTATION_TARGET__H
