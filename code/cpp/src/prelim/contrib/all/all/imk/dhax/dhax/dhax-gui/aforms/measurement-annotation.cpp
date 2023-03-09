
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "measurement-annotation.h"

#include <QPainter>

#include <QDebug>

#include <QWheelEvent>

#include "global-types.h"

Measurement_Annotation::Measurement_Annotation(DHAX_Mouse_Interaction_Data& mouse_interaction_data,
    const QPointF& sc, QWidget* p) :
    MultiStep_Annotation_Base(mouse_interaction_data, p), left_line_width_(5),
    right_line_width_(5), top_line_width_(3),
    bottom_line_width_(3),
    horizontal_extension_(0), vertical_extension_(0)
{
 inner_.setTopLeft(sc);
 inner_.setBottomRight(sc);
 if(p)
   setGeometry(p->geometry());
}


void Measurement_Annotation::_check_outer_adjust(u1 index, s2 amount)
{
 s2 adjust = 0;
 switch(index)
 {
 case 1:
  if(amount < 0)
  {
   horizontal_extension_ = -amount;
   adjust = -amount;
  }
  else
    horizontal_extension_ = amount;
  break;

 case 2:
  if(amount < 0)
  {
   vertical_extension_ = -amount;
   adjust = -amount;
  }
  else
    vertical_extension_ = amount;
  break;

 case 3:
  if(amount < 0)
  {
   horizontal_extension_ = -amount;
   adjust = amount;
  }
  else
    horizontal_extension_ = amount;
  break;

 case 4:
  if(amount < 0)
  {
   vertical_extension_ = -amount;
   adjust = amount;
  }
  else
    vertical_extension_ = amount;
  break;

 default: break;
 }

 if(adjust != 0)
 {
  s2 amounts[4] = {0,0,0,0};
  amounts[index - 1] = adjust;
  outer_.adjust(amounts[0], amounts[1], amounts[2], amounts[3]);
 }
}

void Measurement_Annotation::adjust_geometry(const QPointF& pos)
{
 if(current_corner_pair_direction_ & Corner_Pair_Directions::First_Phase)
 {
  inner_.setBottomRight(pos);
 }
 else if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
 {
//  horizontal_extension_ =
//  QLineF rline(rotation_center_, pos);
//  rotation_ = rline.angleTo(rotation_landmark_);

  s1 h = 0, v = 0;

  Corner_Pair_Directions cpd = (Corner_Pair_Directions) (current_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);
  switch (cpd)
  {
  case Corner_Pair_Directions::Down_Right:
   h = pos.x() - outer_.bottomRight().x();
   v = pos.y() - outer_.bottomRight().y();

   if(h != 0)
     _check_outer_adjust(3, h);
   if(v != 0)
     _check_outer_adjust(4, v);

   break;
  case Corner_Pair_Directions::Up_Right:
   h = pos.x() - outer_.topRight().x();
   v = outer_.topRight().y() - pos.y();
   if(h != 0)
     _check_outer_adjust(3, h);
   if(v != 0)
     _check_outer_adjust(2, v);

   break;
  case Corner_Pair_Directions::Down_Left:
   h = outer_.bottomLeft().x() - pos.x();
   v = pos.y() - outer_.bottomLeft().y();

   if(h != 0)
     _check_outer_adjust(1, h);
   if(v != 0)
     _check_outer_adjust(4, v);
   break;

  case Corner_Pair_Directions::Up_Left:
   h = outer_.topLeft().x() - pos.x();
   v = outer_.topLeft().y() - pos.y();

   if(h != 0)
     _check_outer_adjust(1, h);
   if(v != 0)
     _check_outer_adjust(2, v);
   break;

  default: break;
  }
 }
 else if(current_corner_pair_direction_ & Corner_Pair_Directions::Second_Phase)
 {
  Corner_Pair_Directions cpd = (Corner_Pair_Directions) (current_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);
  switch (cpd)
  {
  case Corner_Pair_Directions::Down_Right:
   outer_.setBottomRight(pos);
   outer_.setTopLeft(inner_.topLeft() + inner_.bottomRight() - outer_.bottomRight());
   break;
  case Corner_Pair_Directions::Up_Right:
   outer_.setTopRight(pos);
   outer_.setBottomLeft(inner_.bottomLeft() + inner_.topRight() - outer_.topRight());
   break;
  case Corner_Pair_Directions::Down_Left:
   outer_.setBottomLeft(pos);
   outer_.setTopRight(inner_.topRight() + inner_.bottomLeft() - outer_.bottomLeft());
   break;
  case Corner_Pair_Directions::Up_Left:
   outer_.setTopLeft(pos);
   outer_.setBottomRight(inner_.bottomRight() + inner_.topLeft() - outer_.topLeft());
   break;
  default:
   return;
  }
 }
}

void Measurement_Annotation::reset_geometry(const QPointF& sc)
{

}

void Measurement_Annotation::init_outer_phase(const QPointF& pos)
{
 Corner_Pair_Directions cpd = get_corner_pair_direction(inner_);

 if(cpd == Corner_Pair_Directions::N_A)
   return;

 inner_ = inner_.normalized();
 outer_ = inner_;

 current_corner_pair_direction_ = cpd | Corner_Pair_Directions::Second_Phase;
}

void Measurement_Annotation::finish_extension_phase(const QPointF& pos)
{
 current_corner_pair_direction_ ^= Corner_Pair_Directions::Third_Phase;
 current_corner_pair_direction_ |= Corner_Pair_Directions::Fourth_Phase;

 repaint();
}

void Measurement_Annotation::finish_outer_phase(const QPointF& pos)
{
 Corner_Pair_Directions cpd = (Corner_Pair_Directions) (current_corner_pair_direction_ &
   Corner_Pair_Directions::Direction_Only);

 current_corner_pair_direction_ ^= Corner_Pair_Directions::Second_Phase;
 current_corner_pair_direction_ |= Corner_Pair_Directions::Third_Phase;

}


void Measurement_Annotation::wheelEvent(QWheelEvent* event)
{
}


void Measurement_Annotation::set_gradient_center(QConicalGradient& gradient)
{
 if(current_corner_pair_direction_ & Corner_Pair_Directions::First_Phase)
   gradient.setCenter(inner_.center());
 else
   gradient.setCenter(outer_.center());
}

void move_p1x(QLine& line, int amount)
{
 line.setP1({line.x1() + amount, line.y1()});
}

void move_p2x(QLine& line, int amount)
{
 line.setP2({line.x2() + amount, line.y2()});
}

void move_p1y(QLine& line, int amount)
{
 line.setP1({line.x1(), line.y1() + amount});
}

void move_p2y(QLine& line, int amount)
{
 line.setP2({line.x2(), line.y2() + amount});
}

void Measurement_Annotation::process_paint_event(QPaintEvent* event, QPainter& painter)
{

 if(current_corner_pair_direction_ & Corner_Pair_Directions::First_Phase)
 {
  QRect _inner; map_from_parent(inner_, _inner);
  painter.drawRect(_inner);
 }

 else if(current_corner_pair_direction_ &
   Corner_Pair_Directions::Phase_234)
 {
  QRect _inner; map_from_parent(inner_.normalized(), _inner);
  QRect _outer; map_from_parent(outer_.normalized(), _outer);

  QLine top_line(_outer.left(), _inner.top(), _outer.right(), _inner.top());
  QLine bottom_line(_outer.left(), _inner.bottom(), _outer.right(), _inner.bottom());

  QLine left_line(_inner.left(), _outer.top(), _inner.left(), _outer.bottom());
  QLine right_line(_inner.right(), _outer.top(), _inner.right(), _outer.bottom());

  if(!(current_corner_pair_direction_ & Corner_Pair_Directions::Second_Phase))
  {
   move_p1x(top_line, -horizontal_extension_);
   move_p1y(left_line, -vertical_extension_);
  }

  QPen store_pen = painter.pen();
  QPen emph_pen = QPen(QColor(200, 20, 20, 100));
  QPen outer_pen = QPen(QColor(20, 20, 200, 150));
  outer_pen.setWidth(2);

  QPen use_pen = store_pen;
  use_pen.setWidth(1);

  emph_pen.setWidth(top_line_width_);
  painter.setPen(use_pen);
  painter.drawLine(top_line);
  painter.setPen(emph_pen);
  painter.drawLine(top_line);

  emph_pen.setWidth(top_line_width_);
  painter.setPen(use_pen);
  painter.drawLine(left_line);
  painter.setPen(emph_pen);
  painter.drawLine(left_line);

  emph_pen.setWidth(top_line_width_);
  painter.setPen(use_pen);
  painter.drawLine(bottom_line);
  painter.setPen(emph_pen);
  painter.drawLine(bottom_line);

  emph_pen.setWidth(top_line_width_);
  painter.setPen(use_pen);
  painter.drawLine(right_line);
  painter.setPen(emph_pen);
  painter.drawLine(right_line);

  if(current_corner_pair_direction_ & Corner_Pair_Directions::Second_Phase)
  {
   painter.setPen(outer_pen);
   painter.drawRect(_outer);
  }
  else if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
  {
   painter.setPen(outer_pen);
   QBrush store_brush = painter.brush();
   painter.setBrush(Qt::NoBrush);
   painter.drawRect(_outer);
   painter.setBrush(store_brush);
  }

  painter.setPen(store_pen);
  painter.drawRect(_inner);

  //  s1 cpd = (current_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);
//  QVector<QPoint> points;
//  switch(cpd)
//  {
//  }
 }
}



// switch (cpd)
// {
// case Corner_Pair_Directions::Down_Right:
//  horizontal_extension_ = 0x40;
//  vertical_extension_ = 0x20;
//  break;
// case Corner_Pair_Directions::Up_Right:
//  horizontal_extension_ = 0x40;
//  vertical_extension_ = -0x20;
//  break;
// case Corner_Pair_Directions::Down_Left:
//  horizontal_extension_ = -0x40;
//  vertical_extension_ = 0x20;
//  break;
// case Corner_Pair_Directions::Up_Left:
//  horizontal_extension_ = -0x40;
//  vertical_extension_ = -0x20;
//  break;
// default:
//  break;
// case Corner_Pair_Directions::Down_Right_Down:
// case Corner_Pair_Directions::Down_Left_Down:
//  break;
// case Corner_Pair_Directions::Up_Right_Up:
// case Corner_Pair_Directions::Up_Left_Up:
//  break;
// }

//   s1 hext = 0, vext = 0, hextl = 0, vextl = 0;
//   if(horizontal_extension_ < 0)
//   {
//    hext = -horizontal_extension_;
//    hextl = hext & 0x1f;
//    hext = hextl - hext;
//   }
//   else if(horizontal_extension_ > 0)
//   {
//    if(horizontal_extension_ > 70)
//      qDebug() << "70";
//    hext = horizontal_extension_;
//    hextl = hext & 0x1f;
//    hext = hext - hextl;
//   }
//   if(vertical_extension_ < 0)
//   {
//    vext = -vertical_extension_;
//    vextl = vext & 0x1f;
//    vext = vextl - vext;
//   }
//   else if(vertical_extension_ > 0)
//   {
//    vext = vertical_extension_;
//    vextl = vext & 0x1f;
//    vext = vext - vextl;
//   }

//   qDebug() << "hext = " << hext;
//   qDebug() << "vext = " << vext;
//   qDebug() << "hext + vext = " << hext + vext;
//   qDebug() << "hextl = " << hextl;
//   qDebug() << "vextl = " << vextl;

//   switch(hext + vext)
//   {
//   case 0: default: break;
//   case -0x40 + -0x20:
//    move_p1x(left_line, -hextl);
//    move_p1y(top_line, -vextl);
//    break;
//   case -0x40 + 0x20:
//    move_p1x(left_line, -hextl);
//    move_p2y(top_line, vextl);
//    break;
//   case 0x40 + -0x20:
//    move_p1x(top_line, -hextl);
//    move_p1y(left_line, -vextl);
//    break;
//   case 0x40 + 0x20:
//    move_p1x(top_line, -hextl);
//    move_p1y(left_line, -vextl);

//    qDebug() << "hl = " << hextl;
//    qDebug() << "vl = " << vextl;

//    break;
//   }

