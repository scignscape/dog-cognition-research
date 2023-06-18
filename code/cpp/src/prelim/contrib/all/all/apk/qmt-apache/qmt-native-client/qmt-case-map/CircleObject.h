#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "MapGraphics_global.h"
#include "MapGraphicsObject.h"

#include "global-types.h"

class MapGraphicsView;
class QMT_Client_Data_Set_Base;

class MAPGRAPHICSSHARED_EXPORT CircleObject : public MapGraphicsObject
{
 Q_OBJECT

 void* ref_;
 u2 outline_code_;
 u2 held_outline_code_;

 QMT_Client_Data_Set_Base* client_data_set_base_;


public:
 explicit CircleObject(MapGraphicsView* containing_view, qreal radius,
   bool sizeIsZoomInvariant=true, QColor fillColor = QColor(0,0,0,0),MapGraphicsObject *parent = 0);
 virtual ~CircleObject();

 //pure-virtual from MapGraphicsObject
 QRectF boundingRect() const;

 //pure-virtual from MapGraphicsObject
 void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

 qreal radius() const;
 void setRadius(qreal radius);

 QColor fillColor()
 {
  return _fillColor;
 }


 ACCESSORS(u2 ,outline_code)
 ACCESSORS(u2 ,held_outline_code)
 ACCESSORS(void* ,ref)
 ACCESSORS(QMT_Client_Data_Set_Base* ,client_data_set_base)


 void swap_outline_code()
 {
  if(outline_code_ == 0)
    outline_code_ = held_outline_code_;
  else
  {
   held_outline_code_ = outline_code_;
   outline_code_ = 0;
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
