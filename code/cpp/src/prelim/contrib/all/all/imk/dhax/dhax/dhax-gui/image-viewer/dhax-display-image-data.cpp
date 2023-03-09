
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-display-image-data.h"

#include <QGraphicsProxyWidget>


DHAX_Drawn_Shape* DHAX_Display_Image_Data::get_current_drawn_shape()
{
 if(current_drawn_shape_)
 {
  if(current_drawn_shape_->shape_kind() != DHAX_Drawn_Shape::Shape_Kinds::N_A)
   return current_drawn_shape_;
 }

 return nullptr;
}

DHAX_Drawn_Shape* DHAX_Display_Image_Data::get_last_canceled_drawn_shape()
{
 if(last_canceled_drawn_shapes_.isEmpty())
   return nullptr;
 return last_canceled_drawn_shapes_.last();
}

void DHAX_Display_Image_Data::reset_drawn_shapes()
{
 while(!held_drawn_shapes_.isEmpty())
 {
  delete held_drawn_shapes_.takeLast();
 }
 while(!held_drawn_shapes_.isEmpty())
 {
  delete last_canceled_drawn_shapes_.takeLast();
 }

 if(current_drawn_shape_)
   current_drawn_shape_->reset_all();

}


DHAX_Display_Image_Data::DHAX_Display_Image_Data()
{
 current_drawn_shape_ = nullptr;
 active_curve_ = nullptr;


 multi_draw = false;

 temporary_pan_mode_ = false;
 temporary_pull_mode_ = false;
 fixed_pan_mode_ = false;
 fixed_pull_mode_ = false;

 isMoving_ = false;
 isPressed_ = false;
 isDoublePressed_ = false;
 shapeMoving_ = false;
 checked_ = false;
 editing_ = false;
 nameSelected_ = false;

 enabled_shape_kind_ = Shape_Kinds::N_A;
// drawingSquareEnabled_ = false;
// drawingEllipseEnabled_ = false;
// drawingPolygonEnabled_ = false;
 pointPosition_ = 0;
 shapePosition_ = -1;
 shapeID_.clear();
 defaultColorsThickness();
}

void DHAX_Display_Image_Data::defaultColorsThickness()
{
 radius_ = 6;
 thickness_ = 2;
 back_thickness_ = 4;
 myRed_ = 255;
 myGreen_ = 0;
 myBlue_ = 0;
 sqRed_ = 255;
 sqGreen_ = 255;
 sqBlue_ = 255;
 shapeRed_ = 240;
 shapeGreen_ = 255;
 shapeBlue_ = 160;
 shapeAlpha_ = 255;
 shapeBackAlpha_ = 125;

}

void DHAX_Display_Image_Data::setColorsThickness(int in_radius, int in_thickness, int in_myRed, int in_myGreen, int in_MyBlue,
  int in_sqRed, int in_sqGreen, int in_sqBlue, int in_shapeRed, int in_shapeGreen, int in_shapeBlue)
{
 radius_ = in_radius;
 thickness_ = in_thickness;
 myRed_ = in_myRed;
 myGreen_ = in_myGreen;
 myBlue_ = in_MyBlue;
 sqRed_ = in_sqRed;
 sqGreen_ = in_sqGreen;
 sqBlue_ = in_sqBlue;
 shapeRed_ = in_shapeRed;
 shapeGreen_ = in_shapeGreen;
 shapeBlue_ = in_shapeBlue;
  //? update();
}


void DHAX_Display_Image_Data::init_polygon_or_polyline(DHAX_Drawn_Shape* dds)
{
 QPoint last_point;
 for(const QPair<QPoint, QPoint>& pr : point_pairs_)
 {
  if(pr.first != last_point)
    dds->points() << pr.first;
  if(pr.second != pr.first)
    dds->points() << pr.second;
  last_point = pr.second;
 }

 point_pairs_.clear();
}

void DHAX_Display_Image_Data::init_polyline()
{
 DHAX_Drawn_Shape* dds = check_current_drawn_shape(DHAX_Drawn_Shape::Shape_Kinds::Polyline);
 init_polygon_or_polyline(dds);
}


void DHAX_Display_Image_Data::complete_polygon()
{
 DHAX_Drawn_Shape* dds = check_current_drawn_shape(DHAX_Drawn_Shape::Shape_Kinds::Non_Regular_Polygon);
 init_polygon_or_polyline(dds);
}

void DHAX_Display_Image_Data::setView(QImage image)
{
 m_background_ = image;
}

void DHAX_Display_Image_Data::enable_multiline_shape()
{
 enabled_shape_kind_ = DHAX_Display_Image_Data::Shape_Kinds::Multiline;
}

void DHAX_Display_Image_Data::enable_measurement_shape()
{
 enabled_shape_kind_ = DHAX_Display_Image_Data::Shape_Kinds::Measurement;
}

void DHAX_Display_Image_Data::enable_skew_rhombus_shape()
{
 enabled_shape_kind_ = DHAX_Display_Image_Data::Shape_Kinds::Skew_Rhombus;
}

void DHAX_Display_Image_Data::enable_arrow_shape()
{
 enabled_shape_kind_ = DHAX_Display_Image_Data::Shape_Kinds::Arrow;
}

void DHAX_Display_Image_Data::enable_rectangle_shape()
{
 enabled_shape_kind_ = DHAX_Display_Image_Data::Shape_Kinds::Rectangle;

// drawingSquareEnabled_ = true;
// drawingEllipseEnabled_ = false;
// drawingPolygonEnabled_ = false;
}

void DHAX_Display_Image_Data::enable_ellipse_shape()
{
 enabled_shape_kind_ = DHAX_Display_Image_Data::Shape_Kinds::Ellipse;

// drawingEllipseEnabled_ = true;
// drawingSquareEnabled_ = false;
// drawingPolygonEnabled_ = false;
}

void DHAX_Display_Image_Data::enable_polygon_shape()
{
 enabled_shape_kind_ = DHAX_Display_Image_Data::Shape_Kinds::Non_Regular_Polygon;

// drawingPolygonEnabled_ = true;
// drawingSquareEnabled_ = false;
// drawingEllipseEnabled_ = false;
}

void DHAX_Display_Image_Data::enableHighlight(bool enable)
{
 checked_ = enable;
}

void DHAX_Display_Image_Data::setNameSelected(bool enable)
{
 nameSelected_ = enable;
}

void DHAX_Display_Image_Data::setShapeSelected(QString in_shapeID)
{
 shapeID_ = in_shapeID;
 //? update();
}

void DHAX_Display_Image_Data::setEdits(QList<shape> inputEdits)
{
 if(!inputEdits.isEmpty())
   allEdits_ = inputEdits;
 else
   allEdits_.clear();
}

void DHAX_Display_Image_Data::resizeEdits(int resize)
{
 if(!allEdits_.isEmpty())
 {
  for(int i=0; i < allEdits_.size(); ++i)
  {
   for(int j=0; j < allEdits_.at(i).shapePoints.size(); ++j){
    allEdits_[i].shapePoints[j].rx()/=(100.0/(190-resize*18));
    allEdits_[i].shapePoints[j].ry()/=(100.0/(190-resize*18));
   }
  }
 }
}

void DHAX_Display_Image_Data::clear_image()
{
 if(!allEdits_.isEmpty())
   allEdits_.clear();
 reset();
}

void DHAX_Display_Image_Data::reset()
{
 isMoving_ = false;
 isPressed_ = false;
 isDoublePressed_ = false;
 shapeMoving_ = false;
 editing_ = false;
 points_.clear();
 mStartPoint_ = QPoint();
 mEndPoint_ = QPoint();
 mTempPoint_ = QPoint();
 pointPosition_ = 0;
 shapePosition_ = -1;
  //? update();
}

void DHAX_Display_Image_Data::clearLastEdits()
{
 if(!allEdits_.isEmpty())
   allEdits_.removeLast();
 //? update();
}
