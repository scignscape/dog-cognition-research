
#include "pdf-annotation-base.h"

#include <QPainter>

#include <QDebug>

#include <QWheelEvent>

#include "global-types.h"

PDF_Annotation_Base::PDF_Annotation_Base(QWidget* p) :
    QWidget(p),
    current_corner_pair_direction_(Corner_Pair_Directions::First_Phase)
{
 if(p)
   setGeometry(p->geometry());
}


void PDF_Annotation_Base::show()
{
 QWidget::show();
}


PDF_Annotation_Base::Corner_Pair_Directions PDF_Annotation_Base::get_corner_pair_direction(const QPointF& landmark,
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

void PDF_Annotation_Base::wheelEvent(QWheelEvent *event)
{

}

void PDF_Annotation_Base::init_second_phase(const QPointF& pos)
{

}

void PDF_Annotation_Base::finish_second_phase(const QPointF& pos)
{

}

void PDF_Annotation_Base::finish_third_phase(const QPointF& pos)
{

}

void PDF_Annotation_Base::map_from_parent(const QRectF& source,
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

void PDF_Annotation_Base::paintEvent(QPaintEvent *event)
{

 QPainter painter(this);

 u1 _tmpRed_ = 55; u1 _tmpGreen_ = 55; u1 _tmpBlue_ = 55;
 u1 _tmpAlpha_ = 100;

 QPen myPen(QColor(_tmpRed_, _tmpGreen_,_tmpBlue_), 3, Qt::SolidLine);
 u1 gradient_base = 140;
 QConicalGradient gradient;
 gradient.setSpread(QGradient::ReflectSpread);
 //?

 //gradient.setCenter(shaft_.center()); // ((mid_rect.topLeft() + mid_rect.center())/2) );

 set_gradient_center(gradient);

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

 process_paint_event(event, painter);
}
