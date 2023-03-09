
#include "rotateable-arrow-annotation.h"

#include <QPainter>

#include <QDebug>

#include <QWheelEvent>

#include "global-types.h"

Rotateable_Arrow_Annotation::Rotateable_Arrow_Annotation(const QPointF& sc, QWidget* p) :
    MultiStep_Annotation_Base(p), tip_point_width_(0), tip_point_width_delta_(1),
    tip_corner_bend_(0), tip_corner_bend_delta_(1), rotation_(0)
{
 shaft_.setTopLeft(sc);
 shaft_.setBottomRight(sc);
 if(p)
   setGeometry(p->geometry());
}

void Rotateable_Arrow_Annotation::adjust_geometry(const QPointF& pos)
{
 if(current_corner_pair_direction_ & Corner_Pair_Directions::First_Phase)
 {
  shaft_.setBottomRight(pos);
 }
 else if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
 {
  QLineF rline(rotation_center_, pos);
  rotation_ = rline.angleTo(rotation_landmark_);
 }
 else if(current_corner_pair_direction_ & Corner_Pair_Directions::Second_Phase)
 {
  Corner_Pair_Directions cpd = (Corner_Pair_Directions) (current_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);
  switch (cpd)
  {
  case Corner_Pair_Directions::Down_Right:
   {
    tip_.setBottomRight(pos);
    tip_.setTopLeft(shaft_.topRight() - QPointF(0, tip_.bottom() - shaft_.bottom()));
   }
   break;
  case Corner_Pair_Directions::Up_Right:
   {
    tip_.setTopRight(pos);
    tip_.setBottomLeft(shaft_.bottomRight() - QPointF(0, tip_.top() - shaft_.top()));
   }
   break;
  case Corner_Pair_Directions::Down_Left:
   {
    tip_.setBottomLeft(pos);
    tip_.setTopRight(shaft_.topLeft() - QPointF(0, tip_.bottom() - shaft_.bottom()));
   }
   break;
  case Corner_Pair_Directions::Up_Left:
   {
    tip_.setTopLeft(pos);
    tip_.setBottomRight(shaft_.bottomLeft() - QPointF(0, tip_.top() - shaft_.top()));
   }
   break;
  case Corner_Pair_Directions::Down_Right_Down:
   {
    tip_.setBottomRight(pos);
    tip_.setTopLeft(shaft_.bottomLeft() - QPointF(tip_.right() - shaft_.right(), 0));
   }
   break;
  case Corner_Pair_Directions::Down_Left_Down:
   {
    tip_.setBottomLeft(pos);
    tip_.setTopRight(shaft_.bottomRight() - QPointF(tip_.left() - shaft_.left(), 0));
   }
   break;

  case Corner_Pair_Directions::Up_Right_Up:
   {
    tip_.setTopRight(pos);
    tip_.setBottomLeft(shaft_.topLeft() - QPointF(tip_.right() - shaft_.right(), 0));
   }
   break;
  case Corner_Pair_Directions::Up_Left_Up:
   {
    tip_.setTopLeft(pos);
    tip_.setBottomRight(shaft_.topRight() - QPointF(tip_.left() - shaft_.left(), 0));
   }
   break;


  default:
   return;
  }
 }
 else if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
 {

 }
}

void Rotateable_Arrow_Annotation::reset_geometry(const QPointF& sc)
{
}

void Rotateable_Arrow_Annotation::init_tip_phase(const QPointF& pos)
{
 Corner_Pair_Directions cpd = get_corner_pair_direction(shaft_);

 if(cpd == Corner_Pair_Directions::N_A)
   return;

 shaft_ = shaft_.normalized();

 if(shaft_.width() < shaft_.height())
 {
  // // switch to up or down facing arrow ...
  cpd ^= 1;
 }

 switch (cpd)
 {
 case Corner_Pair_Directions::Down_Right:
  tip_.setTopLeft(shaft_.topRight());
  tip_.setBottomRight(shaft_.bottomRight());
  break;
 case Corner_Pair_Directions::Up_Right:
  tip_.setBottomLeft(shaft_.bottomRight());
  tip_.setTopRight(shaft_.topRight());
  break;
 case Corner_Pair_Directions::Down_Left:
  tip_.setTopRight(shaft_.topLeft());
  tip_.setBottomLeft(shaft_.bottomLeft());
  break;
 case Corner_Pair_Directions::Up_Left:
  tip_.setBottomRight(shaft_.bottomLeft());
  tip_.setTopLeft(shaft_.topLeft());
  break;

 case Corner_Pair_Directions::Down_Right_Down:
  tip_.setTopLeft(shaft_.bottomLeft());
  tip_.setBottomRight(shaft_.bottomRight());
  break;
 case Corner_Pair_Directions::Down_Left_Down:
  tip_.setTopRight(shaft_.bottomRight());
  tip_.setBottomLeft(shaft_.bottomLeft());
  break;

 case Corner_Pair_Directions::Up_Right_Up:
  tip_.setBottomLeft(shaft_.topLeft());
  tip_.setTopRight(shaft_.topRight());
  break;
 case Corner_Pair_Directions::Up_Left_Up:
  tip_.setBottomRight(shaft_.topRight());
  tip_.setTopLeft(shaft_.topLeft());
  break;

 default:
  return;
 }

 current_corner_pair_direction_ = cpd | Corner_Pair_Directions::Second_Phase;
}

void Rotateable_Arrow_Annotation::finish_rotation_phase(const QPointF& pos)
{
 current_corner_pair_direction_ ^= Corner_Pair_Directions::Third_Phase;
 current_corner_pair_direction_ |= Corner_Pair_Directions::Fourth_Phase;

 repaint();
}

void Rotateable_Arrow_Annotation::finish_tip_phase(const QPointF& pos)
{
 Corner_Pair_Directions cpd = (Corner_Pair_Directions) (current_corner_pair_direction_ &
   Corner_Pair_Directions::Direction_Only);

 current_corner_pair_direction_ ^= Corner_Pair_Directions::Second_Phase;
 current_corner_pair_direction_ |= Corner_Pair_Directions::Third_Phase;

 switch (cpd)
 {
 case Corner_Pair_Directions::Down_Right:
 case Corner_Pair_Directions::Up_Right:
  rotation_center_ =
    ((shaft_.topLeft() + shaft_.bottomLeft()) / 2)
    + QPointF(shaft_.height() / 2, 0)
    ;
  break;
 case Corner_Pair_Directions::Down_Left:
 case Corner_Pair_Directions::Up_Left:
  rotation_center_ = (shaft_.topRight() + shaft_.bottomRight()) / 2;
  break;
 case Corner_Pair_Directions::Down_Right_Down:
 case Corner_Pair_Directions::Down_Left_Down:
  rotation_center_ = (shaft_.topLeft() + shaft_.topRight()) / 2;
  break;
 case Corner_Pair_Directions::Up_Right_Up:
 case Corner_Pair_Directions::Up_Left_Up:
  rotation_center_ = (shaft_.bottomLeft() + shaft_.bottomRight()) / 2;
  break;
 }

 rotation_landmark_.setP1(rotation_center_);
 rotation_landmark_.setP2(pos);
 mapped_rotation_center_ = mapFromParent(rotation_center_.toPoint());
}


void Rotateable_Arrow_Annotation::wheelEvent(QWheelEvent* event)
{
 if( event->buttons() & Qt::RightButton )
 {
  switch (_spaceship(event->angleDelta().y()))
  {
  case 1: if(tip_point_width_ > 0)
   {
    tip_point_width_ -= tip_point_width_delta_;
    repaint();
   }
   break;
  case -1: tip_point_width_ += tip_point_width_delta_; repaint(); break;
  default: return;
  }
 }
 else
 {
  switch (_spaceship(event->angleDelta().y()))
  {
  case 1: if(tip_corner_bend_ > 0)
   {
    tip_corner_bend_ -= tip_corner_bend_delta_;
    repaint();
   }
   break;
  case -1: tip_corner_bend_ += tip_corner_bend_delta_; repaint(); break;
  default: return;
  }
 }
}


void Rotateable_Arrow_Annotation::set_gradient_center(QConicalGradient& gradient)
{
 gradient.setCenter(shaft_.center());
}


void Rotateable_Arrow_Annotation::process_paint_event(QPaintEvent* event, QPainter& painter)
{

 if(current_corner_pair_direction_ & Corner_Pair_Directions::First_Phase)
 {
  QRect _shaft; map_from_parent(shaft_, _shaft);
  painter.drawRect(_shaft);
 }

 else if(current_corner_pair_direction_ &
   Corner_Pair_Directions::Phase_234)
 {
  QRect _shaft; map_from_parent(shaft_.normalized(), _shaft);
  QRect _tip; map_from_parent(tip_.normalized(), _tip);

  s1 cpd = (current_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);

  if(tip_point_width_ > 0)
    cpd = -cpd;

  QPoint bend(tip_corner_bend_, 0);

  if( (cpd & 1) == 0 )
    // //  i.e. a down-right-down or similar
    bend = bend.transposed();

  QVector<QPoint> points;

  switch(cpd)
  {
  case -(s1) Corner_Pair_Directions::Down_Right:
  case -(s1) Corner_Pair_Directions::Up_Right:
   {
    QPoint mid = ((_tip.topRight() + _tip.bottomRight()) / 2);
    points = QVector<QPoint>{
      _shaft.topLeft(), _shaft.topRight(), _tip.topLeft() - bend,
      mid - QPoint(0, tip_point_width_),
      mid + QPoint(0, tip_point_width_),
      _tip.bottomLeft() - bend, _shaft.bottomRight(), _shaft.bottomLeft()
      };
   }
   break;
  case (s1) Corner_Pair_Directions::Down_Right:
  case (s1) Corner_Pair_Directions::Up_Right:
   {
    points = QVector<QPoint>{
      _shaft.topLeft(), _shaft.topRight(), _tip.topLeft() - bend,
      ((_tip.topRight() + _tip.bottomRight()) / 2),
       _tip.bottomLeft() - bend, _shaft.bottomRight(), _shaft.bottomLeft()
      };
   }
   break;
  case (s1) Corner_Pair_Directions::Down_Right_Down:
   {
    points = QVector<QPoint>{
      _shaft.topRight(), _shaft.bottomRight(), _tip.topRight() - bend,
      ((_tip.bottomRight() + _tip.bottomLeft()) / 2),
       _tip.topLeft() - bend, _shaft.bottomLeft(), _shaft.topLeft()
      };
   }
   break;
  case -(s1) Corner_Pair_Directions::Down_Right_Down:
   {
    QPoint mid = ((_tip.bottomLeft() + _tip.bottomRight()) / 2);
    points = QVector<QPoint>{
      _shaft.topRight(), _shaft.bottomRight(), _tip.topRight() - bend,
      mid + QPoint(tip_point_width_, 0),
      mid - QPoint(tip_point_width_, 0),
      _tip.topLeft() - bend, _shaft.bottomLeft(), _shaft.topLeft()
      };
   }
   break;
  case (s1) Corner_Pair_Directions::Up_Right_Up:
   {
    points = QVector<QPoint>{
      _shaft.bottomRight(), _shaft.topRight(), _tip.bottomRight() + bend,
      ((_tip.topRight() + _tip.topLeft()) / 2),
       _tip.bottomLeft() + bend, _shaft.topLeft(), _shaft.bottomLeft()
      };
   }
   break;
  case -(s1) Corner_Pair_Directions::Up_Right_Up:
   {
    QPoint mid = ((_tip.topLeft() + _tip.topRight()) / 2);
    points = QVector<QPoint>{
      _shaft.bottomRight(), _shaft.topRight(), _tip.bottomRight() + bend,
      mid + QPoint(tip_point_width_, 0),
      mid - QPoint(tip_point_width_, 0),
      _tip.bottomLeft() + bend, _shaft.topLeft(), _shaft.bottomLeft()
      };
   }
   break;
  case (s1) Corner_Pair_Directions::Down_Left_Down:
   {
    points = QVector<QPoint>{
      _shaft.topLeft(), _shaft.bottomLeft(), _tip.topLeft() - bend,
      ((_tip.bottomLeft() + _tip.bottomRight()) / 2),
       _tip.topRight() - bend, _shaft.bottomRight(), _shaft.topRight()
      };
   }
   break;
  case -(s1) Corner_Pair_Directions::Down_Left_Down:
   {
    QPoint mid = ((_tip.bottomLeft() + _tip.bottomRight()) / 2);
    points = QVector<QPoint>{
      _shaft.topLeft(), _shaft.bottomLeft(), _tip.topLeft() - bend,
      mid - QPoint(tip_point_width_, 0),
      mid + QPoint(tip_point_width_, 0),
      _tip.topRight() - bend, _shaft.bottomRight(), _shaft.topRight()
      };
   }
   break;
  case (s1) Corner_Pair_Directions::Up_Left_Up:
   {
    points = QVector<QPoint>{
      _shaft.bottomLeft(), _shaft.topLeft(), _tip.bottomLeft() + bend,
      ((_tip.topLeft() + _tip.topRight()) / 2),
       _tip.bottomRight() + bend, _shaft.topRight(), _shaft.bottomRight()
      };
   }
   break;
  case -(s1) Corner_Pair_Directions::Up_Left_Up:
   {
    QPoint mid = ((_tip.topLeft() + _tip.topRight()) / 2);
    points = QVector<QPoint>{
      _shaft.bottomLeft(), _shaft.topLeft(), _tip.bottomLeft() + bend,
      mid - QPoint(tip_point_width_, 0),
      mid + QPoint(tip_point_width_, 0),
       _tip.bottomRight() + bend, _shaft.topRight(), _shaft.bottomRight()
      };
   }
   break;
  case -(s1) Corner_Pair_Directions::Down_Left:
  case -(s1) Corner_Pair_Directions::Up_Left:
   {
    QPoint mid = ((_tip.topLeft() + _tip.bottomLeft()) / 2);

    points = QVector<QPoint>{
      _shaft.topRight(), _shaft.topLeft(), _tip.topRight() + bend,
      mid - QPoint(0, tip_point_width_),
      mid + QPoint(0, tip_point_width_),
      _tip.bottomRight() + bend, _shaft.bottomLeft(), _shaft.bottomRight()
      };
   }
   break;
  case (s1) Corner_Pair_Directions::Down_Left:
  case (s1) Corner_Pair_Directions::Up_Left:
   {
    points = QVector<QPoint>{
      _shaft.topRight(), _shaft.topLeft(), _tip.topRight() + bend,
      ((_tip.topLeft() + _tip.bottomLeft()) / 2),
      _tip.bottomRight() + bend, _shaft.bottomLeft(), _shaft.bottomRight()
      };
   }
   break;
  }
  QPolygon poly(points);

  if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_or_Fourth_Phase)
  {
   poly = QTransform().translate(mapped_rotation_center_.x(), mapped_rotation_center_.y())
     .rotate(rotation_).translate(-mapped_rotation_center_.x(), -mapped_rotation_center_.y())
     .map(poly);
  }
  painter.drawPolygon(poly);

  if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
  {
   painter.setBrush(QColor("orange"));
   painter.drawEllipse(mapped_rotation_center_, 4, 4);
  }

 }
}
