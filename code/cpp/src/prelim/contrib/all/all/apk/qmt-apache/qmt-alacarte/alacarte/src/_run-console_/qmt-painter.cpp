
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qmt-painter.h"

#include "qt-logger.h"

#include <QtMath>


QMT_Painter::QMT_Painter(QImage* image)
  : QPainter(image), base_image_(image)
{
}

void QMT_Painter::draw_rect()
{
 if(base_image_)
   drawRect(base_image_->rect());
}

void QMT_Painter::set_pen_width(u1 width)
{
 QPen new_pen = pen();
 new_pen.setWidth(width);
 setPen(new_pen);
}


void QMT_Painter::reset_pen_color(const QColor& color)
{
 set_pen(color, pen().width());
}


void QMT_Painter::set_pen_color(const QColor &color)
{
 QPen new_pen = pen();
 new_pen.setColor(color);
 setPen(new_pen);
}

void QMT_Painter::set_pen(const QColor& color, u1 width)
{
 QPen new_pen;
 new_pen.setWidth(width);
 new_pen.setColor(color);
 setPen(new_pen);
}




