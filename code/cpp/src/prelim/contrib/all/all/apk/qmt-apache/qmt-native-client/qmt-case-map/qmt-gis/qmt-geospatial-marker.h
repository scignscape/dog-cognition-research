
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

public:

 ACCESSORS(u2 ,outline_code)
 ACCESSORS(u2 ,held_outline_code)
 ACCESSORS(QPolygonF ,outline)
 ACCESSORS(r8 ,scale)

 QMT_Geospatial_Marker(QPolygonF outline);

};


#endif // QMT_GEOSPATIAL_MARKER__H
