
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef SDI_BLOCK_ELEMENT__H
#define SDI_BLOCK_ELEMENT__H

#include <QString>
#include <QPointF>
#include <QVector>

#include "accessors.h"

#include "global-types.h"

#include <QJsonObject>

class SDI_Block_Element_Collection;

class SDI_Block_Element
{
 QString text_;

 QPair<QPair<u4, u4>, QPair<u4, u4>> start_and_end_;

 QVector<QPointF> svg_coordinates_;
 u2 number_of_lines_;

 // //  if this is a sentence, paragraph_id_
  //    will hold the paragraph to which
  //    it belongs.  For a paragraph,
  //    sentence_id_ will be 0.
 u2 paragraph_id_;
 u2 sentence_id_;

 u4 element_id_;

 // //  either the number of sentences in a
  //    paragraph or the count of a sentence
  //    in its containing paragraph
 u2 sentence_count_;

 u2 start_page_;
 u2 end_page_;
 u2 count_in_page_;

// u2 count_in_paragraph_;

 struct Element_GP2S_Data {
   u4 global_count_at_last;
   u2 page_count_at_last;
   u2 paragraph_count_at_last;
   u2 sentence_count_at_last;

   u4 global_count_at_end;
   u2 page_count_at_end;
   u2 paragraph_count_at_end;
   u2 sentence_count_at_end;
 };

 Element_GP2S_Data element_data_;

public:

 SDI_Block_Element(u2 paragraph_id = 0, u2 sentence_id = 0);

 ACCESSORS(u2 ,sentence_id)
 ACCESSORS(u2 ,paragraph_id)

 //QPair<QPair<u4, u4>, QPair<u4, u4>>& start_and_end,
 void init_coordinates(r8 page_height, r8 right_margin, r8 left_margin,
   r8 top_letter_height, r8 bottom_letter_height,
   r8 line_spacing_factor, r8 default_letter_height);

 void svg_coordinates_string(QString& result);

 void read_json(SDI_Block_Element_Collection& element_collection, QJsonObject qjo);

 void read_json_start_object(QString kind, SDI_Block_Element_Collection& element_collection, QJsonObject qjo);
 void read_json_end_object(QJsonObject qjo);

 u2 get_sentence_count_in_paragraph();
};

#endif // SDI_BLOCK_ELEMENT__H

