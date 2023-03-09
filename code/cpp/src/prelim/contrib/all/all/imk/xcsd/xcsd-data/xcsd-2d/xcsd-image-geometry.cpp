
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "xcsd-image-geometry.h"

#include "xcsd-tierbox.h"

#include <QPainter>

#include <QDebug>

#include <deque>

USING_XCNS(XCSD)

XCSD_Image_Geometry::XCSD_Image_Geometry()
  :  total_size_({0,0}),
     overall_tier_counts_({0,0}),
     full_tier_counts_({0,0}),
     horizontal_outer_sizes_({0,0}),
     vertical_outer_sizes_({0,0}),
     tierbox_count_(0),
     actual_tiergrid_setting_(TierGrid_Preferances::N_A)
{

}


pr2s TierBox_Location::mch_distance_from(const TierBox_Location& rhs)
{
 rc2s raw = rc_.minus(rhs.rc_);

 pr2s raw_sp = raw.spaceship_mask()._to<pr2s>();
 raw_sp.add(raw.zeros_mask());
 rc2 raw_abs = raw.abs();
 pr2 chebychev = raw_abs.greater_which()._to<pr2>();
 u2 manhattan = raw_abs.inner_sum();
 pr2s result = {(s2)manhattan, (s2)(manhattan - chebychev.first)};
 if(chebychev.second == 1) // && !raw.has_zero())
 {
  result._Transpose();
  if(raw.r != 0)
    raw_sp._Transpose();
 }
 result.multiply(raw_sp);
// if(chebychev.second == 0 && !raw.is_coequal())
//   result._Transpose();
 return result;
}


void XCSD_Image_Geometry::_calculate_mch_code_Full(TierBox_Location& tbl)
{
// u2 distance_from_edge = std::max({(u2) tbl.r(),
//   (u2) tbl.c(), (u2) (full_tier_counts_.height - tbl.r() - 1),
//   (u2) (full_tier_counts_.width - tbl.c() - 1)});

 //u4 mch_code = 0;

 TierBox_Location center = get_directed_center(tbl);
 pr2s pr = tbl.mch_distance_from(center);
 tbl.set_mch_code(pr);
}

// if(distance_from_edge == tbl.c())
//   tier_ring = (full_tier_counts_.width / 2) - distance_from_edge;
// else if(distance_from_edge == tbl.r())
//   tier_ring = (full_tier_counts_.height / 2) - distance_from_edge;
// else if(distance_from_edge == full_tier_counts_.height - tbl.r() - 1)
//   tier_ring = distance_from_edge - (full_tier_counts_.width / 2);
// else  tier_ring = distance_from_edge - (full_tier_counts_.height / 2);

void XCSD_Image_Geometry::init_directed_centers()
{
 rc2s first = (full_tier_counts_/2)._transposed()._to<rc2s>();
 std::deque<rc2s> deq {{first}};
 //directed_centers_.push_back(TierBox_Location(first));
 switch (actual_tiergrid_setting_)
 {
 case TierGrid_Preferances::Odd_H_Odd_V:
   // // simplest case because there's only one center
   break;
 case TierGrid_Preferances::Even_H_Odd_V:
   // // also the one to the left
   deq.push_front(first.minus({0, 1}));
   break;

 case TierGrid_Preferances::Odd_H_Even_V:
   // // also the one to the left
   deq.push_front(first.minus({1, 0}));
   break;

 case TierGrid_Preferances::Even_H_Even_V:
   // // also the one to the left
   deq.push_front(first.minus({0, 1}));
   deq.push_front(first.minus({1, 0}));
   deq.push_front(first.minus({1, 1}));
   break;

 default: break;
 }

 std::transform(deq.begin(), deq.end(), std::back_inserter(directed_centers_),
   [](rc2s rc)
 {
  return TierBox_Location(rc);
 });
}

TierBox_Location XCSD_Image_Geometry::get_directed_center(TierBox_Location& tbl)
{
 //rc2s result = (full_tier_counts_/2).transposed()._to<rc2s>();
 switch (actual_tiergrid_setting_)
 {
 case TierGrid_Preferances::Odd_H_Odd_V:
   // // simplest case because there's only one center
  return directed_centers_[0];

 case TierGrid_Preferances::Odd_H_Even_V:
  if(tbl.r() < (full_tier_counts_.height / 2))
    return directed_centers_[0];
  return directed_centers_[1];

 case TierGrid_Preferances::Even_H_Odd_V:
  if(tbl.c() < (full_tier_counts_.width / 2))
    return directed_centers_[0];
  return directed_centers_[1];

 case TierGrid_Preferances::Even_H_Even_V:
  if(tbl.rc() < (full_tier_counts_ / 2)._transposed())
    return directed_centers_[0];
  if(tbl.rc() >= (full_tier_counts_ / 2)._transposed())
    return directed_centers_[3];
  if(tbl.c() < (full_tier_counts_.width / 2))
    return directed_centers_[2];
  return directed_centers_[1];

 default: break;
 }
}

void XCSD_Image_Geometry::init_outer_ring_positions()
{
 init_outer_ring_position_array();
 init_outer_ring_offset_array();
}

//case Outer_Ring_Positions::Landscape::Top_Left_Corner:
//case Outer_Ring_Positions::Landscape::Top_Left:
//case Outer_Ring_Positions::Landscape::Center_Left:
//case Outer_Ring_Positions::Landscape::Bottom_Left:
//case Outer_Ring_Positions::Landscape::Bottom_Left_Corner:

//case Outer_Ring_Positions::Landscape::Top_Right_Corner:
//case Outer_Ring_Positions::Landscape::Top_Right:
//case Outer_Ring_Positions::Landscape::Center_Right:
//case Outer_Ring_Positions::Landscape::Bottom_Right:
//case Outer_Ring_Positions::Landscape::Bottom_Right_Corner:

//case Outer_Ring_Positions::Landscape::Top_Left_Top:
//case Outer_Ring_Positions::Landscape::Top_Center:
//case Outer_Ring_Positions::Landscape::Top_Right_Top:

//case Outer_Ring_Positions::Landscape::Bottom_Left_Bottom:
//case Outer_Ring_Positions::Landscape::Bottom_Center:
//case Outer_Ring_Positions::Landscape::Bottom_Right_Bottom:


u2 XCSD_Image_Geometry::get_outer_ring_area_size(Outer_Ring_Positions::Landscape l_area)
{
 // //  inner span, not inner difference ...
 switch(l_area)
 {
 case Outer_Ring_Positions::Landscape::Top_Left_Top:
 case Outer_Ring_Positions::Landscape::Top_Center:
 case Outer_Ring_Positions::Landscape::Top_Right_Top:
  return outer_ring_positions_.index_pairs[(u1)l_area].inner_span()
    * vertical_outer_sizes_.top;

 case Outer_Ring_Positions::Landscape::Bottom_Left_Bottom:
 case Outer_Ring_Positions::Landscape::Bottom_Center:
 case Outer_Ring_Positions::Landscape::Bottom_Right_Bottom:
  return outer_ring_positions_.index_pairs[(u1)l_area].inner_span()
    * vertical_outer_sizes_.bottom;

 case Outer_Ring_Positions::Landscape::Top_Left:
 case Outer_Ring_Positions::Landscape::Center_Left:
 case Outer_Ring_Positions::Landscape::Bottom_Left:
  return outer_ring_positions_.index_pairs[(u1)l_area].inner_span()
    * horizontal_outer_sizes_.left;

 case Outer_Ring_Positions::Landscape::Top_Right:
 case Outer_Ring_Positions::Landscape::Center_Right:
 case Outer_Ring_Positions::Landscape::Bottom_Right:
  return outer_ring_positions_.index_pairs[(u1)l_area].inner_span()
    * horizontal_outer_sizes_.right;

 case Outer_Ring_Positions::Landscape::Top_Left_Corner:
    // // starting at left  ending at top
  return ((outer_ring_positions_.index_pairs[(u1)l_area].start + 1)
    * horizontal_outer_sizes_.left) +
    ((outer_ring_positions_.index_pairs[(u1)l_area].end + 1)
    * vertical_outer_sizes_.top) -
    // //  this would be counted twice
    (horizontal_outer_sizes_.left * vertical_outer_sizes_.top);

 case Outer_Ring_Positions::Landscape::Bottom_Left_Corner:
    // // starting at left  ending at bottom
  return ((outer_ring_positions_.index_pairs[(u1)l_area].end + 1)
    * vertical_outer_sizes_.bottom) +
    ((total_size_.height - outer_ring_positions_.index_pairs[(u1)l_area].start)
    * horizontal_outer_sizes_.left) -
    // //  this would be counted twice
    (horizontal_outer_sizes_.left * vertical_outer_sizes_.bottom);

 case Outer_Ring_Positions::Landscape::Top_Right_Corner:
    // // starting at right  ending at top
  return ((total_size_.width - outer_ring_positions_.index_pairs[(u1)l_area].end)
    * vertical_outer_sizes_.top) +
    ((outer_ring_positions_.index_pairs[(u1)l_area].start + 1)
    * horizontal_outer_sizes_.right) -
    // //  this would be counted twice
    (horizontal_outer_sizes_.right * vertical_outer_sizes_.top);


 case Outer_Ring_Positions::Landscape::Bottom_Right_Corner:
    // // starting at right  ending at bottom
  return ((total_size_.width - outer_ring_positions_.index_pairs[(u1)l_area].end)
    * vertical_outer_sizes_.bottom) +
    ((total_size_.height - outer_ring_positions_.index_pairs[(u1)l_area].start)
    * horizontal_outer_sizes_.right) -
    // //  this would be counted twice
    (horizontal_outer_sizes_.right * vertical_outer_sizes_.bottom);
 }
}

u2 XCSD_Image_Geometry::get_outer_ring_area_size(Outer_Ring_Positions::Portrait p_area)
{
 // //  inner span, not inner difference ...
 switch(p_area)
 {
 case Outer_Ring_Positions::Portrait::Top_Left:
 case Outer_Ring_Positions::Portrait::Center_Left:
 case Outer_Ring_Positions::Portrait::Bottom_Left:
  return outer_ring_positions_.index_pairs[(u1)p_area].inner_span()
    * horizontal_outer_sizes_.left;

 case Outer_Ring_Positions::Portrait::Top_Right:
 case Outer_Ring_Positions::Portrait::Center_Right:
 case Outer_Ring_Positions::Portrait::Bottom_Right:
  return outer_ring_positions_.index_pairs[(u1)p_area].inner_span()
    * horizontal_outer_sizes_.right;

 case Outer_Ring_Positions::Portrait::Top_Left_Top:
 case Outer_Ring_Positions::Portrait::Top_Center:
 case Outer_Ring_Positions::Portrait::Top_Right_Top:
  return outer_ring_positions_.index_pairs[(u1)p_area].inner_span()
    * vertical_outer_sizes_.top;

 case Outer_Ring_Positions::Portrait::Bottom_Left_Bottom:
 case Outer_Ring_Positions::Portrait::Bottom_Center:
 case Outer_Ring_Positions::Portrait::Bottom_Right_Bottom:
  return outer_ring_positions_.index_pairs[(u1)p_area].inner_span()
    * vertical_outer_sizes_.bottom;

 case Outer_Ring_Positions::Portrait::Top_Left_Corner:
    // // starting at top  ending at left
  return ((outer_ring_positions_.index_pairs[(u1)p_area].start + 1)
    * vertical_outer_sizes_.top) +
    ((outer_ring_positions_.index_pairs[(u1)p_area].end + 1)
    * horizontal_outer_sizes_.left) -
    // //  this would be counted twice
    (vertical_outer_sizes_.top * horizontal_outer_sizes_.left);

 case Outer_Ring_Positions::Portrait::Top_Right_Corner:
    // // starting at top  ending at right
  return ((total_size_.width - outer_ring_positions_.index_pairs[(u1)p_area].start + 1)
    * vertical_outer_sizes_.top) +
    ((outer_ring_positions_.index_pairs[(u1)p_area].end + 1)
    * horizontal_outer_sizes_.right) -
    // //  this would be counted twice
    (horizontal_outer_sizes_.right * vertical_outer_sizes_.top);



 case Outer_Ring_Positions::Portrait::Bottom_Left_Corner:
    // // starting at bottom  ending at left
 {
  u2 aa = outer_ring_positions_.index_pairs[(u1)p_area].start + 1;
  u2 bb = total_size_.height - outer_ring_positions_.index_pairs[(u1)p_area].end;

  u2 bb_ = bb - vertical_outer_sizes_.bottom;

  u2 aaa = aa * vertical_outer_sizes_.bottom;
  u2 bbb_ = bb_ * horizontal_outer_sizes_.right;
  u2 bbb = bb_ * horizontal_outer_sizes_.left;

  u2 add = aaa + bbb;
  u2 sub = vertical_outer_sizes_.bottom * horizontal_outer_sizes_.left;
  u2 ssub = add + sub;
 }
  return ((outer_ring_positions_.index_pairs[(u1)p_area].start + 1)
    * vertical_outer_sizes_.bottom) +
    ((total_size_.height - outer_ring_positions_.index_pairs[(u1)p_area].end)
    * horizontal_outer_sizes_.left) -
    // //  this would be counted twice
    (vertical_outer_sizes_.bottom * horizontal_outer_sizes_.left);

 case Outer_Ring_Positions::Portrait::Bottom_Right_Corner:
    // // starting at bottom  ending at right
  return ((total_size_.width - outer_ring_positions_.index_pairs[(u1)p_area].start)
    * vertical_outer_sizes_.bottom) +
    ((total_size_.height - outer_ring_positions_.index_pairs[(u1)p_area].end)
    * horizontal_outer_sizes_.right) -
    // //  this would be counted twice
    (horizontal_outer_sizes_.right * vertical_outer_sizes_.bottom);
 }

}

u2 XCSD_Image_Geometry::get_outer_ring_position_start(Outer_Ring_Positions::Landscape lpos)
{
 return outer_ring_positions_.index_pairs[(u1)lpos].start;
}

u2 XCSD_Image_Geometry::get_outer_ring_position_start(Outer_Ring_Positions::Portrait ppos)
{
 return outer_ring_positions_.index_pairs[(u1)ppos].start;
}

u2 XCSD_Image_Geometry::get_outer_ring_position_end(Outer_Ring_Positions::Landscape lpos)
{
 return outer_ring_positions_.index_pairs[(u1)lpos].end;
}

u2 XCSD_Image_Geometry::get_outer_ring_position_end(Outer_Ring_Positions::Portrait ppos)
{
 return outer_ring_positions_.index_pairs[(u1)ppos].end;
}


void XCSD_Image_Geometry::init_outer_ring_offset_array()
{
 if(full_tier_counts_.is_ascending()) // w < h
 {
  u2 offset = 0;
  for(u1 i = 0; i < 16; ++i)
  {
   outer_ring_positions_.offsets[i] = offset;
   //u2 as = get_outer_ring_area_size((Outer_Ring_Positions::Portrait)i);
   offset += get_outer_ring_area_size((Outer_Ring_Positions::Portrait)i);
  }
  outer_ring_positions_.total_offset = offset;
 }
 else // w >= h
 {
  u2 offset = 0;
  for(u1 i = 0; i < 16; ++i)
  {
   outer_ring_positions_.offsets[i] = offset;
   offset += get_outer_ring_area_size((Outer_Ring_Positions::Landscape)i);
  }
  outer_ring_positions_.total_offset = offset;
 }
}


u4 XCSD_Image_Geometry::get_total_full_tierbox_area()
{
 return full_tier_counts_.area() * tierbox_width * tierbox_width;
}


void XCSD_Image_Geometry::init_outer_ring_position_array()
{
 u1 size_even_odd_code = get_size_even_odd_code();

 u1 center_width_basis = 9;
 u1 corner_width_basis = 6;

//? if( total_size_.lesser() < 800 )
 if( total_size_.lesser() < 729 )
 {
  // //   729 = 27*27; less than that, try
   //     to balance out the segments
  u1 basis = total_size_.lesser() / 27;
  if(basis < 5)
  {
   // //  maybe just don't support too-small images ..
   exit(0);
  }

  switch(basis)
  {
  case 5: center_width_basis = 1; corner_width_basis = 1; break;
  case 6: case 7:
  case 8: center_width_basis = 2; corner_width_basis = 1; break;
  case 9: case 10:
  case 11: center_width_basis = 2; corner_width_basis = 2; break;
  case 12: case 13:
  case 14: center_width_basis = 3; corner_width_basis = 2; break;
  case 15: case 16:
  case 17: center_width_basis = 4; corner_width_basis = 2; break;
  default:  center_width_basis = (basis / 3) - 2;
   corner_width_basis = 3; break;

//  case 18: case 19:
//  case 20: center_width_basis = 4; corner_width_basis = 3; break;
//  case 21: case 22:
//  case 23: center_width_basis = 5; corner_width_basis = 3; break;
//  case 24: case 25:
//  case 26: center_width_basis = 6; corner_width_basis = 3; break;
  }

//  center_width_basis = total_size_.lesser() / 100;
//  center_width_basis += (1 - (center_width_basis % 2));
//  corner_width_basis -= (9 - center_width_basis);
//  if(corner_width_basis < 2)
//    corner_width_basis = 2;
 }


 if(full_tier_counts_.is_ascending()) // w < h
 {
  // even v = 0, 2
  hv1 center_width {(u1)(center_width_basis - (size_even_odd_code / 2)),
     (u1)(center_width_basis + (size_even_odd_code % 2))};

  center_width *= 27;

  u1 corner_width = corner_width_basis * 27;

  u2 left_mark = vertical_outer_sizes_.top - 1;

  left_mark += corner_width;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Left_Corner].end = left_mark;

  ++left_mark;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Left].start = left_mark;

  u2 vgap = total_size_.height - vertical_outer_sizes_.inner_sum()
    - center_width.v - (corner_width * 2);

  u2 test = vgap + (corner_width * 2) + center_width.v + vertical_outer_sizes_.inner_sum();

  u2 vgapt = vgap / 2;
  u2 vgapb = vgapt + vertical_outer_sizes_.inner_positive_difference();

  u1 center_width_extra_v = 1 - (full_tier_counts_.height % 2);
//?  hgapr -= center_width_extra_h;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Left].end_at_plus(vgapt - 1);

  left_mark += vgapt;


  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Center_Left].start = left_mark;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Center_Left].end_at_plus(center_width.v + center_width_extra_v - 1);

  left_mark += center_width.v + center_width_extra_v;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Bottom_Left].start = left_mark;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Bottom_Left].end_at_plus(vgapb - 1);

  left_mark += vgapb;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Bottom_Left_Corner].end = left_mark;


  u2 top_mark = horizontal_outer_sizes_.left - 1;

  top_mark += corner_width;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Left_Corner].start = top_mark;

  ++top_mark;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Left_Top].start = top_mark;

  u2 hgap = total_size_.width - horizontal_outer_sizes_.inner_sum()
    - center_width.h - (corner_width * 2);

  u2 hgapl = hgap / 2;
  u2 hgapr = hgapl + horizontal_outer_sizes_.inner_positive_difference();

  u1 center_width_extra_h = 1 - (full_tier_counts_.width % 2);
//?  vgapb -= center_width_extra_v;


  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Left_Top].end_at_plus(hgapl - 1);

  top_mark += hgapl;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Center].start = top_mark;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Center].end_at_plus(center_width.h + center_width_extra_h - 1);

  top_mark += center_width.h + center_width_extra_h;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Right_Top].start = top_mark;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Right_Top].end_at_plus(hgapr - 1);

  top_mark += hgapr;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Right_Corner].start = top_mark;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Right_Corner].end =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Left_Corner].end;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Right] =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Left];

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Center_Right] =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Center_Left];

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Bottom_Right] =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Bottom_Left];

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Bottom_Left_Bottom] =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Left_Top];

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Bottom_Center] =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Center];

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Bottom_Right_Bottom] =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Right_Top];


  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Bottom_Right_Corner].start =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Right_Corner].start;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Bottom_Right_Corner].end =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Bottom_Left_Corner].end;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Bottom_Left_Corner].start =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Portrait::Top_Left_Corner].start;


 }
 else // w >= h
 {
  // even h = 0, 1
  // even v = 0, 2
//  u1 center_width_h = 6 + (size_even_odd_code / 2);
//  u1 center_width_v = 6 - (size_even_odd_code % 2);

  hv1 center_width {(u1)(center_width_basis + (size_even_odd_code / 2)),
     (u1)(center_width_basis - (size_even_odd_code % 2))};

  center_width *= 27;

  u1 corner_width = corner_width_basis * 27;

  u2 top_mark = horizontal_outer_sizes_.left - 1;

  top_mark += corner_width;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Left_Corner].end = top_mark;

  ++top_mark;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Left_Top].start = top_mark;

  u2 hgap = total_size_.width - horizontal_outer_sizes_.inner_sum()
    - center_width.h - (corner_width * 2);

  u2 hgapl = hgap / 2;
  u2 hgapr = hgapl + horizontal_outer_sizes_.inner_positive_difference();

  u1 center_width_extra_h = 1 - (full_tier_counts_.width % 2);
//?  hgapr -= center_width_extra_h;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Left_Top].end_at_plus(hgapl - 1);

  top_mark += hgapl;


  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Center].start = top_mark;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Center].end_at_plus(center_width.h + center_width_extra_h - 1);

  top_mark += center_width.h + center_width_extra_h;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Right_Top].start = top_mark;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Right_Top].end_at_plus(hgapr - 1);

  top_mark += hgapr;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Right_Corner].end = top_mark;


  u2 left_mark = vertical_outer_sizes_.top - 1;

  left_mark += corner_width;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Left_Corner].start = left_mark;

  ++left_mark;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Left].start = left_mark;

  u2 vgap = total_size_.height - vertical_outer_sizes_.inner_sum()
    - center_width.v - (corner_width * 2);

  u2 vgapt = vgap / 2;
  u2 vgapb = vgapt + vertical_outer_sizes_.inner_positive_difference();

  u1 center_width_extra_v = 1 - (full_tier_counts_.width % 2);
//?  vgapb -= center_width_extra_v;


  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Left].end_at_plus(vgapt - 1);

  left_mark += vgapt;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Center_Left].start = left_mark;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Center_Left].end_at_plus(center_width.v + center_width_extra_v - 1);

  left_mark += center_width.v + center_width_extra_v;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Bottom_Left].start = left_mark;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Bottom_Left].end_at_plus(vgapb - 1);

  left_mark += vgapb;
  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Bottom_Left_Corner].start = left_mark;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Bottom_Left_Corner].end =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Left_Corner].end;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Bottom_Left_Bottom] =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Left_Top];

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Bottom_Center] =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Center];

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Bottom_Right_Bottom] =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Right_Top];


  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Right] =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Left];

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Center_Right] =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Center_Left];

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Bottom_Right] =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Bottom_Left];


  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Bottom_Right_Corner].start =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Bottom_Left_Corner].start;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Bottom_Right_Corner].end =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Right_Corner].end;

  outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Right_Corner].start =
    outer_ring_positions_.index_pairs[(u1)Outer_Ring_Positions::
    Landscape::Top_Left_Corner].start;

  //index_pairs[]

 }
}

void XCSD_Image_Geometry::calculate_mch_code(TierBox_Location& tbl)
{
 if(tbl.is_full_tier())
   _calculate_mch_code_Full(tbl);
}


TierBox_Location XCSD_Image_Geometry::get_tierbox_location_from_ground_position(u2 x, u2 y)
{
 rc2s result {0,0};

 if(horizontal_outer_sizes_.left > 0)
 {
  if(x <= horizontal_outer_sizes_.left)
    result.c = 0;
  else
  {
   result.c = 1;
   x -= horizontal_outer_sizes_.left;
  }
 }
 x /= 27;
 result.c += x;

 if(vertical_outer_sizes_.top > 0)
 {
  if(y <= vertical_outer_sizes_.top)
    result.r = 0;
  else
  {
   result.r = 1;
   y -= vertical_outer_sizes_.top;
  }
 }
 y /= 27;
 result.r += y;

 if((horizontal_outer_sizes_.right > 0) &&
    (result.c == (overall_tier_counts_.width - 1)))
   result.c = -2;
 else if(horizontal_outer_sizes_.left > 0)
   --result.c;

 if((vertical_outer_sizes_.top > 0) &&
    (result.r == (overall_tier_counts_.height - 1)))
   result.r = -2;
 else if(vertical_outer_sizes_.top > 0)
   --result.r;

 return TierBox_Location(result);
}

lmr2 _split_lmr_even_pref(u2 size, u1 box_width)
{
 u1 dbl = box_width * 2;
 u2 main = size / dbl;
 u1 margins = size % dbl;
 u2 right = margins / 2;
 u2 left = right + (margins % 2);
 return {left, (u2) (main * 2), right};
}

lmr2 _split_lmr_odd_pref(u2 size, u1 box_width)
{
 u1 dbl = box_width * 2;
 u2 main = size / dbl;
 u1 margins = size % dbl;

 s1 adj = 0;

 if(margins > box_width)
 {
  margins -= box_width;
  adj = 1;
 }
 else if(margins < box_width)
 {
  margins += box_width;
  adj = -1;
 }
 else
   return {0, (u2) ((main * 2) + 1), 0};

 u2 right = margins / 2;
 u2 left = right + (margins % 2);
 return {left, (u2) ((main * 2) + adj), right};

}

lmr2 _split_lmr_min_pref(u2 size, u1 box_width)
{
 u1 margins = size % (box_width * 2);
 if(margins >= box_width)
  return _split_lmr_odd_pref(size, box_width);
 else
  return _split_lmr_even_pref(size, box_width);
}

lmr2 _split_lmr_max_pref(u2 size, u1 box_width)
{
 u1 margins = size % (box_width * 2);
 if(margins > box_width)
  return _split_lmr_even_pref(size, box_width);
 else
  return _split_lmr_odd_pref(size, box_width);
}

lmr2 XCSD_Image_Geometry::split_lmr(u2 size, u1 box_width, TierGrid_Preferances pref)
{
 if(pref & TierGrid_Preferances::Maximize_Outer_Tiers)
   return _split_lmr_max_pref(size, box_width);
 if(pref & TierGrid_Preferances::Minimize_Outer_Tiers)
   return _split_lmr_min_pref(size, box_width);
 if(pref & TierGrid_Preferances::Odd)
   return _split_lmr_odd_pref(size, box_width);
 return _split_lmr_even_pref(size, box_width);
}

void XCSD_Image_Geometry::reconcile_actual_tiergrid_setting()
{
 if(full_tier_counts_.width % 2)
   actual_tiergrid_setting_ |= TierGrid_Preferances::Odd_H;
 else
   actual_tiergrid_setting_ |= TierGrid_Preferances::Even_H;

 if(full_tier_counts_.height % 2)
   actual_tiergrid_setting_ |= TierGrid_Preferances::Odd_V;
 else
   actual_tiergrid_setting_ |= TierGrid_Preferances::Even_V;
}

void XCSD_Image_Geometry::reconcile_overall_tier_counts()
{
 overall_tier_counts_ = full_tier_counts_;

 if(horizontal_outer_sizes_.left > 0)
   ++overall_tier_counts_.width;
 if(horizontal_outer_sizes_.right > 0)
   ++overall_tier_counts_.width;

 if(vertical_outer_sizes_.top > 0)
   ++overall_tier_counts_.height;
 if(vertical_outer_sizes_.top > 0)
   ++overall_tier_counts_.height;
}

xy2 XCSD_Image_Geometry::Grid_TierBox::top_left()
{
 return ground_center.double_zminus(tierbox_width / 2);
}

// //  these will need an offset on the + if tierbox_width is even ...
xy2 XCSD_Image_Geometry::Grid_TierBox::top_right()
{
 return ground_center.plus_and_zminus(tierbox_width / 2);
}

xy2 XCSD_Image_Geometry::Grid_TierBox::bottom_left()
{
 return ground_center.zminus_and_plus(tierbox_width / 2);
}

xy2 XCSD_Image_Geometry::Grid_TierBox::bottom_right()
{
 return ground_center.double_plus(tierbox_width / 2);
}


void XCSD_Image_Geometry::for_each_horizontal_gridline(std::function<void(Gridline&)> fn)
{
 u1 offset = vertical_outer_sizes_.top;
 for(u2 i = 0; i <= full_tier_counts_.height; ++i)
 {
  Gridline gl {HVD_Options::Horizontal, i, (u2)((i * tierbox_width) + offset)};
  fn(gl);
 }
}

void XCSD_Image_Geometry::for_each_vertical_gridline(std::function<void(Gridline&)> fn)
{
 u1 offset = horizontal_outer_sizes_.left;
 for(u2 i = 0; i <= full_tier_counts_.width; ++i)
 {
  Gridline gl {HVD_Options::Vertical, i, (u2)((i * tierbox_width) + offset)};
  fn(gl);
 }
}

void XCSD_Image_Geometry::for_each_full_tierbox(rc2 top_left, rc2 bottom_right,
  std::function<void(Grid_TierBox&)> fn)
{
 _for_each_full_tierbox(top_left, bottom_right, [fn](Grid_TierBox& gtb) -> s1
 {
  fn(gtb);
  return 0;
 });
}

void XCSD_Image_Geometry::for_each_full_tierbox(std::function<void(Grid_TierBox&)> fn)
{
 _for_each_full_tierbox([fn](Grid_TierBox& gtb) -> s1
 {
  fn(gtb);
  return 0;
 });
}

void XCSD_Image_Geometry::for_each_outer_ring_area(std::function<void(u1, Outer_Ring_Area_Flags)> fn)
{
 _for_each_outer_ring_area([fn](u1 index, Outer_Ring_Area_Flags area_flags) -> s1
 {
  fn(index, area_flags);
  return 0;
 });
}

s1 XCSD_Image_Geometry::_for_each_outer_ring_area(std::function<s1(u1, Outer_Ring_Area_Flags)> fn)
{
 //for(u1 )
 if(full_tier_counts_.width < full_tier_counts_.height)
 {

  for(u1 index = 0; index < 16; ++index)
  {
   Outer_Ring_Area_Flags area_flags = Outer_Ring_Area_Flags::Normal_Portrait;
   if(index == (u1) Outer_Ring_Positions::Portrait::Top_Left_Corner)
     area_flags = Outer_Ring_Area_Flags::Top_Left_Corner_Portrait;
   else if(index == (u1) Outer_Ring_Positions::Portrait::Bottom_Left_Corner)
    area_flags = Outer_Ring_Area_Flags::Bottom_Left_Corner_Portrait;
   else if(index == (u1) Outer_Ring_Positions::Portrait::Top_Right_Corner)
    area_flags = Outer_Ring_Area_Flags::Top_Right_Corner_Portrait;
   else if(index == (u1) Outer_Ring_Positions::Portrait::Bottom_Right_Corner)
    area_flags = Outer_Ring_Area_Flags::Bottom_Right_Corner_Portrait;

   //return
   s1 _break = fn(index, area_flags);
   if(_break != 0)
     return _break;
  }


 }
 else //  w >= h
 {
  for(u1 index = 0; index < 16; ++index)
  {
   Outer_Ring_Area_Flags area_flags = Outer_Ring_Area_Flags::Normal_Landscape;
   if(index == (u1) Outer_Ring_Positions::Landscape::Top_Left_Corner)
     area_flags = Outer_Ring_Area_Flags::Top_Left_Corner_Landscape;
   else if(index == (u1) Outer_Ring_Positions::Landscape::Bottom_Left_Corner)
    area_flags = Outer_Ring_Area_Flags::Bottom_Left_Corner_Landscape;
   else if(index == (u1) Outer_Ring_Positions::Landscape::Top_Right_Corner)
    area_flags = Outer_Ring_Area_Flags::Top_Right_Corner_Landscape;
   else if(index == (u1) Outer_Ring_Positions::Landscape::Bottom_Right_Corner)
    area_flags = Outer_Ring_Area_Flags::Bottom_Right_Corner_Landscape;

   //return
   s1 _break = fn(index, area_flags);
   if(_break != 0)
     return _break;
  }
 }
 return 0;
}

wh2 XCSD_Image_Geometry::get_secondary_outer_ring_rect_wh_for(Outer_Ring_Area_Flags area_flags,
  u1 index, QPoint* qpoint)
{
 // //  the +1s here are because the end is part of the area, like the +1 in inner_span() ...
 switch (area_flags)
 {
 case Outer_Ring_Area_Flags::Top_Left_Corner_Landscape:
  if(qpoint)
    *qpoint = {0, vertical_outer_sizes_.top};
  return {horizontal_outer_sizes_.left,
    (u2)(outer_ring_positions_.index_pairs[index].start - vertical_outer_sizes_.top + 1)};

 case Outer_Ring_Area_Flags::Top_Left_Corner_Portrait:
  if(qpoint)
    *qpoint = {0, vertical_outer_sizes_.top};
  return {horizontal_outer_sizes_.left,
    (u2)(outer_ring_positions_.index_pairs[index].end - vertical_outer_sizes_.top + 1)};


 case Outer_Ring_Area_Flags::Bottom_Left_Corner_Landscape:
  if(qpoint)
    *qpoint = {0, total_size_.height - vertical_outer_sizes_.bottom};
  return {(u2)(outer_ring_positions_.index_pairs[index].end + 1),
    vertical_outer_sizes_.bottom};

 case Outer_Ring_Area_Flags::Bottom_Left_Corner_Portrait:
  if(qpoint)
    *qpoint = {0, total_size_.height - vertical_outer_sizes_.bottom};
  return {(u2)(outer_ring_positions_.index_pairs[index].start + 1),
    vertical_outer_sizes_.bottom};



 case Outer_Ring_Area_Flags::Top_Right_Corner_Landscape:
  if(qpoint)
    *qpoint = {total_size_.width - horizontal_outer_sizes_.right, vertical_outer_sizes_.top};
  return {horizontal_outer_sizes_.right,
    (u2)(outer_ring_positions_.index_pairs[index].start - vertical_outer_sizes_.top + 1)};

 case Outer_Ring_Area_Flags::Top_Right_Corner_Portrait:
  if(qpoint)
    *qpoint = {total_size_.width - horizontal_outer_sizes_.right, vertical_outer_sizes_.top};
  return {horizontal_outer_sizes_.right,
    (u2)(outer_ring_positions_.index_pairs[index].end - vertical_outer_sizes_.top + 1)};



 case Outer_Ring_Area_Flags::Bottom_Right_Corner_Landscape:
  if(qpoint)
    *qpoint = {outer_ring_positions_.index_pairs[index].end,
      total_size_.height - vertical_outer_sizes_.bottom};
  return {(u2)(total_size_.width - //horizontal_outer_sizes_.right
    outer_ring_positions_.index_pairs[index].end),
    vertical_outer_sizes_.bottom};

 case Outer_Ring_Area_Flags::Bottom_Right_Corner_Portrait:
  if(qpoint)
    *qpoint = {outer_ring_positions_.index_pairs[index].start,
      total_size_.height - vertical_outer_sizes_.bottom};
  return {(u2)(total_size_.width - //horizontal_outer_sizes_.right
    outer_ring_positions_.index_pairs[index].start),
    vertical_outer_sizes_.bottom};


  default: break;
 }
 return {0, 0};
}


wh2 XCSD_Image_Geometry::get_outer_ring_rect_wh_for(Outer_Ring_Area_Flags area_flags,
  u1 index, QPoint* qpoint)
{
 // //  span or transposed_inner_difference?
 switch (area_flags)
 {
 case Outer_Ring_Area_Flags::Normal_Portrait:
  switch(index)
  {
  case (u1) Outer_Ring_Positions::Portrait::Top_Left_Top:
  case (u1) Outer_Ring_Positions::Portrait::Top_Center:
  case (u1) Outer_Ring_Positions::Portrait::Top_Right_Top:
   if(qpoint)
     *qpoint = {outer_ring_positions_.index_pairs[index].start, 0};
   return {outer_ring_positions_.index_pairs[index].inner_span(), vertical_outer_sizes_.top};

  case (u1) Outer_Ring_Positions::Portrait::Bottom_Left_Bottom:
  case (u1) Outer_Ring_Positions::Portrait::Bottom_Center:
  case (u1) Outer_Ring_Positions::Portrait::Bottom_Right_Bottom:
   if(qpoint)
     *qpoint = {outer_ring_positions_.index_pairs[index].start, total_size_.height - vertical_outer_sizes_.bottom};
   return {outer_ring_positions_.index_pairs[index].inner_span(), vertical_outer_sizes_.bottom};

  case (u1) Outer_Ring_Positions::Portrait::Top_Left:
  case (u1) Outer_Ring_Positions::Portrait::Center_Left:
  case (u1) Outer_Ring_Positions::Portrait::Bottom_Left:
   if(qpoint)
     *qpoint = {0, outer_ring_positions_.index_pairs[index].start};
   return {horizontal_outer_sizes_.left, outer_ring_positions_.index_pairs[index].inner_span()};

  case (u1) Outer_Ring_Positions::Portrait::Top_Right:
  case (u1) Outer_Ring_Positions::Portrait::Center_Right:
  case (u1) Outer_Ring_Positions::Portrait::Bottom_Right:
   if(qpoint)
     *qpoint = {total_size_.width - horizontal_outer_sizes_.right, outer_ring_positions_.index_pairs[index].start};
   return {horizontal_outer_sizes_.right, outer_ring_positions_.index_pairs[index].inner_span()};

  default: break;
  }

 case Outer_Ring_Area_Flags::Normal_Landscape:
  switch(index)
  {
  case (u1) Outer_Ring_Positions::Landscape::Top_Left_Top:
  case (u1) Outer_Ring_Positions::Landscape::Top_Center:
  case (u1) Outer_Ring_Positions::Landscape::Top_Right_Top:
   if(qpoint)
     *qpoint = {outer_ring_positions_.index_pairs[index].start, 0};
   return {outer_ring_positions_.index_pairs[index].inner_span(), vertical_outer_sizes_.top};

  case (u1) Outer_Ring_Positions::Landscape::Bottom_Left_Bottom:
  case (u1) Outer_Ring_Positions::Landscape::Bottom_Center:
  case (u1) Outer_Ring_Positions::Landscape::Bottom_Right_Bottom:
   if(qpoint)
     *qpoint = {outer_ring_positions_.index_pairs[index].start, total_size_.height - vertical_outer_sizes_.bottom};
   return {outer_ring_positions_.index_pairs[index].inner_span(), vertical_outer_sizes_.bottom};

  case (u1) Outer_Ring_Positions::Landscape::Top_Left:
  case (u1) Outer_Ring_Positions::Landscape::Center_Left:
  case (u1) Outer_Ring_Positions::Landscape::Bottom_Left:
   if(qpoint)
     *qpoint = {0, outer_ring_positions_.index_pairs[index].start};
   return {horizontal_outer_sizes_.left, outer_ring_positions_.index_pairs[index].inner_span()};

  case (u1) Outer_Ring_Positions::Landscape::Top_Right:
  case (u1) Outer_Ring_Positions::Landscape::Center_Right:
  case (u1) Outer_Ring_Positions::Landscape::Bottom_Right:
   if(qpoint)
     *qpoint = {total_size_.width - horizontal_outer_sizes_.right, outer_ring_positions_.index_pairs[index].start};
   return {horizontal_outer_sizes_.right, outer_ring_positions_.index_pairs[index].inner_span()};

  default: break;
  }
  break;

 case Outer_Ring_Area_Flags::Top_Left_Corner_Landscape:
  if(qpoint)
    *qpoint = {0, 0};
  return {(u1)(outer_ring_positions_.index_pairs[index].end + 1), vertical_outer_sizes_.top};

 case Outer_Ring_Area_Flags::Top_Left_Corner_Portrait:
  if(qpoint)
    *qpoint = {0, 0};
  return {(u1)(outer_ring_positions_.index_pairs[index].start + 1), vertical_outer_sizes_.top};


 case Outer_Ring_Area_Flags::Bottom_Left_Corner_Landscape:
  if(qpoint)
    *qpoint = {0, outer_ring_positions_.index_pairs[index].start};
  return {horizontal_outer_sizes_.left, (u2)(total_size_.height -
    vertical_outer_sizes_.bottom -
    outer_ring_positions_.index_pairs[index].start)};

 case Outer_Ring_Area_Flags::Bottom_Left_Corner_Portrait:
  if(qpoint)
    *qpoint = {0, outer_ring_positions_.index_pairs[index].end};
  return {horizontal_outer_sizes_.left, (u2)(total_size_.height -
    vertical_outer_sizes_.bottom -
    outer_ring_positions_.index_pairs[index].end)};



 case Outer_Ring_Area_Flags::Top_Right_Corner_Landscape:
  if(qpoint)
    *qpoint = {outer_ring_positions_.index_pairs[index].end, 0};
  return {(u2)(total_size_.width - outer_ring_positions_.index_pairs[index].end),
     vertical_outer_sizes_.top};

 case Outer_Ring_Area_Flags::Top_Right_Corner_Portrait:
  if(qpoint)
    *qpoint = {outer_ring_positions_.index_pairs[index].start, 0};
  return {(u2)(total_size_.width - outer_ring_positions_.index_pairs[index].start),
     vertical_outer_sizes_.top};



 case Outer_Ring_Area_Flags::Bottom_Right_Corner_Landscape:
  if(qpoint)
    *qpoint = {total_size_.width - horizontal_outer_sizes_.right, outer_ring_positions_.index_pairs[index].start};
  return {horizontal_outer_sizes_.right, (u2)(total_size_.height - vertical_outer_sizes_.bottom -
    outer_ring_positions_.index_pairs[index].start)};

 case Outer_Ring_Area_Flags::Bottom_Right_Corner_Portrait:
  if(qpoint)
    *qpoint = {total_size_.width - horizontal_outer_sizes_.right, outer_ring_positions_.index_pairs[index].end};
  return {horizontal_outer_sizes_.right, (u2)(total_size_.height - vertical_outer_sizes_.bottom -
    outer_ring_positions_.index_pairs[index].end)};

 }
 return {0, 0};
}

//?
//s1 XCSD_Image_Geometry::_for_each_central_tierbox(std::function<s1(XCSD_TierBox*)> fn)
//{

//}


s1 XCSD_Image_Geometry::_for_each_full_tierbox(std::function<s1(Grid_TierBox&)> fn)
{
 return _for_each_full_tierbox({0, 0}, full_tier_counts_._transposed_to<rc2>() - 1, fn);
}

s1 XCSD_Image_Geometry::_for_each_full_tierbox(rc2 top_left, rc2 bottom_right,
  std::function<s1(Grid_TierBox&)> fn)
{
// u1 offset = vertical_outer_sizes_.top;
 tl2 tl{vertical_outer_sizes_.top, horizontal_outer_sizes_.left};
// u4 area = full_tier_counts_.area();

 tl2 offsets = tl || 1;
 for(u2 r = top_left.r; r <= bottom_right.r; ++r)
 {
  for(u2 c = top_left.c; c <= bottom_right.c; ++c)
  {

//   for(u2 r = 0; r < full_tier_counts_.height; ++r)
//   {
//    for(u2 c = 0; c < full_tier_counts_.width; ++c)
//    {

   rc2 rc{r, c};
   //rc.add(offsets);
   TierBox_Location tbl(rc._to<rc2s>());
   calculate_mch_code(tbl);
   tbl.rc().add(offsets);

   Grid_TierBox gtb({tbl, ((rc * tierbox_width).plus(tl) + (tierbox_width / 2))._transposed_to<xy2>()});
   s1 _break = fn(gtb);
   if(_break != 0)
     return _break;
  }
 }
 return 0;
}

void TierBox_Location::set_mch_code(pr2s mch)
{
 mch_code_ = mch.binary_merge();

//   (u4)mch.first << 16;
//  (((u4)mch.first << (16)) | (u4)mch.second);

// mch_code_ |= (u4)(u2)mch.second;

// s2 mc = (s2)(u2)(mch_code_ >> 16);
// s2 mc1 = (mch_code_ & ~(u2)0);

// s2 tt = mc - mc1;
}

pr2s TierBox_Location::get_mch_code() const
{
 return {(s2)(mch_code_ >> 16), (s2)(mch_code_ & ~(u2)0)};
}

u1 TierBox_Location::get_mch_clock_code(pr2s pr, u1* mask)
{
// if(pr.has_zero())
// {
////  qDebug() << "pr = " << pr;
// }

 if(pr.is_zeros())
 {
  if(mask)
    *mask = 0;
   return 0;
 }

 u1 _mask = 0;

 pr2 abs = pr.abs();

 if(abs.is_ascending())
 {
  _mask |= 4;
  pr._Transpose();
  abs._Transpose();
 }
 if(pr.first < 0)
   _mask |= 2;
 if(pr.second < 0)
   _mask |= 1;

 if(mask)
   *mask = _mask;

// return mask;

 // // size_even_odd_code :
  //   0 = e_e  1 = e_o  2 = o_e  3 = o_o

// static u1 cycle_ortho[4][4] =
//  {
//   {18, 6, 12, 0},
//  // {12, 4, 8, 16},
//  // //  6 -> 0  2 -> 6  4 -> 12  0 -> 18
//   {18, 6, 12, 0},
//   {18, 6, 12, 0},
//  // //  6 -> 0  2 -> 6  4 -> 12  0 -> 18
//   {18, 6, 12, 0}
// };

 // //  6 -> 1  2 -> 7  4 -> 13  0 -> 19
 static u1 cycle_ortho[4] = {19, 7, 13, 1};
 if(pr.has_zero())
 {
  return cycle_ortho[_mask/2];
 }

 // 3 -> 4  2 -> 10  0 -> 16  1 -> 22
 static u1 cycle_diag[4] = {16, 22, 10, 4};

 if(abs.first == (abs.second * 2))
 {
  return cycle_diag[_mask];
 }

 // //  7 -> 3  3 -> 5   2 -> 9   6 -> 11
  //    4 -> 15  0 -> 17  1 -> 21  5 -> 23
 static u1 cycle[8] = {17, 21, 9, 5, 15, 23, 11, 3};
  //{11, 13, 5, 3, 9, 15, 7, 1},

 return cycle[_mask];
}

u1 TierBox_Location::get_mch_clock_code(u1* mask)
{
 return get_mch_clock_code(get_mch_code(), mask);
}

//u1 TierBox_Location::get_orthogonal_quadrant_from_mch_code(u1 size_even_odd_code, u1 quadrant_code, prr2 mch_code)
//{

//}

void TierBox_Location::reconcile_mch_quadrant(u1 size_even_odd_code, u1 quadrant_code,
  u2& clk //prr2& mch_code
  )
{
 if(size_even_odd_code == 3)
   return;

 u1 orthogonal_quadrant = (clk - 1) / 6;

 if((size_even_odd_code > 0)
   && ((size_even_odd_code % 2) != (orthogonal_quadrant % 2)))
   return;

 // //  make it clockwise ...
 if(quadrant_code == 2)
   quadrant_code = 3;
 else if(quadrant_code == 3)
  quadrant_code = 2;

 s1 offset = (quadrant_code == orthogonal_quadrant)? 1 : -1; //1 - 2 * (orthogonal_quadrant % 2);
 clk += offset;

 if(clk == 0)
   clk = 24;

// if((s1) mch_code.third == -1)
//   mch_code.third += 24;
}
// return;

//// s1 offset = (orthogonal_quadrant % 2)? 1 : -1; //1 - 2 * (orthogonal_quadrant % 2);


// if(size_even_odd_code == 0)
// {
//  mch_code.third += offset;
////  if(quadrant_code == orthogonal_quadrant)
////    ++mch_code.third;
////  else
////   --mch_code.third;

//  if((s1) mch_code.third == -1)
//    mch_code.third += 24;

//  return;
// }

// if(size_even_odd_code == 1)
// {
//  if(orthogonal_quadrant % 2)
//    mch_code.third += offset;

////  if(orthogonal_quadrant % 2)
////  {
////   if(quadrant_code == orthogonal_quadrant)
////     ++mch_code.third;
////   else
////    --mch_code.third;
////  }

//  if((s1) mch_code.third == -1)
//    mch_code.third += 24;

//  return;
// }
//  if(quadrant_code == 0 && orthogonal_quadrant == 1)
//    --mch_code.third;
//  else if(quadrant_code == 1 && orthogonal_quadrant == 1)
//    ++mch_code.third;
//  else if(quadrant_code == 2 && orthogonal_quadrant == 3)
//    --mch_code.third;
//  else if(quadrant_code == 3 && orthogonal_quadrant == 3)
//    ++mch_code.third;

//  if((s1) mch_code.third == -1)
//    mch_code.third += 24;

// if(size_even_odd_code == 2)
// {
//  if(orthogonal_quadrant % 2 == 0)
//    mch_code.third += offset;

////  if(orthogonal_quadrant % 2)
////  {
////   if(quadrant_code == orthogonal_quadrant)
////     ++mch_code.third;
////   else
////    --mch_code.third;
////  }

//  if((s1) mch_code.third == -1)
//    mch_code.third += 24;

//  return;
// }


// switch(quadrant_code)
// {
// case 0:
//  if(size_even_odd_code == 1 && orthogonal_quadrant == 1)
//    --mch_code.third;
//  else if(size_even_odd_code == 2 && orthogonal_quadrant == 0)
//    ++mch_code.third;
//  break;
// case 1:
//  if(size_even_odd_code == 1 && orthogonal_quadrant == 1)
//    ++mch_code.third;
//  else if(size_even_odd_code == 2 && orthogonal_quadrant == 2)
//    --mch_code.third;
//  else if(size_even_odd_code == 2 && orthogonal_quadrant == 3)
//    ++mch_code.third;
//  break;
// case 3:
//  if(size_even_odd_code == 1 && orthogonal_quadrant == 3)
//    ++mch_code.third;
//  else if(size_even_odd_code == 2 && orthogonal_quadrant == 2)
//    ++mch_code.third;
//  else if(size_even_odd_code == 2 && orthogonal_quadrant == 0)
//    mch_code.third = 23;
//  break;
// case 2:
//  if(size_even_odd_code == 1 && orthogonal_quadrant == 3)
//    --mch_code.third;
//  else if(size_even_odd_code == 2 && orthogonal_quadrant == 2)
//    ++mch_code.third;
//  break;
// }

// if((s1) mch_code.third == -1)
//   mch_code.third %= 24;

//}

prr2 TierBox_Location::get_mch_code_normalized(u1* mask) const
{
 pr2s mch = get_mch_code();
 pr2 result = mch.abs().make_ascending();
 u1 clk = get_mch_clock_code(mch, mask);
 return {result.first, result.second, clk};
}

xy4 XCSD_Image_Geometry::get_tierbox_scanline_top_left(Grid_TierBox& gtb)
{
 xy4 result {horizontal_outer_sizes_.left, vertical_outer_sizes_.top};
 result.add(gtb.loc.rc()._transposed_to<xy4>() * tierbox_width);
 return result;
}

u1 XCSD_Image_Geometry::get_size_even_odd_code()
{
 switch (actual_tiergrid_setting_)
 {
 case TierGrid_Preferances::Even_H_Even_V: return 0;
 case TierGrid_Preferances::Even_H_Odd_V: return 1;
 case TierGrid_Preferances::Odd_H_Even_V: return 2;
 case TierGrid_Preferances::Odd_H_Odd_V: return 3;
 default: return 0;
 }
}

u2 XCSD_Image_Geometry::sdi_index_to_ground_offset(const ab1& sdi)
{
 // // rc here is 0 - 3
 rc1 arc = {(u1)(sdi.a / 3), (u1)(sdi.a % 3)};
 rc1 brc = {(u1)(sdi.b / 3), (u1)(sdi.b % 3)};

 return 81 * (3 * arc.r + arc.c) + 9 * (3 * brc.r + brc.c);
}


ab1 XCSD_Image_Geometry::ground_offset_coords_to_sdi_coords(const go_xy1& coords)
{
 //u1 gc = coords.go_x % 3;
 u1 bc = (coords.go_x / 3) % 3;
 u1 ac = (coords.go_x / 9) % 3;

 //u1 gr = coords.go_y % 3;
 u1 br = (coords.go_y / 3) % 3;
 u1 ar = (coords.go_y / 9) % 3;

 return {(u1)(ar * 3 + ac), (u1)(br * 3 + bc)};
}

abg1 XCSD_Image_Geometry::ground_offset_coords_to_sdi3_coords(const go_xy1& coords)
{
 u1 gc = coords.go_x % 3;
 u1 bc = (coords.go_x / 3) % 3;
 u1 ac = (coords.go_x / 9) % 3;

 u1 gr = coords.go_y % 3;
 u1 br = (coords.go_y / 3) % 3;
 u1 ar = (coords.go_y / 9) % 3;

 return {(u1)(ar * 3 + ac), (u1)(br * 3 + bc), (u1)(gr * 3 + gc)};
}

go_xy1 XCSD_Image_Geometry::ground_offset_to_ground_offset_coords(u2 index)
{
 u2 digit1 = index % 3;
 u2 digit2 = (index / 3) % 3;
 u2 digit3 = (index / 9) % 3;
 u2 digit4 = (index / 27) % 3;
 u2 digit5 = (index / 81) % 3;
 u2 digit6 = (index / 243) % 3;

 return {(u1)(9 * digit5 + 3 * digit3 + digit1),
   (u1)(9 * digit6 + 3 * digit4 + digit2)};

}

u2 XCSD_Image_Geometry::ground_offset_to_sdi3(u2 index)
{
 u2 digit1 = index % 3;
 u2 digit2 = (index / 3) % 3;
 u2 digit3 = (index / 9) % 3;
 u2 digit4 = (index / 27) % 3;
 u2 digit5 = (index / 81) % 3;
 u2 digit6 = (index / 243) % 3;


 // u1 bc = (coords.go_x / 3) % 3;
// u1 ac = (coords.go_x / 9) % 3;

}

u2 XCSD_Image_Geometry::ground_offset_coords_to_sdi3(const go_xy1& coords)
{
 abg1 abg = ground_offset_coords_to_sdi3_coords(coords);

 abg.add(1);

 // //  I put this here just to make sure vector_product works ok ...
  //    return abg._to<abg2>().vector_product(abg2 {100, 10, 1});
 return abg.to_base(10);
}

u2 XCSD_Image_Geometry::ground_offset_coords_to_ground_offset(const go_xy1& coords)
{
 u1 gc = coords.go_x % 3;
// u1 bc = (coords.go_x / 3) % 3;
// u1 ac = (coords.go_x / 9) % 3;

 u1 gr = coords.go_y % 3;
// u1 br = (coords.go_y / 3) % 3;
// u1 ar = (coords.go_y / 9) % 3;

// u2 go = sdi_index_to_ground_offset({(u1)(ar * 3 + ac), (u1)(br * 3 + bc)});

 ab1 ab = ground_offset_coords_to_sdi_coords(coords);
 u2 go = sdi_index_to_ground_offset(ab);

 return go + gr * 3 + gc;
}


// u2 thro_1 =  3 * brc.r + brc.c;
// u2 thro_2 =  9 * thro_1;

// u2 thro_3 =  3 * arc.r + arc.c;
// u2 thro_4 =  81 * thro_3;

// u2 thro = thro_2 + thro_4;
//}

u2 XCSD_Image_Geometry::sdi_index_to_ground_offset(s1 sdi)
{
 ab1 ab = {(u1)((u1)sdi / 10), (u1)((u1)sdi % 10)};
 return sdi_index_to_ground_offset( ab.double_minus(1) );
}

u1 XCSD_Image_Geometry::MCH_Info::get_compressed_clock_index(u1 clk,
  u1 size_even_odd_code, u1 quadrant_code)
{
 // //  make it clockwise ...
 if(quadrant_code == 2)
   quadrant_code = 3;
 else if(quadrant_code == 3)
  quadrant_code = 2;

 s1 adj = clk - 4;

 if(clk == 0)
 {
  if(size_even_odd_code == 0)
    return quadrant_code;
  else if(size_even_odd_code < 2)
    return 1 - (quadrant_code % 2);
  else
    return 0;
 }

 if((adj % 6) == 0)
   return adj / 6;

 if( (clk % 2) && ((clk - 1) % 6))
 {
  u1 uclk = (clk - 3) / 2;
  if(uclk > 2)
    return uclk - (uclk - 2) / 3  - 1;
  return uclk;
 }

 pr1s adj_1_4;

 switch (size_even_odd_code)
 {
 case 0:
 {
  u1 uclk = clk % 6? clk + 1 : clk - 1;
  s1 sclk = (uclk / 3);
  if(clk % 6)
   --sclk;
  return (u1) (sclk % 8);
 }
 case 1:
  if(clk % 2) // 1, 13
   return (clk - 1) / 4;
  else if(clk % 6) // 8, 20            // !% ?
   adj_1_4 = {3, -12}; //return 3 + ((clk - 12) / 4);
  else  // 6, 18
   adj_1_4 = {-1, 2}; //return ((clk + 2) / 4) - 1;
  break;
 case 2:
  if(clk % 2) // 7, 19
   adj_1_4 = {1, -7}; //return 1 + ((clk - 7) / 4);
  else if(clk % 6) // 2, 14
   return (clk - 2) / 4;
  else // 12, 24
   adj_1_4 = {2, -12};
  break;//return 2 + ((clk - 12) / 4);
 case 3:
  return (clk - 1) / 6;
 default:
  break;
 }

 // //  return adj_1_4.times({4, 1}).plus({0, (s1)clk}).divide({1, 4}).inner_sum();
 return adj_1_4.first + ((clk + adj_1_4.second) / 4);
}

XCSD_Image_Geometry::MCH_Info::MCH_Info(const prr2& mch, const prr2& margin_info,
   u2 lesser_side, Size_Even_Odd_Info& size_even_odd_info, u1 quadrant_code)
{
 margin_code = (u1) margin_info.first;
 margin_gap = margin_info.second;

 u1 size_even_odd_code = size_even_odd_info.size_even_odd_code;

 intra_tier_ring_index = mch.first; //quadrant_code;

 full_clock_index = mch.third;

 if(margin_code == 0)
 {
  area_threshold_adjustment = 0;
  clock_index_adjustment = 0;
 }
 else
 {
  area_threshold_adjustment = (margin_gap - 1) * lesser_side * 2;

  // // note 4, 10, 16, 22 are not
   //   handled because the diagnols
   //   will never be subject to
   //   a clock index adjustment
  switch (full_clock_index)
  {
   // 3 - 23: margin_code == 1
  default: clock_index_adjustment = 0; break;
  case 23: // top and bottom
   clock_index_adjustment = 4; break;
  case 24:  // 1 or 2, top and bottom ortho
   clock_index_adjustment = 2 * (1 + size_even_odd_info.h_center_adjustment);
   break;

   // 5 - 9: margin_code == 2
  case 5: case 9: // left
  case 6: case 7: case 8: // left ortho
   clock_index_adjustment = 1; break;

   // 11 - 15: margin_code == 3
  case 11: case 15: // top
    clock_index_adjustment = 2; break;
  case 12: case 13: case 14: // top ortho
    clock_index_adjustment = 1 + size_even_odd_info.h_center_adjustment; break;

   // 17 - 21: margin_code == 4
  case 17: case 21: // 1 left and 2 right
    clock_index_adjustment = 3; break;
  case 18: case 19: case 20: // left and right ortho
    // // only count the one extra v-center from the left
     //   because the other (if it exists) is at index 24
    clock_index_adjustment = 2 + size_even_odd_info.v_center_adjustment;
    break;
  }

 }

 tier_ring = mch.second - mch.first;
 inner_pushout = mch.first;

 if(tier_ring == 0)
 {
  area_threshold = 0;

  switch (size_even_odd_code)
  {
  case 0: // h even, v even
    compressed_clock_index = quadrant_code;
    if(compressed_clock_index == 2)
       compressed_clock_index = 3;
    else if(compressed_clock_index == 3)
      compressed_clock_index = 2;
    break;
  case 1: // h even, v odd
    compressed_clock_index = quadrant_code == 3; break;
  case 2: // h odd, v even
   compressed_clock_index = quadrant_code != 1; break;
  default:
  case 3: // h odd, v odd
    compressed_clock_index = 0; break;

  }

  full_tier_index = compressed_clock_index;
  return;
 }

 u4 sq, sqh, sqv;

 if(margin_code == 0 || margin_gap == 1) //? (2 * tier_ring) - 1 : lesser_side;
 {
  sq = (2 * tier_ring) - 1;
  sqh = sq + 1 - (size_even_odd_code & 1);
  sqv = sq + 1 - ((size_even_odd_code >> 1) & 1);
 }
 else if((size_even_odd_code == 0) || (size_even_odd_code == 3))
   sqh = sqv = lesser_side;
 else
 {
  sq = lesser_side;
  sqh = sq + size_even_odd_info.h_center_area_threshold_adjustment;// - (size_even_odd_code & 1);
  sqv = sq + size_even_odd_info.v_center_area_threshold_adjustment;// - ((size_even_odd_code >> 1) & 1);
 }

 area_threshold = sqh * sqv;
 area_threshold += area_threshold_adjustment;

 compressed_clock_index = get_compressed_clock_index(mch.third,
   size_even_odd_code, quadrant_code);

// if(margin_code % 1) // 1, 3
//   compressed_clock_index = get_compressed_clock_index_landscape(mch.third,
//     size_even_odd_code, quadrant_code);
// else if(margin_code != 0) // 2, 4
//   compressed_clock_index = get_compressed_clock_index_portrait(mch.third,
//     size_even_odd_code, quadrant_code);

 // // calculate full_tier_index
 full_tier_index = area_threshold;

 if(intra_tier_ring_index > 0)
 {
  if(margin_code == 0)
  {
   full_tier_index += size_even_odd_info.full_ortho_cycle_size;
   full_tier_index += ((intra_tier_ring_index - 1) * 8);
  }
  else
  {
   full_tier_index += size_even_odd_info.margin_ortho_cycle_size;
   full_tier_index += ((intra_tier_ring_index - 1) * 4);
  }
 }

 full_tier_index += compressed_clock_index - clock_index_adjustment;

}

prr2 XCSD_Image_Geometry::get_margin_info(const TierBox_Location& loc, u1 quadrant_code)
{
 u1 lmod = full_tier_counts_.width % 2;
 u1 hmod = full_tier_counts_.height % 2;

 u1 adj = hmod & lmod;

 u1 margin_code = 0;
 //
 u2 full_margin = 0;

 u2 margin_gap = 0;


 if(full_tier_counts_.is_ascending())
 {
  // //  portrait-like
  u2 r = loc.r();
  u2 top = full_tier_counts_._transposed().inner_difference() / 2;
  full_margin = top;

  if(r < top + hmod - adj)
  {
   margin_code = 2;
   margin_gap = top + hmod - adj - r;
  }

  if(r > top + full_tier_counts_.width + lmod - 1 - adj)
  {
   margin_code = 4;
   // margin_gap = r - (top + full_tier_counts_.width + lmod - 1 - adj);
   margin_gap = r - top - full_tier_counts_.width - lmod + 1 + adj;
  }

  //?

 }
 else
 {
 // //  landscape-like
  u2 c = loc.c();
  u2 left = full_tier_counts_.inner_difference() / 2;

  full_margin = left;

  if(c < left + lmod - adj)
  {
   margin_code = 1;
   margin_gap = left + lmod - adj - c;
  }

  if(c > left + full_tier_counts_.height + hmod - 1 - adj)
  {
   margin_code = 3;
   //margin_gap = c - (left + full_tier_counts_.height + hmod - 1 - adj);
   margin_gap = c - left - full_tier_counts_.height - hmod + 1 + adj;
  }

 }
 return {margin_code, margin_gap, full_margin};
}

void XCSD_Image_Geometry::Size_Even_Odd_Info::landscape()
{
 margin_ortho_cycle_size = 2 * (1 + v_center_adjustment);

 if(size_even_odd_code == 1)
   h_center_area_threshold_adjustment = 1;

 else if(size_even_odd_code == 2)
   h_center_area_threshold_adjustment = -1;
}

void XCSD_Image_Geometry::Size_Even_Odd_Info::portrait()
{
 margin_ortho_cycle_size = 2 * (1 + h_center_adjustment);

 if(size_even_odd_code == 2)
   v_center_area_threshold_adjustment = 1;

 else if(size_even_odd_code == 1)
   v_center_area_threshold_adjustment = -1;
}

u4 XCSD_Image_Geometry::get_tierbox_index(const Grid_TierBox& gtb,
  Size_Even_Odd_Info size_even_odd_info, MCH_Info* mchi)
{
 //static constexpr u2 tierbox_pixel_size = 27*27;

 rc2s quadrant = gtb.loc.rc() - directed_centers_.back().rc();

//  qDebug() << "quadrant = " << quadrant;

 rc2s quadrant_mask = quadrant.spaceship_mask().plus(quadrant.zeros_mask());

 u1 quadrant_code = quadrant_mask.floor(0).times({2, 1}).inner_sum();

//  qDebug() << "quadrant_code = " << quadrant_code;

// u3
 //pr2s mch_code = gtb.loc.get_mch_code();

 prr2 mch = gtb.loc.get_mch_code_normalized();

 if(mch.first == 0)
 {
  if(mch.second > 0)
  {
   TierBox_Location::reconcile_mch_quadrant(size_even_odd_info.size_even_odd_code,
     quadrant_code, mch.third);
  }
 }

 prr2 margin_info = get_margin_info(gtb.loc, quadrant_code);

 MCH_Info _mchi(mch, margin_info, full_tier_counts_.lesser(),
   size_even_odd_info, quadrant_code);

 if(mchi)
   *mchi = _mchi;

 return _mchi.full_tier_index;
 //pr2s raw_mch = gtb.loc.get_mch_code();

}

XCSD_Image_Geometry::Iteration_Environment::Iteration_Environment(u1 size_even_odd_code)
  :  size_even_odd_info(size_even_odd_code)
{

}

XCSD_Image_Geometry::Iteration_Environment
XCSD_Image_Geometry::formulate_iteration_environment()
{
 u1 size_even_odd_code = get_size_even_odd_code();
 Iteration_Environment result(size_even_odd_code);

 if(full_tier_counts_.is_ascending()) // w < h
   result.size_even_odd_info.portrait();
 else if(full_tier_counts_.is_descending()) // w > h
   result.size_even_odd_info.landscape();

 return result;
}


void XCSD_Image_Geometry::draw_tier_summary(QString path, QString path1,
  r8 magnification, u1 circle_radius)
{
 static xy2s bl_text_pixel_offset {1, -6};
 static xy2s bl1_text_pixel_offset {1, -1};
 static xy2s tl_text_pixel_offset {1, 3};

 static xy2s br_text_pixel_offset {-5, -4};

 static xy2s br_text1_pixel_offset {-7, -2};

 static xy2s tr_text_pixel_offset {-3, 6};

 static xy2s ml_text_pixel_offset {1, 10};

 wh2 summary_image_size = total_size_ * magnification;
 QImage image(summary_image_size.width, summary_image_size.height, QImage::Format_RGB16);
 image.fill(-1);

 QImage image1(summary_image_size.width, summary_image_size.height, QImage::Format_RGB16);
 image1.fill(-1);

 u1 size_even_odd_code = get_size_even_odd_code();
 Size_Even_Odd_Info size_even_odd_info(size_even_odd_code);

 if(full_tier_counts_.is_ascending()) // w < h
   size_even_odd_info.portrait();
 else if(full_tier_counts_.is_descending()) // w > h
   size_even_odd_info.landscape();

 QPainter painter;
 painter.begin(&image);

 QPainter painter1;
 painter1.begin(&image1);

 for_each_horizontal_gridline([&painter, &painter1, &summary_image_size, magnification](Gridline& gl)
 {
  painter.drawLine(0, gl.ground_index * magnification,
    summary_image_size.width, gl.ground_index * magnification);

  painter1.drawLine(0, gl.ground_index * magnification,
    summary_image_size.width, gl.ground_index * magnification);
 });

 for_each_vertical_gridline([&painter, &painter1, &summary_image_size, magnification](Gridline& gl)
 {
  painter.drawLine(gl.ground_index * magnification, 0,
    gl.ground_index * magnification, summary_image_size.height);

  painter1.drawLine(gl.ground_index * magnification, 0,
    gl.ground_index * magnification, summary_image_size.height);
 });

 for_each_full_tierbox([this, &painter, &painter1, magnification,
   circle_radius, size_even_odd_code, &size_even_odd_info](Grid_TierBox& gtb)
 {
  xy2s extra_trtext_pixel_offset {0, 0};
  xy2s extra_brtext_pixel_offset {0, 0};
  xy2s extra_brtext1_pixel_offset {0, 0};

  bool is_notation_center = (gtb.loc.rc() == directed_centers_[0].rc());

  rc2s quadrant = gtb.loc.rc() - directed_centers_.back().rc();

//  qDebug() << "quadrant = " << quadrant;

  rc2s quadrant_mask = quadrant.spaceship_mask().plus(quadrant.zeros_mask());

  u1 quadrant_code = quadrant_mask.floor(0).times({2, 1}).inner_sum();

//  qDebug() << "quadrant_code = " << quadrant_code;

 // u3



  xy2 xyc = gtb.ground_center * magnification;

  //pr2s mch_code = gtb.loc.get_mch_code();

  u1 mask;
  prr2 mch = gtb.loc.get_mch_code_normalized(&mask);


  if(mch.first == 0)
  {
   if(mch.second == 0)
   {
    painter.setBrush(Qt::yellow);
    painter1.setBrush(Qt::yellow);
   }
   else
   {
    painter.setBrush(Qt::red);
    painter1.setBrush(Qt::red);
    TierBox_Location::reconcile_mch_quadrant(size_even_odd_code, quadrant_code, mch.third);
   }
  }
  else if(mch.second == mch.first * 2)
  {
   painter.setBrush(Qt::cyan);
   painter1.setBrush(Qt::cyan);
  }

  painter.drawEllipse(QPoint(xyc.x, xyc.y), circle_radius, circle_radius);
  painter1.drawEllipse(QPoint(xyc.x, xyc.y), circle_radius, circle_radius);

  painter.setBrush(Qt::NoBrush);
  painter1.setBrush(Qt::NoBrush);

  prr2 margin_info = get_margin_info(gtb.loc, quadrant_code);

  if(gtb.loc.rc() == rc2{0, 4})
  {
   qDebug() << "stop ...";
  }


  MCH_Info mchi(mch, margin_info, full_tier_counts_.lesser(),
    size_even_odd_info, quadrant_code);

  pr2s raw_mch = gtb.loc.get_mch_code();

  QString tl_text = QString("%1,%2")
    .arg(gtb.loc.r()).arg(gtb.loc.c())
    ;

  QString tl_text1 = QString("%1 %2 + %3")
    .arg(mchi.area_threshold).arg(mchi.margin_gap).arg(mchi.area_threshold_adjustment);


  QString bl_text = QString("%1,%2")
    .arg(mch.first).arg(mch.second)//.arg(mch.third)
    //.arg(raw_mch.first).arg(raw_mch.second)
     //.arg(raw_mch.first).arg(raw_mch.second).arg(mask)
    ;

  QString bl1_text = QString("%1 %2")
    //.arg(mch.first).arg(mch.second)//.arg(mch.third)
    .arg(raw_mch.first).arg(raw_mch.second)
     //.arg(raw_mch.first).arg(raw_mch.second).arg(mask)
    ;

  QString tr_text = QString::number(mask)
    ;


  QString br_text = QString::number(mch.third)
    ;

  QString ml_text1 = QString("%1 %2").arg(mchi.intra_tier_ring_index)
    .arg(quadrant_code);

  //QString br_text1 = QString::number(mchi.tier_ring); //mch.drop_last()._transposed().inner_difference());
  QString br_text1 = QString("%1;%2").arg(mchi.compressed_clock_index).arg(mchi.clock_index_adjustment);
//    .arg(mchi.clock_index); //mch.drop_last()._transposed().inner_difference());

  QString bl_text1 = QString("%1~ %2").arg(mchi.inner_pushout)
    .arg(mchi.margin_code); //mch.drop_last()._transposed().inner_difference());

  QString tr_text1 = QString::number(mchi.tier_ring);
    ;

  QString bl1_text1 = QString::number(mchi.full_tier_index); //mch.drop_last()._transposed().inner_difference());

  if(is_notation_center)
  {
   extra_trtext_pixel_offset.x = -13;
   extra_brtext_pixel_offset.x = -3;
   extra_brtext1_pixel_offset.x = -3;


   bl_text.prepend("mch=");
   bl1_text.prepend("raw= ");

   tr_text.prepend("mask=");
   br_text.prepend("clk ");

   tr_text1.prepend("tierring ");
   tl_text1.prepend("ath ");
   br_text1.prepend("clk");

   bl_text1.prepend("psh,mc ");
   bl1_text1.prepend("index ");

   ml_text1.prepend("itr,qc ");

  }
  else if(br_text.length() == 1)
    extra_brtext_pixel_offset.x = 1;
   // br_text.prepend('0');

  xy2 bl_xy = gtb.bottom_left()._to<xy2s>().plus(bl_text_pixel_offset)._to<xy2>() * magnification;
  xy2 bl1_xy = gtb.bottom_left()._to<xy2s>().plus(bl1_text_pixel_offset)._to<xy2>() * magnification;
  xy2 tl_xy = gtb.top_left()._to<xy2s>().plus(tl_text_pixel_offset)._to<xy2>() * magnification;
  xy2 br_xy = gtb.bottom_right()._to<xy2s>().plus(br_text_pixel_offset)
    .plus(extra_brtext_pixel_offset)._to<xy2>() * magnification;
  xy2 br1_xy = gtb.bottom_right()._to<xy2s>().plus(br_text1_pixel_offset)
    .plus(extra_brtext1_pixel_offset)._to<xy2>() * magnification;
  xy2 tr_xy = gtb.top_right()._to<xy2s>().plus(tr_text_pixel_offset)
    .plus(extra_trtext_pixel_offset)._to<xy2>() * magnification;
  xy2 ml_xy = gtb.top_left()._to<xy2s>().plus(ml_text_pixel_offset)
    ._to<xy2>() * magnification;


  painter.drawText(bl1_xy.x, bl1_xy.y, bl1_text);
  painter.drawText(bl_xy.x, bl_xy.y, bl_text);
  painter.drawText(tl_xy.x, tl_xy.y, tl_text);

  painter.drawText(br_xy.x, br_xy.y, br_text);
  painter.drawText(tr_xy.x, tr_xy.y, tr_text);

  painter1.drawText(tr_xy.x, tr_xy.y, tr_text1);
  painter1.drawText(tl_xy.x, tl_xy.y, tl_text1);
  painter1.drawText(br1_xy.x, br1_xy.y, br_text1);
  painter1.drawText(bl_xy.x, bl_xy.y, bl_text1);
  painter1.drawText(bl1_xy.x, bl1_xy.y, bl1_text1);

  painter1.drawText(ml_xy.x, ml_xy.y, ml_text1);

  //qDebug() << "xy = " << xy << " str = " << str;
  });

 painter.end();
 painter1.end();

 image.save(path);
 image1.save(path1);
}




void XCSD_Image_Geometry::init_tier_counts(TierGrid_Preferances pref)
{
 u2 w = total_size_.width;
 u2 h = total_size_.height;

 lmr2 lmr = split_lmr(w, tierbox_width, (TierGrid_Preferances) (pref & 15));
 tmb2 tmb = split_tmb(h, tierbox_width, (TierGrid_Preferances) (pref >> 4));

 full_tier_counts_ = {lmr.main, tmb.main};

 horizontal_outer_sizes_ = lmr.drop_mid();
 vertical_outer_sizes_ = tmb.drop_mid();

 reconcile_actual_tiergrid_setting();
 init_directed_centers();
 reconcile_overall_tier_counts();

 //(TierGrid_Preferances) (pref >> 4)

// u2 ws = w / 27;
// u2 hs = h / 27;

// u2 w0 = w % 27 / 2;
// u2 h0 = h % 27 / 2;
// //return {(u2)image_.width(), (u2)image_.height()};

// if(w0 == 0)
// {
//  if((w % 27) == 1)
//  {
//   ++ws;
//   horizontal_outer_sizes_.right = 1;
//  }
// }
// else
// {
//  ws += 2;
//  horizontal_outer_sizes_ = {w0, (u2) (w0 + ((w % 27) % 2))};
// }

// if(h0 == 0)
// {
//  if((h % 27) == 1)
//  {
//   ++hs;
//   vertical_outer_sizes_.bottom = 1;
//  }
// }
// else
// {
//  hs += 2;
//  vertical_outer_sizes_ = {h0, (u2) (h0 + ((h % 27) % 2))};
// }

// tier_counts_ = {ws, hs};
// tierbox_count_ = tier_counts_.area();
}



//case 0:
// if(size_even_odd_code == 1 && orthogonal_quadrant == 1)
//   --mch_code.third;
// else if(size_even_odd_code == 2 && orthogonal_quadrant == 0)
//   ++mch_code.third;
// else if(size_even_odd_code == 0)
// { qDebug() << "0 - " << orthogonal_quadrant;
////   mch_code.third += offset;
//  if(orthogonal_quadrant == 1)
//    --mch_code.third;
//  else // 2
//    ++mch_code.third;
// }
// break;
//case 1:
// if(size_even_odd_code == 1 && orthogonal_quadrant == 1)
//   ++mch_code.third;
// else if(size_even_odd_code == 2 && orthogonal_quadrant == 2)
//   --mch_code.third;
// else if(size_even_odd_code == 2 && orthogonal_quadrant == 3)
//   ++mch_code.third;
// else if(size_even_odd_code == 0)
// { qDebug() << "1 - " << orthogonal_quadrant;
//  if(orthogonal_quadrant == 1)
//    ++mch_code.third;
//  else // == 2
//    --mch_code.third;
// }
// break;
//case 2:
// if(size_even_odd_code == 1 && orthogonal_quadrant == 3)
//   ++mch_code.third;
// else if(size_even_odd_code == 2 && orthogonal_quadrant == 2)
//   ++mch_code.third;
// else if(size_even_odd_code == 2 && orthogonal_quadrant == 0)
//   mch_code.third = 23;
// else if(size_even_odd_code == 0)
// { qDebug() << "2 - " << orthogonal_quadrant;
//  if(orthogonal_quadrant == 3)
//    ++mch_code.third;
//  else // == 4
//    --mch_code.third; // mch_code.third = 23;
// }
// break;
//case 3:
// if(size_even_odd_code == 1 && orthogonal_quadrant == 3)
//   --mch_code.third;
// else if(size_even_odd_code == 2 && orthogonal_quadrant == 2)
//   ++mch_code.third;
// else if(size_even_odd_code == 0)
// { qDebug() << "3 - " << orthogonal_quadrant;
//  if(orthogonal_quadrant == 2)
//    ++mch_code.third;
//  else // == 3
//    --mch_code.third;
// }



//XCSD_Image_Geometry::MCH_Info::MCH_Info(const prr2& mch, u1 size_even_odd_code, u1 quadrant_code)
//{
// tier_ring = mch.second - mch.first;
// inner_pushout = mch.first;

// clock_index = 0;

// // //  make it clockwise ...
// if(quadrant_code == 2)
//   quadrant_code = 3;
// else if(quadrant_code == 3)
//  quadrant_code = 2;

// //s1 adj = mch.third - 4;

// u1 clk = mch.third;

// s1 adj = clk - 4;

//// if(mch.first == 0)
//// {
////  if(mch.second == 0)
//  if(clk == 0)
//  {
//   if(size_even_odd_code == 0)
//     clock_index = quadrant_code;
//   else if(size_even_odd_code < 2)
//    clock_index = 1 - (quadrant_code % 2);
//  }

////   else if(clk % 2)
////   {
////    clock_index = 100 + ((clk - 3) / 2);
////   }

//  else if((adj % 6) == 0)
//  {

// //  if(adj % 6)
// //    ;
// //  else // clk = 4, 10, 16, 22
//   clock_index = adj / 6;
//  }

//  else if( (clk % 2) && ((clk - 1) % 6))
//  {
//   u1 uclk = (clk - 3) / 2;
//   if(uclk > 2)
//     clock_index = uclk - (uclk - 2) / 3  - 1;
//   else clock_index = uclk;
//   //clock_index = 100 + ((clk - 3) / 2);
//  }


//  else
////   if //(mch.first == 0) //
////   (  ((clk % 2) == 0)   //((clk % 2 == 0) && ((clk - 4) % 6))

////    ||  ((clk - 1) % 6) == 0
////   )
//    // 6,8, 12,14, 18,20  24,2
//  {
//   u1 uclk;
//   s1 sclk;
//   switch (size_even_odd_code)
//   {
//   case 0:
//    uclk = clk % 6? clk + 1 : clk - 1;
//    sclk = (uclk / 3);
//    if(clk % 6)
//      --sclk;
//    clock_index = (u1) (sclk % 8);
//    break;
//   case 1:
//    if(clk % 2) // 1, 13
//      clock_index = (clk - 1) / 4;
//    else if(clk % 6) // 8, 20            // !% ?
//      clock_index = 3 + ((clk - 12) / 4);
//    else  // 6, 18
//      clock_index = ((clk + 2) / 4) - 1;
//    break;
//   case 2:
//    if(clk % 2) // 7, 19
//      clock_index = 1 + ((clk - 7) / 4);
//    else if(clk % 6) // 2, 14
//      clock_index = (clk - 2) / 4;
//    else // 12, 24
//      clock_index = 2 + ((clk - 12) / 4);
//    break;
//   case 3:
//      clock_index = (clk - 1) / 6;
//    break;
//   default:
//    break;

//   }
//  }

// //}

//   //static u1 index[4] {};
////   switch (size_even_odd_code)
////   {
////   case 0: clock_index = quadrant_code; break;
////   case 1: clock_index = 1 - quadrant_code % 2; break;
////   case 2: clock_index = 1 - quadrant_code % 2; break;
////   default: break;
////   }

// //red
// //u1 index[4][25] =

//}


