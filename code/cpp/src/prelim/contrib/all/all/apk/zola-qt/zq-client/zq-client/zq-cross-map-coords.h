
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ZQ_CROSS_MAP_COORDS__H
#define ZQ_CROSS_MAP_COORDS__H

#include <QObject>

#include <QPointF>
#include <QSizeF>

#include "global-types.h"

struct ZQ_Cross_Map_Coords
{
 r8 latitude;
 r8 longitude;

 r8 exact_zoom;
 r8 adjusted_zoom;

 s1 zoom;

 QPointF global_window_coords;
 QPointF local_window_coords;

 QSizeF window_size;


};


#endif // ZQ_CROSS_MAP_COORDS__H
