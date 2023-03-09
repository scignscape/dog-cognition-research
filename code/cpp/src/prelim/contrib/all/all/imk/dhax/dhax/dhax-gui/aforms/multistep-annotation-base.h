
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef MULTISTEP_ANNOTATION_BASE__H
#define MULTISTEP_ANNOTATION_BASE__H


#include <QRubberBand>

#include "global-types.h"

#include "accessors.h"

#include "dhax-annotation-presentation-data.h"

class DHAX_Mouse_Interaction_Data;

class MultiStep_Annotation_Base //
  : public QWidget
{
 Q_OBJECT


protected:

 enum class Corner_Pair_Directions {
  N_A, Up = 1, Up_Right_Up = 2, Up_Right = 3,
  Right = 5,
  Down_Right_Down = 6, Down_Right = 7,
  Down = 9,
  Down_Left_Down = 10, Down_Left = 11,
  Left = 13,
  Up_Left_Up = 14, Up_Left = 15,
  Direction_Only = 15,
  First_Phase = 16, Second_Phase = 32, Third_Phase = 64,
  Second_or_Third_Phase = Second_Phase | Third_Phase,
  Fourth_Phase = 128, Third_or_Fourth_Phase = Third_Phase | Fourth_Phase,
  Phase_234 = Second_or_Third_Phase | Fourth_Phase,
 };

 ENUM_FLAGS_OP_MACROS(Corner_Pair_Directions)


 Corner_Pair_Directions current_corner_pair_direction_;

 DHAX_Annotation_Presentation_Data presentation_data_;

 void draw_control_square(const QPoint& center, QPainter& painter,
   u1 wind, u1 radius, QColor color);

 void map_from_parent(const QRectF& source, QRect& result);
// void map_from_parent_plus_x(const QRectF& source, r8 x_delta, QRect& result);
// void map_from_parent_plus_y(const QRectF& source, r8 y_delta, QRect& result);

 static s1 _spaceship(r8 lhs, r8 rhs = 0)
 {
  if(lhs < rhs)
    return 1;
  if(rhs < lhs)
    return -1;
  return 0;
 }

 static Corner_Pair_Directions get_corner_pair_direction(const QPointF& landmark,
   const QPointF& trajector);

 static Corner_Pair_Directions get_corner_pair_direction(const QRectF& rect)
 {
  // //  assumes rect has been normalized ...
  return get_corner_pair_direction(rect.topLeft(), rect.bottomRight());
 }

 void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

 DHAX_Mouse_Interaction_Data& mouse_interaction_data_;

 QImage* containing_image_;
// u2 image_width_;
// u2 image_height_;

public:

 MultiStep_Annotation_Base(DHAX_Mouse_Interaction_Data& mouse_interaction_data,
   QWidget* p = nullptr);

 ACCESSORS(QImage* ,containing_image)

 virtual void adjust_geometry(const QPointF& pos) = 0;
 virtual void reset_geometry(const QPointF& sc = {}) = 0;

 virtual void pressed_mode_data_request_code(QMouseEvent*, n8&) { }
 virtual void released_mode_data_request_code(QMouseEvent*, n8&) { }
 virtual void moved_mode_data_request_code(QMouseEvent*, n8&) { }


 // //  These won't be called unless a subclass overrides the
  //    mode_data_request_code() so there's no harm in providing
  //    a default implementation which just forwards to a handler
  //    that only needs the mouse event position
 virtual void fulfill_left_init(QMouseEvent* mev, n8 mode_data_request);
 virtual void fulfill_left_move(QMouseEvent* mev, n8 mode_data_request);
 virtual void fulfill_left_move_release(QMouseEvent* mev, n8 mode_data_request);
 virtual void fulfill_left_resume(QMouseEvent* mev, n8 mode_data_request);

 virtual void fulfill_left_init(const QPoint&, n8) { }
 virtual void fulfill_left_move(const QPoint&, n8) { }
 virtual void fulfill_left_resume(const QPoint&, n8) { }
 virtual void fulfill_left_move_release(const QPoint&, n8) { }


 virtual void init_second_phase(const QPointF& pos);
 virtual void finish_second_phase(const QPointF& pos);
 virtual void finish_third_phase(const QPointF& pos);

 virtual void show();

 virtual QString kind_name(){return {};}
 virtual void generate_ntxh(QString& result) {}

 virtual void init_shape_pen(QConicalGradient& gradient, QPen& pen);
 virtual void init_dotted_shape_pen(QConicalGradient& gradient, QPen& pen);
 virtual void init_solid_shape_pen(QConicalGradient& gradient, QPen& pen);

 virtual void init_shape_brush(QBrush& brush, Qt::BrushStyle& style, u1 density_level = 0);
 virtual void init_dotted_shape_brush(QBrush& brush, Qt::BrushStyle& style, u1 density_level = 6);
 virtual void init_solid_shape_brush(QBrush& brush, Qt::BrushStyle& style, u1 density_level = 0);

 virtual u1 get_vertex_handle_wind_offset()
 {
  return 0;
 }

 virtual void draw_vertex_handles(const QVector<const QPoint*>& points,
   QPainter& painter, u1 radius);

 virtual u1 get_vertex_handles_radius() { return 8; }

 virtual void draw_vertex_handles(QPainter& painter, u1 radius);
 virtual void init_vertex_handle_brush(QBrush& brush);
 virtual void draw_vertex_handles(QPainter& painter)
 {
  draw_vertex_handles(painter, get_vertex_handles_radius());
 }

protected:

Q_SIGNALS:
 virtual void process_paint_event(QPaintEvent* event, QPainter& painter);
 virtual void set_gradient_center(QConicalGradient& gradient);

protected:

 virtual void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

//   32 33 34  35 36 37  38 39 40  41 42 43  44 45 46  47 48 49  50 51 52  53 54 55  56 57 58  59
//   11 11 11  12 12 12  13 13 13  14 14 14  15 15 15  16 16 16  17 17 17  18 18 18  19 19 19  20
//

//   32 33 34 35  36 37 38  39 40 41  42 43 44  45 46 47  48 49 50  51 52 53  54 55 56  57 58 59
//   11 11 11 11  12 12 12  13 13 13  14 14 14  15 15 15  16 16 16  17 17 17  18 18 18  19 19 19
//

public Q_SLOTS:

};

#endif // MULTISTEP_ANNOTATION_BASE__H
