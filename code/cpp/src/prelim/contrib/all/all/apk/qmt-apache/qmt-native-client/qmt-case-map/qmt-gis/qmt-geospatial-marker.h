
#ifndef QMT_GEOSPATIAL_MARKER__H
#define QMT_GEOSPATIAL_MARKER__H

#include <QObject>
#include <QPointF>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsItem>
#include <QString>

#include <QVariant>

#include "MapGraphics_global.h"

#include "global-types.h"

#include "accessors.h"

#include <QDebug>

class MapGraphicsView;

class QMT_Geospatial_Marker
{

 r8 scale_;
 QPolygonF outline_;
 u2 outline_code_;
 u2 held_outline_code_;

 QColor passive_color_;
 QColor highlight_color_;
 QColor current_color_;

public:

 ACCESSORS(u2 ,outline_code)
 ACCESSORS(u2 ,held_outline_code)
 ACCESSORS(QPolygonF ,outline)
 ACCESSORS(r8 ,scale)

 ACCESSORS(QColor ,passive_color)
 ACCESSORS(QColor ,highlight_color)
 ACCESSORS(QColor ,current_color)

 QMT_Geospatial_Marker(QPolygonF outline, QColor passive_color, QColor active_color);

 QMT_Geospatial_Marker(QPolygonF outline, QColor passive_color)
   :  QMT_Geospatial_Marker(outline, passive_color, passive_color)
 {

 }

 void adopt_highlight_color()
 {
  current_color_ = highlight_color_;
 }

 void adopt_passive_color()
 {
  current_color_ = passive_color_;
 }

};


#endif // QMT_GEOSPATIAL_MARKER__H
