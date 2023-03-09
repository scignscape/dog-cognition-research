
#include "simple-polyline-annotation.h"

#include "image-viewer/dhax-mouse-interaction-data.h"

#include <QPainter>

#include <QDebug>

#include <QWheelEvent>

#include "global-types.h"


Simple_Polyline_Annotation::Simple_Polyline_Annotation(DHAX_Mouse_Interaction_Data& mouse_interaction_data,
  const QPointF& sc, QWidget* p)
 : Simple_Annotation_Base(mouse_interaction_data, sc, p)
{
 scaffold_.setTopLeft(sc);
 scaffold_.setBottomRight(sc);
}

void Simple_Polyline_Annotation::fulfill_left_resume(const QPoint& pos, n8 request_code)
{
 point_pairs_.push_back({pos, pos}); //{mev->pos(), mev->pos()});
 mouse_interaction_data_.flags.mouse_moving = true;
 mouse_interaction_data_.flags.needs_resume = false;
 mouse_interaction_data_.flags.has_resumed = true;
 mouse_interaction_data_.flags.ui_needs_update = true;
}

void Simple_Polyline_Annotation::fulfill_left_init(const QPoint& pos, n8 request_code)
{
 point_pairs_.push_back({pos, pos}); //{mev->pos(), mev->pos()});
 mouse_interaction_data_.flags.mouse_moving = true;
}

void Simple_Polyline_Annotation::fulfill_left_move_release(const QPoint& pos, n8 request_code)
{
 point_pairs_.last().second = pos;
 mouse_interaction_data_.flags.mouse_moving = false;
 mouse_interaction_data_.flags.needs_resume = true;
}

void Simple_Polyline_Annotation::fulfill_left_move(const QPoint& pos, n8 request_code)
{
 point_pairs_.last().second = pos;
}

void Simple_Polyline_Annotation::pressed_mode_data_request_code(QMouseEvent* mev, n8& result)
{
 result = 1;
}

void Simple_Polyline_Annotation::released_mode_data_request_code(QMouseEvent* mev, n8& result)
{
 result = 1;
}

void Simple_Polyline_Annotation::moved_mode_data_request_code(QMouseEvent* mev, n8& result)
{
 result = 1;
}

void Simple_Polyline_Annotation::draw_vertex_handles(QPainter& painter, u1 radius)
{
 for(const QPair<QPoint, QPoint>& pr : point_pairs_)
 {
  this->MultiStep_Annotation_Base::draw_vertex_handles({&pr.first, &pr.second}, painter, radius);
 }
}

void Simple_Polyline_Annotation::process_paint_event(QPaintEvent* event, QPainter& painter)
{
// QRect _scaffold; map_from_parent(scaffold_, _scaffold);
// painter.drawEllipse(_scaffold);


 u1 count = 0;
 QPoint sec;

 for(QPair<QPoint, QPoint>& pr : point_pairs_)
 {
//  painter.setPen(back_pen);
//  painter.setBrush(QBrush());

//?  painter.setPen(QPen(QColor("orange")));

  painter.drawLine(pr.first, pr.second);
  if(count)
    painter.drawLine(sec, pr.first);

//  painter.setPen(local_pen);
//  painter.setBrush(local_brush);

//  painter.drawLine(pr.first, pr.second);
//  if(count)
//    painter.drawLine(sec, pr.first);

  ++count;
  sec = pr.second;

  //paintEvent_draw_vertex_handles({&pr.first, &pr.second}, painter);
 }


}

