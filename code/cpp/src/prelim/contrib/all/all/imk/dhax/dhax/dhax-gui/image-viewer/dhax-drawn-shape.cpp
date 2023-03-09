
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "dhax-drawn-shape.h"

#include "dhax-data/ann/dhax-annotation-instance.h"

//#include "iat-model/axfi/axfi-annotation.h"


DHAX_Drawn_Shape::DHAX_Drawn_Shape(Shape_Kinds Shape_Kinds)
  :  shape_kind_(Shape_Kinds)
{

}

void DHAX_Drawn_Shape::reset()
{
 points_.clear();
}

void DHAX_Drawn_Shape::reset_all()
{
 points_.clear();
 shape_kind_ = Shape_Kinds::N_A;
}

QString DHAX_Drawn_Shape::shape_kind_to_string()
{
 switch (shape_kind_)
 {
 case Shape_Kinds::Rectangle: return "Rectangle";
 case Shape_Kinds::Ellipse: return "Ellipse";
 //case Shape_Kinds::Polygon: return "Polygon";
 case Shape_Kinds::Non_Regular_Polygon: return "Polygon";
 case Shape_Kinds::Polyline: return "Polyline";

 default: return {};

 }
}

QPoint _coordinate_scaling(const QPoint& init_point, r8 resize_factor)
{
 QPoint new_point;
 if(resize_factor == 25)
 {
  new_point = init_point;
 }
 else
 {
  new_point = init_point;

//  new_point.rx() = init_point.x()*(100.0/(190 - resize_factor * 18));
//  new_point.ry() = init_point.y()*(100.0/(190 - resize_factor * 18));
 }
 return new_point;
}

void DHAX_Drawn_Shape::parse_shape_kind(QString text)
{
 static QMap<QString, Shape_Kinds> static_map {
  {"Rectangle", Shape_Kinds::Rectangle},
  {"Ellipse", Shape_Kinds::Ellipse},
  //{"Polygon", Shape_Kinds::Polygon},
  {"Polygon", Shape_Kinds::Non_Regular_Polygon},
  {"Polyline", Shape_Kinds::Polyline},
  {"Curve", Shape_Kinds::Curve},
 };
 shape_kind_ = static_map.value(text, Shape_Kinds::N_A);
}


void DHAX_Drawn_Shape::init_from_dhax_annotation(DHAX_Annotation_Instance& dai, r8 resize_factor)
{
//? shape_kind_ = (Shape_Kinds) dai.opaque_shape_kind_code();

// parse_shape_kind(dai.shape_designation());

 shape_kind_ = dai.check_compact_representation();

// QVector<QPoint>* prelim_points = dai.prelim_shape_points();
// if(prelim_points)
//   std::copy(prelim_points->begin(), prelim_points->end(), std::back_inserter(points_));

//? dai.locations_to_qpoints(points);

 //points_.resize(points.size());

 QVector<QPoint> qps;
 dai.locations_to_qpoints(qps);
 std::copy(qps.begin(), qps.end(), std::back_inserter(points_));
}

DHAX_Annotation_Instance* DHAX_Drawn_Shape::to_dhax_annotation() //r8 resize_factor)
{
 DHAX_Annotation_Instance* result = new DHAX_Annotation_Instance;

 result->qpoint_dimensions();

 result->set_shape_designation(QString("(%1)").arg(shape_kind_to_string()));

 switch(shape_kind_)
 {
 case Shape_Kinds::Rectangle: result->init_rectangle(); break;
 case Shape_Kinds::Ellipse: result->init_ellipse(); break;// return "Ellipse";
 case Shape_Kinds::Non_Regular_Polygon: result->init_polygon(); break;
 case Shape_Kinds::Polyline: result->init_polyline(); break;
 default: break;
  //case Shape_Kinds::Polygon: return "Polygon";
 }

// result->set_opaque_shape_kind_code((n8) shape_kind_);

 r8 resize_factor = 1;

 //?result->check_init_prelim_shape_points();

 QVector<QPoint> qps;
 for(const QPoint& point : points_)
 {
  QPoint sp = _coordinate_scaling(point, resize_factor);
  result->add_shape_point(sp.x(), sp.y());
  //qps.push_back(sp);
 }


// for(const QPoint& point : points_)
// {
//  QPoint sp = _coordinate_scaling(point, resize_factor);
//  result->add_prelim_shape_point(sp);
// }


 return result;
}

