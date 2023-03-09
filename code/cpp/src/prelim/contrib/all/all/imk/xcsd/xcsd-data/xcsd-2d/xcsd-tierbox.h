
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef XCSD_TIERBOX__H
#define XCSD_TIERBOX__H


#include "xcsd-1d/_vec1d.h"

#include "xcsd-1d/vec1d.h"
#include "xcsd-1d/arr1d.h"

#include "xcsd-sdi-structures.h"

#include <QImage>

#include <set>

#include "accessors.h"

XCNS_(XCSD)

//class XCSD_XPixel;

class XCSD_Image;

struct Box3x3_8bytepx
{
 n8 color_average;
 Box3x3_8bytepx();
};

struct Box9x9_8bytepx
{
 n8 color_average;
 Vec1d<Box3x3_8bytepx> vec_3x3;
 Box9x9_8bytepx();
};

class XCSD_TierBox
{
// u2 pixel_bytelength_;

 u2 non_full_;
 Vec1d<Box9x9_8bytepx> box9x9_;

 u4 full_tier_index_;

 rc2 matrix_position_;

 pr2s mch_code_;

 u4 pixel_data_ground_offset_;

 u2 tier_ring_;
 u2 inner_pushout_;
 u1 compressed_clock_index_;
 u1 full_clock_index_;
 u2 intra_tier_ring_index_;

 n8 reference_color_;
 n8 color_average_;

 xy4 global_top_left_;

 //s2 checked_average_codes_ [3];
 std::set<u1> checked_average_codes_;

public:

 XCSD_TierBox(rc2 matrix_position);

 ACCESSORS__DECLARE(u2 ,non_full_h)
 ACCESSORS__DECLARE(u2 ,non_full_v)

 ACCESSORS__DECLARE(bool ,non_full_up)
 ACCESSORS__DECLARE(bool ,non_full_left)

 ACCESSORS(u4 ,full_tier_index)

 ACCESSORS(rc2 ,matrix_position)
 ACCESSORS(pr2s ,mch_code)

 ACCESSORS(u4 ,pixel_data_ground_offset)

 ACCESSORS(u2 ,tier_ring)
 ACCESSORS(u2 ,inner_pushout)
 ACCESSORS(u1 ,compressed_clock_index)
 ACCESSORS(u1 ,full_clock_index)
 ACCESSORS(u2 ,intra_tier_ring_index)

 ACCESSORS(n8 ,reference_color)
 ACCESSORS(n8 ,color_average)

 ACCESSORS(xy4 ,global_top_left)

 union _inner_box {
   Box3x3_8bytepx* _3x3;
   Box9x9_8bytepx* _9x9;
   XCSD_TierBox* _this;
 };

 typedef Box3x3_8bytepx _inner_box_3x3;
 typedef Box9x9_8bytepx _inner_box_9x9;

 _inner_box_3x3* get_3x3_box(s1 ab_s1);
 _inner_box_9x9* get_9x9_box(s1 a_s1);

 rc2 get_matrix_index_position()
 {
  return matrix_position_ + 1;
 }

 rc2 get_grid_position()
 {
  return matrix_position_ - 1;
 }

 QString grid_position_string()
 {
  return QString("%1-%2").arg(get_grid_position().r).arg(get_grid_position().c);
 }

 QString matrix_position_string()
 {
  return QString("%1-%2").arg(matrix_position_.r).arg(matrix_position_.c);
 }

 void set_non_full_up() { set_non_full_up(true); }
 void set_non_full_left() { set_non_full_left(true); }

 void init_boxes();

 _inner_box get_inner_box(s1 index);

 static u2 get_scanline_offset_for_inner_top_left(s1 index);
 static u2 get_scanline_offset_for_inner_center(s1 index);

 static u2 get_ground_offset_for_inner_top_left(s1 index);
 static u2 get_ground_offset_for_inner_center(s1 index);

 static u2 get_ground_offset_for_tierbox_center()
 {
  static u2 result = get_ground_offset_for_inner_center(55);
  return result;
 }

 void check_calculate_pixel_averages_1byte(u1 start_byte, u1 end_byte,
   XCSD_Image* image, n8* reset = nullptr);

 void check_calculate_pixel_averages_1byte_level1(u1 start_byte, u1 end_byte,
   XCSD_Image* image, n8* reset = nullptr);

 void check_calculate_pixel_averages_1byte_level2(u1 start_byte, u1 end_byte,
   XCSD_Image* image, n8* reset = nullptr);

 void check_calculate_pixel_averages_1byte_level3(u1 start_byte, u1 end_byte,
   XCSD_Image* image, n8* reset = nullptr);


 u2 get_ground_offset_for_tierbox_center(u2 tierbox_column_count, u1 tierbox_width)
 {
  return get_ground_offset(tierbox_column_count, tierbox_width) + get_ground_offset_for_tierbox_center();
 }

 u2 get_ground_offset(u2 tierbox_column_count, u1 tierbox_width)
 {
  rc2 gp = get_grid_position();
  return (gp.r * tierbox_column_count + gp.c) * tierbox_width  * tierbox_width;
 }


 static u2 get_ground_offset_sdi(s2 index);

 static bool normalize_sdi_index(s2& index);
 static bool normalize_inner_index(s1& index);

//? xy1 get_inner_location_for_inner_index(s1 index);

 static xy1 get_local_ground_location_for_inner_top_left(s1 index);
 static xy1 get_local_ground_location_for_inner_center(s1 index)
 {
  return get_local_ground_location_for_inner_top_left(index) + 1;
 }

 static u2 get_scanline_offset_sdi(s2 index);
 static xy1 get_local_ground_location_sdi(s2 index);

 static xy1 get_local_ground_location_for_tierbox_center()
 {
  static xy1 result = get_local_ground_location_sdi(555);
  return result;
 }

 xy4 get_image_ground_location_sdi(s2 index)
 {
  return global_top_left_.add(get_local_ground_location_sdi(index));
 }

 xy4 get_image_ground_location_for_tierbox_center()
 {
  static xy4 offset = get_local_ground_location_sdi(555)._to<xy4>();
  return global_top_left_.add(offset);
 }

};


_XCNS(XCSD)

#endif // XCSD_IMAGE__H
