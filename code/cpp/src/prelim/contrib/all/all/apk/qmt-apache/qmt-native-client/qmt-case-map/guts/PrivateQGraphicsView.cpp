#include "PrivateQGraphicsView.h"

#include <QWheelEvent>
#include <QContextMenuEvent>
#include <QtDebug>

PrivateQGraphicsView::PrivateQGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

 init_custom_cursor();
}

PrivateQGraphicsView::PrivateQGraphicsView(QGraphicsScene *scene, QWidget *parent) :
    QGraphicsView(scene,parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

 init_custom_cursor();
}

void PrivateQGraphicsView::init_custom_cursor()
{
 setMouseTracking(true);

 int mid = 7;
 int hot = 4;
 int hota = hot + 5;
 int max = 15;



// int mid = 6;
// int hot = 16;
// int hota = hot + 2;
// int max = 31;

 {
  signed short xoffset = 0;
  signed short yoffset = 0;

  QPixmap pm(max + 1 + qAbs(xoffset), max + 1 + qAbs(yoffset));
  pm.fill(Qt::transparent);
  QPainter qp(&pm);


  qp.drawLine(0 + xoffset, mid + yoffset, max + xoffset, mid + yoffset);
  qp.drawLine(mid + xoffset, 0 + yoffset, mid + xoffset, max + yoffset);
//  qp.drawLine(hot + xoffset, mid + yoffset, hot + xoffset, hot + yoffset);
 // qp.drawLine(hot + xoffset, hot + yoffset, mid + xoffset, hot + yoffset);

  qp.drawRect(mid + xoffset, mid + yoffset, hot + xoffset, hot + yoffset);

  custom_cursor_ = QCursor(pm, hota, hota);
 }

 {
  signed short xoffset = 0;
  signed short yoffset = 0;

  QPixmap pm(max + 1 + qAbs(xoffset), max + 1 + qAbs(yoffset));
  pm.fill(Qt::transparent);
  QPainter qp(&pm);

//  qp.setBrush(Qt::cyan);
  qp.setPen(QPen(QBrush(Qt::cyan), 1.5, Qt::DotLine));
  qp.drawRect(mid + xoffset, mid + yoffset, hot + xoffset, hot + yoffset);

  qp.setPen(Qt::darkCyan);

  qp.drawRect(mid + xoffset, mid + yoffset, hot + xoffset, hot + yoffset);

  qp.drawLine(0 + xoffset, mid + yoffset, max + xoffset, mid + yoffset);
  qp.drawLine(mid + xoffset, 0 + yoffset, mid + xoffset, max + yoffset);


//  qp.drawLine(13 + xoffset, 6 + yoffset, 13 + xoffset, 13 + yoffset);
//  qp.drawLine(6 + xoffset, 6 + yoffset, 13 + xoffset, 13 + yoffset);
//  qp.drawLine(13 + xoffset, 13 + yoffset, 6 + xoffset, 13 + yoffset);

  alt_cursor_ = QCursor(pm, hota, hota);
 }



}

void PrivateQGraphicsView::activate_alt_cursor()
{
 viewport()->setCursor(alt_cursor_);
}

void PrivateQGraphicsView::activate_custom_cursor()
{
 viewport()->setCursor(custom_cursor_);
}


PrivateQGraphicsView::~PrivateQGraphicsView()
{
}

//protected
////virtual from QGraphicsView
void PrivateQGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->setAccepted(false);
    this->hadMouseDoubleClickEvent(event);
    if (!event->isAccepted())
        QGraphicsView::mouseDoubleClickEvent(event);
}

//protected
////virtual from QGraphicsView
void PrivateQGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    event->setAccepted(false);
    this->hadMouseMoveEvent(event);
    if (!event->isAccepted())
        QGraphicsView::mouseMoveEvent(event);
}

//protected
////virtual from QGraphicsView
void PrivateQGraphicsView::enterEvent(QEvent *event)
{
 QGraphicsView::enterEvent(event);
 viewport()->setCursor(custom_cursor_);
}

//protected
////virtual from QGraphicsView
void PrivateQGraphicsView::mousePressEvent(QMouseEvent *event)
{
    event->setAccepted(false);
    this->hadMousePressEvent(event);
    if (!event->isAccepted())
        QGraphicsView::mousePressEvent(event);

    viewport()->setCursor(custom_cursor_);
}

//protected
////virtual from QGraphicsView
void PrivateQGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    event->setAccepted(false);
    this->hadMouseReleaseEvent(event);
    if (!event->isAccepted())
        QGraphicsView::mouseReleaseEvent(event);

    viewport()->setCursor(custom_cursor_);
}

//protected
////virtual from QGraphicsView
void PrivateQGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    event->setAccepted(false);
    this->hadContextMenuEvent(event);
    if (!event->isAccepted())
        QGraphicsView::contextMenuEvent(event);

    viewport()->setCursor(custom_cursor_);
}

//protected
//virtual from QGraphicsView
void PrivateQGraphicsView::wheelEvent(QWheelEvent *event)
{
    event->setAccepted(false);
    this->hadWheelEvent(event);
    if (!event->isAccepted())
        QGraphicsView::wheelEvent(event);
}
