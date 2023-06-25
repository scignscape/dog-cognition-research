
#ifndef QMT_CASE_GROUP__H
#define QMT_CASE_GROUP__H

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

#include "Position.h"

#include "global-types.h"

#include "accessors.h"

#include <QDebug>

#include <QGeoLocation>
#include <QGeoCoordinate>

class QMT_Single_Case;
class PolygonObject;
class MapGraphicsObject;

class QMT_Case_Group
{
 QVector<QMT_Single_Case*> cases_;
 QGeoLocation geo_location_;
 MapGraphicsObject* geomarker_;

public:

 ACCESSORS__CONST_RGET(QVector<QMT_Single_Case*> ,cases)
 ACCESSORS__CONST_RGET(QGeoLocation ,geo_location)

 ACCESSORS(MapGraphicsObject* ,geomarker)

 QMT_Case_Group(QGeoLocation geo_location);

 Position position()
 {
  return {geo_location_.coordinate().longitude(), geo_location_.coordinate().latitude()};
 }

 u2 number_of_cases()
 {
  return cases_.size();
 }

};


#endif // QMT_GEOSPATIAL_MARKER__H
