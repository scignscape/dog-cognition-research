
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef SDI_SENTENCE__H
#define SDI_SENTENCE__H

#include <QString>
#include <QPointF>
#include <QVector>

#include "accessors.h"

#include "global-types.h"


class SDI_Sentence
{
 QString text_;

 QVector<QPointF> svg_coordinates_;
 u2 number_of_lines_;

public:

 SDI_Sentence();

 void init_coordinates(QPair<QPair<u4, u4>, QPair<u4, u4>>& start_and_end,
   r8 page_height, r8 right_margin, r8 left_margin,
   r8 top_letter_height, r8 bottom_letter_height,
   r8 line_spacing_factor, r8 first_line_height_adjustment);

 void svg_coordinates_string(QString& result);

};

#endif
