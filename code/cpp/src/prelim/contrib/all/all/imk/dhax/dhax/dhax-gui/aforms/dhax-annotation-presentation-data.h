
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_ANNOTATION_PRESENTATION_DATA__H
#define DHAX_ANNOTATION_PRESENTATION_DATA__H

#include <QFrame>
#include <QBoxLayout>
#include <QStack>

#include "accessors.h"

#include "global-types.h"

//#include "dhax-data/ann/dhax-annotation-instance.h"

class QConicalGradient;

class DHAX_Annotation_Presentation_Data
{
 u1 vertex_handle_radius_;
 u1 dotted_pen_width_;
 u1 solid_pen_width_;
 s2 pen_gradient_angle_;

 QColor solid_shape_color_;
 QColor patterned_shape_color_;

 QColor gradient_pen_base_color_;
 QColor gradient_pen_variant_color_;

 QColor vertex_handle_highlight_color_;

 QConicalGradient* pen_gradient_;

public:

 DHAX_Annotation_Presentation_Data();

 ACCESSORS__GET(QColor ,solid_shape_color)
 ACCESSORS__GET(QColor ,patterned_shape_color)

 ACCESSORS__GET(QColor ,gradient_pen_base_color)
 ACCESSORS__GET(QColor ,gradient_pen_variant_color)

 ACCESSORS__GET(QColor ,vertex_handle_highlight_color)


 ACCESSORS(u1 ,vertex_handle_radius)
 ACCESSORS(u1 ,dotted_pen_width)
 ACCESSORS(u1 ,solid_pen_width)

 QConicalGradient& pen_gradient()
 {
  return *pen_gradient_;
 }

 void init_pen_gradient();


};

#endif //  DHAX_ANNOTATION_PRESENTATION_DATA__H




