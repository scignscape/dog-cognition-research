
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QMT_PAINTER__H
#define QMT_PAINTER__H

#include <QString>

#include <string>

#include "accessors.h"

#include "global-types.h"

#include <QPainter>

class QMT_Painter : public QPainter
{
 QImage* base_image_;

public:

 QMT_Painter(QImage* image);

 void draw_rect();
 void set_pen_width(u1 width);
 void set_pen_color(const QColor& color);
 void reset_pen_color(const QColor& color);
 void set_pen(const QColor& color, u1 width);

};


#endif // QMT_PAINTER__H
