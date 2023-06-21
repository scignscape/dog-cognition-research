#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "MapGraphics_global.h"
#include "MapGraphicsObject.h"

#include "global-types.h"

class MapGraphicsView;

class MAPGRAPHICSSHARED_EXPORT CircleObject : public MapGraphicsObject
{
 Q_OBJECT


public:

 Supplement sup;

 explicit CircleObject(MapGraphicsView* containing_view, qreal radius,
   bool sizeIsZoomInvariant=true, QColor fillColor = QColor(0,0,0,0),MapGraphicsObject *parent = 0);
 virtual ~CircleObject();

 //pure-virtual from MapGraphicsObject
 QRectF boundingRect() const;

 //pure-virtual from MapGraphicsObject
 void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

 qreal radius() const;
 void setRadius(qreal radius);

 QColor fillColor()
 {
  return _fillColor;
 }


 void swap_outline_code()
 {
  if(sup.outline_code_ == 0)
    sup.outline_code_ = sup.held_outline_code_;
  else
  {
   sup.held_outline_code_ = sup.outline_code_;
   sup.outline_code_ = 0;
  }

 }



Q_SIGNALS:


protected:
   //virtual from MapGraphicsObject
 virtual void keyReleaseEvent(QKeyEvent *event);

private:
 qreal _radius;
 QColor _fillColor;

};

#endif // CIRCLEOBJECT_H
