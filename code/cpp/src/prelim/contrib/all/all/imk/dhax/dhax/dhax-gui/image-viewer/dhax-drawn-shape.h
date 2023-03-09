
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_DRAWN_SHAPE__H
#define DHAX_DRAWN_SHAPE__H

#include <QPoint>
#include <QVector>
//#include <QtGui>

#include "accessors.h"

#include "global-types.h"

#include "dhax-data/ann/dhax-annotation-instance.h"

class DHAX_Annotation_Instance;

class DHAX_Drawn_Shape
{
 QVector<QPoint> points_;
 QVector<QPoint> extra_points_;

public:

 typedef DHAX_Annotation_Instance::Compact_Shape_Kind_Summary Shape_Kinds;
// enum class Shape_Kinds
// {
//  N_A, Rectangle, Ellipse, Polygon, Polyline, Curve
// };

private:

 //Shape_Kinds shape_kind_;
 Shape_Kinds shape_kind_;
 //DHAX_Annotation_Instance::Compact_Shape_Kind_Summary shape_kind_;

public:

 DHAX_Drawn_Shape(Shape_Kinds Shape_Kinds = Shape_Kinds::N_A);

 void init_from_dhax_annotation(DHAX_Annotation_Instance& dai, r8 resize_factor);

 void reset();
 void reset_all();

 DHAX_Annotation_Instance* to_dhax_annotation(); //r8 resize_factor);

 QString shape_kind_to_string();

 void parse_shape_kind(QString text);

 void add_extra_point(const QPoint& qp)
 {
  extra_points_.push_back(qp);
 }

 ACCESSORS__RGET(QVector<QPoint> ,points)
 ACCESSORS__RGET(QVector<QPoint> ,extra_points)
 ACCESSORS(Shape_Kinds ,shape_kind)
};


#endif // DHAX_DRAWN_SHAPE__H
