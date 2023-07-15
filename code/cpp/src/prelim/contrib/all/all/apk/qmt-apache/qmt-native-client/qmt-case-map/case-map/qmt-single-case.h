
#ifndef QMT_SINGLE_CASE__H
#define QMT_SINGLE_CASE__H

#include <QObject>
#include <QPointF>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsItem>
#include <QString>

#include <QVariant>

#include "Position.h"

#include "global-types.h"

#include "accessors.h"

#include <QDebug>

#include <QMap>

class MapGraphicsView;

class QMT_Single_Case
{
 Position coarse_position_;
 Position fine_position_;

 QMap<QString, QString> test_;

public:

 QMT_Single_Case(Position coarse_position, Position fine_position = {0, 0});

 ACCESSORS(QMap<QString, QString> ,test)

};


#endif // QMT_SINGLE_CASE__H
