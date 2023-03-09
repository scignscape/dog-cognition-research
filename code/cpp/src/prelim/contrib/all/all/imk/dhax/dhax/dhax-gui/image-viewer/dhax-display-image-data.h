
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_DISPLAY_IMAGE_DATA__H
#define DHAX_DISPLAY_IMAGE_DATA__H

#include <QFrame>
#include <QBoxLayout>
#include <QStack>

#include <QDebug>

#include "accessors.h"

#include "global-types.h"

#include "dhax-drawn-shape.h"

//#include "dhax-data/ann/dhax-annotation-instance.h"

class DHAX_Graphics_Scene;
class DHAX_Graphics_View;

class DHAX_Image_Scene_Item;
class DHAX_Display_Image_Data;
class DHAX_Main_Window;
class DHAX_Annotation_Instance;

class DHAX_Application_State;


class DHAX_Display_Image_Data
{
  friend class DHAX_Image_Scene_Item;

 DHAX_Application_State* application_state_;

  bool temporary_pan_mode_;
  bool temporary_pull_mode_;

  bool fixed_pan_mode_;
  bool fixed_pull_mode_;

  bool multi_draw;

  bool isMoving_;
  bool isPressed_;
  bool isDoublePressed_;
  bool shapeMoving_;
  bool checked_;
  bool editing_;
  bool nameSelected_;

  typedef DHAX_Drawn_Shape::Shape_Kinds Shape_Kinds;

  Shape_Kinds enabled_shape_kind_;
//  bool drawingSquareEnabled_;
//  bool drawingEllipseEnabled_;
//  bool drawingPolygonEnabled_;

  int pointPosition_;
  int shapePosition_;
  int radius_;
  int thickness_;
  int back_thickness_;
  int myRed_;
  int myGreen_;
  int myBlue_;
  int sqRed_;
  int sqGreen_;
  int sqBlue_;
  int shapeRed_;
  int shapeGreen_;
  int shapeBlue_;
  int shapeAlpha_;
  int shapeBackAlpha_;

  QImage m_background_;
  QPoint mStartPoint_;
  QPoint mEndPoint_;
  QPoint mTempPoint_;
  QList<QPoint> points_;
  QString shapeID_;
  QVector<QPair<QPoint, QPoint>> point_pairs_;

 public:

  struct shape
  {
   QString id;
   int form;
   QList<QPoint> shapePoints;

   DHAX_Annotation_Instance* dhax_annotation;
  };

 public:

  void setView(QImage image);

  Shape_Kinds current_enabled_shape_kind()
  {
   return enabled_shape_kind_;
//   if(drawingSquareEnabled_)
//     return DHAX_Drawn_Shape::Shape_Kinds::Rectangle;
//   if(drawingEllipseEnabled_)
//     return DHAX_Drawn_Shape::Shape_Kinds::Ellipse;
//   if(drawingPolygonEnabled_)
//     return DHAX_Drawn_Shape::Shape_Kinds::Non_Regular_Polygon;

//   return DHAX_Drawn_Shape::Shape_Kinds::N_A;
  }

  ACCESSORS__GET(bool ,temporary_pan_mode)
  ACCESSORS__GET(bool ,temporary_pull_mode)
  ACCESSORS__GET(bool ,fixed_pan_mode)
  ACCESSORS__GET(bool ,fixed_pull_mode)

  inline bool pan_modes()
  {
   return temporary_pan_mode() || fixed_pan_mode();
  }

  inline bool pull_modes()
  {
   return temporary_pull_mode() || fixed_pull_mode();
  }

  inline bool pan_or_pull_mode()
  {
   return temporary_pan_mode() || temporary_pull_mode() || fixed_pan_mode() || fixed_pull_mode();
  }

  void set_temporary_pan_mode()
  {
   temporary_pan_mode_ = true;
  }

  void set_fixed_pan_mode()
  {
   fixed_pan_mode_ = true;
  }

  void unset_temporary_pan_mode()
  {
   temporary_pan_mode_ = false;
  }

  void unset_fixed_pan_mode()
  {
   fixed_pan_mode_ = false;
  }

  void unset_pan_modes()
  {
   unset_temporary_pan_mode();
   unset_fixed_pan_mode();
  }

  void set_temporary_pull_mode()
  {
   temporary_pull_mode_ = true;
  }

  void set_fixed_pull_mode()
  {
   fixed_pull_mode_ = true;
  }

  void unset_temporary_pull_mode()
  {
   temporary_pull_mode_ = false;
  }

  void unset_fixed_pull_mode()
  {
   fixed_pull_mode_ = false;
  }

  void unset_pull_modes()
  {
   unset_temporary_pull_mode();
   unset_fixed_pull_mode();
  }

  void set_multi_draw()
  {
   multi_draw = true;
  }

  void unset_multi_draw()
  {
   multi_draw = false;
  }


 private:

  QList<shape> allEdits_; //lista di tutte le shape che si stanno disegnando sull'immagine

  DHAX_Drawn_Shape* current_drawn_shape_;
  DHAX_Drawn_Shape* active_curve_;

  QStack<DHAX_Drawn_Shape*> held_drawn_shapes_;

  QList<DHAX_Drawn_Shape*> last_canceled_drawn_shapes_;

 public:

  ACCESSORS(DHAX_Drawn_Shape* ,current_drawn_shape)
  ACCESSORS(DHAX_Drawn_Shape* ,active_curve)

  ACCESSORS(DHAX_Application_State* ,application_state)


  ACCESSORS__RGET(QStack<DHAX_Drawn_Shape*> ,held_drawn_shapes)
  ACCESSORS__RGET(QList<DHAX_Drawn_Shape*> ,last_canceled_drawn_shapes)

  DHAX_Drawn_Shape* get_current_drawn_shape();

  DHAX_Drawn_Shape* get_last_canceled_drawn_shape();



  void reset_drawn_shapes();

  void init_polygon_or_polyline(DHAX_Drawn_Shape* dds);
  void complete_polygon();
  void init_polyline();

  void check_clear_last_canceled_drawn_shapes()
  {
   while(!last_canceled_drawn_shapes_.isEmpty())
   {
    DHAX_Drawn_Shape* dds = last_canceled_drawn_shapes_.takeLast();
    delete dds;
   }
  }

  DHAX_Drawn_Shape* check_current_drawn_shape(DHAX_Drawn_Shape::Shape_Kinds sk)
  {
   if(!current_drawn_shape_)
     current_drawn_shape_ = new DHAX_Drawn_Shape(sk);
   else
     current_drawn_shape_->set_shape_kind(sk);
   return current_drawn_shape_;
  }

  DHAX_Drawn_Shape* check_current_drawn_shape()
  {
   return check_current_drawn_shape(current_enabled_shape_kind());
  }

  void cancel_current_drawn_shape()
  {
   last_canceled_drawn_shapes_.push_back(current_drawn_shape_);
   current_drawn_shape_ = nullptr;
   points_.clear();
   point_pairs_.clear();
  }

  void check_hold_drawn_shape()
  {
   if(current_drawn_shape_)
     held_drawn_shapes_.push(current_drawn_shape_);
   current_drawn_shape_ = nullptr;
  }

  DHAX_Drawn_Shape* check_reset_drawn_shape()
  {
   if(current_drawn_shape_)
   {
    current_drawn_shape_->reset_all();
    return current_drawn_shape_;
   }
   return nullptr;
  }



  void defaultColorsThickness();

  void setColorsThickness(int in_radius, int in_thickness, int in_myRed, int in_myGreen, int in_MyBlue, int in_sqRed, int in_sqGreen, int in_sqBlue, int in_shapeRed, int in_shapeGreen, int in_shapeBlue);

//  void enableSquareDraw();
//  void enableEllipseDraw();
//  void enablePolygonDraw();
  void enable_rectangle_shape();
  void enable_ellipse_shape();
  void enable_polygon_shape();
  void enable_multiline_shape();
  void enable_arrow_shape();
  void enable_measurement_shape();
  void enable_skew_rhombus_shape();

  void enableHighlight(bool enable);
  void setNameSelected(bool enable);
  void setShapeSelected(QString in_shapeID);
  void setEdits(QList<shape> inputEdits);
  void resizeEdits(int resize);
  void clear_image();
  void reset();
  void clearLastEdits();

 public:

  DHAX_Display_Image_Data();

};

#endif //  DHAX_GRAPHICS_FRAME__H




