
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "simple-annotation-base.h"

#include <QPainter>

#include <QDebug>

#include <QWheelEvent>

#include "global-types.h"

Simple_Annotation_Base::Simple_Annotation_Base(DHAX_Mouse_Interaction_Data& mouse_interaction_data,
   const QPointF& sc, QWidget* p) :
   MultiStep_Annotation_Base(mouse_interaction_data, p)
{
 if(p)
   setGeometry(p->geometry());
}

void Simple_Annotation_Base::draw_vertex_handles(QPainter& painter, u1 radius)
{
 QPoint tl = scaffold_.topLeft().toPoint(),
   tr = scaffold_.topRight().toPoint(),
   br = scaffold_.bottomRight().toPoint(),
   bl = scaffold_.bottomLeft().toPoint();
 this->MultiStep_Annotation_Base::draw_vertex_handles({&tl, &tr, &br, &bl}, painter, radius);
}

void Simple_Annotation_Base::adjust_geometry(const QPointF& pos)
{
 scaffold_.setBottomRight(pos);
}

void Simple_Annotation_Base::reset_geometry(const QPointF& sc)
{

}

void Simple_Annotation_Base::process_paint_event(QPaintEvent* event, QPainter& painter)
{
 QRect _scaffold; map_from_parent(scaffold_, _scaffold);
 painter.drawRect(_scaffold);
}

void Simple_Annotation_Base::set_gradient_center(QConicalGradient& gradient)
{
 gradient.setCenter(scaffold_.center());
}

