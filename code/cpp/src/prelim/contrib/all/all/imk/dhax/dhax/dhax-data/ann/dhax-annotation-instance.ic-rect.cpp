
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-annotation-instance.h"

#include "location/dhax-location-2d.h"
#include "location/dhax-signed-location-2d.h"
#include "location/dhax-float-location-2d.h"
#include "location/dhax-double-location-2d.h"

#include <QDebug>


void DHAX_Annotation_Instance::init_as(QRectF& qrf)
{
 if( (internal_codes_ & internal_code_checked_qrect) == 0)
 {
  if(!fits<QGraphicsRectItem>())
   return;
 }

 _Internal_Codes ic = (_Internal_Codes) (internal_codes_ & 31);

 QVector<QPointF> vec;

 switch (ic)
 {
 case _Internal_Codes::Declared_As_Rectangle_two_corners:
  locations_to_qpoints(vec);

 default:
  break;

 }

}


void DHAX_Annotation_Instance::init_as(QRect& qr)
{
 if( (internal_codes_ & internal_code_checked_qrect) == 0)
 {
  if(!fits<QGraphicsRectItem>())
   return;
 }

 _Internal_Codes ic = (_Internal_Codes) (internal_codes_ & 31);

 QVector<QPoint> vec;

 switch (ic)
 {
 case _Internal_Codes::Declared_As_Rectangle_two_corners:
  locations_to_qpoints(vec);
  to_tlbr_points(vec);
  qr.setTopLeft(vec.value(0));
  qr.setBottomRight(vec.value(1));
 default:
  break;

 }

}
