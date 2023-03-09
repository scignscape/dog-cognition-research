
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef XCSD_IMAGE__H
#define XCSD_IMAGE__H


#include "xcsd-1d/_vec1d.h"

#include "xcsd-1d/vec1d.h"

#include <QImage>

#include "accessors.h"

#include "xcsd-sdi-structures.h"
#include "xcsd-image-data.h"
#include "xcsd-image-geometry.h"

#include "mat2d.templates.h"

#include "enum-macros.h"


XCNS_(XCSD)

class Local_Histogram_Data;

struct XCSD_Outer_Ring_Info
{
 enum Position { Corner, Horizontal, Horizontal_Center, Vertical, Vertical_Center };

 Position position;
 QImage image;
 QRect rect;
 QRect extra;
};


class XCSD_Image
{
 enum class Set_Channels_Info : u2 {

  Nothing_Set = 0,  RGB24_Set = 1,
  RGBA32_Set = 2, Non_Alpha_4th_Set = 4,
  RGB555_Set = 8,
  Channel_5_Set = 16,
  Channel_6_Set = 32,
  Channels_56_Set = Channel_5_Set | Channel_6_Set,
  Channels_56_Set_Jointly = 64,

  Channels_78_Set_FB = 128,
  Channel_7_Set = 256,
  Channel_8_Set = 1024,
  Channels_78_Set = Channel_7_Set | Channel_8_Set,
  Channels_78_Set_Jointly = 2048,
 };

 ENUM_FLAGS_OP_MACROS(Set_Channels_Info)

 Set_Channels_Info set_channels_info_;

 QImage image_;

 XCSD_Image_Data data_;
 XCSD_Image_Geometry geometry_;

 rc2s initial_setup_tierbox_;

 QVector<XCSD_Outer_Ring_Info>* outer_ring_info_;

 QColor background_pole_;
 QColor foreground_pole_;

 QString ntxh_file_;

 void _init_outer_ring_pixel_data_landscaoe();
 void _init_outer_ring_pixel_data_landscaoe_sym();

 void _init_outer_ring_pixel_data_portrait();
 void _init_outer_ring_pixel_data_portrait_sym();

 void _init_outer_ring_pixel_data(u4 start_offset,
   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape area_index, se2 x_se, mm2 y_mm);

// void _init_outer_ring_pixel_data(u4 start_offset,
//   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape area_index_start,
//   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape area_index_end, se2 x_se);

// void _init_outer_ring_pixel_data(u4 start_offset,
//   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape area_index_start,
//   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape area_index_end, se2 x_se, mm2 y_mm);

 void _init_outer_ring_pixel_data(u4 start_offset,
   se1 area_index_se, pr4 outside_xareas, pr1 outside);

 void _init_outer_ring_pixel_data(u4 start_offset,
   se1 area_index_se);

 void _init_outer_ring_pixel_data(u4 start_offset,
   se1 area_index_se, pr4 outside_xareas, mm2 y_mm);

 void _init_outer_ring_pixel_data(u4 start_offset,
   se1 area_index_se, pr4 outside_xareas, pr1 outside, mm2 y_mm, u1 index_gap = 1, u2 x_ses [4] = nullptr);

 void _init_outer_ring_pixel_data_portrait(u4 start_offset,
   se1 area_index_se, pr4 outside_xareas, pr1 outside, mm2 y_mm, u1 index_gap = 1, u2 x_ses [4] = nullptr);


 void _init_outer_ring_pixel_data(QRgb* scanline,
   u4 mark_offset, u4 start_offset, se2 x_se);


 void _init_outer_ring_pixel_data_portrait(u4 start_offset,
   se1 area_index_se);

 void _init_outer_ring_pixel_data_portrait(u4 start_offset,
   se1 area_index_se, pr4 outside_xareas, pr1 outside);

 void _init_outer_ring_pixel_data_portrait(u4 start_offset,
   se1 area_index_se, pr4 outside_xareas, mm2 y_mm);


public:

 XCSD_Image();

 ACCESSORS__RGET(QImage ,image)
 ACCESSORS__RGET(XCSD_Image_Geometry ,geometry)

 ACCESSORS(QVector<XCSD_Outer_Ring_Info>* ,outer_ring_info)

 ACCESSORS(QColor ,background_pole)
 ACCESSORS(QColor ,foreground_pole)

 ACCESSORS(QString ,ntxh_file)


// void autoset_fb_poles(u1 center = 30, QPair<u1, u1> top = {4, 4},
//   QPair<u1, u1> bottom = {4, 4}, QPair<u1, u1> left = {0, 0}, QPair<u1, u1> right = {0, 0});

 void autoset_fb_poles(u1 center, QPair<u1, u1> tblr [4]); //{4, 4}, {0,0}, {0,0}, {0,0}});

 void autoset_fb_poles(u1 center = 30)
 {
  static QPair<u1, u1> defaults [4] {{8, (u1)-1}, {0,0}, {0,0}, {0,0}};
  autoset_fb_poles(center, defaults);
 }
 //{4, 4}, {0,0}, {0,0}, {0,0}});

 enum Save_Mode : u1 {
   Save_QRgb, Save_Palette, Save_FB, Save_FG, Save_BG,
   Save_FB_One_Channel,

   Fade_To_White = 32,
   Tier_Blur_3 = 64, Tier_Blur_9 = 128, Tier_Blur_27 = 192
 };

 ENUM_FLAGS_OP_MACROS(Save_Mode)

 QPair<QColor, QColor> get_fb_poles()
 {
  return { background_pole_, foreground_pole_ };
 }

 static QColor pixel_number_to_qcolor(n8 pixel);
 static QColor pixel_number_fb_to_qcolor(n8 pixel, Save_Mode save_mode);
 QColor pixel_number_palette_to_qcolor(n8 pixel);

 static QRgb pixel_number_to_qrgba(n8 pixel);
 static QRgb pixel_number_to_qrgb(n8 pixel);
 static QRgb pixel_number_fb_to_qrgb(n8 pixel, Save_Mode save_mode);
 QRgb pixel_number_palette_to_qrgb(n8 pixel);

 static n8 qrgb_to_pixel_number(QRgb rgb);

 XCSD_TierBox* get_tierbox_at_ground_position(u2 x, u2 y);

 rc2 get_tierbox_at_ground_position_RC2(u2 x, u2 y);

 SDI_Position get_sdi_at_ground_position(u2 x, u2 y);

 void load_image(QString path, QString* ntxh_file = nullptr);
 void load_image_all(QString path, QString* ntxh_file = nullptr);

 static constexpr u1 tierbox_width = 27;

 //get_pixel_vector(SDI_Position )

 void image_tierbox_to_sdi_pixel_map(const QImage& ci, std::map<s1, std::vector<n8>>& result);

 void init_outer_ring_pixel_data();

 u4 data_tierbox_to_sdi_pixel_map(u4 tierbox_index,
   std::map<s1, std::pair<u2, std::vector<n8>>>& result);

 void tierbox_to_qimage(XCSD_Image_Geometry::Grid_TierBox& gtb, QImage& target,
   Save_Mode save_mode,
   XCSD_Image_Geometry::Iteration_Environment ienv,
   u4* data_index, n8** data_start,
   XCSD_Image_Geometry::MCH_Info* mchi,
   QString info_folder); // = {});

 wh2 get_wh()
 {
  return {(u2)image_.width(), (u2)image_.height()};
 }

 void init_tier_counts(XCSD_Image_Geometry::TierGrid_Preferances pref);

 void init_geometry();
 void init_tierboxes();

 void init_pixel_data(QString info_folder = {});

 void calculate_pixel_averages_1byte(u1 start, u1 end, n8* reset = nullptr);

 void get_255_palette(QVector<QColor>& vec);

 void save_full_tier_image(QString path, Save_Mode save_mode,
    QString info_folder = {},
   std::function<void(QImage&, XCSD_Image_Geometry::Grid_TierBox&,
     XCSD_Image_Geometry::Iteration_Environment, u4, n8*,
     const XCSD_Image_Geometry::MCH_Info&, QString, u1)> cb = nullptr,
   std::function<void(QImage&, s1)> ocb = nullptr);

 static QString stringify_qcolor(const QColor& qc)
 {
  return QString("%1:%2:%3;%4").arg(qc.red()).arg(qc.green()).arg(qc.blue()).arg(qc.alpha());
 }

 void draw_tierboxes_to_folder(QString path,
   Mat2d<Vec1d<QString>>* paths = nullptr);

 void init_outer_ring_info();

 u4 tierbox_index_to_full_tier_index(rc2 rc);

 QVector<Local_Histogram_Data>* calculate_local_histograms(); //QString path_template);
 void set_individual_pixel_local_histogram_channels(n8& pixel);
 void set_local_histograms_channels();
 void check_set_local_histograms_channels()
 {
  if( (set_channels_info_ & Set_Channels_Info::RGB555_Set) == 0 )
    set_local_histograms_channels();
 }

 void init_local_histogram_vector(QVector<Local_Histogram_Data>& result);
 void save_local_histogram_vector_to_folder(const QVector<Local_Histogram_Data>& data, QString path_template);

 void calculate_tierbox_histogram(XCSD_TierBox* tbox, Local_Histogram_Data& result);
 void calculate_tierbox_histogram(u4 start_offset, Local_Histogram_Data& result);

 static QVector<s2> rgb555_to_hsv(u2 rgb555);
 static QColor rgb555_to_qcolor(u2 rgb555);

 static prr1 rgb555_color_distance(clrs2 colors);
 static prr1 rgb555_color_distance_expanded(clrs2 colors);
 static prr1 rgb555_to_prr(u2 rgb555);
 static prr1 rgb_to_prr(u4 rgb);
 static prr1 qcolor_to_prr(const QColor& clr);
 static u2 qcolor_to_rgb555(const QColor& clr);
 static u2 rgb_to_rgb555(u4 rgb);

 static prr1 rgb555_888_color_distance(u2 rgb555, u4 rgb);

 static prr1 rgb888_qcolor_distance(u4 rgb, const QColor& clr);
 static fb1 collapse_fb_distances(const prr1& dist1, const prr1& dist2);

 QSize show_255_palette(QString path,
   QString sorted_path, u1 box_width = 50, u1 padline_width = 8);


 void save_fb_gradient_trimap(fb2 poles, QString file_path,
   QString folder);

 void save_fb_gradient_trimap(QString file_path, QString folder);

 void set_fb_gradient_trimap_to_channels(fb2 poles);
 void check_set_fb_gradient_trimap_to_channels();

 void save_channel_to_red_black_image(u1 channel_number, QString file_path);
 void save_channel_to_red_white_image(u1 channel_number, QString file_path);

 void save_channel_to_blue_black_image(u1 channel_number, QString file_path);
 void save_channel_to_blue_white_image(u1 channel_number, QString file_path);

 void save_foreground_distance_channel_to_red_black_image(QString file_path);

 void save_foreground_distance_channel_to_red_white_image(QString file_path);

 void save_background_distance_channel_to_blue_black_image(QString file_path);

 void save_background_distance_channel_to_blue_white_image(QString file_path);

 void save_fb_one_channel_image(QString file_path);

 void find_ntxh_file(QString file_path, u1 maybe_up = 2);


 XCSD_TierBox* get_tierbox_from_grid_tierbox(const XCSD_Image_Geometry::Grid_TierBox& gtb);
};


_XCNS(XCSD)

#endif // XCSD_IMAGE__H
