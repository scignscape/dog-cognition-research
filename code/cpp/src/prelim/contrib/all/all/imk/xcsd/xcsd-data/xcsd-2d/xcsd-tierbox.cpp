
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "xcsd-tierbox.h"

#include "xcsd-image.h"

Box3x3_8bytepx::Box3x3_8bytepx()
 :  color_average(0)
{
// for(u1 count = 0; count < 9; ++count)
// {
//  pixels.get_at(count) = 0;
// }
}

Box9x9_8bytepx::Box9x9_8bytepx()
 :  vec_3x3({0})
{
 vec_3x3.init_static_hive(9);
 for(u1 count = 0; count < 9; ++count)
 {
  Box3x3_8bytepx* ptr = vec_3x3.get(count);
  Box3x3_8bytepx* box = new (ptr) Box3x3_8bytepx;
//  vec_3x3.get_at(count) = box;
//  Box3x3_8bytepx* box = new Box3x3_8bytepx;
//  Box3x3_8bytepx* box1 = new (ptr) Box3x3_8bytepx;
 }
}



XCSD_TierBox::XCSD_TierBox(rc2 matrix_position)
  :  non_full_(0), full_tier_index_(0),
     matrix_position_(matrix_position), mch_code_({0,0}),
     pixel_data_ground_offset_(0),
     tier_ring_(0),
     inner_pushout_(0),
     compressed_clock_index_(0),
     full_clock_index_(0),
     intra_tier_ring_index_(0),
     reference_color_(0), color_average_(0),
     global_top_left_({0,0})
{
 init_boxes();
}

void XCSD_TierBox::check_calculate_pixel_averages_1byte(u1 start_byte, u1 end_byte,
  XCSD_Image* image, n8* reset)
{
 check_calculate_pixel_averages_1byte_level1(start_byte, end_byte, image, reset);
 check_calculate_pixel_averages_1byte_level2(start_byte, end_byte, image, reset);
 check_calculate_pixel_averages_1byte_level3(start_byte, end_byte, image, reset);
}


void XCSD_TierBox::check_calculate_pixel_averages_1byte_level1(u1 start_byte, u1 end_byte,
  XCSD_Image* image, n8* reset)
{
 u1 code = (start_byte - 1);
 u1 diff = end_byte - start_byte;
 if(diff > 3)
 {
  // //  idea here is use highest bit combined with
   //    no diff to signal diff unexpectedly large,
   //    because the 8th-bit 2byte flag wouldn't
   //    ordinarily use the diff bits
  code |= 128;
  diff -= 3;
  if(diff > 3)
    // //  so diff can't be more than 6 ...
    diff = 3;
 }
 code |= diff << 3;

 if(checked_average_codes_.count(code) > 0)
   return;

 checked_average_codes_.insert(code);

 u4 fti = full_tier_index();

//  u4 offset = tbox->pixel_data_ground_offset();
//  n8* start = data_.get_pixel_data_start(offset);
//  std::map<s1, std::pair<u2, std::vector<n8>>> sdi;

 std::map<s1, std::pair<u2, std::vector<n8>>> sdi;

 //u4 start =

 image->data_tierbox_to_sdi_pixel_map(fti, sdi);


 for(auto const& [ab_s1, thr_vec]: sdi)
 {
  n8 avg_3x3 = 0;

  u2 averages[8] = {0}; // // seems we don't need more than 2 bytes for sum ...

  for(u1 v = 0; v < 9; ++v)
  {
   n8 pixel = thr_vec.second[v];

   for(u1 u = start_byte - 1; u < end_byte; ++u)
     averages[u] += (u1)(pixel >> (u << 3));
  }
  for(u1 u = start_byte - 1; u < end_byte; ++u)
    avg_3x3 |= ((n8)((u1)(averages[u] / 9)) << (u << 3));

  XCSD_TierBox::_inner_box_3x3* box = get_3x3_box(ab_s1);

  if(reset)
    box->color_average = *reset;

  box->color_average |= avg_3x3;
 }

}

void XCSD_TierBox::check_calculate_pixel_averages_1byte_level2(u1 start_byte, u1 end_byte,
  XCSD_Image* image, n8* reset)
{
 for(u1 b = 0; b < 9; ++b)
 {
  _inner_box_9x9* box = box9x9_.get(b);

  n8 avg_9x9 = 0;

  u2 averages_9x9[8] = {0}; // // seems we don't need more than 2 bytes for sum ...

  for(u1 v = 0; v < 9; ++v)
  {
   _inner_box_3x3* vbox = box->vec_3x3.get(v);

   for(u1 u = start_byte - 1; u < end_byte; ++u)
   {
    n8 pixel = vbox->color_average;
    averages_9x9[u] += (u1)(pixel >> (u << 3));
   }
  }

  for(u1 u = start_byte - 1; u < end_byte; ++u)
  {
   avg_9x9 |= ((n8)((u1)(averages_9x9[u] / 9)) << (u << 3));
  }

  if(reset)
    box->color_average = *reset;

  box->color_average = avg_9x9;
 }


}

void XCSD_TierBox::check_calculate_pixel_averages_1byte_level3(u1 start_byte, u1 end_byte,
  XCSD_Image* image, n8* reset)
{
 if(reset)
   color_average_ = *reset;

 u2 averages_27x27[8] = {0}; // // seems we don't need more than 2 bytes for sum ...

 n8 avg_27x27 = 0;

 for(u1 b = 0; b < 9; ++b)
 {
  _inner_box_9x9* box = box9x9_.get(b);

  for(u1 u = start_byte - 1; u < end_byte; ++u)
  {
   n8 pixel = box->color_average;
   averages_27x27[u] += (u1)(pixel >> (u << 3));
  }
 }

 for(u1 u = start_byte - 1; u < end_byte; ++u)
 {
  avg_27x27 |= ((n8)((u1)(averages_27x27[u] / 9)) << (u << 3));
 }

 color_average_ |= avg_27x27;


}


XCSD_TierBox::_inner_box_9x9* XCSD_TierBox::get_9x9_box(s1 a_s1)
{
 return box9x9_.get(a_s1 - 1);
}

XCSD_TierBox::_inner_box_3x3* XCSD_TierBox::get_3x3_box(s1 ab_s1)
{
 ab1 ab = ab1::from_base_10(ab_s1).double_minus(1); // {(u1)((u1)ab_s1 / 10), (u1)((u1)ab_s1 % 10)};

 _inner_box_9x9* abox = box9x9_.get(ab.a);
 return abox->vec_3x3.get(ab.b);
}

void XCSD_TierBox::init_boxes()
{
 if(non_full_ == 0)
 {
  box9x9_.init_static_hive(9);
  for(u1 count = 0; count < 9; ++count)
  {
   //box9x9_[count] = Box9x9_8bytepx()
   //box9x9_.get_at(count) = Box9x9_8bytepx();
   Box9x9_8bytepx* ptr = box9x9_.get(count);
   Box9x9_8bytepx* box = new (ptr) Box9x9_8bytepx;

  }
 }
}


u2 XCSD_TierBox::non_full_h() const
{
 u1 result = non_full_ & 0b0000'0000'0001'1111;
 if(result < 27)
   return result;
 return 0;
}

u2 XCSD_TierBox::non_full_v() const
{
 u1 result = (non_full_ & 0b0000'0111'1100'0000) >> 6;
 if(result < 27)
   return result;
 return 0;
}

void XCSD_TierBox::set_non_full_h(u2 h)
{
 if(h < 27)
 {
  non_full_ &= 0b0000'0000'0001'1111;
  non_full_ |= h;
 }
}

void XCSD_TierBox::set_non_full_v(u2 v)
{
 if(v < 27)
 {
  non_full_ &= 0b0000'0111'1100'0000;
  non_full_ |= (v << 6);
 }
}


bool XCSD_TierBox::non_full_up() const
{
 u1 result = non_full_ & 0b0000'0000'0001'1111;
 if(result < 27)
   return result;
 return 0;
}

bool XCSD_TierBox::non_full_left() const
{
 u1 result = (non_full_ & 0b0000'0111'1100'0000) >> 6;
 if(result < 27)
   return result;
 return 0;
}

void XCSD_TierBox::set_non_full_up(bool v)
{
 if(v)
   non_full_ |= 0b0000'0000'0010'0000;
 else
   non_full_ &= 0b1111'1111'1101'1111;
}

void XCSD_TierBox::set_non_full_left(bool h)
{
 if(h)
   non_full_ |= 0b0000'1000'0000'0000;
 else
   non_full_ &= 0b1111'0111'1111'1111;
}

u2 XCSD_TierBox::get_scanline_offset_sdi(s2 index)
{
 xy1 result = get_local_ground_location_sdi(index);
 return result.y * 27 + result.x;
}


u2 XCSD_TierBox::get_ground_offset_sdi(s2 index)
{
 bool negate = normalize_sdi_index(index);

 if(negate)
   return 81 * (9 - (index / 100)) +
     9 * (9 - ((index % 100) / 10)) + 9 - index % 10;

 else
   return 81 * ((index / 100) - 1) +
     9 * (((index % 100) / 10) - 1) + index % 10 - 1;
}


xy1 XCSD_TierBox::get_local_ground_location_sdi(s2 index)
{
 bool negate = normalize_sdi_index(index);
 s1 index10 = (s1)(index / 10);

 if(negate)
   index10 = -index10;

 index %= 10;
 if(index == 0)
   index = 5;
 else if(negate)
   index = 10 - index;

 --index;

 xy1 result = get_local_ground_location_for_inner_top_left(index10);

 return result.add({(u1)(index % 3), (u1)(index / 3)});

}

bool XCSD_TierBox::normalize_sdi_index(s2& index)
{
 if(index == 0)
 {
  index = 555;
  return false;
 }

 bool result = false;
 if(index < 0)
 {
  result = true;
  index = -index;
 }

 if(index < 10)
 {
  // //  001 - 009 are treated as a "ring"
   //    around the center 9x9, like the 3x3 case
  if(result)
  {
   result = false;
   index = 10 - index;
  }

  // //  001 -> 019 which will -> 199, etc.
  index = index * 10 + 10 - index;
 }

 else if((index % 100) < 10)
 {
  // //  _01 -> _19, etc., same pattern as
   //    with 3x3s but on the pixel scale
  u1 i100 = index % 100;
  index -= i100;
  index += 100 * 10 + 10 - i100;
 }

 return result;
}


bool XCSD_TierBox::normalize_inner_index(s1& index)
{
 if(index == 0)
 {
  index = 55;
  return false;
 }

 bool result = false;

 if(index < 0)
 {
  result = true;
  index = -index;
 }

 if(index > 99)
 {
  index = 55;
  return false;
 }

 if(index < 10)
 {
  if(result)
    index = 10 - index;

  // //  somewhat arbitrarily, make 01 - 09 mean
   //    the nearest 3x3 box to the center 9x9,
   //    except 05 which is the center overall.
   //    That is, 01 -> 19, 02 -> 28, etc.

  index = 10 * index + 10 - index;
 }

 if(index % 10)
 {
  if(result)
    index = 110 - index;
 }
 else
 {
  if(result)
    index = 100 - index;
  index += 5; // move to center
 }

 return result;
}


u2 XCSD_TierBox::get_scanline_offset_for_inner_top_left(s1 index)
{
 xy1 loc = get_local_ground_location_for_inner_top_left(index);
 return loc.y * 27 + loc.x;
}

u2 XCSD_TierBox::get_scanline_offset_for_inner_center(s1 index)
{
 xy1 loc = get_local_ground_location_for_inner_center(index);
 return loc.y * 27 + loc.x;
}


//xy1 XCSD_TierBox::get_inner_location_for_inner_index(s1 index)
//{
// bool negate = normalize_inner_index(index);

//}


u2 XCSD_TierBox::get_ground_offset_for_inner_top_left(s1 index)
{
 bool negate = normalize_inner_index(index);

// u1 ten = negate? 9 - (index / 10) : (index / 10) - 1;
// u1 one = negate? 9 - (index % 10) : (index % 10) - 1;

// u1 teny = ten / 3;
// u1 oney = one / 3;

// u1 tenx = ten % 3;
// u1 onex = one % 3;


 if(negate)
   return 81 * (9 - (index / 10)) + 9 * (9 - (index % 10));

 return 81 * ((index / 10) - 1) + 9 * ((index % 10) - 1);
}

u2 XCSD_TierBox::get_ground_offset_for_inner_center(s1 index)
{
 return get_ground_offset_for_inner_top_left(index) + 4;
}

xy1 XCSD_TierBox::get_local_ground_location_for_inner_top_left(s1 index)
{
 bool negate = normalize_inner_index(index);

 u1 ten = negate? 9 - (index / 10) : (index / 10) - 1;
 u1 one = negate? 9 - (index % 10) : (index % 10) - 1;

 u1 teny = ten / 3;
 u1 oney = one / 3;

 u1 tenx = ten % 3;
 u1 onex = one % 3;

 return {(u1)(tenx * 9 + onex * 3), (u1)(teny * 9 + oney * 3)};
}

XCSD_TierBox::_inner_box XCSD_TierBox::get_inner_box(s1 index)
{

 if(index > 99)
   return {nullptr};

 if(index == 0)
   return _inner_box {._this = this};

 bool negate = false;
 if(index < 0)
 {
  negate = true;
  index = -index;
  if(index > 99)
    return {nullptr};
 }

 if(index < 10)
 {
  if(negate)
    index = 10 - index;

  // //  somewhat arbitrarily, make 01 - 09 mean
   //    the nearest 3x3 box to the center 9x9,
   //    except 05 which is the center overall.
   //    That is, 01 -> 19, 02 -> 28, etc.

  index = 10 * index + 10 - index;
 }

 if(index % 10)
 {
  if(negate)
    index = 110 - index;
  return {box9x9_.at_index((index / 10) - 1).vec_3x3.get((index % 10) - 1)};
 }

 if(negate)
   index = 100 - index;

 return _inner_box {._9x9 = box9x9_.get((index / 10) - 1)};

}
