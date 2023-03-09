
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_VIDEO_ANNOTATION_SET__H
#define DHAX_VIDEO_ANNOTATION_SET__H


#include <QMap>

#include <QVideoFrame>
#include <QVideoSurfaceFormat>
#include <QAbstractVideoSurface>

#include "global-types.h"
#include "accessors.h"

#include "dhax-video-annotation.h"

#include "ntxh-parser/ntxh-document.h"

USING_KANS(HGDMCore)

class DHAX_Video_Annotation_Set : public QMap<s4, DHAX_Video_Annotation>
{
 typedef NTXH_Graph::hypernode_type hypernode_type;

 QString source_file_;
 QString source_folder_;

 QMap<u4, QVector<QPair<void*, void*>>> end_frame_data_;

 QColor circled_text_default_background_color_;
 QColor circled_text_default_foreground_color_;
 QColor circled_text_default_outline_color_;

 r4 circled_text_default_font_size_;
 u1 circled_text_default_width_;
 u1 circled_text_default_border_;

 QSizeF smaller_video_size_;
 QSizeF larger_video_size_;


 r8 sizes_ratio_x_;
 r8 sizes_ratio_y_;

 r8 sizes_ratio_x_adjustment_;
 r8 sizes_ratio_y_adjustment_;

 s2 smaller_size_x_translation_;
 s2 smaller_size_y_translation_;

 s2 larger_size_x_translation_;
 s2 larger_size_y_translation_;

 QMap<QString, DHAX_Video_Annotation*> annotations_by_id_;

 DHAX_Video_Annotation* current_pause_annotation_;
 QMap<DHAX_Video_Annotation*, QSet<DHAX_Video_Annotation*>>
   anchored_ref_annotations_;

 s4 reffed_annotation_count_;

 QMap<QString, QString> text_macros_;

 QMap<QString, s4> auto_ids_;

 QString* template_file_;

 void parse_text_macro(QString& text, int start = 0);
 void fetch_text_macro(QString& text, int start = 0);


 void check_lighter_darker(QString& text);

 void check_text_macro(QString& text, int start = 0);

 void check_text_macro(QString& text, int start_start, int start_end)
 {
  for(int ss = start_start; ss <= start_end; ++ss)
  {
   check_text_macro(text, ss);
  }
 }

 QMap<s4, QPair<void*, void*>> carried_items_forward_;
 QMap<s4, QPair<void*, void*>> carried_items_backward_;

 QVector<DHAX_Video_Annotation*> latex_annotation_group_;

 void parse_latex_annotation(DHAX_Video_Annotation& dva, QString text);

 void update_template_text(const QVector<QPair<QString, QString>>& substitutions);
 void prepare_template_text();

public:

 DHAX_Video_Annotation_Set();


 ACCESSORS(QColor ,circled_text_default_background_color)
 ACCESSORS(QColor ,circled_text_default_foreground_color)
 ACCESSORS(QColor ,circled_text_default_outline_color)

 ACCESSORS(r4 ,circled_text_default_font_size)
 ACCESSORS(u1 ,circled_text_default_width)
 ACCESSORS(u1 ,circled_text_default_border)

 ACCESSORS(QSizeF ,smaller_video_size)
 ACCESSORS(QSizeF ,larger_video_size)

 ACCESSORS(s2 ,smaller_size_x_translation)
 ACCESSORS(s2 ,smaller_size_y_translation)

 ACCESSORS(s2 ,larger_size_x_translation)
 ACCESSORS(s2 ,larger_size_y_translation)

 ACCESSORS(r8 ,sizes_ratio_x)
 ACCESSORS(r8 ,sizes_ratio_y)


 ACCESSORS(r8 ,sizes_ratio_x_adjustment)
 ACCESSORS(r8 ,sizes_ratio_y_adjustment)

 ACCESSORS(DHAX_Video_Annotation* ,current_pause_annotation)
 ACCESSORS(QString* ,template_file)

 void compile_latex(QSizeF sz); //QPair<u4, u4> dpis);

 QPair<void*, void*> get_carried_item_at_frame(s4 count)
 {
  return carried_items_backward_.value(count);
 }

 QSet<DHAX_Video_Annotation*> get_anchored_ref_annotations(DHAX_Video_Annotation* ref)
 {
  return anchored_ref_annotations_.value(ref);
 }

 QSet<DHAX_Video_Annotation*> get_current_anchored_ref_annotations()
 {
  return get_anchored_ref_annotations(current_pause_annotation_);
 }

 DHAX_Video_Annotation_Set* reinit_and_delete();

 void check_ratios()
 {
  sizes_ratio_x_ = larger_video_size_.width() / smaller_video_size_.width();
  sizes_ratio_y_ = larger_video_size_.height() / smaller_video_size_.height();
 }


 DHAX_Video_Annotation* get_annotation_by_start_frame(u4 key);

 QPair<void*, void*> get_data_by_end_frame(u4 key);
 void set_end_frame_data(u4 key, void* data1, void* data2);
 void set_end_frame_data(u4 key, DHAX_Video_Annotation& dva);

 void load_sample_annotations();

 void load_annotation(const DHAX_Video_Annotation& dva,
   QVector<DHAX_Video_Annotation*>* group = nullptr);

 void load_annotation_file(QString file_path);
 void load_annotation_template_file();
 void update_template_text(QString file_path);
 void clear_scene_data();
 void clear_end_frame_data();
 void clear_scene_and_end_frame_data();


 void read_ntxh_hypernode(NTXH_Graph& g, hypernode_type* h);

 void parse_circled_text_default_hypernode(NTXH_Graph& g, hypernode_type* h);
 void parse_circled_text_annotation_hypernode(NTXH_Graph& g, hypernode_type* h);
 void parse_pause_annotation_hypernode(NTXH_Graph& g, hypernode_type* h);
 void parse_text_annotation_hypernode(NTXH_Graph& g, hypernode_type* h);
 void parse_shape_annotation_hypernode(NTXH_Graph& g, hypernode_type* h);
 void parse_annotation_settings_hypernode(NTXH_Graph& g, hypernode_type* h);
 void parse_graphic_annotation_hypernode(NTXH_Graph& g, hypernode_type* h);

};

#endif //DHAX_VIDEO_ANNOTATION_SET__H
