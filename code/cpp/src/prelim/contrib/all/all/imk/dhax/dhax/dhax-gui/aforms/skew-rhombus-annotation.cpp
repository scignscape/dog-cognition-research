
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "skew-rhombus-annotation.h"

#include <QPainter>

#include <QDebug>

#include <QtMath>

#include "global-types.h"

Skew_Rhombus_Annotation::Skew_Rhombus_Annotation(DHAX_Mouse_Interaction_Data& mouse_interaction_data,
  const QPointF& sc, QWidget *p) :
    MultiStep_Annotation_Base(mouse_interaction_data, p),
      x_offset_(0), expansion_(0), y_offset_(0)
{
 if(p)
 {
  MultiStep_Annotation_Base::setGeometry(p->geometry());
 }

 scaffold_.setTopLeft(sc);
 scaffold_.setBottomRight(sc);

}

void Skew_Rhombus_Annotation::show()
{
 MultiStep_Annotation_Base::show();
}

void Skew_Rhombus_Annotation::reset_geometry(const QPointF& pos)
{

}

void Skew_Rhombus_Annotation::adjust_geometry(const QPointF& pos)
{
 if(current_corner_pair_direction_ & Corner_Pair_Directions::First_Phase)
 {
  scaffold_.setBottomRight(pos);
 }
 else if(current_corner_pair_direction_ & Corner_Pair_Directions::Second_Phase)
 {
  Corner_Pair_Directions cpd = (Corner_Pair_Directions) (current_corner_pair_direction_ &
    Corner_Pair_Directions::Direction_Only);

  switch (cpd)
  {
  case Corner_Pair_Directions::Up_Left:
  case Corner_Pair_Directions::Down_Left:
   x_offset_ = scaffold_.left() - pos.x();
   break;

  case Corner_Pair_Directions::Up_Right:
  case Corner_Pair_Directions::Down_Right:
  default:
   x_offset_ = pos.x() - scaffold_.right();
   break;
  }
 }
 else if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
 {
  Corner_Pair_Directions cpd = (Corner_Pair_Directions) (current_corner_pair_direction_ &
    Corner_Pair_Directions::Direction_Only);

  switch (cpd)
  {
  case Corner_Pair_Directions::Up_Left:
  case Corner_Pair_Directions::Up_Right:
   scaffold_.setTop(pos.y() - y_offset_);
   break;

  case Corner_Pair_Directions::Down_Left:
  case Corner_Pair_Directions::Down_Right:
  default:
   scaffold_.setBottom(pos.y() - y_offset_);
   break;
  }

 }
}

void Skew_Rhombus_Annotation::init_skew_phase(const QPointF& pos)
{
 if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
 {
  current_corner_pair_direction_ ^= Corner_Pair_Directions::Third_Phase;
  current_corner_pair_direction_ |= Corner_Pair_Directions::Second_Phase;
  return;
 }

 Corner_Pair_Directions cpd = get_corner_pair_direction(scaffold_);


 if(cpd == Corner_Pair_Directions::N_A)
   return;

 scaffold_ = scaffold_.normalized();

 current_corner_pair_direction_ = cpd | Corner_Pair_Directions::Second_Phase;

 qDebug() << "ccpd: " << (int) current_corner_pair_direction_;
}

void Skew_Rhombus_Annotation::finish_skew_phase(const QPointF& pos)
{
 Corner_Pair_Directions cpd = (Corner_Pair_Directions) (current_corner_pair_direction_ &
   Corner_Pair_Directions::Direction_Only);

 current_corner_pair_direction_ ^= Corner_Pair_Directions::Second_Phase;
 current_corner_pair_direction_ |= Corner_Pair_Directions::Third_Phase;

 switch (cpd)
 {
 case Corner_Pair_Directions::Up_Left:
 case Corner_Pair_Directions::Up_Right:
  y_offset_ = scaffold_.top() - pos.y();
  break;

 case Corner_Pair_Directions::Down_Left:
 case Corner_Pair_Directions::Down_Right:
 default:
  y_offset_ = pos.y() - scaffold_.bottom();
  break;

 }
}

void Skew_Rhombus_Annotation::finish_expansion_phase(const QPointF& pos)
{
 current_corner_pair_direction_ ^= Corner_Pair_Directions::Third_Phase;
 current_corner_pair_direction_ |= Corner_Pair_Directions::Fourth_Phase;
}


QPair<r8, r8> Skew_Rhombus_Annotation::get_offset_angle()
{
 double inv = x_offset_ / scaffold_.height();
 r8 ang = qAtan(inv);
 return {qRadiansToDegrees(ang), -inv};
}


void Skew_Rhombus_Annotation::process_paint_event(QPaintEvent* event, QPainter& painter)
{
 if(current_corner_pair_direction_ & Corner_Pair_Directions::First_Phase)
 {
  QRect _scaffold; map_from_parent(scaffold_, _scaffold);
  painter.drawRect(_scaffold);
 }
 else if(current_corner_pair_direction_ & Corner_Pair_Directions::Phase_234)
 {
  QPoint offset;
  Corner_Pair_Directions cpd = (Corner_Pair_Directions) (current_corner_pair_direction_ &
    Corner_Pair_Directions::Direction_Only);
  switch (cpd)
  {
  case Corner_Pair_Directions::Up_Left:
  case Corner_Pair_Directions::Down_Left:
   offset = QPoint{-x_offset_, 0};
   break;
  case Corner_Pair_Directions::Up_Right:
  case Corner_Pair_Directions::Down_Right:
   offset = QPoint{x_offset_, 0};
   break;
  default:
   break;
  }


  //qDebug() << "2";
  QPolygon poly;
  //QPoint p1 = scaffold_.topLeft().toPoint() + offset;
  poly << scaffold_.topLeft().toPoint() + offset << scaffold_.topRight().toPoint() + offset
       << scaffold_.bottomRight().toPoint() << scaffold_.bottomLeft().toPoint();
  painter.drawPolygon(poly);
 }
}

void Skew_Rhombus_Annotation::set_gradient_center(QConicalGradient& gradient)
{
 gradient.setCenter(scaffold_.center());
}

