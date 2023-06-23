#ifndef PRIVATEQGRAPHICSVIEW_H
#define PRIVATEQGRAPHICSVIEW_H

#include <QGraphicsView>

class PrivateQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PrivateQGraphicsView(QWidget *parent = 0);
    PrivateQGraphicsView(QGraphicsScene* scene, QWidget * parent=0);
    virtual ~PrivateQGraphicsView();

    void activate_alt_cursor();
    void activate_custom_cursor();


protected:
    //virtual from QGraphicsView
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    //virtual from QGraphicsView
    virtual void mouseMoveEvent(QMouseEvent *event);

    //virtual from QGraphicsView
    virtual void mousePressEvent(QMouseEvent *event);

    //virtual from QGraphicsView
    virtual void mouseReleaseEvent(QMouseEvent *event);

    //virtual from QGraphicsView
    virtual void contextMenuEvent(QContextMenuEvent *event);

    //virtual from QGraphicsView
    virtual void wheelEvent(QWheelEvent *event);

    virtual void enterEvent(QEvent *event);

    QCursor custom_cursor_;
    QCursor alt_cursor_;
    void init_custom_cursor();


//?    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    
Q_SIGNALS:
    void hadMouseDoubleClickEvent(QMouseEvent* event);
    void hadMouseMoveEvent(QMouseEvent * event);
    void hadMousePressEvent(QMouseEvent * event);
    void hadMouseReleaseEvent(QMouseEvent * event);
    void hadContextMenuEvent(QContextMenuEvent *);
    void hadWheelEvent(QWheelEvent *);
    
public Q_SLOTS:
    
};

#endif // PRIVATEQGRAPHICSVIEW_H
