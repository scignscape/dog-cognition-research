#include "PolygonObject.h"

#include "guts/Conversions.h"
#include "CircleObject.h"

#include <QtDebug>
#include <QKeyEvent>

#include "MapTileSource.h"
#include "MapGraphicsView.h"

#include "qmt-gis/qmt-geospatial-marker.h"


PolygonObject::PolygonObject(MapGraphicsView* containing_view, QPolygonF geoPoly, QColor fillColor, QObject *parent) :
    MapGraphicsObject(containing_view, parent), _geoPoly(geoPoly), _fillColor(fillColor),
    ref_marker_(nullptr)
{
    this->setFlag(MapGraphicsObject::ObjectIsMovable);
    this->setFlag(MapGraphicsObject::ObjectIsSelectable,false);
    this->setFlag(MapGraphicsObject::ObjectIsFocusable);
    this->setGeoPoly(geoPoly);
}

PolygonObject::~PolygonObject()
{
    qDebug() << this << "destroying";
    foreach(MapGraphicsObject * circle, _editCircles)
        this->destroyEditCircle(circle);
    _editCircles.clear();

    foreach(MapGraphicsObject * circle, _addVertexCircles)
        this->destroyAddVertexCircle(circle);
    _addVertexCircles.clear();
}

void PolygonObject::init_ref_marker(const QPolygonF& qpf)
{
 ref_marker_ = new QMT_Geospatial_Marker(qpf);
}


//pure-virtual from MapGraphicsObject
QRectF PolygonObject::boundingRect() const
{
    QRectF latLonRect = _geoPoly.boundingRect();
    QPointF latLonCenter = latLonRect.center();
    Position latLonCenterPos(latLonCenter,0.0);
    Position topLeftPos(latLonRect.topLeft(),0.0);
    Position bottomRightPos(latLonRect.bottomRight(),0.0);

    QPointF topLeftENU = Conversions::lla2enu(topLeftPos,latLonCenterPos).toPointF();
    QPointF bottomRightENU = Conversions::lla2enu(bottomRightPos,latLonCenterPos).toPointF();

    return QRectF(topLeftENU,bottomRightENU);
}

//virtual from MapGraphicsObject
bool PolygonObject::contains(const QPointF &geoPos) const
{
    return _geoPoly.containsPoint(geoPos,
                                  Qt::OddEvenFill);
}

//pure-virtual from MapGraphicsObject
void PolygonObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
 Q_UNUSED(option)
 Q_UNUSED(widget)

 //?qDebug() << "polygon " << index_code_ << "painting";

 if(ref_marker_)
 {
  QPolygonF qpf = ref_marker_->outline();
  static r8 scale_factor = .000125;
  QTransform trans;
  trans = trans.fromTranslate(longitude(), latitude()).scale(scale_factor, scale_factor);


  QPointF base {longitude(), latitude()};

 // QPointF base_pixels = //tileSource

    QPolygonF qpf1;
  //  qpf1 << QPointF(longitude(), latitude());


    QSharedPointer<MapTileSource> tileSource = containing_view_->tileSource();  //_infoSource->tileSource();
    if (tileSource.isNull())
    {
        qWarning() << this << "can't do bounding box conversion, null tile source.";
    }
    else
    {
     int zoom_level = containing_view_->zoomLevel();
     QPointF base_pixels = tileSource->ll2qgs(base, zoom_level); //tileSource

     QPointF pixels_1 = base_pixels - QPointF {12, 12};
     QPointF pixels_2 = base_pixels - QPointF {0, 24};
     QPointF pixels_3 = base_pixels - QPointF {-12, 12};

     QPointF ll_1 = tileSource->qgs2ll(pixels_1, zoom_level);
     QPointF ll_2 = tileSource->qgs2ll(pixels_2, zoom_level);
     QPointF ll_3 = tileSource->qgs2ll(pixels_3, zoom_level);;

//?     qpf1 << base << ll_1 << ll_2 << ll_3;

//     static r8 scale_factor = .1;
     QTransform trans;
     trans = trans.scale(ref_marker_->scale(), ref_marker_->scale());

     QPolygonF qpf2 = trans.map(ref_marker_->outline());

     qDebug() << "qpf2 = " << qpf2;

     QTransform trans1;
     trans1 = trans1.translate(longitude(), latitude());

     for(QPointF point : qpf2)
     {
      qDebug() << "point = " << point;

      QPointF p1 = base_pixels - point;
      qDebug() << "p1 = " << p1;

      qpf1 << tileSource->qgs2ll(p1, zoom_level);
     }



//     QPointF topLeft = tileSource->ll2qgs(latLonRect.topLeft(),zoomLevel);
//     QPointF bottomRight = tileSource->ll2qgs(latLonRect.bottomRight(),zoomLevel);

    }




//  QPolygonF qpf1;
//  qpf1 << QPointF(longitude(), latitude());
//  qpf1 << QPointF(longitude() - 0.001, latitude() - 0.001);
//  qpf1 << QPointF(longitude(), latitude() - 0.002);
//  qpf1 << QPointF(longitude() + 0.001, latitude() - 0.001);

  _geoPoly = qpf1;

//?  _geoPoly= trans.map(qpf);
 }

 painter->setRenderHint(QPainter::Antialiasing,true);

 QPolygonF enuPoly;

 Position latLonCenterPos(_geoPoly.boundingRect().center(),0);
 foreach(QPointF latLon, _geoPoly)
 {
  Position latLonPos(latLon,0.0);
  QPointF enu = Conversions::lla2enu(latLonPos,latLonCenterPos).toPointF();
  enuPoly << enu;
 }

 painter->setBrush(_fillColor);
 painter->drawPolygon(enuPoly);

//?
 if(ref_marker_)
 //if(false)
 {
  // //  anything here?
 }
 else
 {
  //Populate edit and add-vertex handles if necessary.
  //Is there a better place to do this? Most likely, yes.
  if (_editCircles.isEmpty())
  {
   //Create objects to edit the polygon!
   for (int i = 0; i < _geoPoly.size(); i++)
   {
    //Edit circles - to change the shape
    CircleObject* circle = this->constructEditCircle();
    circle->setPos(_geoPoly.at(i));
    _editCircles.append(circle);

    QPointF current = _geoPoly.at(i);
    QPointF next = _geoPoly.at((i+1) % _geoPoly.size());
    QPointF avg((current.x() + next.x())/2.0,
                (current.y() + next.y())/2.0);

    //Add vertex circles - to add new vertices
    CircleObject* betweener = this->constructAddVertexCircle();
    betweener->setPos(avg);
    _addVertexCircles.append(betweener);
   }
  }
 }
}

//???

    //#ifdef HIDE
       //   qpf = trans.map(qpf);
       //   trans = {};
       //   trans = trans.fromTranslate(longitude(), latitude());
       ////   QTransform trans1;
       ////   trans1 = trans1.fromTranslate(longitude(), latitude());

    //   qDebug() << "qpf 3= " << qpf;
    //   qDebug() << "qpf1 = " << *qpf1;

    //   _geoPoly = qpf;
    //?   QPolygonF enuPoly;

    //   QPolygonF qpf1;
    //    QPolygonF* qpf1 = new QPolygonF;
    //    (*qpf1) << QPointF(40.8782, -74.1096).transposed();
    //    (*qpf1) << QPointF(40.8782, -74.1196).transposed();
    //    (*qpf1) << QPointF(40.8882, -74.1196).transposed();
    //    (*qpf1) << QPointF(40.8882, -74.1096).transposed();

    //   Position latLonCenterPos(qpf1->boundingRect().center(),0);
    //   foreach(QPointF latLon, *qpf1)
    //   {

    //       Position latLonPos(latLon,0.0);
    //       QPointF enu = Conversions::lla2enu(latLonPos,latLonCenterPos).toPointF();

    //       qDebug() << "1 enu latLon = " << latLon << "; enu = " << enu;

    //       enuPoly << enu;
    //   }

    //   painter->setBrush(_fillColor);
    //   painter->drawPolygon(enuPoly);

    //   return;

    //   PolygonObject* poly  = new PolygonObject(view_, *qpf, transit_color);

    //   poly->setLatitude(loc.coordinate().latitude());
    //   poly->setLongitude(loc.coordinate().longitude());
    //   scene_->addObject(poly);

    //   #endif //def HIDE

void PolygonObject::setPos(const QPointF & nPos)
{
    /*
      If the new position moved the object from the center of the bounding box made by the geo poly
      then we need to move the geo poly
    */
    if (nPos != _geoPoly.boundingRect().center())
    {
        const QPointF diff = nPos - this->pos();
        //_geoPoly.translate(diff);

        //We should also move our edit handles
        foreach(MapGraphicsObject * circle, _editCircles)
            circle->setPos(circle->pos() + diff);

        //And our "add vertex" handles
        this->fixAddVertexCirclePos();
    }

    MapGraphicsObject::setPos(nPos);

    //If this isn't here, we get TEARING when we edit our polygons
    this->posChanged();
}

QPolygonF PolygonObject::geoPoly() const
{
    return _geoPoly;
}

void PolygonObject::setGeoPoly(const QPolygonF &newPoly)
{
    if (newPoly == _geoPoly)
        return;

    _geoPoly = newPoly;

    foreach(MapGraphicsObject * obj, _editCircles)
        this->destroyEditCircle(obj);
    foreach(MapGraphicsObject * obj, _addVertexCircles)
        this->destroyAddVertexCircle(obj);
    _editCircles.clear();
    _addVertexCircles.clear();

    this->setPos(newPoly.boundingRect().center());
    this->polygonChanged(newPoly);
}

void PolygonObject::setFillColor(const QColor &color)
{
    if (_fillColor == color)
        return;

    _fillColor = color;
    this->redrawRequested();
}

//protected
//virtual from MapGraphicsObject
void PolygonObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /*
      This method is a bit of a hack --- ideally contains() or some other method
      we "reimplement" from PrivateQGraphicsObject should take care of this, but it
      hasn't been working. This prevents the polygon from being grabbed when the user
      click inside the bounding box but outside of the actual polygon
    */
    const QPointF geoPos = event->scenePos();

    //If the geo point is within our geo polygon, we might accept it
    if (_geoPoly.containsPoint(geoPos,Qt::OddEvenFill))
        MapGraphicsObject::mousePressEvent(event);
    //Otherwise we ignore it
    else
        event->ignore();
}

//protected
//virtual from MapGraphicsObject
void PolygonObject::keyReleaseEvent(QKeyEvent *event)
{
    if (event->matches(QKeySequence::Delete))
    {
        this->deleteLater();
        event->accept();
    }
    else
        event->ignore();
}

//private slot
void PolygonObject::handleEditCirclePosChanged()
{
    QObject * sender = QObject::sender();
    if (sender == 0)
        return;
    CircleObject * circle = qobject_cast<CircleObject *>(sender);
    if (circle == 0)
        return;

    int index = _editCircles.indexOf(circle);
    if (index == -1)
        return;

    QPointF newPos = circle->pos();
    _geoPoly.replace(index,newPos);
    this->setPos(_geoPoly.boundingRect().center());

    //We need to update the positions of our "add vertex" controllers
    this->fixAddVertexCirclePos();

    //Emit a signal so everyone knows that the polygon changed
    this->polygonChanged(this->geoPoly());
}

//private slot
void PolygonObject::handleAddVertexCircleSelected()
{
    QObject * sender = QObject::sender();
    if (sender == 0)
        return;
    CircleObject * circle = qobject_cast<CircleObject *>(sender);
    if (circle == 0)
        return;

    //If the circle isn't selected, something is wrong
    if (!circle->isSelected())
        return;

    //Now that we know the circle was selected, just deselect it. We don't need it selected actually
    circle->setSelected(false);

    //Get the position at which we should add a vertex
    QPointF geoPos = circle->pos();

    //The index at which we should insert the new vertex
    int index = _addVertexCircles.indexOf(circle);
    if (index == -1)
        return;
    index++;

    //Put the vertex in the polygon
    _geoPoly.insert(index,geoPos);

    //Create a new "Edit Circle" and put it in the right spot
    CircleObject * editCircle = this->constructEditCircle();
    editCircle->setPos(geoPos);
    _editCircles.insert(index,editCircle);

    editCircle->setSelected(true);


    //Create a new "Add vertex" circle and put it in the right spot
    CircleObject * addVertexCircle = this->constructAddVertexCircle();
    QPointF current = _geoPoly.at(index-1);
    QPointF next = _geoPoly.at(index);
    QPointF avg((current.x() + next.x())/2.0,
                (current.y() + next.y())/2.0);
    addVertexCircle->setPos(avg);
    _addVertexCircles.insert(index,addVertexCircle);

    this->fixAddVertexCirclePos();

    //Emit a signal so everyone knows that the polygon changed
    this->polygonChanged(this->geoPoly());
}

//private slot
void PolygonObject::handleEditCircleDestroyed()
{
    QObject * sender = QObject::sender();
    if (sender == 0)
    {
        qWarning() << "Can't process desyroyed edit circle. Sender is null";
        return;
    }
    CircleObject * circle = (CircleObject *) sender;

    int index = _editCircles.indexOf(circle);
    if (index == -1)
    {
        qWarning() << "Can't process destroyed edit circle. Not contained in edit circle list";
        return;
    }

    _geoPoly.remove(index);
    _editCircles.removeAt(index);
    _addVertexCircles.takeAt(index)->deleteLater();

    this->fixAddVertexCirclePos();
    this->redrawRequested();
    this->setPos(_geoPoly.boundingRect().center());
}

//private
void PolygonObject::fixAddVertexCirclePos()
{
    for (int i = 0; i < _geoPoly.size(); i++)
    {
        QPointF current = _geoPoly.at(i);
        QPointF next = _geoPoly.at((i+1) % _geoPoly.size());
        QPointF avg((current.x() + next.x())/2.0,
                    (current.y() + next.y())/2.0);

        //?
        if(!_addVertexCircles.isEmpty())
          _addVertexCircles.at(i)->setPos(avg);
    }
}

//private
CircleObject *PolygonObject::constructEditCircle()
{
//? CircleObject * toRet = new CircleObject(containing_view_, 8);
    CircleObject * toRet = new CircleObject(containing_view_, 18);
    connect(toRet,
            SIGNAL(posChanged()),
            this,
            SLOT(handleEditCirclePosChanged()));
    connect(toRet,
            SIGNAL(destroyed()),
            this,
            SLOT(handleEditCircleDestroyed()));

    this->newObjectGenerated(toRet);
    return toRet;
}

//private
void PolygonObject::destroyEditCircle(MapGraphicsObject *obj)
{
    disconnect(obj,
               SIGNAL(posChanged()),
               this,
               SLOT(handleEditCirclePosChanged()));
    disconnect(obj,
               SIGNAL(destroyed()),
               this,
               SLOT(handleEditCircleDestroyed()));
    obj->deleteLater();
}

//private
CircleObject *PolygonObject::constructAddVertexCircle()
{
    CircleObject * toRet = new CircleObject(containing_view_, 3,
                                            true,
                                            QColor(100,100,100,255));
    toRet->setFlag(MapGraphicsObject::ObjectIsMovable,false);
    connect(toRet,
            SIGNAL(selectedChanged()),
            this,
            SLOT(handleAddVertexCircleSelected()));

    this->newObjectGenerated(toRet);
    toRet->setToolTip("Single-click (don't drag!) to add vertex.");
    return toRet;
}

//private
void PolygonObject::destroyAddVertexCircle(MapGraphicsObject *obj)
{
    disconnect(obj,
               SIGNAL(selectedChanged()),
               this,
               SLOT(handleAddVertexCircleSelected()));
    obj->deleteLater();
}
