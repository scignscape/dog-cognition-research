
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_DOUBLE_LOCATION_2D__H
#define DHAX_DOUBLE_LOCATION_2D__H

#include <QString>
#include <QPoint>


#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include <functional>

#include "kans.h"


//KANS_(GTagML)


class DHAX_Double_Location_2d
{
 double c1_;
 double c2_;

public:

 DHAX_Double_Location_2d(double c1, double c2);

 ACCESSORS(double ,c1)
 ACCESSORS(double ,c2)

 QString to_string();

 QPoint to_qpoint();

 //?static void read_string(QString str, QVector<n8>& locations);

};

// _KANS(GTagML)


#endif  //  DHAX_DOUBLE_2D__H
