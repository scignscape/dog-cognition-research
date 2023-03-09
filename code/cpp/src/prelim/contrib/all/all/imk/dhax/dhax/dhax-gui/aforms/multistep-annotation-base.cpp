
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "multistep-annotation-base.h"

#include <QPainter>

#include <QDebug>

#include <QWheelEvent>

#include "global-types.h"

MultiStep_Annotation_Base::MultiStep_Annotation_Base(DHAX_Mouse_Interaction_Data& mouse_interaction_data,
    QWidget* p) :
    QWidget(p), current_corner_pair_direction_(Corner_Pair_Directions::First_Phase),
    mouse_interaction_data_(mouse_interaction_data), containing_image_(nullptr)
{
 if(p)
   setGeometry(p->geometry());
}

void MultiStep_Annotation_Base::fulfill_left_init(QMouseEvent* mev, n8 mode_data_request)
{
 fulfill_left_init(mev->pos(), mode_data_request);
}

void MultiStep_Annotation_Base::fulfill_left_move_release(QMouseEvent* mev, n8 mode_data_request)
{
 fulfill_left_move_release(mev->pos(), mode_data_request);
}

void MultiStep_Annotation_Base::fulfill_left_move(QMouseEvent* mev, n8 mode_data_request)
{
 fulfill_left_move(mev->pos(), mode_data_request);
}

void MultiStep_Annotation_Base::fulfill_left_resume(QMouseEvent* mev, n8 mode_data_request)
{
 fulfill_left_resume(mev->pos(), mode_data_request);
}

void MultiStep_Annotation_Base::show()
{
 QWidget::show();
}


MultiStep_Annotation_Base::Corner_Pair_Directions MultiStep_Annotation_Base::get_corner_pair_direction(const QPointF& landmark,
  const QPointF& trajector)
{
 QPair<s1, s1> xy_ss = {_spaceship(landmark.x(), trajector.x()),
   _spaceship(landmark.y(), trajector.y())};

 static QMap<QPair<s1, s1>, Corner_Pair_Directions> static_map {
  { {1, 1}, Corner_Pair_Directions::Down_Right },
  { {1, 0}, Corner_Pair_Directions::Right },
  { {1, -1}, Corner_Pair_Directions::Up_Right },

  { {0, 1}, Corner_Pair_Directions::Down },
  { {0, 0}, Corner_Pair_Directions::N_A },
  { {0, -1}, Corner_Pair_Directions::Up },

  { {-1, 1}, Corner_Pair_Directions::Down_Left },
  { {-1, 0}, Corner_Pair_Directions::Left },
  { {-1, -1}, Corner_Pair_Directions::Up_Left },

 };

 return static_map.value(xy_ss, Corner_Pair_Directions::N_A);
}

void MultiStep_Annotation_Base::wheelEvent(QWheelEvent *event)
{

}

void MultiStep_Annotation_Base::init_second_phase(const QPointF& pos)
{

}

void MultiStep_Annotation_Base::finish_second_phase(const QPointF& pos)
{

}

void MultiStep_Annotation_Base::finish_third_phase(const QPointF& pos)
{

}

void MultiStep_Annotation_Base::map_from_parent(const QRectF& source,
  QRect& result)
{
 result.setTopLeft(mapFromParent(source.topLeft().toPoint()));
 result.setBottomRight(mapFromParent(source.bottomRight().toPoint()));
}

//void Arrow_Annotation::wheelEvent(QWheelEvent* event)
//{
// if( event->buttons() & Qt::RightButton )
// {
//  switch (_spaceship(event->angleDelta().y()))
//  {
//  case 1: if(tip_point_width_ > 0)
//   {
//    tip_point_width_ -= tip_point_width_delta_;
//    repaint();
//   }
//   break;
//  case -1: tip_point_width_ += tip_point_width_delta_; repaint(); break;
//  default: return;
//  }
// }
// else
// {
//  switch (_spaceship(event->angleDelta().y()))
//  {
//  case 1: if(tip_corner_bend_ > 0)
//   {
//    tip_corner_bend_ -= tip_corner_bend_delta_;
//    repaint();
//   }
//   break;
//  case -1: tip_corner_bend_ += tip_corner_bend_delta_; repaint(); break;
//  default: return;
//  }
// }
//}

void MultiStep_Annotation_Base::init_shape_brush(QBrush& brush, Qt::BrushStyle& style, u1 density_level)
{
 init_solid_shape_brush(brush, style, density_level);
}

void MultiStep_Annotation_Base::init_dotted_shape_brush(QBrush& brush, Qt::BrushStyle& style, u1 density_level)
{
// shapeRed_ = 240;
// shapeGreen_ = 255;
// shapeBlue_ = 160;

 u1 _tmpRed_ = 240, _tmpGreen_ = 255, _tmpBlue_ = 160, _tmpAlpha_ = 200;

 switch (density_level)
 {
 default: break;
 case 0: style = Qt::SolidPattern; break;
 case 1: style = Qt::Dense1Pattern; break;
 case 2: style = Qt::Dense2Pattern; break;
 case 3: style = Qt::Dense3Pattern; break;
 case 4: style = Qt::Dense4Pattern; break;
 case 5: style = Qt::Dense5Pattern; break;
 case 6: style = Qt::Dense6Pattern; break;
 case 7: style = Qt::Dense7Pattern; break;
 }

 brush = QBrush(QColor(_tmpRed_, _tmpGreen_, _tmpBlue_, _tmpAlpha_), style);
}

void MultiStep_Annotation_Base::init_solid_shape_brush(QBrush& brush, Qt::BrushStyle& style, u1 density_level)
{
 u1 _tmpRed_ = 55, _tmpGreen_ = 55, _tmpBlue_ = 55, _tmpAlpha_ = 100;
 switch (density_level)
 {
 default: break;
 case 0: style = Qt::SolidPattern; break;
 case 1: style = Qt::Dense1Pattern; break;
 case 2: style = Qt::Dense2Pattern; break;
 case 3: style = Qt::Dense3Pattern; break;
 case 4: style = Qt::Dense4Pattern; break;
 case 5: style = Qt::Dense5Pattern; break;
 case 6: style = Qt::Dense6Pattern; break;
 case 7: style = Qt::Dense7Pattern; break;
 }

 brush = QBrush(QColor(_tmpRed_, _tmpGreen_, _tmpBlue_, _tmpAlpha_), style);
}

void MultiStep_Annotation_Base::init_vertex_handle_brush(QBrush& brush)
{

}


void MultiStep_Annotation_Base::draw_control_square(const QPoint& center,
  QPainter& painter, u1 wind, u1 radius, QColor color)
{
 QPoint pr(radius, radius);
 QPoint pr1(radius - 1, radius - 1);

 QRect rect(center - pr, center + pr1);
 //painter.fillRect(rect, QColor(data_->sqRed_, data_->sqGreen_, data_->sqBlue_));

 //QRect rect(center.x() - data_->radius_, center.y() - data_->radius_, data_->radius_*2, data_->radius_*2);

 u1 sgradient_base = 0;
 u1 sgradient_mid = 100;
 u1 wind_multiple = 30;
 QConicalGradient sgradient;
 sgradient.setAngle((wind * wind_multiple) + get_vertex_handle_wind_offset());
 sgradient.setCenter(center);//.x() - data_->radius_/2,
                     //center.y() - data_->radius_/2);
 sgradient.setColorAt(0.0, color);
 sgradient.setColorAt(0.15, color);
 sgradient.setColorAt(0.2, QColor(sgradient_mid,sgradient_mid,sgradient_base));
 sgradient.setColorAt(0.25, color);
 sgradient.setColorAt(0.5, color);
 sgradient.setColorAt(0.55, QColor(sgradient_mid,sgradient_base,sgradient_mid));
 sgradient.setColorAt(0.6, color);
 sgradient.setColorAt(0.8, color);
 sgradient.setColorAt(0.85, QColor(sgradient_base,sgradient_mid,sgradient_mid));
 sgradient.setColorAt(0.9, color);
 sgradient.setColorAt(1, color);
 painter.fillRect(rect, sgradient);

}


void MultiStep_Annotation_Base::draw_vertex_handles(const QVector<const QPoint*>& points,
   QPainter& painter, u1 radius)
{
// QBrush brush;
// init_vertex_handle_brush(brush);

 //QColor highlight(data_->sqRed_,data_->sqGreen_,data_->sqBlue_)
 const QColor& highlight = presentation_data_.vertex_handle_highlight_color(); //(250,250,250);

 u1 i = 0;
 for(const QPoint* const point : points)
 {
  draw_control_square(*point, painter, ++i, radius, highlight);
 }
}

void MultiStep_Annotation_Base::draw_vertex_handles(QPainter& painter, u1 radius)
{

}

void MultiStep_Annotation_Base::init_shape_pen(QConicalGradient& gradient, QPen& pen)
{
 init_solid_shape_pen(gradient, pen); //, Qt::DashDotDotLine); //shapePen
}

void MultiStep_Annotation_Base::init_solid_shape_pen(QConicalGradient& gradient, QPen& pen)
{
 pen = QPen(gradient, presentation_data_.solid_pen_width()); //, Qt::DashDotDotLine); //shapePen
}

void MultiStep_Annotation_Base::init_dotted_shape_pen(QConicalGradient& gradient, QPen& pen)
{
 pen = QPen(gradient, presentation_data_.dotted_pen_width(), Qt::DashDotDotLine); //shapePen
}

void MultiStep_Annotation_Base::paintEvent(QPaintEvent *event)
{

 QPainter painter(this);

// u1 _tmpRed_ = 55; u1 _tmpGreen_ = 55; u1 _tmpBlue_ = 55;
// u1 _tmpAlpha_ = 100;

// QPen myPen(QColor(_tmpRed_, _tmpGreen_,_tmpBlue_), 3, Qt::SolidLine);
// u1 gradient_base = 140;

 QConicalGradient& gradient = presentation_data_.pen_gradient();

 //?

 //gradient.setCenter(shaft_.center()); // ((mid_rect.topLeft() + mid_rect.center())/2) );

 set_gradient_center(gradient);

   QPen shapePen; //(gradient, 4); //, Qt::DashDotDotLine); //shapePen

 init_shape_pen(gradient, shapePen);

 //myPen.setCapStyle(Qt::RoundCap);
 shapePen.setCapStyle(Qt::RoundCap);


 painter.setPen(shapePen);
 QBrush shape_brush;
 Qt::BrushStyle style;
 init_shape_brush(shape_brush, style);
 painter.setBrush(shape_brush);

 process_paint_event(event, painter);

 draw_vertex_handles(painter);
}
