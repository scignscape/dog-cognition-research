#include "CircleObject.h"

#include "PolygonObject.h"

#include "guts/Conversions.h"

#include <QtDebug>
#include <QKeyEvent>

CircleObject::CircleObject(MapGraphicsView* containing_view, qreal radius,bool sizeIsZoomInvariant, QColor fillColor, MapGraphicsObject *parent) :
  MapGraphicsObject(containing_view, sizeIsZoomInvariant,parent), client_data_set_base_(nullptr),
  _fillColor(fillColor), ref_(nullptr), held_outline_code_(0), outline_code_(0)
{
 _radius = qMax<qreal>(radius,0.01);

 this->setFlag(MapGraphicsObject::ObjectIsSelectable);
 this->setFlag(MapGraphicsObject::ObjectIsMovable);
 this->setFlag(MapGraphicsObject::ObjectIsFocusable);
}

CircleObject::~CircleObject()
{
}

QRectF CircleObject::boundingRect() const
{
 return QRectF(-1*_radius,
               -1*_radius,
               2*_radius,
               2*_radius);
}

void CircleObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
 Q_UNUSED(option)
 Q_UNUSED(widget)

 if(ref_)
 {
  QPolygonF* pf = (QPolygonF*) ref_;
  painter->setRenderHint(QPainter::Antialiasing,true);
  painter->setBrush(_fillColor);


  //  painter->drawEllipse(QPointF(0,0),
  //                       200,
  //                       200);

  painter->drawPolygon(*pf);

  if(outline_code_ & 64)
  {
   QPen pen(QBrush(QColor(Qt::darkMagenta)), 15, Qt::DotLine);
   painter->setBrush(Qt::NoBrush);
   painter->setPen(pen);
   painter->drawPolygon(*pf);
  }

  if(outline_code_ & 30) // 2, 4, 8, 16
  {
   int outline_count = 0;
   if(outline_code_ & 2)
    ++outline_count;
   if(outline_code_ & 4)
    ++outline_count;
   if(outline_code_ & 8)
    ++outline_count;
   if(outline_code_ & 16)
    ++outline_count;

   int overall_width = 12 + outline_count * 3;

   int one_ring_width = overall_width / outline_count;
   int ring_width = overall_width;

   {
    QPen pen(QBrush(QColor(Qt::white)), ring_width + 4);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(pen);
    painter->drawPolygon(*pf);
   }

   if(outline_code_ & 2)
   {
    QPen pen(QBrush(QColor(Qt::darkGreen)), ring_width);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(pen);
    painter->drawPolygon(*pf);
    ring_width -= one_ring_width;
   }

   if(outline_code_ & 4)
   {
    QPen pen(QBrush(QColor(Qt::darkRed)), ring_width);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(pen);
    painter->drawPolygon(*pf);
    ring_width -= one_ring_width;
   }

   if(outline_code_ & 8)
   {
    QPen pen(QBrush(QColor(Qt::darkMagenta)), ring_width);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(pen);
    painter->drawPolygon(*pf);
    ring_width -= one_ring_width;
   }

   if(outline_code_ & 16)
   {
    QPen pen(QBrush(QColor(Qt::cyan)), ring_width);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(pen);
    painter->drawPolygon(*pf);
    ring_width -= one_ring_width;
   }

   {
    QPen pen(QBrush(QColor(Qt::white)), 2);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(pen);
    painter->drawPolygon(*pf);
   }


  }
  if(outline_code_ & 1)
  {
   painter->setBrush(QColor(Qt::red));
   painter->setPen(QPen(Qt::white, 3));
   painter->drawEllipse(pf->boundingRect().center(), 24, 24);
  }

  //    (painter, option, widget);
  return;

 }

 //?qDebug() << "latLon = " << latLon << "; enu = " << enu;

 painter->setRenderHint(QPainter::Antialiasing,true);
 painter->setBrush(_fillColor);
 painter->drawEllipse(QPointF(0,0),
                      _radius,
                      _radius);
}

qreal CircleObject::radius() const
{
 return _radius;
}

void CircleObject::setRadius(qreal radius)
{
 _radius = radius;
 this->redrawRequested();
}

//protected
//virtual from MapGraphicsObject
void CircleObject::keyReleaseEvent(QKeyEvent *event)
{
 if (event->matches(QKeySequence::Delete))
 {
  this->deleteLater();
  event->accept();
 }
 else
  event->ignore();
}



//PolygonObject* po = (PolygonObject*) ref_;

//QPolygonF geo = po->geoPoly();

//QPointF cent {this->longitude(), this->latitude()};

////  geo = geo.translated(cent);

//// this->
////  Conversions::lla2enu(this->latitude(), this->longitude(), 0)



////  QPointF p11 { (geo.at(0) - cent).transposed() };
////  QPointF p12 { (geo.at(1) - cent).transposed() };
////  QPointF p13 { (geo.at(2) - cent).transposed() };


//QPointF p11 { (geo.at(0) - cent) };
//QPointF p12 { (geo.at(1) - cent) };
//QPointF p13 { (geo.at(2) - cent) };

////  p11 *= 10;
////  p12 *= 10;
////  p13 *= 10;

//p11 *= 100000;
//p12 *= 100000;
//p13 *= 100000;

////  Position p11ENU = Conversions::enu2lla(p11.x(), p11.y(), 0,
////    this->longitude(), this->latitude(),  0).lonLat();

////  Position p12ENU = Conversions::enu2lla(p12.x(), p12.y(), 0,
////    this->longitude(), this->latitude(), 0).lonLat();

////  Position p13ENU = Conversions::enu2lla(p13.x(), p13.y(), 0,
////    this->longitude(), this->latitude(), 0).lonLat();

//qDebug() << "=p11 = " << p11;
//qDebug() << "=p12 = " << p12;
//qDebug() << "=p13 = " << p13;

////  qDebug() << "=p11ENU = " << p11ENU;
////  qDebug() << "=p12ENU = " << p12ENU;
////  qDebug() << "=p13ENU = " << p13ENU;

//qDebug() << "=cent = " << cent;

//QPointF p1 {400, 400};
//QPointF p2 {400, -400};
//QPointF p3 {-400, -400};
//QPointF p4 {-400, 400};

