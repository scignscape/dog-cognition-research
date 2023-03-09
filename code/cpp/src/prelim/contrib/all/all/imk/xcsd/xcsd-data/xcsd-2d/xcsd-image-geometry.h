
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef XCSD_IMAGE_GEOMETRY__H
#define XCSD_IMAGE_GEOMETRY__H

#include "xcns.h"

#include "xcsd-sdi-structures.h"

#include "enum-macros.h"

#include <vector>


XCNS_(XCSD)

class TierBox_Location
{
 rc2s rc_;
 //u1 tier_ring_;
 u4 mch_code_;

public:

 explicit TierBox_Location(rc2s rc) : rc_(rc), mch_code_(0) {}

 ACCESSORS(u4 ,mch_code)
 ACCESSORS(rc2s ,rc)

 void set_mch_code(pr2s mch);
 pr2s get_mch_code() const;
 prr2 get_mch_code_normalized(//u1 size_even_odd_code,
                              u1* mask = nullptr) const;

 u1 get_mch_clock_code(u1* mask = nullptr);
 static u1 get_mch_clock_code(pr2s pr, u1* mask = nullptr);

 static void reconcile_mch_quadrant(u1 size_even_odd_code, u1 quadrant_code, u2& clk);
// static u1 get_orthogonal_quadrant_from_mch_code(u1 size_even_odd_code, u1 quadrant_code, prr2 mch_code);


 pr2s mch_distance_from(const TierBox_Location& rhs);

 s2 r() const { return rc_.r; }
 s2 c() const { return rc_.c; }

 bool is_full_tier()
 {
  return rc_.is_nonnegative();
 }

};


class XCSD_Image_Geometry
{
public:

 enum class HVD_Options {  Horizontal, Vertical, Diagonal,
   Horizontal_Positive, Horizontal_Negative,
   Vertical_Positive, Vertical_Negative,
   Diagonal_0, Diagonal_1, Diagonal_2, Diagonal_3
          };

 enum class TierGrid_Preferances {
   N_A = 0,
   Even_H = 1,
   Even_V = 16,
   Even = 17,
   Odd_H = 2,
   Odd_V = 32,
   Odd = 34,
   Maximize_Outer_Tiers_H = 4,
   Maximize_Outer_Tiers_V = 64,
   Maximize_Outer_Tiers = 68,
   Minimize_Outer_Tiers_H = 8,
   Minimize_Outer_Tiers_V = 128,
   Minimize_Outer_Tiers = 136,

   Even_H_Even_V = Even_H | Even_V,
   Even_H_Odd_V = Even_H | Odd_V,
   Odd_H_Even_V = Odd_H | Even_V,
   Odd_H_Odd_V = Odd_V | Odd_H,
 };

 ENUM_FLAGS_OP_MACROS(TierGrid_Preferances)

 enum class Outer_Ring_Area_Flags {
   N_A = 0, Normal_Landscape, Normal_Portrait,
   Top_Left_Corner_Landscape, Top_Left_Corner_Portrait,
   Top_Right_Corner_Landscape, Top_Right_Corner_Portrait,
   Bottom_Left_Corner_Landscape, Bottom_Left_Corner_Portrait,
   Bottom_Right_Corner_Landscape, Bottom_Right_Corner_Portrait,
 };

 struct Outer_Ring_Positions {
  enum class Landscape : u1 {
    Center_Left, Top_Left, Bottom_Left, Top_Left_Corner, Bottom_Left_Corner,
    Center_Right, Top_Right, Bottom_Right, Top_Right_Corner, Bottom_Right_Corner,

    Top_Center, Top_Left_Top, Top_Right_Top,
    Bottom_Center, Bottom_Left_Bottom, Bottom_Right_Bottom,
  };
//  ENUM_FLAGS_OP_MACROS(Landscape)

  enum class Portrait : u1 {
    Top_Center, Top_Left_Top, Top_Right_Top, Top_Left_Corner, Top_Right_Corner,
    Bottom_Center, Bottom_Left_Bottom, Bottom_Right_Bottom, Bottom_Left_Corner, Bottom_Right_Corner,

    Center_Left, Top_Left, Bottom_Left,
    Center_Right, Top_Right, Bottom_Right,
  };
//  ENUM_FLAGS_OP_MACROS(Portrait)

  se2 index_pairs[16];
  u4 offsets[16];
  u4 total_offset;

  Outer_Ring_Positions() : index_pairs{ {0,0} },
    //{0,0}, {0,0}, {0,0}, {0,0}, {0,0},
    //{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} },
    offsets {0}, total_offset (0) {}

  u4 offset_for(Landscape lpos) const { return offsets[(u1)lpos]; }
  u4 offset_for(Portrait ppos) const { return offsets[(u1)ppos]; }

  u4 offset_for_area_index(u1 index) const { return offsets[index]; }

 };

 struct Size_Even_Odd_Info {
  u1 size_even_odd_code;
  u1 v_center_adjustment;
  u1 h_center_adjustment;
  s1 v_center_area_threshold_adjustment;
  s1 h_center_area_threshold_adjustment;
  u1 full_ortho_cycle_size;
  u1 margin_ortho_cycle_size;

  void landscape();
  void portrait();

  Size_Even_Odd_Info(u1 code)
  {
   size_even_odd_code = code;
   v_center_adjustment = 1 - (size_even_odd_code % 2); // 1 extra center row
   h_center_adjustment = 1 - ((size_even_odd_code >> 1) % 2); // 1 extra center column

   full_ortho_cycle_size = 4 + 2 * v_center_adjustment + 2 * h_center_adjustment;
   v_center_area_threshold_adjustment = h_center_area_threshold_adjustment = margin_ortho_cycle_size = 0;
  }
 };

 struct MCH_Info {
   u2 tier_ring;
   u2 inner_pushout;
   u1 compressed_clock_index;
   u1 full_clock_index;
   u1 clock_index_adjustment;
   u4 area_threshold;
   u4 area_threshold_adjustment;
   u4 full_tier_index;
   u1 margin_code;
   u2 margin_gap;
   u2 intra_tier_ring_index;

   MCH_Info(){}

   MCH_Info(const prr2& mch, const prr2& margin_info, u2 lesser_side,
     Size_Even_Odd_Info& size_even_odd_info, u1 quadrant_code);

   static u1 get_compressed_clock_index(u1 clk, u1 size_even_odd_code, u1 quadrant_code);

   u1 get_clock_index_to_direction() const
   {
    if(full_clock_index == 0)
      return 0;

    u1 adj = (full_clock_index + 2) % 24;
    u1 mod = adj % 6;
    u1 div = adj / 6;

    if(mod == 0)
      return 2 * ((div + 3) % 4) + 2; // figuring +3%4 is like --%4 without sign issues
      //return 2 * (div? --div: 3) + 2;

    return 2 * div + 1;
   }
 };

 struct Gridline {
   HVD_Options hvd;
   u2 tier_index;
   u2 ground_index;
 };

 struct Grid_TierBox {
   TierBox_Location loc;
   xy2 ground_center;
   xy2 top_left();
   xy2 top_right();
   xy2 bottom_left();
   xy2 bottom_right();
 };

 struct Iteration_Environment {
   Size_Even_Odd_Info size_even_odd_info;

   Iteration_Environment(u1 size_even_odd_code);
 };

private:

 wh2 total_size_;

 wh2 overall_tier_counts_;
 wh2 full_tier_counts_;

 lr2 horizontal_outer_sizes_;
 tb2 vertical_outer_sizes_;

 u4 tierbox_count_;

 TierGrid_Preferances actual_tiergrid_setting_;

 std::vector<TierBox_Location> directed_centers_;

 Outer_Ring_Positions outer_ring_positions_;

 void reconcile_overall_tier_counts();
 void reconcile_actual_tiergrid_setting();
 void init_directed_centers();

//? s1 _for_each_central_tierbox(std::function<s1(XCSD_TierBox*)> fn);

 s1 _for_each_full_tierbox(rc2 top_left, rc2 bottom_right, std::function<s1(Grid_TierBox&)> fn);
 s1 _for_each_full_tierbox(std::function<s1(Grid_TierBox&)> fn);

 s1 _for_each_outer_ring_area(std::function<s1(u1, Outer_Ring_Area_Flags)> fn);

public:

 XCSD_Image_Geometry();

 ACCESSORS(wh2 ,total_size)
 ACCESSORS(wh2 ,overall_tier_counts)
 ACCESSORS(wh2 ,full_tier_counts)
 ACCESSORS(lr2 ,horizontal_outer_sizes)
 ACCESSORS(tb2 ,vertical_outer_sizes)

 ACCESSORS__CONST_RGET(std::vector<TierBox_Location> ,directed_centers)

 ACCESSORS__CONST_RGET(Outer_Ring_Positions ,outer_ring_positions)

 Iteration_Environment formulate_iteration_environment();

 std::vector<TierBox_Location> get_directed_centers();

 void init_outer_ring_positions();
 void init_outer_ring_position_array();
 void init_outer_ring_offset_array();


 u2 get_outer_ring_area_size(Outer_Ring_Positions::Landscape l_area);
 u2 get_outer_ring_area_size(Outer_Ring_Positions::Portrait p_area);

 u2 get_outer_ring_position_start(Outer_Ring_Positions::Landscape lpos);
 u2 get_outer_ring_position_start(Outer_Ring_Positions::Portrait ppos);
 u2 get_outer_ring_position_end(Outer_Ring_Positions::Landscape lpos);
 u2 get_outer_ring_position_end(Outer_Ring_Positions::Portrait ppos);

 wh2 get_outer_ring_rect_wh_for(Outer_Ring_Area_Flags area_flags,
   u1 index, QPoint* qpoint = nullptr);

 wh2 get_secondary_outer_ring_rect_wh_for(Outer_Ring_Area_Flags area_flags,
   u1 index, QPoint* qpoint = nullptr);

 static constexpr u1 tierbox_width = 27;

 xy4 get_tierbox_scanline_top_left(Grid_TierBox& gtb);

//  u2 rect_width_for(Outer_Ring_Area_Flags area_flags, Portrait ppos);

 u4 get_total_full_tierbox_area();

 static u2 sdi_index_to_ground_offset(const ab1& sdi);
 static u2 sdi_index_to_ground_offset(s1 sdi);
 static u2 ground_offset_coords_to_ground_offset(const go_xy1& coords);

 static ab1 ground_offset_coords_to_sdi_coords(const go_xy1& coords);
 static abg1 ground_offset_coords_to_sdi3_coords(const go_xy1& coords);


 static u2 ground_offset_coords_to_sdi3(const go_xy1& coords);
 static u2 ground_offset_to_sdi3(u2 index);

 static go_xy1 ground_offset_to_ground_offset_coords(u2 index);

 u1 get_size_even_odd_code();

 prr2 get_margin_info(const TierBox_Location& loc, u1 quadrant_code);

 void for_each_horizontal_gridline(std::function<void(Gridline&)> fn);
 void for_each_vertical_gridline(std::function<void(Gridline&)> fn);

 inline s1 for_each_full_tierbox_(std::function<s1(Grid_TierBox&)> fn)
 {
  return _for_each_full_tierbox(fn);
 }
 void for_each_full_tierbox(std::function<void(Grid_TierBox&)> fn);

 inline s1 for_each_full_tierbox_(rc2 top_left, rc2 bottom_right,
   std::function<s1(Grid_TierBox&)> fn)
 {
  return _for_each_full_tierbox(top_left, bottom_right, fn);
 }
 void for_each_full_tierbox(rc2 top_left, rc2 bottom_right,
   std::function<void(Grid_TierBox&)> fn);


// for_each_full_tierbox(rc2 top_left, rc2 bottom_right,

 inline s1 for_each_outer_ring_area_(std::function<s1(u1, Outer_Ring_Area_Flags)> fn)
 {
  return _for_each_outer_ring_area(fn);
 }
 void for_each_outer_ring_area(std::function<void(u1, Outer_Ring_Area_Flags)> fn);



 TierBox_Location get_tierbox_location_from_ground_position(u2 x, u2 y);

 TierBox_Location get_directed_center(TierBox_Location& tbl);

 void calculate_mch_code(TierBox_Location& tbl);
 void _calculate_mch_code_Full(TierBox_Location& tbl);

 void set_total_size(u2 w, u2 h)
 {
  set_total_size({w, h});
 }

 static lmr2 split_lmr(u2 size, u1 box_width, TierGrid_Preferances pref);

 static tmb2 split_tmb(u2 size, u1 box_width, TierGrid_Preferances pref)
 {
  return split_lmr(size, box_width, pref)._to<tmb2>();
 }

 void init_tier_counts(TierGrid_Preferances pref);
 void init_tierboxes();

 void draw_tier_summary(QString path, QString path1,
   r8 magnification, u1 circle_radius);

 u4 get_tierbox_index(const Grid_TierBox& gtb,
   Size_Even_Odd_Info size_even_odd_info, MCH_Info* mchi);
};


_XCNS(XCSD)

#endif // XCSD_IMAGE_GEOMETRY__H

