

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-video-annotation.h"

#include <QtWidgets>
#include <qabstractvideosurface.h>
#include <qvideosurfaceformat.h>



DHAX_Video_Annotation::DHAX_Video_Annotation()
  :  ref_time_offset_(0), ref_annotation_(nullptr), scene_data_(nullptr),
     starting_frame_number_(-1), ending_frame_number_(-1),
     scene_type_data_(nullptr), pause_time_(0)
{

}

void DHAX_Video_Annotation::check_substitution(QString key, QString value)
{
 text_ = template_text_;
 html_text_ = template_html_text_;
 text_.replace(key, value);
 html_text_.replace(key, value);
}

void DHAX_Video_Annotation::prepare_template_text()
{
 template_text_ = text_;
 template_html_text_ = html_text_;
}


void DHAX_Video_Annotation::finalize_html_text()
{
 static QString html = "<%1 style=\"%2\">%3%4%5</%1>";

 static QString font = "<span style=\"font-size:%1\">";

// static QString inner = "<%1%2>"; // style=\"font-size:%1\">";
// static QString inner = "<%1%2>"; // style=\"font-size:%1\">";

 QString text = text_;

 QString font_start, font_end;

 if(!font_size_.isEmpty())
 {

  QRegExp re("\\d+");
  if (re.exactMatch(font_size_))
    font_start = font.arg(font_size_ + "pt");
  else
    font_start = font.arg(font_size_);

  font_end = "</span>";
 }

// QString pre_inner_element, post_inner_element;
 QString ibc = inner_element_background_color_;
 if(ibc.startsWith('>'))
 {
  ibc = ibc.mid(1);
  font_start += "<br>";
  font_end.prepend("<br>");
//  pre_inner_element = "<br>";
//  post_inner_element = "<br>";
 }

 if(!inner_element_name_.isEmpty())
 {
  if(ibc.isEmpty())
    font_start += "<%1>"_qt.arg(inner_element_name_);
  else
    font_start += "<%1 style=\"background-color:%2\">"_qt
     .arg(inner_element_name_).arg(ibc);
  font_end.prepend("</%1>"_qt.arg(inner_element_name_));
 }

 text.replace("<|||", "&nbsp;&nbsp;");

 text.replace("<||", "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
 text.replace("<|", "&nbsp;");

 text.replace("|||>", "&nbsp;&nbsp;<br>");
 text.replace("||>", "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>");
 text.replace("|>", "&nbsp;<br>");


 html_text_ = html.arg(element_name_).arg(inner_style_sheet_)
   .arg(font_start).arg(text).arg(font_end);

 static int count = 0;

 if(count < 5)
   qDebug() << "html text: " << html_text_;

 ++count;
}


