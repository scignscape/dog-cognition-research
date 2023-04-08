
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "sdi-block-element.h"

#include "sdi-block-element-collection.h"

#include <QJsonArray>
#include <QJsonValue>

SDI_Block_Element::SDI_Block_Element(u2 paragraph_id, u2 sentence_id)
  :  paragraph_id_(paragraph_id), sentence_id_(sentence_id),
     sentence_count_(0), start_page_(0), end_page_(0), count_in_page_(0),
     element_data_({0,0,0,0,0,0,0,0}), start_and_end_({{0,0},{0,0}})
     //count_in_paragraph_(0)
{

}

namespace  {

r4 pt_to_px(r8 pt)
{
 return pt * (96./72);
}

}

void SDI_Block_Element::read_json(SDI_Block_Element_Collection& element_collection, QJsonObject qjo)
{


}

void SDI_Block_Element::read_json_start_object(QString kind,
  SDI_Block_Element_Collection& element_collection, QJsonObject qjo)
{
 QJsonArray s_coords = qjo.value("start").toArray();

 start_and_end_.first = {s_coords[0].toInt(), s_coords[1].toInt()};

 u4 id = qjo.value("id").toInt();

 if(kind == "paragraph")
 {
  element_collection.paragraphs().push_back(this);
  paragraph_id_ = id;
 }
 else if(kind == "sentence")
 {
  element_collection.sentences().push_back(this);
  sentence_id_ = id;
  paragraph_id_ = qjo.value("par").toInt();
  sentence_count_ = qjo.value("pac").toInt();
 }

 start_page_ = qjo.value("pg").toInt();
 count_in_page_ = qjo.value("pgc").toInt();

 QJsonArray qja = qjo.value("gp2s").toArray();

 element_data_.global_count_at_last = qja.at(0).toInt();
 element_data_.page_count_at_last = qja.at(1).toInt();
 element_data_.paragraph_count_at_last = qja.at(2).toInt();
 element_data_.sentence_count_at_last = qja.at(3).toInt();

}

void SDI_Block_Element::read_json_end_object(QJsonObject qjo)
{
 QJsonArray e_coords = qjo.value("end").toArray();

 start_and_end_.second = {e_coords[0].toInt(), e_coords[1].toInt()};


 QJsonArray qja = qjo.value("gp2s").toArray();

 element_data_.global_count_at_end = qja.at(0).toInt();
 element_data_.page_count_at_end = qja.at(1).toInt();
 element_data_.paragraph_count_at_end = qja.at(2).toInt();
 element_data_.sentence_count_at_end = qja.at(3).toInt();


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

u2 SDI_Block_Element::get_sentence_count_in_paragraph()
{
 if(sentence_id_)
   return sentence_count_;

 return 0;
}


void SDI_Block_Element::init_coordinates(
  r8 page_height, r8 right_margin, r8 left_margin,
  r8 top_letter_height, r8 bottom_letter_height,
  r8 line_spacing_factor, r8 default_letter_height)
{
 r8 first_line_height_adjustment = 0;

 // // a sentence
 if(get_sentence_count_in_paragraph() == 1)
   first_line_height_adjustment = default_letter_height;


 // //  scaled points to "big" points
 static u4 rescale = 0x10000;

 r8 x1 = (double) start_and_end_.first.first / rescale;
 r8 y1 = (double) start_and_end_.first.second / rescale;

 y1 -= first_line_height_adjustment;

 r8 x2 = (double) start_and_end_.second.first / rescale;
 r8 y2 = (double) start_and_end_.second.second / rescale;

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

