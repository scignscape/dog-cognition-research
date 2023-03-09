
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-annotation-presentation-data.h"

//#include <QGraphicsProxyWidget>

#include <QConicalGradient>

DHAX_Annotation_Presentation_Data::DHAX_Annotation_Presentation_Data()
  :  vertex_handle_radius_(7), dotted_pen_width_(4), solid_pen_width_(4)
{
 gradient_pen_base_color_ = QColor(140, 140, 140);
 gradient_pen_variant_color_ = QColor(55, 55, 55, 100);
 vertex_handle_highlight_color_ = QColor(195, 195, 195);
 pen_gradient_angle_ = -65;

 pen_gradient_ = new QConicalGradient;
 init_pen_gradient();
}

void DHAX_Annotation_Presentation_Data::init_pen_gradient()
{
 QConicalGradient& gradient = pen_gradient();

 gradient.setSpread(QGradient::ReflectSpread);

 gradient.setAngle(-65);
 gradient.setColorAt(0, QColor(gradient_pen_variant_color_.red(),gradient_pen_base_color_.green(),gradient_pen_base_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.05, QColor(gradient_pen_variant_color_.red(),gradient_pen_variant_color_.green(),gradient_pen_base_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.1, QColor(gradient_pen_variant_color_.red(),gradient_pen_variant_color_.green(),gradient_pen_variant_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.15, QColor(gradient_pen_base_color_.red(), gradient_pen_variant_color_.green(), gradient_pen_variant_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.2, QColor(gradient_pen_base_color_.red(), gradient_pen_variant_color_.green(), gradient_pen_base_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.25, QColor(gradient_pen_variant_color_.red(), gradient_pen_variant_color_.green(), gradient_pen_base_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.3, QColor(gradient_pen_variant_color_.red(), gradient_pen_base_color_.blue(), gradient_pen_variant_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.35, QColor(gradient_pen_base_color_.red(), gradient_pen_base_color_.blue(), gradient_pen_variant_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.4, QColor(0,255,0,gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.45, QColor(255,255,0,gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.5, QColor(0,255,255,gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.55, QColor(255,255,0,gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.6, QColor(0,255,0,gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.65, QColor(gradient_pen_base_color_.red(), gradient_pen_base_color_.green(), gradient_pen_variant_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.7, QColor(gradient_pen_variant_color_.red(), gradient_pen_base_color_.green(), gradient_pen_variant_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.75, QColor(gradient_pen_variant_color_.red(), gradient_pen_variant_color_.green(), gradient_pen_base_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.8, QColor(gradient_pen_base_color_.red(), gradient_pen_variant_color_.green(), gradient_pen_base_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.85, QColor(gradient_pen_base_color_.red(), gradient_pen_variant_color_.green(), gradient_pen_variant_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.9, QColor(gradient_pen_variant_color_.red(),gradient_pen_variant_color_.green(),gradient_pen_variant_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(0.95, QColor(gradient_pen_variant_color_.red(),gradient_pen_variant_color_.green(),gradient_pen_base_color_.blue(),gradient_pen_variant_color_.alpha()));
 gradient.setColorAt(1, QColor(gradient_pen_variant_color_.red(),gradient_pen_base_color_.green(),gradient_pen_base_color_.blue(),gradient_pen_variant_color_.alpha()));
}

