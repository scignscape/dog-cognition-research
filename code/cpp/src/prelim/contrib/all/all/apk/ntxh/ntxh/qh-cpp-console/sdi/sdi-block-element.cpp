
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "sdi-block-element.h"


SDI_Block_Element::SDI_Block_Element(u2 paragraph_id, u2 sentence_id)
  :  paragraph_id_(paragraph_id), sentence_id_(sentence_id)
{

}

namespace  {

r4 pt_to_px(r8 pt)
{
 return pt * (96./72);
}

}

void SDI_Block_Element::svg_coordinates_string(QString& result)
{
 if(svg_coordinates_.isEmpty())
   return;

 for(QPointF point : svg_coordinates_)
 {
  result += "%1,%2 "_qt.arg(point.toPoint().x()).arg(point.toPoint().y());
 }
 result.chop(1); // trailing space
}


void SDI_Block_Element::init_coordinates(QPair<QPair<u4, u4>, QPair<u4, u4>>& start_and_end,
  r8 page_height, r8 right_margin, r8 left_margin,
  r8 top_letter_height, r8 bottom_letter_height,
  r8 line_spacing_factor, r8 first_line_height_adjustment)
{
 // //  scaled points to "big" points
 static u4 rescale = 0x10000;

 r8 x1 = (double) start_and_end.first.first / rescale;
 r8 y1 = (double) start_and_end.first.second / rescale;

 y1 -= first_line_height_adjustment;

 r8 x2 = (double) start_and_end.second.first / rescale;
 r8 y2 = (double) start_and_end.second.second / rescale;

// if(start_and_end.first.second == start_and_end.second.second)
// {
//  number_of_lines_ = 1;
// }
// else
// {
//  r8 approximate_number_of_lines = (start_and_end.first.second - start_and_end.second.second) /
//    ((quint64) (line_spacing_factor * (quint64) rescale));
//  number_of_lines_ = ((u2) approximate_number_of_lines) + 1;
// }

 if(y1 == y2)
 {
  number_of_lines_ = 1;
 }
 else
 {
  r8 approximate_number_of_lines = (y1 - y2) / line_spacing_factor;
  number_of_lines_ = ((u2) approximate_number_of_lines) + 1;
 }

 r4 x1_px = pt_to_px(x1);
 r4 y1_px = pt_to_px(y1);

 r4 x2_px = pt_to_px(x2);
 r4 y2_px = pt_to_px(y2);

 r4 tlh = pt_to_px(top_letter_height);
 r4 blh = pt_to_px(bottom_letter_height);

 r4 page_height_px = pt_to_px(page_height);

 r4 start_x = x1_px;
 r4 start_y_baseline = page_height_px - y1_px;
 r4 start_y_topline = start_y_baseline - tlh;

 r4 end_x = x2_px;
 r4 end_y_baseline = page_height_px - y2_px;
 r4 end_y_topline = end_y_baseline - blh;

 if(number_of_lines_ == 1)
 {
  // //  here we only need four points ...

  r4 top_y = qMin(start_y_topline, end_y_topline);
  r4 bottom_y = qMax(start_y_baseline, end_y_baseline);


  svg_coordinates_ = {{start_x, bottom_y},
    {start_x, top_y}, {end_x, top_y},
    {end_x, bottom_y}};
 }
 else
 {
  r4 left_margin_px = pt_to_px(left_margin);
  r4 right_margin_px = pt_to_px(right_margin);

  r4 right_margin_x = right_margin_px;
  r4 right_margin_y_top = start_y_topline;
  r4 right_margin_y_bottom = end_y_topline;


  r4 left_margin_x = left_margin_px;
  r4 left_margin_y_top = start_y_baseline;
  r4 left_margin_y_bottom = end_y_baseline;

  svg_coordinates_ = {{start_x, start_y_baseline},
    {start_x, start_y_topline},
    {right_margin_x, right_margin_y_top},
    {right_margin_x, right_margin_y_bottom},
    {end_x, end_y_topline},
    {end_x, end_y_baseline},
    {left_margin_x, left_margin_y_bottom},
    {left_margin_x, left_margin_y_top} };

 }
}

