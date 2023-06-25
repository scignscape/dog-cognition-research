
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

class MapGraphicsView;

class QMT_Single_Case
{
 Position coarse_position_;
 Position fine_position_;

public:

 QMT_Single_Case(Position coarse_position, Position fine_position = {0, 0});


};


#endif // QMT_SINGLE_CASE__H
