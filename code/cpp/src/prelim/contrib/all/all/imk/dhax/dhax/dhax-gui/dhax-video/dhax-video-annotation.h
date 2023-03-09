
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_VIDEO_ANNOTATION__H
#define DHAX_VIDEO_ANNOTATION__H

#include <QtWidgets>

#include <QVideoFrame>
#include <QVideoSurfaceFormat>
#include <QAbstractVideoSurface>

#include <QPointF>

#include "global-types.h"
#include "accessors.h"


class DHAX_Video_Annotation
{
 QString kind_;

 QString id_;
 QString ref_id_;
 u4 ref_time_offset_;

 s4 starting_frame_number_;
 s4 ending_frame_number_;

 QString text_;
 QString template_text_;

 QString inner_style_sheet_;

 QPointF corner_position_;

 QString html_text_;
 QString template_html_text_;

 void* scene_data_;
 void* scene_type_data_;

 QString data64_;
 QString kv_text_;

 QString element_name_;
 QString inner_element_name_;
 QString inner_element_background_color_;

 QString font_size_;

 DHAX_Video_Annotation* ref_annotation_;

 s4 pause_time_;

 QString graphics_file_;
 QString graphics_folder_;

 QVector<QString> pdflatex_;

public:

 DHAX_Video_Annotation();

 ACCESSORS(s4 ,starting_frame_number)
 ACCESSORS(s4 ,ending_frame_number)

 ACCESSORS(QString ,kind)
 ACCESSORS(QString ,text)
 ACCESSORS(QString ,element_name)
 ACCESSORS(QString ,inner_style_sheet)
 ACCESSORS(QPointF ,corner_position)
 ACCESSORS(QString ,html_text)
 ACCESSORS(QString ,kv_text)

 ACCESSORS(QString ,font_size)

 ACCESSORS(QString ,inner_element_name)
 ACCESSORS(QString ,inner_element_background_color)

 ACCESSORS(QString ,graphics_file)
 ACCESSORS(QString ,graphics_folder)

 ACCESSORS(QString ,id)
 ACCESSORS(QString ,ref_id)
 ACCESSORS(u4 ,ref_time_offset)
 ACCESSORS(s4 ,pause_time)


 ACCESSORS(DHAX_Video_Annotation* ,ref_annotation)

 ACCESSORS(void* ,scene_data)
 ACCESSORS(void* ,scene_type_data)

 ACCESSORS(QString ,data64)


 void check_substitution(QString key, QString value);
 void prepare_template_text();

 void set_pdflatex_shell(QString code)
 {
  pdflatex_.resize(3);
  pdflatex_[0] = code;
 }

 QString get_pdflatex_shell()
 {
  return pdflatex_.value(0);
 }

 void set_pdflatex_pdf(QString path)
 {
  pdflatex_[1] = path;
 }

 QString get_pdflatex_pdf()
 {
  return pdflatex_.value(1);
 }

 void set_pdflatex_png(QString path)
 {
  pdflatex_[2] = path;
 }

 QString get_pdflatex_png()
 {
  return pdflatex_.value(2);
 }


 void finalize_html_text();

 template<typename DATA_Type>
 DATA_Type* scene_data_as()
 {
  return (DATA_Type*) scene_data_;
 }

 template<typename DATA_Type>
 DATA_Type* scene_type_data_as()
 {
  return (DATA_Type*) scene_type_data_;
 }

 template<typename DATA_Type>
 bool scene_data_as(DATA_Type*& d)
 {
  if(scene_data_)
  {
   d = (DATA_Type*) scene_data_;
   return true;
  }
  return false;
 }

//?
// template<typename T>
// friend T& operator<<(T& lhs, const DHAX_Video_Annotation& rhs)
// {
//  lhs << "%1 -> %2: %3"_qt.arg(rhs.starting_frame_number_)
//    .arg(rhs.ending_frame_number_).arg(rhs.text().mid(0, 10));
//  return lhs;
// }

 template<typename T>
 friend T operator<<(T lhs, const DHAX_Video_Annotation& rhs)
 {
  if(rhs.kind() == "text")
    lhs << "%1 -> %2: %3"_qt.arg(rhs.starting_frame_number_)
      .arg(rhs.ending_frame_number_).arg(rhs.text().mid(0, 10));
  else
    lhs << "%1 -> %2: %3"_qt.arg(rhs.starting_frame_number_)
      .arg(rhs.ending_frame_number_).arg(rhs.kind());
  return lhs;
 }

};

#endif //DHAX_VIDEO_ANNOTATION__H
