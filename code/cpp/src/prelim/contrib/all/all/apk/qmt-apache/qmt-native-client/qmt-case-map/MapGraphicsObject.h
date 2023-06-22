#ifndef MAPGRAPHICSOBJECT_H
#define MAPGRAPHICSOBJECT_H

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

class QMT_Client_Data_Set_Base;


struct Supplement {

 r8 scale_;
 void* ref_;
 u2 outline_code_;
 u2 held_outline_code_;

 QMT_Client_Data_Set_Base* client_data_set_base_;


 ACCESSORS(u2 ,outline_code)
 ACCESSORS(u2 ,held_outline_code)
 ACCESSORS(void* ,ref)
 ACCESSORS(r8 ,scale)
 ACCESSORS(QMT_Client_Data_Set_Base* ,client_data_set_base)

 Supplement() : client_data_set_base_(nullptr),
   ref_(nullptr), held_outline_code_(0),
   outline_code_(0), scale_(1)
 {}

 void check_ref()
 {
  qDebug() << "ref = " << *(QPolygonF*) ref_;
 }

};

class MAPGRAPHICSSHARED_EXPORT MapGraphicsObject : public QObject
{
 Q_OBJECT

 u4 move_increment_value_;

protected:
 MapGraphicsView* containing_view_;
 void* style_params_;
 QVariant client_data_;

 u4 index_code_;


public:
 enum MapGraphicsObjectFlag
 {
  ObjectIsMovable = 0x01,
  ObjectIsSelectable = 0x02,
  ObjectIsFocusable = 0x04
 };
 Q_DECLARE_FLAGS(MapGraphicsObjectFlags,MapGraphicsObjectFlag)

 //PrivateQGraphicsObject will call some of our protected event handlers that nobody else needs to touch
 friend class PrivateQGraphicsObject;
public:
 explicit MapGraphicsObject(MapGraphicsView* containing_view,
   bool sizeIsZoomInvariant=false,MapGraphicsObject *parent = 0);
 virtual ~MapGraphicsObject();

 ACCESSORS(void* ,style_params)
 ACCESSORS(QVariant ,client_data)
 ACCESSORS(u4 ,index_code)




 bool sizeIsZoomInvariant() const;

 /*!
     \brief You need to implement this. If sizeIsZoomInvariant() is true, this should return the size of the
     rectangle you want in PIXELS. If false, this should return the size of the rectangle in METERS. The
     rectangle should be centered at (0,0) regardless.

     \return QRectF
    */
 virtual QRectF boundingRect() const=0;

 /*!
     \brief You can reimplement this if you want. Given a point in geographic coordinates (lat/lon),
     return true if the object contains that point. Return false otherwise. The default implementation just uses
     boundingRect() to decide.

     \param geoPos
     \return bool
    */
 virtual bool contains(const QPointF& geoPos) const;

 virtual bool pixel_contains(const QPointF &geoPos) const
 {
  return contains(geoPos);
 }

 /**
     * @brief Paints the contents of the Object in ENU coordinates if the object is not zoom invariant.
     * If it is zoom invariant, the units are pixels. That is, this painter should operate in the same
     * units as returned by boundingRect().
     * You must implement this.
     *
     * @param painter
     * @param option
     * @param widget
     */
 virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget=0)=0;

 void move_increment()
 {
  ++move_increment_value_;
 }

 void reset_move_increment()
 {
  move_increment_value_ = 0;
 }


 QPointF map_to_scene(const QPointF &pos);
 QPointF map_pos_to_scene();

 QPoint map_to_view(const QPointF &pos);
 QPoint map_pos_to_view();

 bool enabled() const;
 void setEnabled(bool);

 qreal opacity() const;
 void setOpacity(qreal);

 MapGraphicsObject * parent() const;
 void setParent(MapGraphicsObject *);

 const QPointF& pos() const;
 virtual void setPos(const QPointF&);

 qreal rotation() const;
 void setRotation(qreal);

 bool visible() const;
 void setVisible(bool);

 qreal longitude() const;
 void setLongitude(qreal);

 qreal latitude() const;
 void setLatitude(qreal);

 qreal zValue() const;
 void setZValue(qreal);

 bool isSelected() const;
 void setSelected(bool);

 QString toolTip() const;
 void setToolTip(const QString& toolTip);

 void setFlag(MapGraphicsObjectFlag, bool enabled=true);

 void clearFlag(MapGraphicsObjectFlag flag)
 {
  setFlag(flag, false);
 }

 void setFlags(MapGraphicsObject::MapGraphicsObjectFlags);
 MapGraphicsObject::MapGraphicsObjectFlags flags() const;

protected:
 virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent * event);
 virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value);
 virtual void keyPressEvent(QKeyEvent * event);
 virtual void keyReleaseEvent(QKeyEvent * event);
 virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
 virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
 virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
 virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
 virtual void wheelEvent(QGraphicsSceneWheelEvent * event);


Q_SIGNALS:
 void enabledChanged();
 void opacityChanged();
 void parentChanged();
 void posChanged();
 void rotationChanged();
 void visibleChanged();
 void zValueChanged();
 void toolTipChanged(const QString& toolTip);

 void move_registered(const QPointF& pos);

 void flagsChanged();

 //Please do not use this for now. It should only be used internally for now. Ugly, I know.
 void selectedChanged();

 void newObjectGenerated(MapGraphicsObject *);

 /*!
     \brief Emitted when we'd like to be redrawn
    */
 void redrawRequested();

 /*!
     \brief Emitted when this MapGraphicsObject wants keyboard focus. (to receive keyboard events)
    */
 void keyFocusRequested();


public Q_SLOTS:

private Q_SLOTS:
 void setConstructed();

private:
 bool _sizeIsZoomInvariant;

 bool _enabled;
 qreal _opacity;
 MapGraphicsObject * _parent;
 QPointF _pos;
 qreal _rotation;
 bool _visible;
 qreal _zValue;
 bool _selected;

 QString _toolTip;

 MapGraphicsObject::MapGraphicsObjectFlags _flags;

 bool _constructed;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(MapGraphicsObject::MapGraphicsObjectFlags)

#endif // MAPGRAPHICSOBJECT_H
