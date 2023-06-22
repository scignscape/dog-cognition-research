#ifndef POLYGONOBJECT_H
#define POLYGONOBJECT_H

#include <QPolygonF>
#include <QList>

#include "tsl/ordered_map.h"

#include "MapGraphicsObject.h"
#include "MapGraphics_global.h"
class CircleObject;
class Position;

class QMT_Geospatial_Marker;

class MAPGRAPHICSSHARED_EXPORT PolygonObject : public MapGraphicsObject
{
 Q_OBJECT

 QMT_Geospatial_Marker* ref_marker_;
 QPolygonF current_enu_polygon_;
 //QPolygonF ref_enu_polygon_;
 QPointF ref_enu_hot_spot_;
 Position* ref_geo_hot_spot_;

 mutable QPointF held_enu_hot_spot_;

public:

    PolygonObject(MapGraphicsView* containing_view, QPolygonF geoPoly, QColor fillColor = QColor(200,200,200,200), QObject *parent = 0);
    virtual ~PolygonObject();

    ACCESSORS(QMT_Geospatial_Marker* ,ref_marker)

    void init_ref_marker(const QPolygonF& qpf);

    //pure-virtual from MapGraphicsObject
    QRectF boundingRect() const;

    //virtual from MapGraphicsObject
    bool contains(const QPointF &geoPos) const;

    bool pixel_contains(const QPointF &geoPos) const;

    //pure-virtual from MapGraphicsObject
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //virtual from MapGraphicsObject
    virtual void setPos(const QPointF &);

    QPolygonF geoPoly() const;

    virtual void setGeoPoly(const QPolygonF& newPoly);

    void setFillColor(const QColor& color);
    
Q_SIGNALS:
    void polygonChanged(const QPolygonF& poly);
    
public Q_SLOTS:

protected:
    //virtual from MapGraphicsObject
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    void draw_scene_polygon_at_ll(const QPolygonF& poly, QPointF latlon, QColor color,
      tsl::ordered_map<const QString*, QVector<QPair<QBrush, QPen>>>& styles,
      r8 scale = 1);

private Q_SLOTS:
    void handleEditCirclePosChanged();
    void handleAddVertexCircleSelected();
    void handleEditCircleDestroyed();

private:
    void fixAddVertexCirclePos();

    CircleObject * constructEditCircle();
    void destroyEditCircle(MapGraphicsObject * obj);

    CircleObject * constructAddVertexCircle();
    void destroyAddVertexCircle(MapGraphicsObject * obj);

    QPolygonF _geoPoly;
    QColor _fillColor;

    QList<MapGraphicsObject *> _editCircles;
    QList<MapGraphicsObject *> _addVertexCircles;
    
};

#endif // POLYGONOBJECT_H
