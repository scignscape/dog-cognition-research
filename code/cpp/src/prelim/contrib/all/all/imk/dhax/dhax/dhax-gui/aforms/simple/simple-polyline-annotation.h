
#ifndef SIMPLE_POLYLINE_ANNOTATION__H
#define SIMPLE_POLYLINE_ANNOTATION__H


#include <QRubberBand>

#include "global-types.h"

#include "accessors.h"

#include "../simple-annotation-base.h"


class Simple_Polyline_Annotation : public Simple_Annotation_Base
{
 Q_OBJECT

 QVector<QPair<QPoint, QPoint>> point_pairs_;

public:

 Simple_Polyline_Annotation(DHAX_Mouse_Interaction_Data& mouse_interaction_data,
   const QPointF& sc, QWidget* p = nullptr);

 void pressed_mode_data_request_code(QMouseEvent*, n8&) Q_DECL_OVERRIDE;
 void released_mode_data_request_code(QMouseEvent*, n8&) Q_DECL_OVERRIDE;
 void moved_mode_data_request_code(QMouseEvent*, n8&) Q_DECL_OVERRIDE;

 void draw_vertex_handles(QPainter& painter, u1 radius) Q_DECL_OVERRIDE;

 void fulfill_left_init(const QPoint& pos, n8 request_code) Q_DECL_OVERRIDE;
 void fulfill_left_move_release(const QPoint& pos, n8 request_code) Q_DECL_OVERRIDE;
 void fulfill_left_move(const QPoint& pos, n8 request_code) Q_DECL_OVERRIDE;
 void fulfill_left_resume(const QPoint& pos, n8 request_code) Q_DECL_OVERRIDE;

protected:

 void process_paint_event(QPaintEvent* event, QPainter& painter) Q_DECL_OVERRIDE;


Q_SIGNALS:

protected:

// void paintEvent(QPaintEvent *event) ;


public Q_SLOTS:

};

#endif // SIMPLE_POLYLINE_ANNOTATION__H
