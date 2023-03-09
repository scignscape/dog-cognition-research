
#include "pdf-rubber-band.h"

#include <QPainter>

#include <QDebug>

#include "global-types.h"

PDF_Rubber_Band::PDF_Rubber_Band(QRubberBand::Shape s,
    const QPointF& sc, QWidget *p) :
    QRubberBand(s,p),
      active_corner_pair_direction_(Corner_Pair_Directions::Pre_Double),
      inner_starting_corner_(sc), outer_end_corner_(sc)
{
 if(p)
   setGeometry(p->geometry());
}


s1 _spaceship(r8 lhs, r8 rhs)
{
 if(lhs < rhs)
   return 1;
 if(rhs < lhs)
   return -1;
 return 0;
}

PDF_Rubber_Band::Corner_Pair_Directions PDF_Rubber_Band::get_corner_pair_direction(const QPointF& landmark,
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


void PDF_Rubber_Band::reset_active_corner_pair_direction(Corner_Pair_Directions cpd, const QPointF& pos)
{

}

void PDF_Rubber_Band::init_active_corner_pair_direction(Corner_Pair_Directions cpd, const QPointF& pos)
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
   active_corner_pair_direction_ = cpd; //Corner_Pair_Directions::Down_Right;
   outer_end_corner_ = pos;
  }
  break;



  // //  todo: other direections
 }
}

void PDF_Rubber_Band::get_mid_rect_post(QRectF& result)
{
 result = QRectF(outer_starting_corner_, outer_end_corner_).normalized();
}

void PDF_Rubber_Band::get_mapped_mid_rect_post(QRect& result)
{
 QRectF mid_rect; get_mid_rect_post(mid_rect);
 result = QRect(mapFromParent(mid_rect.topLeft().toPoint()),
   mapFromParent(mid_rect.bottomRight().toPoint()));
}

void PDF_Rubber_Band::get_mid_rect(QRectF& result)
{
 result = QRectF(inner_starting_corner_, outer_end_corner_).normalized();
}

void PDF_Rubber_Band::get_mapped_mid_rect(QRect& result)
{
 QRectF mid_rect; get_mid_rect(mid_rect);
 result = QRect(mapFromParent(mid_rect.topLeft().toPoint()),
   mapFromParent(mid_rect.bottomRight().toPoint()));
}



void PDF_Rubber_Band::finish_double_band(const QPointF& pos)
{
 inner_end_corner_ = pos;

 active_corner_pair_direction_ ^= Corner_Pair_Directions::Double;

 QRectF mid_rect = QRectF(outer_starting_corner_, outer_end_corner_).normalized();

 switch(active_corner_pair_direction_)
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

 active_corner_pair_direction_ |= Corner_Pair_Directions::Post_Double;
}

void PDF_Rubber_Band::complete_band(const QPointF& pos)
{
 if(active_corner_pair_direction_ & Corner_Pair_Directions::Post_Double)
 {
  QRectF mid = QRectF(outer_starting_corner_, outer_end_corner_).normalized();
  switch ((Corner_Pair_Directions) (active_corner_pair_direction_ ^ Corner_Pair_Directions::Post_Double))
  {
   default:
   case Corner_Pair_Directions::Down_Right:
     outer_starting_corner_ = mid.topLeft();
     outer_end_corner_ = mid.bottomRight();
     inner_end_corner_ = pos;
  }
 }
}


void PDF_Rubber_Band::adjust_geometry(const QPointF& pos)
{
 if(active_corner_pair_direction_ & Corner_Pair_Directions::Double)
 {
  outer_end_corner_ = pos;
  return;
 }

 if(active_corner_pair_direction_ & Corner_Pair_Directions::Post_Double)
 {
  inner_end_corner_ = pos;
//  Corner_Pair_Directions acpd = (Corner_Pair_Directions) (active_corner_pair_direction_ ^ Corner_Pair_Directions::Post_Double);
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

 if(active_corner_pair_direction_ & Corner_Pair_Directions::Pre_Double)
 {
  outer_end_corner_ = pos;
  return;
 }

// Corner_Pair_Directions cpd = get_corner_pair_direction(inner_starting_corner_, pos);

// if(cpd == Corner_Pair_Directions::N_A)
//  return;

// if(active_corner_pair_direction_ == Corner_Pair_Directions::N_A)
// {
//  init_active_corner_pair_direction(cpd, pos);
// }

// else
// {
//  switch(active_corner_pair_direction_)
//  {
//   default:
//   case Corner_Pair_Directions::Down:
//   case Corner_Pair_Directions::Down_Right:
//    outer_end_corner_ = pos;
//    break;
//  }
// }
}


void PDF_Rubber_Band::reset_geometry(const QPointF& sc)
{
 active_corner_pair_direction_ = Corner_Pair_Directions::Pre_Double;

 inner_starting_corner_ = sc;
 outer_end_corner_ = sc;

 outer_starting_corner_ = {};

 inner_end_corner_ = {};
}

void PDF_Rubber_Band::init_double_band(const QPointF& pos)
{
 Corner_Pair_Directions cpd = get_corner_pair_direction(inner_starting_corner_, pos);

 if(cpd == Corner_Pair_Directions::N_A)
   return;

 active_corner_pair_direction_ = cpd | Corner_Pair_Directions::Double; //Corner_Pair_Directions::Down_Right;

 outer_starting_corner_ = pos;
 outer_end_corner_ = pos;


//  if(active_corner_pair_direction_ == Corner_Pair_Directions::N_A)
//  {
//   init_active_corner_pair_direction(cpd, pos);
//  }
// active_corner_pair_direction_ |= Corner_Pair_Directions::Double;
}


QPoint PDF_Rubber_Band::_map_start_outside_corner(QRect& rect)
{
 Corner_Pair_Directions acpd = (Corner_Pair_Directions) (active_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);

 switch (acpd)
 {
 case Corner_Pair_Directions::Down_Right: return rect.topLeft();
 case Corner_Pair_Directions::Up_Left: return rect.bottomRight();

 case Corner_Pair_Directions::Down_Left: return rect.topRight();
 case Corner_Pair_Directions::Up_Right: return rect.bottomLeft();

 default: return {};
 }
}

QPoint PDF_Rubber_Band::_map_start_cross_corner(QRect& rect)
{
 Corner_Pair_Directions acpd = (Corner_Pair_Directions) (active_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);

 switch (acpd)
 {
 case Corner_Pair_Directions::Down_Right: return rect.bottomLeft();
 case Corner_Pair_Directions::Up_Left: return rect.topRight();

 case Corner_Pair_Directions::Down_Left: return rect.bottomRight();
 case Corner_Pair_Directions::Up_Right: return rect.topLeft();

 default: return {};
 }
}

QPoint PDF_Rubber_Band::_map_start_double_corner(QRect& rect)
{
 Corner_Pair_Directions acpd = (Corner_Pair_Directions) (active_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);

 switch (acpd)
 {
 case Corner_Pair_Directions::Down_Right: return rect.topRight();
 case Corner_Pair_Directions::Up_Left: return rect.bottomLeft();

 case Corner_Pair_Directions::Down_Left: return rect.topLeft();
 case Corner_Pair_Directions::Up_Right: return rect.bottomRight();

 default: return {};
 }
}

QPoint PDF_Rubber_Band::_map_end_double_corner(QRect& rect)
{
 Corner_Pair_Directions acpd = (Corner_Pair_Directions) (active_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);

 switch (acpd)
 {
 case Corner_Pair_Directions::Down_Right: return rect.bottomRight();
 case Corner_Pair_Directions::Up_Left: return rect.topLeft();

 case Corner_Pair_Directions::Down_Left: return rect.bottomLeft();
 case Corner_Pair_Directions::Up_Right: return rect.topRight();

 default: return {};
 }
}


void PDF_Rubber_Band::paintEvent(QPaintEvent *event)
{
 QRect mid_rect; //get_mapped_mid_rect_post(mid_rect);
 if(active_corner_pair_direction_ &
   (Corner_Pair_Directions::Post_Double | Corner_Pair_Directions::Double))
   get_mapped_mid_rect_post(mid_rect);
 else
   get_mapped_mid_rect(mid_rect);

 QPainter painter(this);

 u1 _tmpRed_ = 55; u1 _tmpGreen_ = 55; u1 _tmpBlue_ = 55;
 u1 _tmpAlpha_ = 100;

 QPen myPen(QColor(_tmpRed_, _tmpGreen_,_tmpBlue_), 3, Qt::SolidLine);
 u1 gradient_base = 140;
 QConicalGradient gradient;
 gradient.setSpread(QGradient::ReflectSpread);
 gradient.setCenter(mid_rect.center()); // ((mid_rect.topLeft() + mid_rect.center())/2) );
 gradient.setAngle(-65);
   gradient.setColorAt(0, QColor(_tmpRed_,gradient_base,gradient_base,_tmpAlpha_));
   gradient.setColorAt(0.05, QColor(_tmpRed_,_tmpGreen_,gradient_base,_tmpAlpha_));
   gradient.setColorAt(0.1, QColor(_tmpRed_,_tmpGreen_,_tmpBlue_,_tmpAlpha_));
   gradient.setColorAt(0.15, QColor(gradient_base, _tmpGreen_, _tmpBlue_,_tmpAlpha_));
   gradient.setColorAt(0.2, QColor(gradient_base, _tmpGreen_, gradient_base,_tmpAlpha_));
   gradient.setColorAt(0.25, QColor(_tmpRed_, _tmpGreen_, gradient_base,_tmpAlpha_));
   gradient.setColorAt(0.3, QColor(_tmpRed_, gradient_base, _tmpBlue_,_tmpAlpha_));
   gradient.setColorAt(0.35, QColor(gradient_base, gradient_base, _tmpBlue_,_tmpAlpha_));
   gradient.setColorAt(0.4, QColor(0,255,0,_tmpAlpha_));
   gradient.setColorAt(0.45, QColor(255,255,0,_tmpAlpha_));
   gradient.setColorAt(0.5, QColor(0,255,255,_tmpAlpha_));
   gradient.setColorAt(0.55, QColor(255,255,0,_tmpAlpha_));
   gradient.setColorAt(0.6, QColor(0,255,0,_tmpAlpha_));
   gradient.setColorAt(0.65, QColor(gradient_base, gradient_base, _tmpBlue_,_tmpAlpha_));
   gradient.setColorAt(0.7, QColor(_tmpRed_, gradient_base, _tmpBlue_,_tmpAlpha_));
   gradient.setColorAt(0.75, QColor(_tmpRed_, _tmpGreen_, gradient_base,_tmpAlpha_));
   gradient.setColorAt(0.8, QColor(gradient_base, _tmpGreen_, gradient_base,_tmpAlpha_));
   gradient.setColorAt(0.85, QColor(gradient_base, _tmpGreen_, _tmpBlue_,_tmpAlpha_));
   gradient.setColorAt(0.9, QColor(_tmpRed_,_tmpGreen_,_tmpBlue_,_tmpAlpha_));
   gradient.setColorAt(0.95, QColor(_tmpRed_,_tmpGreen_,gradient_base,_tmpAlpha_));
   gradient.setColorAt(1, QColor(_tmpRed_,gradient_base,gradient_base,_tmpAlpha_));

   QPen shapePen(gradient, 4);//, Qt::DashDotDotLine); //shapePen
 myPen.setCapStyle(Qt::RoundCap);
 shapePen.setCapStyle(Qt::RoundCap);


 painter.setPen(shapePen);
 painter.setBrush(QBrush(QColor(_tmpRed_, _tmpGreen_, _tmpBlue_, 100)));

 if(active_corner_pair_direction_ & Corner_Pair_Directions::Post_Double)
 {
  QRect top_rect = QRect(mapFromParent(inner_starting_corner_.toPoint()),
    _map_start_double_corner(mid_rect)//  mid_rect.topRight()
                 ).normalized();

  QRect top_gap_rect = QRect(_map_start_outside_corner(mid_rect), //  mid_rect.topLeft(),
    mapFromParent(inner_starting_corner_.toPoint())).normalized();
  QRect bottom_gap_rect = QRect(mapFromParent(inner_end_corner_.toPoint()),
    _map_end_double_corner(mid_rect)   //mid_rect.bottomRight()
                                ).normalized();
  QRect bottom_rect = QRect(_map_start_cross_corner(mid_rect), //    mid_rect.bottomLeft(),
                    mapFromParent(inner_end_corner_.toPoint())).normalized();

  gradient.setCenter((gradient.center() + QPointF(bottom_rect.width(), bottom_rect.height())));
  QPen qp = painter.pen();
  qp.setBrush(gradient);
  painter.setPen(qp);

  QPolygon poly({
    _map_start_outside_corner(mid_rect),
    _map_end_double_corner(top_gap_rect),
    _map_start_outside_corner(top_rect),
    _map_start_double_corner(top_rect),
    _map_end_double_corner(mid_rect),
    _map_start_outside_corner(bottom_gap_rect),
    _map_end_double_corner(bottom_rect),
    _map_start_cross_corner(bottom_rect)
  });

  painter.drawPolygon(poly);
  return;
 }
 else if(active_corner_pair_direction_ & Corner_Pair_Directions::Double)
 {
  QRect start_rect = QRect(mapFromParent(inner_starting_corner_.toPoint()),
    _map_start_double_corner(mid_rect)).normalized();
  QPolygon poly({
       _map_start_outside_corner(mid_rect),
       _map_start_cross_corner(start_rect),
       _map_start_outside_corner(start_rect),
       _map_start_double_corner(start_rect),
       _map_end_double_corner(mid_rect),
       _map_start_cross_corner(mid_rect),
    });

  painter.drawPolygon(poly);
 }
 else
   painter.drawRect(mid_rect);
}
