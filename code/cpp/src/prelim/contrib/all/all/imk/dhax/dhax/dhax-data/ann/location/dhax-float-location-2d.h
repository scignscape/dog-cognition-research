
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_FLOAT_LOCATION_2D__H
#define DHAX_FLOAT_LOCATION_2D__H

#include <QString>
#include <QPoint>


#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include <functional>

#include "kans.h"


//KANS_(GTagML)


class DHAX_Float_Location_2d
{
 float c1_;
 float c2_;

public:

 DHAX_Float_Location_2d(float c1, float c2);

 ACCESSORS(float ,c1)
 ACCESSORS(float ,c2)

 n8 encode8();
 void decode8(n8 compressed);
 void check_decode8(n8 compressed);

 QString to_string();

 QPoint to_qpoint();

 //?static void read_string(QString str, QVector<n8>& locations);

};

// _KANS(GTagML)


#endif  //  DHAX_LOCATION_2D__H
