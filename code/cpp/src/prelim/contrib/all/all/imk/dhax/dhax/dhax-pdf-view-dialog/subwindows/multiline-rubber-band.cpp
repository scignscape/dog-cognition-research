
#include "multiline-rubber-band.h"

#include <QPainter>

#include <QDebug>

#include "global-types.h"

MultiLine_Rubber_Band::MultiLine_Rubber_Band(QRubberBand::Shape s,
    const QPointF& sc, QWidget *p) :
    MultiStep_Annotation_Base(p), // new QRubberBand(s, p) ), //QRubberBand(s,p),
      //current_corner_pair_direction_(Corner_Pair_Directions::First_Phase),
      inner_starting_corner_(sc), outer_end_corner_(sc)
{
 if(p)
 {
//  if(QRubberBand* r = qobject_cast<QRubberBand*>(parent()))
//    r->setGeometry({}); //p->geometry());
  MultiStep_Annotation_Base::setGeometry(p->geometry());
  //QRubberBand::setGeometry(p->geometry());
 }
}

void MultiLine_Rubber_Band::show()
{
// if(QRubberBand* r = qobject_cast<QRubberBand*>(parent()))
//   r->hide();
 MultiStep_Annotation_Base::show();
}

void MultiLine_Rubber_Band::reset_active_corner_pair_direction(Corner_Pair_Directions cpd, const QPointF& pos)
{

}

void MultiLine_Rubber_Band::init_active_corner_pair_direction(Corner_Pair_Directions cpd, const QPointF& pos)
{
 switch (cpd)
 {
  // //  assume in the N_A case that users are mostly likely to
   //    eventually drag the mouse down and right, but note
   //    this procedure might not even get called with an N_A value
 case Corner_Pair_Directions::N_A:

 case Corner_Pair_Directions::Up_Left:
 case Corner_Pair_Directions::Up_Right:

 case Corner_Pair_Directions::Down_Left:
 case Corner_Pair_Directions::Down_Right:
  {
   current_corner_pair_direction_ = cpd; //Corner_Pair_Directions::Down_Right;
   outer_end_corner_ = pos;
  }
  break;



  // //  todo: other direections
 }
}

void MultiLine_Rubber_Band::get_mid_rect_post(QRectF& result)
{
 result = QRectF(outer_starting_corner_, outer_end_corner_).normalized();
}

void MultiLine_Rubber_Band::get_mapped_mid_rect_post(QRect& result)
{
 QRectF mid_rect; get_mid_rect_post(mid_rect);
 result = QRect(mapFromParent(mid_rect.topLeft().toPoint()),
   mapFromParent(mid_rect.bottomRight().toPoint()));
}

void MultiLine_Rubber_Band::get_mid_rect(QRectF& result)
{
 result = QRectF(inner_starting_corner_, outer_end_corner_).normalized();
}

void MultiLine_Rubber_Band::get_mapped_mid_rect(QRect& result)
{
 QRectF mid_rect; get_mid_rect(mid_rect);
 result = QRect(mapFromParent(mid_rect.topLeft().toPoint()),
   mapFromParent(mid_rect.bottomRight().toPoint()));
}



void MultiLine_Rubber_Band::finish_double_band(const QPointF& pos)
{
 inner_end_corner_ = pos;

 current_corner_pair_direction_ ^= Corner_Pair_Directions::Second_Phase;

 QRectF mid_rect = QRectF(outer_starting_corner_, outer_end_corner_).normalized();

 switch(current_corner_pair_direction_)
 {
 case Corner_Pair_Directions::Down_Right:
  outer_starting_corner_ = mid_rect.topLeft();
  outer_end_corner_ = mid_rect.bottomRight();
  break;

 case Corner_Pair_Directions::Down_Left:
  outer_starting_corner_ = mid_rect.topRight();
  outer_end_corner_ = mid_rect.bottomLeft();
  break;

 case Corner_Pair_Directions::Up_Right:
  outer_starting_corner_ = mid_rect.bottomLeft();
  outer_end_corner_ = mid_rect.topRight();
  break;

 case Corner_Pair_Directions::Up_Left:
  outer_starting_corner_ = mid_rect.bottomRight();
  outer_end_corner_ = mid_rect.topLeft();
  break;

 default: break;
 }

 current_corner_pair_direction_ |= Corner_Pair_Directions::Third_Phase;
}

void MultiLine_Rubber_Band::complete_band(const QPointF& pos)
{
 if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
 {
  QRectF mid = QRectF(outer_starting_corner_, outer_end_corner_).normalized();
  switch ((Corner_Pair_Directions) (current_corner_pair_direction_ ^ Corner_Pair_Directions::Third_Phase))
  {
   default:
   case Corner_Pair_Directions::Down_Right:
     outer_starting_corner_ = mid.topLeft();
     outer_end_corner_ = mid.bottomRight();
     inner_end_corner_ = pos;
  }
 }
}


void MultiLine_Rubber_Band::adjust_geometry(const QPointF& pos)
{
 if(current_corner_pair_direction_ & Corner_Pair_Directions::Second_Phase)
 {
  outer_end_corner_ = pos;
  return;
 }

 if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
 {
  inner_end_corner_ = pos;
//  Corner_Pair_Directions acpd = (Corner_Pair_Directions) (current_corner_pair_direction_ ^ Corner_Pair_Directions::Post_Double);
//  switch(acpd)
//  {
//   default:
//   case Corner_Pair_Directions::Down:
//   case Corner_Pair_Directions::Down_Right:
//    inner_end_corner_ = pos;
//    break;
//  }
  return;
 }

 if(current_corner_pair_direction_ & Corner_Pair_Directions::First_Phase)
 {
  outer_end_corner_ = pos;
  return;
 }

// Corner_Pair_Directions cpd = get_corner_pair_direction(inner_starting_corner_, pos);

// if(cpd == Corner_Pair_Directions::N_A)
//  return;

// if(current_corner_pair_direction_ == Corner_Pair_Directions::N_A)
// {
//  init_active_corner_pair_direction(cpd, pos);
// }

// else
// {
//  switch(current_corner_pair_direction_)
//  {
//   default:
//   case Corner_Pair_Directions::Down:
//   case Corner_Pair_Directions::Down_Right:
//    outer_end_corner_ = pos;
//    break;
//  }
// }
}


void MultiLine_Rubber_Band::reset_geometry(const QPointF& sc)
{
 current_corner_pair_direction_ = Corner_Pair_Directions::First_Phase;

 inner_starting_corner_ = sc;
 outer_end_corner_ = sc;

 outer_starting_corner_ = {};

 inner_end_corner_ = {};
}

void MultiLine_Rubber_Band::init_double_band(const QPointF& pos)
{
 Corner_Pair_Directions cpd = get_corner_pair_direction(inner_starting_corner_, pos);

 if(cpd == Corner_Pair_Directions::N_A)
   return;

 current_corner_pair_direction_ = cpd | Corner_Pair_Directions::Second_Phase; //Corner_Pair_Directions::Down_Right;

 outer_starting_corner_ = pos;
 outer_end_corner_ = pos;


//  if(current_corner_pair_direction_ == Corner_Pair_Directions::N_A)
//  {
//   init_active_corner_pair_direction(cpd, pos);
//  }
// current_corner_pair_direction_ |= Corner_Pair_Directions::Double;
}


QPoint MultiLine_Rubber_Band::_map_start_outside_corner(QRect& rect)
{
 Corner_Pair_Directions acpd = (Corner_Pair_Directions) (current_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);

 switch (acpd)
 {
 case Corner_Pair_Directions::Down_Right: return rect.topLeft();
 case Corner_Pair_Directions::Up_Left: return rect.bottomRight();

 case Corner_Pair_Directions::Down_Left: return rect.topRight();
 case Corner_Pair_Directions::Up_Right: return rect.bottomLeft();

 default: return {};
 }
}

QPoint MultiLine_Rubber_Band::_map_start_cross_corner(QRect& rect)
{
 Corner_Pair_Directions acpd = (Corner_Pair_Directions) (current_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);

 switch (acpd)
 {
 case Corner_Pair_Directions::Down_Right: return rect.bottomLeft();
 case Corner_Pair_Directions::Up_Left: return rect.topRight();

 case Corner_Pair_Directions::Down_Left: return rect.bottomRight();
 case Corner_Pair_Directions::Up_Right: return rect.topLeft();

 default: return {};
 }
}

QPoint MultiLine_Rubber_Band::_map_start_double_corner(QRect& rect)
{
 Corner_Pair_Directions acpd = (Corner_Pair_Directions) (current_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);

 switch (acpd)
 {
 case Corner_Pair_Directions::Down_Right: return rect.topRight();
 case Corner_Pair_Directions::Up_Left: return rect.bottomLeft();

 case Corner_Pair_Directions::Down_Left: return rect.topLeft();
 case Corner_Pair_Directions::Up_Right: return rect.bottomRight();

 default: return {};
 }
}

QPoint MultiLine_Rubber_Band::_map_end_double_corner(QRect& rect)
{
 Corner_Pair_Directions acpd = (Corner_Pair_Directions) (current_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);

 switch (acpd)
 {
 case Corner_Pair_Directions::Down_Right: return rect.bottomRight();
 case Corner_Pair_Directions::Up_Left: return rect.topLeft();

 case Corner_Pair_Directions::Down_Left: return rect.bottomLeft();
 case Corner_Pair_Directions::Up_Right: return rect.topRight();

 default: return {};
 }
}

void MultiLine_Rubber_Band::set_gradient_center(QConicalGradient& gradient)
{
 if(current_corner_pair_direction_ & Corner_Pair_Directions::Second_or_Third_Phase)
   get_mapped_mid_rect_post(mid_rect_);
 else
   get_mapped_mid_rect(mid_rect_);

 gradient.setCenter(mid_rect_.center());
}



void MultiLine_Rubber_Band::process_paint_event(QPaintEvent* event, QPainter& painter)
{
 //QRect mid_rect; //get_mapped_mid_rect_post(mid_rect);
 if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
 {
  QRect top_rect = QRect(mapFromParent(inner_starting_corner_.toPoint()),
    _map_start_double_corner(mid_rect_)//  mid_rect_.topRight()
                 ).normalized();

  QRect top_gap_rect = QRect(_map_start_outside_corner(mid_rect_), //  mid_rect_.topLeft(),
    mapFromParent(inner_starting_corner_.toPoint())).normalized();
  QRect bottom_gap_rect = QRect(mapFromParent(inner_end_corner_.toPoint()),
    _map_end_double_corner(mid_rect_)   //mid_rect_.bottomRight()
                                ).normalized();
  QRect bottom_rect = QRect(_map_start_cross_corner(mid_rect_), //    mid_rect_.bottomLeft(),
                    mapFromParent(inner_end_corner_.toPoint())).normalized();

//?
//  gradient.setCenter((gradient.center() + QPointF(bottom_rect.width(), bottom_rect.height())));
//  QPen qp = painter.pen();
//  qp.setBrush(gradient);
//  painter.setPen(qp);

  QPolygon poly({
    _map_start_outside_corner(mid_rect_),
    _map_end_double_corner(top_gap_rect),
    _map_start_outside_corner(top_rect),
    _map_start_double_corner(top_rect),
    _map_end_double_corner(mid_rect_),
    _map_start_outside_corner(bottom_gap_rect),
    _map_end_double_corner(bottom_rect),
    _map_start_cross_corner(bottom_rect)
  });

  painter.drawPolygon(poly);
  return;
 }
 else if(current_corner_pair_direction_ & Corner_Pair_Directions::Second_Phase)
 {
  QRect start_rect = QRect(mapFromParent(inner_starting_corner_.toPoint()),
    _map_start_double_corner(mid_rect_)).normalized();
  QPolygon poly({
       _map_start_outside_corner(mid_rect_),
       _map_start_cross_corner(start_rect),
       _map_start_outside_corner(start_rect),
       _map_start_double_corner(start_rect),
       _map_end_double_corner(mid_rect_),
       _map_start_cross_corner(mid_rect_),
    });

  painter.drawPolygon(poly);
 }
 else
   painter.drawRect(mid_rect_);
}
