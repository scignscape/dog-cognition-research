
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qmt-paint-context.h"

#include "qt-logger.h"

#include <QtMath>


QMT_Paint_Context::QMT_Paint_Context(QImage* image)
  : base_image_(image)
{

}


void QMT_Paint_Context::draw_gappy_rectangle(QPainter& painter, const QRect& rect, u2 gap)
{
 painter.drawLine(rect.topLeft() + QPoint(gap, 0), rect.topRight() - QPoint(gap, 0));
 painter.drawLine(rect.bottomLeft() + QPoint(gap, 0), rect.bottomRight() - QPoint(gap, 0));

 painter.drawLine(rect.topLeft() + QPoint(0, gap), rect.bottomLeft() - QPoint(0, gap));
 painter.drawLine(rect.topRight() + QPoint(0, gap), rect.bottomRight() - QPoint(0, gap));

}

void QMT_Paint_Context::draw_gappy_rectangle_as_octagon(QPainter& painter, const QRect& rect, u2 gap)
{
 draw_gappy_rectangle(painter, rect, gap);

 painter.drawLine(rect.topLeft() + QPoint(gap, 0), rect.topLeft() + QPoint(0, gap));

 painter.drawLine(rect.topRight() - QPoint(gap, 0), rect.topRight() + QPoint(0, gap));

 painter.drawLine(rect.bottomLeft() + QPoint(gap, 0), rect.bottomLeft() - QPoint(0, gap));

 painter.drawLine(rect.bottomRight() - QPoint(gap, 0), rect.bottomRight() - QPoint(0, gap));

}

QLine QMT_Paint_Context::make_vline(const QPoint& center, u2 half_height)
{
 //QLine result(center.x(), center.y() - height, )
 return QLine(center - QPoint{0, half_height}, center + QPoint{0, half_height});
}

QLine QMT_Paint_Context::make_hline(const QPoint& center, u2 half_width)
{
 //QLine result(center.x(), center.y() - height, )
 return QLine(center - QPoint{half_width, 0}, center + QPoint{half_width, 0});
}

QRect QMT_Paint_Context::make_rectangle_from_center(const QPoint& center, u2 width, u2 height)
{
 QRect result(center, QSize{0, 0});
 result.adjust(-width, -height, width, height);
 return result;
}

QRect QMT_Paint_Context::make_square_from_center(const QPoint& center, u2 half_side)
{
 QRect result(center, QSize{0, 0});
 result.adjust(-half_side, -half_side, half_side, half_side);
 return result;
}

void QMT_Paint_Context::center_transpose(QRect& rect)
{
 rect = make_rectangle_from_center(rect.center(), (u2) rect.height() / 2, (u2) rect.width() / 2);
}
