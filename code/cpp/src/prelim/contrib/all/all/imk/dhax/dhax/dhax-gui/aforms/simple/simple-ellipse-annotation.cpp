
#include "simple-ellipse-annotation.h"

#include <QPainter>

#include <QDebug>

#include <QWheelEvent>

#include "global-types.h"


Simple_Ellipse_Annotation::Simple_Ellipse_Annotation(DHAX_Mouse_Interaction_Data& mouse_interaction_data,
   const QPointF& sc, QWidget* p)
 : Simple_Annotation_Base(mouse_interaction_data, sc, p)
{
 scaffold_.setTopLeft(sc);
 scaffold_.setBottomRight(sc);
}

void Simple_Ellipse_Annotation::process_paint_event(QPaintEvent* event, QPainter& painter)
{
 QRect _scaffold; map_from_parent(scaffold_, _scaffold);
 painter.drawEllipse(_scaffold);
}

