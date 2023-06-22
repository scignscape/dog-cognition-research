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
 signed short xoffset = 3;
 signed short yoffset = 0;

 QPixmap pm(17 + qAbs(xoffset), 17 + qAbs(yoffset));
 pm.fill(Qt::transparent);
 QPainter qp(&pm);


 qp.drawLine(0 + xoffset, 6 + yoffset, 16 + xoffset, 6 + yoffset);
 qp.drawLine(6 + xoffset, 0 + yoffset, 6 + xoffset, 16 + yoffset);
 qp.drawLine(13 + xoffset, 6 + yoffset, 13 + xoffset, 13 + yoffset);
 qp.drawLine(13 + xoffset, 13 + yoffset, 6 + xoffset, 13 + yoffset);

 custom_cursor_ = QCursor(pm, 0, 0);
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
