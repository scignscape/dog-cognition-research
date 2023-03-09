
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "xcsd-image.h"

#include "xcsd-tierbox.h"

#include <QPainter>

#include <QPainterPath>

#include <cmath>


#include "textio.h"

#include "mat2d.templates.special-modes.h"

#include "local-histogram-data.h"

USING_KANS(TextIO)

USING_XCNS(XCSD)

XCSD_Image::XCSD_Image()
  :  set_channels_info_(Set_Channels_Info::Nothing_Set),
     outer_ring_info_(nullptr),
     background_pole_(Qt::white),
     foreground_pole_(Qt::black)

//  :  tier_counts_({0,0}),
//     horizontal_outer_sizes_({0,0}),
//     vertical_outer_sizes_({0,0}),
//     tierbox_count_(0), tierboxes_(nullptr)
{

}


void XCSD_Image::find_ntxh_file(QString file_path, u1 maybe_up)
{
 QFileInfo qfi(file_path + ".ntxh");

 if(qfi.exists())
   ntxh_file_ = qfi.absoluteFilePath();


 else if(maybe_up)
 {
  --maybe_up;
  QDir qd = qfi.absoluteDir();
  if(qd.cdUp())
    find_ntxh_file(qd.absoluteFilePath(qfi.completeBaseName()), maybe_up);
 }

 if(ntxh_file_.isEmpty())
   if(qfi.baseName() != qfi.completeBaseName())
     find_ntxh_file(qfi.absolutePath() + "/" + qfi.baseName());

}


void XCSD_Image::load_image(QString path, QString* ntxh_file)
{
 image_.load(path);

 if(ntxh_file)
 {
  find_ntxh_file(path);
  *ntxh_file = ntxh_file_;
 }
}

void XCSD_Image::load_image_all(QString path, QString* ntxh_file)
{
 load_image(path, ntxh_file);
 init_geometry();
 geometry_.init_tier_counts(XCSD_Image_Geometry::TierGrid_Preferances::Minimize_Outer_Tiers);
 geometry_.init_outer_ring_positions();
 init_pixel_data(); //ROOT_FOLDER "/../test/ukraine");
 init_tierboxes();
}


XCSD_TierBox* XCSD_Image::get_tierbox_at_ground_position(u2 x, u2 y)
{

}

// void autoset_fb_poles(u1 center = 30, QPair<u1, u1> top = {4, 4},
//   QPair<u1, u1> bottom = {4, 4}, QPair<u1, u1> left = {0, 0}, QPair<u1, u1> right = {0, 0});


void XCSD_Image::init_geometry()
{
 geometry_.set_total_size(get_wh());
}

void XCSD_Image::init_pixel_data(QString info_folder)
{
 static u2 box_area = tierbox_width * tierbox_width;

 data_.init_pixels(geometry_.total_size());

 init_outer_ring_pixel_data();

 XCSD_Image_Geometry::Iteration_Environment ienv = geometry_.formulate_iteration_environment();

 geometry_.for_each_full_tierbox([this, &ienv, &info_folder](XCSD_Image_Geometry::Grid_TierBox& gtb)
 {
  QString info_path;
  QString info_string;

  u4 index = geometry_.get_tierbox_index(gtb, ienv.size_even_odd_info, nullptr);
  u4 threshold = index * box_area;

  if(!info_folder.isEmpty())
  {
   info_path = QString("%1/%2-%3-%4.txt").arg(info_folder).arg(gtb.loc.r())
     .arg(gtb.loc.c()).arg(threshold);
   info_string = QString("Full tierbox %1 %2 (%3)\n\n").arg(gtb.loc.r()).arg(gtb.loc.c()).arg(index);
  }

  u2 threshold_offset = 0;

  xy2 tl = gtb.top_left();

  QImage ci = image_.copy(tl.x, tl.y, tierbox_width, tierbox_width);
  if(ci.format() != QImage::Format_ARGB32)
  {
   ci = ci.convertToFormat(QImage::Format_ARGB32);
  }

  if(!info_path.isEmpty())
  {
   ci.save(info_path + ".png");
  }

  std::map<s1, std::vector<n8>> sdi;

  // temporary
  initial_setup_tierbox_ = gtb.loc.rc();

  image_tierbox_to_sdi_pixel_map(ci, sdi);

  u4 offset;

  for(u1 a = 1; a <= 9; ++a)
   for(u1 b = 1; b <= 9; ++b)
   {
    const std::vector<n8>& data3x3 = sdi[(ab1{a,b}).to_base(10)];

    data_.copy_pixels(threshold + threshold_offset, data3x3);

    offset = threshold_offset;
    threshold_offset += 9;

    if(!info_string.isEmpty())
    {
     abg1 abg {a,b,0};

     info_string += QString("\nSDI location %1\n").arg(ab1{a,b}.to_base(10));
     u1 vi = 0;
     for(u1 y = 0; y < 3; ++y)
     {
      ++abg.g;
      xy1 xy_0 = XCSD_TierBox::get_local_ground_location_sdi(abg.to_base(10));
      ++abg.g;
      xy1 xy_1 = XCSD_TierBox::get_local_ground_location_sdi(abg.to_base(10));
      ++abg.g;
      xy1 xy = XCSD_TierBox::get_local_ground_location_sdi(abg.to_base(10));


//      info_string += QString(" %1 %2 %3\n").arg(data3x3[vi], 16, 16, QChar('0'))
//        .arg(data3x3[vi + 1], 16, 16, QChar('0')).arg(data3x3[vi + 2], 16, 16, QChar('0'));

      info_string += QString(" %1-%2:%3 %4-%5:%6 %7-%8:%9\n")
        .arg(xy_0.to_qstring(2))
        .arg(offset++, 3, 10, QChar('0'))
        .arg(data3x3[vi], 16, 16, QChar('0'))
        .arg(xy_1.to_qstring(2))
        .arg(offset++, 3, 10, QChar('0'))
        .arg(data3x3[vi + 1], 16, 16, QChar('0'))
        .arg(xy.to_qstring(2))
        .arg(offset++, 3, 10, QChar('0'))
        .arg(data3x3[vi + 2], 16, 16, QChar('0'));


      vi += 3;
     }
    }
   }

  if(!info_path.isEmpty())
    save_file(info_path, info_string);

 });


}


void XCSD_Image::init_outer_ring_pixel_data()
{
 if(geometry_.full_tier_counts().is_ascending()) // w < h
   _init_outer_ring_pixel_data_portrait();
 else
   _init_outer_ring_pixel_data_landscaoe();
}


n8 XCSD_Image::qrgb_to_pixel_number(QRgb rgb)
{
 n8 result = 0;

 // //  the (n8) casts here are strictly speaking unnecessary
  //    but could become necessary with something other
  //    than 1-byte rgba ...
 result |= (n8)qRed(rgb);
 result |= (n8)qGreen(rgb) << 8;
 result |= (n8)qBlue(rgb) << 16;
 result |= (n8)(255 - qAlpha(rgb)) << 24;

 return result;
}

void XCSD_Image::_init_outer_ring_pixel_data(QRgb* scanline,
  u4 mark_offset, u4 start_offset, se2 x_se)
{
 // //  too small?
 if(!scanline)
   return;

 for(u2 x = x_se.start; x <= x_se.end; ++x)
 {
  QRgb qpixel = scanline[x];
  n8 pixel = qrgb_to_pixel_number(qpixel);
  data_.init_single_pixel(start_offset + mark_offset, pixel);

  //  qDebug() << "x = " << x << "y = " << y << " index = " << start_offset + mark_offset << " pixel = " << pixel;

  ++mark_offset;
 }
}


//void XCSD_Image::_init_outer_ring_pixel_data(u4 start_offset,
//  XCSD_Image_Geometry::Outer_Ring_Positions::Landscape start_area_index,
//  XCSD_Image_Geometry::Outer_Ring_Positions::Landscape end_area_index, se2 x_se, mm2 y_mm)
//{

//// QImage ci = image_.copy(x_se.start, y_mm.min, x_se.inner_span(), y_mm.inner_span());
//// ci.save(QString("/home/nlevisrael/gits/ctg-temp/test/tmp/temp-%1.png").arg((u1)area_index));

// for(u2 y = y_mm.min; y <= y_mm.max; ++y)
// {
//  for(u1 i = (u1) start_area_index; i < (u1) end_area_index; ++i)
//  {
//   QRgb* scanline = (QRgb*) image_.constScanLine(y);
//   u4 mark_offset = geometry_.outer_ring_positions().offset_for(
//     (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape)i)
//     + (y - y_mm.min) * x_se.inner_span();

//   _init_outer_ring_pixel_data(scanline, mark_offset, start_offset, x_se);
//  }
// }
//}


void XCSD_Image::_init_outer_ring_pixel_data_portrait(u4 start_offset,
  se1 area_index_se, pr4 outside_xareas, pr1 outside, mm2 y_mm, u1 index_gap, u2 x_ses [4])
{
 u1 x_ses_count = 0;

 for(u2 y = y_mm.min; y <= y_mm.max; ++y)
 {
  QRgb* scanline = (QRgb*) image_.constScanLine(y);

  se2 x_se; u4 mark_offset; u1 area_index;

  for(area_index = area_index_se.start; area_index <= area_index_se.end; area_index += index_gap)
  {
   u4 extra_offset = (outside.second != 0)? 0 : x_ses_count & 2? outside_xareas.second : outside_xareas.first;
   x_se = x_ses? se2{x_ses[x_ses_count++], x_ses[x_ses_count++]}:
     geometry_.outer_ring_positions().index_pairs[area_index];
   mark_offset = geometry_.outer_ring_positions().offset_for_area_index(area_index)
     + (y - y_mm.min) * x_se.inner_span();
   _init_outer_ring_pixel_data(scanline, mark_offset, start_offset + extra_offset, x_se);
   x_ses_count %= 4;
  }

  //if(index_gap == 1)
  if(outside.second != 0)
  {
   area_index = outside.first;
   x_se = {0, geometry_.outer_ring_positions().index_pairs[area_index].start};
   mark_offset = geometry_.outer_ring_positions().offset_for_area_index(area_index)
     + (y - y_mm.min) * x_se.inner_span();

   _init_outer_ring_pixel_data(scanline, mark_offset, start_offset + outside_xareas.first, x_se);

   area_index = outside.second;

   x_se = {geometry_.outer_ring_positions().index_pairs[area_index].start,
     (u2)(geometry_.total_size().width - 1)};
   mark_offset = geometry_.outer_ring_positions().offset_for_area_index(area_index)
     + (y - y_mm.min) * x_se.inner_span();
   _init_outer_ring_pixel_data(scanline, mark_offset, start_offset + outside_xareas.second, x_se);
  }
 }
}


void XCSD_Image::_init_outer_ring_pixel_data(u4 start_offset,
  se1 area_index_se, pr4 outside_xareas, pr1 outside, mm2 y_mm, u1 index_gap, u2 x_ses [4])
{
 // : se2{0, geometry_.horizontal_outer_sizes().left};

 u1 x_ses_count = 0;

 for(u2 y = y_mm.min; y <= y_mm.max; ++y)
 {
  QRgb* scanline = (QRgb*) image_.constScanLine(y);

  se2 x_se; u4 mark_offset; u1 area_index;

  for(area_index = area_index_se.start; area_index <= area_index_se.end; area_index += index_gap)
  {
   x_se = x_ses? se2{x_ses[x_ses_count++], x_ses[x_ses_count++]}:
     geometry_.outer_ring_positions().index_pairs[area_index];
   mark_offset = geometry_.outer_ring_positions().offset_for_area_index(area_index)
     + (y - y_mm.min) * x_se.inner_span();

   u4 extra_offset = (outside.second != 0)? 0 : x_ses_count & 2? outside_xareas.second : outside_xareas.first;

   _init_outer_ring_pixel_data(scanline, mark_offset, start_offset + extra_offset, x_se);
   x_ses_count %= 4;
  }

  //if(index_gap == 1)
  if(outside.second != 0)
  {
   area_index = outside.first;
   x_se = {0, geometry_.outer_ring_positions().index_pairs[area_index].end};
   mark_offset = geometry_.outer_ring_positions().offset_for_area_index(area_index)
     + (y - y_mm.min) * x_se.inner_span();

//   if(outside.first == 0)
   _init_outer_ring_pixel_data(scanline, mark_offset, start_offset + outside_xareas.first, x_se);

   area_index = outside.second;
   x_se = {geometry_.outer_ring_positions().index_pairs[area_index].end,
     (u2)(geometry_.total_size().width - 1)};
   mark_offset = geometry_.outer_ring_positions().offset_for_area_index(area_index)
     + (y - y_mm.min) * x_se.inner_span();

//   if(outside.second == 5)
   _init_outer_ring_pixel_data(scanline, mark_offset, start_offset + outside_xareas.second, x_se);
  }
 }
}


void XCSD_Image::_init_outer_ring_pixel_data_portrait(u4 start_offset,
  se1 area_index_se, pr4 outside_xareas, pr1 outside)
{
 u2 x_ses [4] {0, (u2)(geometry_.horizontal_outer_sizes().left - 1),
   (u2)(geometry_.total_size().width - geometry_.horizontal_outer_sizes().right),
   (u2)(geometry_.total_size().width - 1)};

 se2 first_pair = geometry_.outer_ring_positions().index_pairs[area_index_se.start];
 mm2 y_mm = first_pair._to<mm2>();

 _init_outer_ring_pixel_data_portrait(start_offset, area_index_se,
   outside_xareas, outside, y_mm, area_index_se.transposed_inner_difference(), x_ses);
}


void XCSD_Image::_init_outer_ring_pixel_data(u4 start_offset,
  se1 area_index_se, pr4 outside_xareas, pr1 outside)
{
 u2 x_ses [4] {0, (u2)(geometry_.horizontal_outer_sizes().left - 1),
   (u2)(geometry_.total_size().width - geometry_.horizontal_outer_sizes().right),
   (u2)(geometry_.total_size().width - 1)};

 se2 first_pair = geometry_.outer_ring_positions().index_pairs[area_index_se.start];
 mm2 y_mm = first_pair._to<mm2>();

 _init_outer_ring_pixel_data(start_offset, area_index_se,
   outside_xareas, outside, y_mm, area_index_se.transposed_inner_difference(), x_ses);
}

void XCSD_Image::_init_outer_ring_pixel_data(u4 start_offset,
  se1 area_index_se)
{
 _init_outer_ring_pixel_data(start_offset,
   area_index_se, {0, 0}, pr1 {0, 0});
}



void XCSD_Image::_init_outer_ring_pixel_data_portrait(u4 start_offset,
  se1 area_index_se)
{
 _init_outer_ring_pixel_data_portrait(start_offset,
   area_index_se, {0, 0}, pr1 {0, 0});
}



void XCSD_Image::_init_outer_ring_pixel_data_portrait(u4 start_offset,
  se1 area_index_se, pr4 outside_xareas, mm2 y_mm)
{
 u2 x_ses [4] {0, (u2)(geometry_.horizontal_outer_sizes().left - 1),
   (u2)(geometry_.total_size().width - geometry_.horizontal_outer_sizes().right),
   (u2)(geometry_.total_size().width - 1)};

 _init_outer_ring_pixel_data_portrait(start_offset, area_index_se,
    outside_xareas, {0, 0}, y_mm, area_index_se.transposed_inner_difference(), x_ses);
}


void XCSD_Image::_init_outer_ring_pixel_data(u4 start_offset,
  se1 area_index_se, pr4 outside_xareas, mm2 y_mm)
{
 u2 x_ses [4] {0, (u2)(geometry_.horizontal_outer_sizes().left - 1),
   (u2)(geometry_.total_size().width - geometry_.horizontal_outer_sizes().right),
   (u2)(geometry_.total_size().width - 1)};

 _init_outer_ring_pixel_data(start_offset, area_index_se,
    outside_xareas, {0, 0}, y_mm, area_index_se.transposed_inner_difference(), x_ses);
}


//void XCSD_Image::_init_outer_ring_pixel_data(u4 start_offset,
//  XCSD_Image_Geometry::Outer_Ring_Positions::Landscape start_area_index,
//  XCSD_Image_Geometry::Outer_Ring_Positions::Landscape end_area_index, se2 x_se)
//{
// se2 first_pair = geometry_.outer_ring_positions().index_pairs[(u1)start_area_index];
// mm2 y_mm = first_pair._to<mm2>();
// //init_outer_ring_pixel_data(start_offset, start_area_index, end_area_index, x_se, y_mm);
//}

void XCSD_Image::_init_outer_ring_pixel_data(u4 start_offset,
  XCSD_Image_Geometry::Outer_Ring_Positions::Landscape area_index,
  se2 x_se, mm2 y_mm)
{
// QImage ci = image_.copy(x_se.start, y_mm.min, x_se.inner_span(), y_mm.inner_span());
// ci.save(QString("/home/nlevisrael/gits/ctg-temp/test/tmp/temp-%1.png").arg((u1)area_index));
 for(u2 y = y_mm.min; y <= y_mm.max; ++y)
 {
  QRgb* scanline = (QRgb*) image_.constScanLine(y);
  u4 mark_offset = geometry_.outer_ring_positions().offset_for(area_index)
    + (y - y_mm.min) * x_se.inner_span();

  _init_outer_ring_pixel_data(scanline, mark_offset, start_offset, x_se);
 }
}


//  for(u2 x = x_se.start; x <= x_se.end; ++x)
//  {
//   QRgb qpixel = scanline[x];
//   n8 pixel = qrgb_to_pixel_number(qpixel);
//   data_.init_single_pixel(start_offset + mark_offset, pixel);

//   //  qDebug() << "x = " << x << "y = " << y << " index = " << start_offset + mark_offset << " pixel = " << pixel;

//   ++mark_offset;
//  }
// for(u1 i = (u1) start_area_index; i < (u1) end_area_index; ++i)
// {

//  for(u2 y = y_mm.min; y <= y_mm.max; ++y)
//  {
//    QRgb* scanline = (QRgb*) image_.constScanLine(y);
//    u4 mark_offset = geometry_.outer_ring_positions().offset_for(area_index)
//      + (y - y_mm.min) * x_se.inner_span();

//    _init_outer_ring_pixel_data(scanline, mark_offset, start_offset, x_se);
//  }

//  QRgb* scanline = (QRgb*) image_.constScanLine(y);
//  u4 mark_offset = geometry_.outer_ring_positions().offset_for(
//    (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape)i)
//    + (y - y_mm.min) * x_se.inner_span();

//  _init_outer_ring_pixel_data(scanline, mark_offset, start_offset, x_se);
// }


void XCSD_Image::_init_outer_ring_pixel_data_landscaoe_sym()
{
 u4 offset = geometry_.get_total_full_tierbox_area();

 //u1 height = geometry_.vertical_outer_sizes().top;
 u1 long_strip_width = geometry_.vertical_outer_sizes().top;
 u1 short_strip_width = geometry_.horizontal_outer_sizes().left;

 u2 total_longer_side = geometry_.total_size().width - 1;
 u2 total_longer_side_without_strip = geometry_.total_size().width - geometry_.horizontal_outer_sizes().right;

 u2 total_shorter_side = geometry_.total_size().height - 1;
 u2 total_shorter_side_without_strip = geometry_.total_size().height - geometry_.vertical_outer_sizes().bottom;


 _init_outer_ring_pixel_data(offset, se1{0, 5});
 _init_outer_ring_pixel_data(offset, se1{1, 6});
 _init_outer_ring_pixel_data(offset, se1{2, 7});

 u1 index = 3;

 se2 current_pair = geometry_.outer_ring_positions().index_pairs[index];
 se2 x_se = {0, current_pair.end};
 mm2 y_mm = {0, (u2)(long_strip_width - 1)};

 pr4 xareas_prior, xareas_later;

 xareas_prior.first = x_se.inner_span() * y_mm.inner_span();

// y_mm = {(u2)(y_mm.max + 1), current_pair.start};

 index = 4;
 current_pair = geometry_.outer_ring_positions().index_pairs[index];
 y_mm = {current_pair.start, (u2)(total_shorter_side_without_strip - 1)};
 x_se.end = short_strip_width - 1;
 xareas_later.first = x_se.inner_span() * y_mm.inner_span();

// y_mm = {(u2)(y_mm.max + 1), total_bottom};
// x_se.end = current_pair.end;

 index = 8;
 current_pair = geometry_.outer_ring_positions().index_pairs[index];
 y_mm = {0, (u2)(long_strip_width - 1)};
 x_se = {current_pair.end, total_longer_side};
 xareas_prior.second = x_se.inner_span() * y_mm.inner_span();

 y_mm = {long_strip_width, current_pair.start};
 _init_outer_ring_pixel_data(offset, se1{3, 8}, xareas_prior, y_mm);


 index = 9;
 current_pair = geometry_.outer_ring_positions().index_pairs[index];
 y_mm = {current_pair.start, (u2)(total_shorter_side_without_strip - 1)};

 _init_outer_ring_pixel_data(offset, se1{4, 9}, {0, 0}, y_mm);

 x_se.start = total_longer_side_without_strip;
 xareas_later.second = x_se.inner_span() * y_mm.inner_span();

 y_mm = {0, (u2)(long_strip_width - 1)};
 _init_outer_ring_pixel_data(offset, {10, 12}, {0, 0}, {3, 8}, y_mm);

 y_mm = {total_shorter_side_without_strip, total_shorter_side};
 _init_outer_ring_pixel_data(offset, {13, 15}, xareas_later, {4, 9}, y_mm);
}


void XCSD_Image::_init_outer_ring_pixel_data_portrait_sym()
{
 u4 offset = geometry_.get_total_full_tierbox_area();

 //u1 height = geometry_.vertical_outer_sizes().top;
 u1 long_strip_width = geometry_.horizontal_outer_sizes().left;
 u1 short_strip_width = geometry_.vertical_outer_sizes().top;

 u2 total_longer_side = geometry_.total_size().height - 1;
 u2 total_longer_side_without_strip = geometry_.total_size().height - geometry_.vertical_outer_sizes().bottom;

 u2 total_shorter_side = geometry_.total_size().width - 1;
 u2 total_shorter_side_without_strip = geometry_.total_size().width - geometry_.horizontal_outer_sizes().right;

 mm2 y_mm = {0, (u2)(short_strip_width - 1)};

 _init_outer_ring_pixel_data_portrait(offset, {0, 2}, {0, 0}, {3, 4},
    y_mm, 1);

 pr4 xareas_bottom, xareas_top;

 u1 index = 3;
 se2 current_pair = geometry_.outer_ring_positions().index_pairs[index];
 y_mm = {0, (u2)(short_strip_width - 1)};
 se2 x_se {0, (u2)(current_pair.start)};
 xareas_top.first = y_mm.inner_span() * x_se.inner_span();

 index = 4;
 current_pair = geometry_.outer_ring_positions().index_pairs[index];
 x_se = {current_pair.start, total_shorter_side};
 xareas_top.second = y_mm.inner_span() * x_se.inner_span();

 y_mm = {short_strip_width, current_pair.end};

 _init_outer_ring_pixel_data_portrait(offset, se1{3, 4}, xareas_top, y_mm);

 index = 8;
 current_pair = geometry_.outer_ring_positions().index_pairs[index];
 y_mm = {current_pair.end, (u2)(total_longer_side_without_strip - 1)};
 x_se = {0, (u2)(long_strip_width - 1)};
 xareas_bottom.first = y_mm.inner_span() * x_se.inner_span();

 index = 9;
 current_pair = geometry_.outer_ring_positions().index_pairs[index];
 y_mm = {current_pair.end, (u2)(total_longer_side_without_strip - 1)};
 x_se = {total_shorter_side_without_strip, total_shorter_side};
 xareas_bottom.second = y_mm.inner_span() * x_se.inner_span();

  _init_outer_ring_pixel_data_portrait(offset, se1{8, 9}, {0, 0}, y_mm);

 y_mm = {total_longer_side_without_strip, total_longer_side};

 _init_outer_ring_pixel_data_portrait(offset, {5, 7}, xareas_bottom, {8, 9},
    y_mm, 1);

 _init_outer_ring_pixel_data_portrait(offset, se1{10, 13});
 _init_outer_ring_pixel_data_portrait(offset, se1{11, 14});
 _init_outer_ring_pixel_data_portrait(offset, se1{12, 15});

}

void XCSD_Image::_init_outer_ring_pixel_data_portrait()
{
 _init_outer_ring_pixel_data_portrait_sym();
}

void XCSD_Image::_init_outer_ring_pixel_data_landscaoe()
{
 _init_outer_ring_pixel_data_landscaoe_sym();
 return;


 u4 offset = geometry_.get_total_full_tierbox_area();

 u1 height = geometry_.vertical_outer_sizes().top;
 u2 total_bottom = geometry_.total_size().height - 1;
 u2 height_from_bottom = geometry_.total_size().height - geometry_.vertical_outer_sizes().bottom;

 u1 left = geometry_.horizontal_outer_sizes().left;
// u1 right = geometry_.horizontal_outer_sizes().right;

 u2 total_right = geometry_.total_size().width - 1;
 u2 width_from_right = geometry_.total_size().width - geometry_.horizontal_outer_sizes().right;

 u1 index = 3;

 se2 current_pair = geometry_.outer_ring_positions().index_pairs[index];
 se2 x_se = {0, current_pair.end};
 mm2 y_mm = {0, (u2)(height - 1)};

 _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
    x_se, y_mm);

 u4 area = x_se.inner_span() * y_mm.inner_span();
 x_se.end = left - 1;
 y_mm = {(u2)(y_mm.max + 1), current_pair.start};

 _init_outer_ring_pixel_data(offset + area, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
   x_se, y_mm);

 for(index = 0; index <= 2; ++index)
 {
  current_pair = geometry_.outer_ring_positions().index_pairs[index];
  _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
    x_se, current_pair._to<mm2>());
 }

 index = 4;
 current_pair = geometry_.outer_ring_positions().index_pairs[index];
 y_mm = {current_pair.start, (u2)(height_from_bottom - 1)};
 _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
   x_se, y_mm);

 area = x_se.inner_span() * y_mm.inner_span();
 y_mm = {(u2)(y_mm.max + 1), total_bottom};
 x_se.end = current_pair.end;
 _init_outer_ring_pixel_data(offset + area, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
   x_se, y_mm);


 index = 8;
 current_pair = geometry_.outer_ring_positions().index_pairs[index];
 y_mm = {0, (u2)(height - 1)};
 x_se = { (u2)(current_pair.end), total_right};
 _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
   x_se, y_mm);

 area = x_se.inner_span() * y_mm.inner_span();
 x_se.start = width_from_right;
 y_mm = {height, current_pair.start};
 _init_outer_ring_pixel_data(offset + area, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
   x_se, y_mm);

 for(index = 5; index <= 7; ++index)
 {
  current_pair = geometry_.outer_ring_positions().index_pairs[index];
  _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
    x_se, current_pair._to<mm2>());
 }

 index = 9;
 current_pair = geometry_.outer_ring_positions().index_pairs[index];
 y_mm = {current_pair.start, (u2)(height_from_bottom - 1)};
 _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
   x_se, y_mm);

 area = x_se.inner_span() * y_mm.inner_span();
 x_se.start = current_pair.end;
 y_mm = {height_from_bottom, total_bottom};
 _init_outer_ring_pixel_data(offset + area, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
   x_se, y_mm);

 y_mm = {0, (u2)(height - 1)};
 for(index = 10; index <= 12; ++index)
 {
  current_pair = geometry_.outer_ring_positions().index_pairs[index];
  _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
    current_pair, y_mm);
 }


 y_mm = {height_from_bottom, total_bottom};
 for(index = 13; index <= 15; ++index)
 {
  current_pair = geometry_.outer_ring_positions().index_pairs[index];
  _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
    current_pair, y_mm);
 }

}


// for(index = 1; index <= 3; ++index)
// {
//  current_pair = geometry_.outer_ring_positions().index_pairs[index];
//  _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
//    x_se, current_pair._to<mm2>());
// }

// for(index = 6; index <= 8; ++index)
// {
//  current_pair = geometry_.outer_ring_positions().index_pairs[index];
//  _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
//    x_se, current_pair._to<mm2>());
// }

// for(index = 10; index <= 12; ++index)
// {
//  current_pair = geometry_.outer_ring_positions().index_pairs[index];
//  _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
//    current_pair, y_mm);
// }



// for(index = 13; index <= 15; ++index)
// {
//  current_pair = geometry_.outer_ring_positions().index_pairs[index];
//  _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
//    current_pair, y_mm);
// }


void XCSD_Image::image_tierbox_to_sdi_pixel_map(const QImage& ci, std::map<s1, std::vector<n8>>& result)
{
 u1 a = 0, b = 0;
 for(u1 ar = 0; ar < 3; ++ar)
 {
  for(u1 ac = 0; ac < 3; ++ac)
  {
   ++a; b = 0;
   for(u1 br = 0; br < 3; ++br)
   {
    for(u1 bc = 0; bc < 3; ++bc)
    {
     ++b;
     xy1 rows {br, ar};
     xy1 cols {bc, ac};
     xy1 tl = {cols.times({3, 9}).inner_sum(), rows.times({3, 9}).inner_sum()};

     for(u1 y = 0; y < 3; ++y)
     {
      const QRgb* scan = (const QRgb*) ci.scanLine(tl.y + y);

      scan += tl.x;
      for(u1 x = 0; x < 3; ++x)
      {
       const QRgb& qpixel = *(scan + x);
       n8 pixel = 0;

       QString tr = QString("%1%2").arg(initial_setup_tierbox_.r,2,10,QChar('0'))
         .arg(initial_setup_tierbox_.c,2,10,QChar('0'));


//       QString test = QString("%1a%2%3c%4b%5%6c%7%8%9").arg(tr, 4)
//         .arg(a).arg(ar).arg(ac).arg(b).arg(br).arg(bc).arg(x).arg(y);

//       pixel = test.toLongLong(nullptr, 16);
       //pixel = 0x20202020;

       pixel = qrgb_to_pixel_number(qpixel);

//       pixel = 0;

//       // //  the (n8) casts here are strictly speaking unnecessary
//        //    but could become necessary with something other
//        //    than 1-byte rgba ...
//       pixel |= (n8)qRed(qpixel);
//       pixel |= (n8)qGreen(qpixel) << 8;
//       pixel |= (n8)qBlue(qpixel) << 16;
//       pixel |= (n8)(255 - qAlpha(qpixel)) << 24;

//       pixel |= (n8)14 << 40;
//       pixel |= (n8)(tl.y + y) << 44;
//       pixel |= (n8)(tl.x + x) << 52;
//       pixel |= (n8)14 << 60;

       result[(ab1{a,b}).to_base(10)].push_back(pixel);
      }
     }
    }
   }
  }
 }
}


void XCSD_Image::save_full_tier_image(QString path,
  Save_Mode save_mode,
  QString info_folder,
  std::function<void(QImage&, XCSD_Image_Geometry::Grid_TierBox&,
    XCSD_Image_Geometry::Iteration_Environment, u4, n8*, // data_index,
    const XCSD_Image_Geometry::MCH_Info&, QString, u1)> cb,
  std::function<void(QImage&, s1)> ocb)
{

 XCSD_Image_Geometry::Iteration_Environment ienv = geometry_.formulate_iteration_environment();

 QPainter painter;

 QImage target_image;

 if(!path.isEmpty())
 {
  target_image = QImage(image_.width(), image_.height(), image_.format());
  QColor fillc(0,200,0);
  target_image.fill(fillc);
  painter.begin(&target_image);
 }

 u4 outer_ring_offset = geometry_.full_tier_counts().area() * tierbox_width  * tierbox_width;
 //if(geometry_.full_tier_counts().)

//#ifdef HIDE
 geometry_.for_each_outer_ring_area(
    [this, ocb, save_mode, &painter,
     outer_ring_offset](u1 index, XCSD_Image_Geometry::Outer_Ring_Area_Flags area_flags)
 {
  u4 mark_offset = geometry_.outer_ring_positions().offset_for_area_index(index);
    //(XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index);

  QPoint *qpoint, primary_qpoint, secondary_qpoint;
  wh2 primary_rect_wh = geometry_.get_outer_ring_rect_wh_for(area_flags, index, &primary_qpoint);
  wh2 secondary_rect_wh = geometry_.get_secondary_outer_ring_rect_wh_for(area_flags, index, &secondary_qpoint);

  qpoint = &primary_qpoint;

  u4 local_offset = 0;
  s1 sindex = index;
  for(wh2 rect_wh = primary_rect_wh ;; rect_wh = secondary_rect_wh)
  {
   if(rect_wh != wh2{0,0})
   {
    QImage outer_ring_image(rect_wh.width, rect_wh.height, QImage::Format_ARGB32);

    QColor fillc(0,100,0);
    outer_ring_image.fill(fillc);

    for(u2 y = 0; y < rect_wh.height; ++y)
    {
     QRgb* scanline = (QRgb*) outer_ring_image.scanLine(y);

     for(u2 x = 0; x < rect_wh.width; ++x)
     {
      n8 pixel_number = data_.get_single_pixel(outer_ring_offset + mark_offset + local_offset);

      QRgb rgb;

      if(save_mode == Save_QRgb)
        rgb = pixel_number_to_qrgb(pixel_number);
      else if(save_mode >= Save_FB)
        rgb = pixel_number_fb_to_qrgb(pixel_number, save_mode);
      else if(save_mode == Save_Palette)
        rgb = pixel_number_palette_to_qrgb(pixel_number);
      else
        rgb = pixel_number_to_qrgb(pixel_number);

      scanline[x] = rgb;

      ++local_offset;
     }
    }

    if(outer_ring_info_)
    {
     QSize sz;
     std::tie(sz.rwidth(), sz.rheight()) = rect_wh._tuple();

     XCSD_Outer_Ring_Info::Position position;

     if( (area_flags == XCSD_Image_Geometry::Outer_Ring_Area_Flags::Normal_Landscape)
        || (area_flags == XCSD_Image_Geometry::Outer_Ring_Area_Flags::Normal_Portrait) )
     {
      if(geometry_.full_tier_counts().is_ascending()) // portrait
      {
       if( (index == (u1) XCSD_Image_Geometry::Outer_Ring_Positions::Portrait::Top_Center)
          || (index == (u1) XCSD_Image_Geometry::Outer_Ring_Positions::Portrait::Bottom_Center) )
         position = XCSD_Outer_Ring_Info::Horizontal_Center;
       else if( (index == (u1) XCSD_Image_Geometry::Outer_Ring_Positions::Portrait::Center_Left)
          || (index == (u1) XCSD_Image_Geometry::Outer_Ring_Positions::Portrait::Center_Right) )
         position = XCSD_Outer_Ring_Info::Vertical_Center;
      else if(index > 9) // relies on hard-coded enum values ...
        position = XCSD_Outer_Ring_Info::Vertical;
      else
        position = XCSD_Outer_Ring_Info::Horizontal;
      }
      else // landscape (or square)
      {
       if( (index == (u1) XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Center)
          || (index == (u1) XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Bottom_Center) )
         position = XCSD_Outer_Ring_Info::Horizontal_Center;
       else if( (index == (u1) XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Center_Left)
          || (index == (u1) XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Center_Right) )
        position = XCSD_Outer_Ring_Info::Vertical_Center;
      else if(index > 9) // relies on hard-coded enum values ...
        position = XCSD_Outer_Ring_Info::Horizontal;
      else
        position = XCSD_Outer_Ring_Info::Vertical;
      }
     }
     else
       position = XCSD_Outer_Ring_Info::Corner;

     if(rect_wh == secondary_rect_wh)
     {
      XCSD_Outer_Ring_Info& xori = outer_ring_info_->last();
      xori.extra = QRect(*qpoint, sz);
      outer_ring_info_->push_back({position, outer_ring_image, QRect(*qpoint, sz), xori.rect});
     }
     else
       outer_ring_info_->push_back({position, outer_ring_image, QRect(*qpoint, sz), {}});

//     else
//     {
//      outer_ring_info_->last().secondary = QRect(*qpoint, sz);
//     }
    }

   // if(index <= 2 || (index >= 5 && index <= 7) )

//    if(index == 3)
      painter.drawImage(*qpoint, outer_ring_image);

//     if(index <= 9)
//     {
//      if(sindex >= 0)
//        painter.drawImage(*qpoint, outer_ring_image);

//     }

//    if(index == 10)
//      painter.drawImage(*qpoint, outer_ring_image);

   }
   if(sindex < 0)
     break;
   qpoint = &secondary_qpoint;
   sindex = -index - 1;
  }
 });

//#endif //def HIDE


 geometry_.for_each_full_tierbox(
    [this, save_mode, &path, cb, &ienv, &painter, &info_folder](XCSD_Image_Geometry::Grid_TierBox& gtb)
 {
  QImage ti(tierbox_width, tierbox_width, QImage::Format_ARGB32);

  XCSD_Image_Geometry::MCH_Info mchi;
  //pr2s mch;

  u4 data_index;

  n8* data_start;

  tierbox_to_qimage(gtb, ti, save_mode, ienv, &data_index, &data_start, &mchi, info_folder);

  if(!info_folder.isEmpty())
  {
   QString path = QString("%1/%2-%3.png").arg(info_folder).arg(gtb.loc.r()).arg(gtb.loc.c());
   ti.save(path);
  }

  if(cb)
  {
   cb(ti, gtb, ienv, data_index, data_start, mchi,  info_folder, tierbox_width);
  }

  if(!path.isEmpty())
  {
   QPoint tl(gtb.top_left().as_qpoint());
   painter.drawImage(tl, ti);
  }

  //return-1;
 });

 if(!path.isEmpty())
 {
  painter.end();
  target_image.save(path);
 }
}

u2 XCSD_Image::qcolor_to_rgb555(const QColor& clr)
{
 u4 rgb = clr.red() + (clr.green() << 8) + (clr.blue() << 16);
 return rgb_to_rgb555(rgb);
}

u2 XCSD_Image::rgb_to_rgb555(u4 rgb)
{
 u1 red = (u1)(rgb & 255), green = (u1)((rgb >> 8) & 255),
   blue = (u1)((rgb >> 16) & 255);
 red >>= 3;
 green >>= 3;
 blue >>= 3;
 return ((u2) red) | (((u2) green) << 5) | (((u2) blue) << 10);
}


void XCSD_Image::set_individual_pixel_local_histogram_channels(n8& pixel)
{
 u2 rgb555 = rgb_to_rgb555(pixel);

 static u1 temp = 0;
// if(temp < 55)
// {
//  qDebug() << temp << " rgb555 = " << rgb555 << ", pixel = " << pixel;

//  qDebug() << "rgb555 1 = " << (((n8) rgb555) << 32);
//  qDebug() << "pixel = " << pixel;
  pixel |= (((n8) rgb555) << 32);

//  qDebug() << "pixel2 = " << pixel;
  ++temp;
// }
}

void XCSD_Image::set_local_histograms_channels()
{
 geometry_.for_each_full_tierbox([this](XCSD_Image_Geometry::Grid_TierBox& gtb)
 {
  rc2 rc  = gtb.loc.rc()._to_unsigned();

//  if(rc == rc2{0, 1})
//    qDebug() << rc;

// rc2 rc  = {0, 21};

  XCSD_TierBox* tbox = data_.get_full_tierbox_at_position(rc);

//  qDebug() << tbox->get_grid_position();

  u4 offset = tbox->pixel_data_ground_offset();

  n8* start = data_.get_pixel_data_start(offset);

  for(u4 i = 0; i < tierbox_width * tierbox_width; ++i)
  {
   set_individual_pixel_local_histogram_channels(*start);
   ++start;
  }

 });

 //?calculate_pixel_averages_1byte(7, 8);

 set_channels_info_ |= Set_Channels_Info::RGB555_Set;
}

void XCSD_Image::autoset_fb_poles(u1 center, QPair<u1, u1> tblr [4]) //{4, 4}, {0,0}, {0,0}, {0,0}})
{
 check_set_local_histograms_channels();

 QPair<u1, u1> top = tblr[0];
 QPair<u1, u1> bottom = tblr[1];
 QPair<u1, u1> left = tblr[2];
 QPair<u1, u1> right = tblr[3];

 QVector<Local_Histogram_Data> center_histograms (center);

 if(top.second == (u1) -1)
   top.second = top.first;

 u1 top_count = top.first + top.second;

 QVector<Local_Histogram_Data> top_histograms (top_count);

 for(u4 count = 0, start_offset = 0; count < center;
   start_offset += tierbox_width * tierbox_width, ++count)
 {
  calculate_tierbox_histogram(start_offset, center_histograms[count]);
 }

 s2 c_left = (geometry_.full_tier_counts().width / 2) - top.first;
 if(c_left < 0)
   c_left = 0;
 u2 c_right = c_left + top.first + top.second - 1;
 if(c_right > geometry_.full_tier_counts().width)
   c_right = geometry_.full_tier_counts().width;

 rc2 rc_left = {0, (u2) c_left};
 rc2 rc_right = {0, c_right};

 u1 count = 0;
 geometry_.for_each_full_tierbox(rc_left, rc_right, [this, &top_histograms, &count](XCSD_Image_Geometry::Grid_TierBox& gtb)
 {
  rc2 rc  = gtb.loc.rc()._to_unsigned();
  XCSD_TierBox* tbox = data_.get_full_tierbox_at_position(rc);
  //?
  u2 fti = tbox->full_tier_index();
  qDebug() << "top: " << fti;

  calculate_tierbox_histogram(tbox, top_histograms[count]);
  ++count;
 });

 r8 center_avg_red = 0, center_avg_green = 0, center_avg_blue = 0,
   top_avg_red = 0, top_avg_green = 0, top_avg_blue = 0;

 QColor center_avg, top_avg;

 for(const Local_Histogram_Data& lhd : center_histograms)
 {
  QColor color = lhd.get_ref_color();

  qDebug() << "center color: " << color;

  center_avg_red += (u1) color.red();
  center_avg_green += (u1) color.green();
  center_avg_blue += (u1) color.blue();
 }

 center_avg = QColor(center_avg_red / center, center_avg_green / center,
   center_avg_blue / center);


 for(const Local_Histogram_Data& lhd : top_histograms)
 {
  QColor color = lhd.get_ref_color();

  qDebug() << "top color: " << color;


  top_avg_red += (u1) color.red();
  top_avg_green += (u1) color.green();
  top_avg_blue += (u1) color.blue();
 }

 top_avg = QColor(top_avg_red / top_count, top_avg_green / top_count,
   top_avg_blue / top_count);

 set_foreground_pole(top_avg);

 set_background_pole(center_avg);

//   top_count

//   QPair<u1, u1> bottom = {4, 4}, QPair<u1, u1> left = {0, 0}, QPair<u1, u1> right =

}



QVector<Local_Histogram_Data>* XCSD_Image::calculate_local_histograms() //QString path_template)
{
 check_set_local_histograms_channels();
 u2 count = geometry_.full_tier_counts().inner_product();

 QVector<Local_Histogram_Data>* result = new QVector<Local_Histogram_Data> (count);

 init_local_histogram_vector(*result); //, path_template);
 return result;
}

prr1 XCSD_Image::rgb_to_prr(u4 rgb)
{
 static const u1 mask = 255;

 return {(u1) (rgb & mask),
   (u1) ((rgb >> 8) & mask),
   (u1) ((rgb >> 16) & mask)};

}


prr1 XCSD_Image::rgb555_to_prr(u2 rgb555)
{
// u1 red = (u1) (rgb555 & 0b00011111);
// u1 green = (u1) ((rgb555 >> 5) & 0b00011111);
// u1 blue = (u1) ((rgb555 >> 10) & 0b00011111);
// return {red, green, blue};

 static const u1 mask = 0b00011111;

 return {(u1) (rgb555 & mask),
   (u1) ((rgb555 >> 5) & mask),
   (u1) ((rgb555 >> 10) & mask)};

}

QColor XCSD_Image::rgb555_to_qcolor(u2 rgb555)
{
 auto [red, green, blue] = rgb555_to_prr(rgb555);
// u1 red = (u1) (rgb555 & 0b00011111);
// u1 green = (u1) ((rgb555 >> 5) & 0b00011111);
// u1 blue = (u1) ((rgb555 >> 10) & 0b00011111);

// qDebug() << "red = " << red << ", green = " << green << ", blue = " << blue;

 QColor rgb(red << 3, green << 3, blue << 3);
 return rgb;
}

QVector<s2> XCSD_Image::rgb555_to_hsv(u2 rgb555)
{
// u1 red = (u1) (rgb555 & 0b00011111);
// u1 green = (u1) ((rgb555 >> 5) & 0b00011111);
// u1 blue = (u1) ((rgb555 >> 10) & 0b00011111);
 QColor rgb = rgb555_to_qcolor(rgb555); // (red, green, blue);
 return { (s2) rgb.hsvHue(),  (s2) rgb.hsvSaturation(),  (s2) rgb.value() };
}


void XCSD_Image::save_local_histogram_vector_to_folder(const QVector<Local_Histogram_Data>& data,
  QString path_template)
{
 geometry_.for_each_full_tierbox([this, &data, &path_template](XCSD_Image_Geometry::Grid_TierBox& gtb)
 {
  rc2 rc  = gtb.loc.rc()._to_unsigned();

  XCSD_TierBox* tbox = data_.get_full_tierbox_at_position(rc);

  u2 fti = tbox->full_tier_index();

  u2 image_height = 520;
  u2 max_bin_height = 200;
  u2 min_bin_height = 10;
  u2 bin_base = 260;
  u2 bin_width = 9;

  u2 max_hue_height = 200;
  u2 min_hue_height = 10;

  QMap<u2, u2>& rgb555_counts = data[fti].rgb555_map();
  QMap<s2, u2>& hue_counts = data[fti].hue_map();
  QMap<s2, Histogram_Group_Summary>& combined = data[fti].combined_map();

  u2 sz = rgb555_counts.size();

  QImage rgb555_summary(sz * 10, image_height, QImage::Format_RGB32);
  QPainter painter(&rgb555_summary);

  QPen pen = painter.pen();
  pen.setWidth(1);

  painter.setPen(pen);
  painter.fillRect(rgb555_summary.rect(), Qt::white);

  QFont font = painter.font() ;
  font.setPointSize(7);
  painter.setFont(font);

  u2 hue_counts_max = data[fti].largest_group_total();
  u2 rgb_counts_max = data[fti].largest_bin();

  u2 h = 0;

  for(s2 hue = 0, go_on = 1; go_on; ++hue)
  {
   if(hue == 360)
   {
    hue = -1;
    go_on = 0;
   }

   auto it = combined.find(hue);
   if(it == combined.end())
     continue;

   QColor color = rgb555_to_qcolor(it.value().max);


//    qDebug() << "color = " << color;


   u2 height = (((r8) hue_counts[hue]) / hue_counts_max) * (max_hue_height - min_hue_height);

//    qDebug() << "v = " << v << ", height = " << height;

   QRect rect(h, bin_base, ((bin_width + 1) * it.value().counts.size()) - 1, min_hue_height + height);
//    qDebug() << "rect = " << rect;

   QBrush qbr(color);
   painter.setBrush(qbr);
   painter.drawRect(rect);

   for(pr2 pr : it.value().counts)
   {
    u2 v = pr.second;
    QColor color = rgb555_to_qcolor(pr.first);
    u2 height = (((r8) pr.second) / rgb_counts_max) * (max_bin_height - min_bin_height);

    QRect rect(h, bin_base, bin_width, -(min_bin_height + height));
    QBrush qbr(color);
    painter.setBrush(qbr);
    painter.drawRect(rect);

    if(hue < 10)
      painter.drawText(rect.bottomLeft() - QPoint{-2, 2}, QString::number(hue));
    else if(hue < 100)
    {
     painter.drawText(rect.bottomLeft() - QPoint{-2, 2}, QString::number(hue % 10));
     painter.drawText(rect.bottomLeft() - QPoint{-2, 10},
       QString::number( (hue / 10) %  10) );
    }
    else
    {
     painter.drawText(rect.bottomLeft() - QPoint{-2, 2}, QString::number(hue % 10));
     painter.drawText(rect.bottomLeft() - QPoint{-2, 10},
       QString::number( (hue / 10) %  10) );
     painter.drawText(rect.bottomLeft() - QPoint{-2, 18},
       QString::number( (hue / 100) %  10) );
    }
    h += 10;
   }
  }

  rgb555_summary.save(path_template.arg(rc.r).arg(rc.c));

 });
}

prr1 XCSD_Image::rgb555_color_distance(clrs2 colors)
{
 prr1 c1 = rgb555_to_prr(colors.color1);
 prr1 c2 = rgb555_to_prr(colors.color2);
 return c1.distance(c2);
}

prr1 XCSD_Image::rgb555_color_distance_expanded(clrs2 colors)
{
 prr1 result = rgb555_color_distance(colors);
 result <<= 3;
 return result;
}

prr1 XCSD_Image::rgb555_888_color_distance(u2 rgb555, u4 rgb)
{
 prr1 c1 = rgb555_to_prr(rgb555);
 c1 <<= 3;
 prr1 c2 = rgb_to_prr(rgb);

 return c1.distance(c2);
}

prr1 XCSD_Image::qcolor_to_prr(const QColor& clr)
{
 return {(u1)clr.red(), (u1)clr.green(), (u1)clr.blue()};
}


prr1 XCSD_Image::rgb888_qcolor_distance(u4 rgb, const QColor& clr)
{
 prr1 c1 = rgb_to_prr(rgb);
 prr1 c2 = qcolor_to_prr(clr);
 return c1.distance(c2);
}


fb1 XCSD_Image::collapse_fb_distances(const prr1& dist1, const prr1& dist2)
{
 r8 d1 = sqrt(dist1.inner_sum_of_squares());
 r8 d2 = sqrt(dist2.inner_sum_of_squares());
 r8 dd = d1 + d2;
 r8 dd1 = (d1/dd);// * distance;
 r8 dd2 = (d2/dd);// * distance;

 u1 fg = (r8) 255 * (1 - dd1);
 u1 bg = (r8) 255 * (1 - dd2);

 return {fg, bg};

}


void XCSD_Image::set_fb_gradient_trimap_to_channels(fb2 poles)
{
 n8* pixel = data_.get_pixel_data_start();
 u4 count = 0, sz = data_.get_pixel_data_length();

 while(count++ < sz)
 {
  u4 rgb = (*pixel) & 0xFF'FF'FF;
  prr1 dist1 = rgb555_888_color_distance(poles.fg, rgb);
  prr1 dist2 = rgb555_888_color_distance(poles.bg, rgb);

  fb1 fb = collapse_fb_distances(dist1, dist2);

  n8 p = (*pixel);

  (*pixel) |= (((n8) fb.fg) << 48);
  (*pixel) |= (((n8) fb.bg) << 56);

  ++pixel;
 }
 calculate_pixel_averages_1byte(7, 8);
}


void XCSD_Image::check_set_fb_gradient_trimap_to_channels()
{
 if( (set_channels_info_ & Set_Channels_Info::Channels_78_Set_FB) )
   return;

 fb2 poles = {qcolor_to_rgb555(foreground_pole_), qcolor_to_rgb555(background_pole_)};

 set_fb_gradient_trimap_to_channels(poles);
  // set_fb_gradient_trimap_to_channels(poles);
}


void XCSD_Image::save_fb_gradient_trimap(QString file_path, QString folder)
{
 fb2 poles = {qcolor_to_rgb555(foreground_pole_), qcolor_to_rgb555(background_pole_)};

 save_fb_gradient_trimap(poles, file_path, folder);
}

void XCSD_Image::save_fb_gradient_trimap(fb2 poles, QString file_path, QString folder)
{
 //? calculate_pixel_averages();

// n8 sq = rgb555_color_distance_expanded(poles._to<clrs2>()).inner_sum_of_squares();
// r8 distance = sqrt(sq);

 if( (set_channels_info_ & Set_Channels_Info::Channels_78_Set_FB) == 0 )
   set_fb_gradient_trimap_to_channels(poles);


 //QImage image;
 save_full_tier_image(file_path.arg("fb"), Save_FB, folder);
 save_full_tier_image(file_path.arg("fg"), Save_FG); //, folder);
 save_full_tier_image(file_path.arg("bg"), Save_BG); //, folder);

 save_full_tier_image(file_path.arg("fbr"), Save_FB | Tier_Blur_3);
 save_full_tier_image(file_path.arg("fgr"), Save_FG | Tier_Blur_3); //, folder);
 save_full_tier_image(file_path.arg("bgr"), Save_BG | Tier_Blur_3); //, folder);

 save_full_tier_image(file_path.arg("fb2r"), Save_FB | Tier_Blur_9);
 save_full_tier_image(file_path.arg("fg2r"), Save_FG | Tier_Blur_9); //, folder);
 save_full_tier_image(file_path.arg("bg2r"), Save_BG | Tier_Blur_9); //, folder);


 save_full_tier_image(file_path.arg("fb3r"), Save_FB | Tier_Blur_27);
 save_full_tier_image(file_path.arg("fg3r"), Save_FG | Tier_Blur_27); //, folder);
 save_full_tier_image(file_path.arg("bg3r"), Save_BG | Tier_Blur_27); //, folder);


 save_full_tier_image(file_path.arg("original"), Save_QRgb);

 //data_.start();

}


void XCSD_Image::save_channel_to_red_black_image(u1 channel_number, QString file_path)
{
}

void XCSD_Image::save_channel_to_red_white_image(u1 channel_number, QString file_path)
{

}

void XCSD_Image::save_channel_to_blue_black_image(u1 channel_number, QString file_path)
{

}

void XCSD_Image::save_channel_to_blue_white_image(u1 channel_number, QString file_path)
{

}

void XCSD_Image::save_foreground_distance_channel_to_red_black_image(QString file_path)
{
 save_full_tier_image(file_path, Save_FG);

//? save_channel_to_red_black_image(7, file_path);
}

void XCSD_Image::save_foreground_distance_channel_to_red_white_image(QString file_path)
{
 save_full_tier_image(file_path, Save_FG | Fade_To_White);
//? save_channel_to_red_white_image(7, file_path);
}

void XCSD_Image::save_background_distance_channel_to_blue_black_image(QString file_path)
{
 save_full_tier_image(file_path, Save_BG);

//? save_channel_to_blue_black_image(8, file_path);
}

void XCSD_Image::save_background_distance_channel_to_blue_white_image(QString file_path)
{
 save_full_tier_image(file_path, Save_BG | Fade_To_White);
//? save_channel_to_blue_white_image(8, file_path);
}

void XCSD_Image::save_fb_one_channel_image(QString file_path)
{
 save_full_tier_image(file_path, Save_FB_One_Channel);
}


void XCSD_Image::calculate_tierbox_histogram(XCSD_TierBox* tbox, Local_Histogram_Data& result)
{
 u4 start_offset = tbox->pixel_data_ground_offset();
 calculate_tierbox_histogram(start_offset, result);
}

void XCSD_Image::calculate_tierbox_histogram(u4 start_offset, Local_Histogram_Data& result)
{
// xy4 xy = tbox->get_image_ground_location_for_tierbox_center();
// u2 fti = tbox->full_tier_index();
 n8* start = data_.get_pixel_data_start(start_offset);

 QMap<u2, u2>& rgb555_counts = result.rgb555_map();
 QMap<s2, u2>& hue_counts = result.hue_map();
 QMap<s2, Histogram_Group_Summary>& combined = result.combined_map();

 for(u4 i = 0; i < tierbox_width * tierbox_width; ++i)
 {
  u2 code = (u2) ( (*start) >> 32 );
  u2 c = ++rgb555_counts[code];
  ++start;
 }

 u2 rgb_counts_max = std::max_element(rgb555_counts.begin(), rgb555_counts.end()).value();

 result.set_largest_bin(rgb_counts_max);

// u2 sz = rgb555_counts.size();

 QMapIterator<u2, u2> r_it(rgb555_counts);

 while(r_it.hasNext())
 {
  r_it.next();

  s2 hue = rgb555_to_hsv(r_it.key())[0];
  hue_counts[hue] += r_it.value();

//   combined[hue].push_back({r_it.key(), r_it.value()});
  combined[hue].counts.push_back(pr2().from_key_value_iterator(r_it));

 }

 auto max_it = std::max_element(hue_counts.begin(), hue_counts.end());

 //u2 hue_counts_max = it.value();
 result.set_largest_group_total(max_it.value());
 result.set_largest_group_hue(max_it.key());

 for(s2 hue = 0, go_on = 1; go_on; ++hue)
 {
  if(hue == 360)
  {
   hue = -1;
   go_on = 0;
  }

  auto it = combined.find(hue);
  if(it == combined.end())
    continue;

  it.value().max = std::max_element(it.value().counts.begin(), it.value().counts.end(),
    UNARY_COMPARE_2(pr2))->first;
  it.value().total = hue_counts[hue];

  if(hue == max_it.key())
    result.set_largest_group_hue_ref_color(it.value().max);
 }

}


void XCSD_Image::init_local_histogram_vector(QVector<Local_Histogram_Data>& result)
{
 u1 threshold = 255;

 geometry_.for_each_full_tierbox([this, &result](XCSD_Image_Geometry::Grid_TierBox& gtb)
 {  
  rc2 rc  = gtb.loc.rc()._to_unsigned();
  XCSD_TierBox* tbox = data_.get_full_tierbox_at_position(rc);
  u2 fti = tbox->full_tier_index();
  calculate_tierbox_histogram(tbox, result[fti]);
 });
}

#ifdef HIDE
//  qDebug() << tbox->get_grid_position();

  xy4 xy = tbox->get_image_ground_location_for_tierbox_center();
//  qDebug() << "xy = " << xy;

  u2 fti = tbox->full_tier_index();

//  qDebug() << "index = " << fti;

  u4 offset = tbox->pixel_data_ground_offset();

  n8* start = data_.get_pixel_data_start(offset);

  QMap<u2, u2>& rgb555_counts = result[fti].rgb555_map();
  QMap<s2, u2>& hue_counts = result[fti].hue_map();
  QMap<s2, Histogram_Group_Summary>& combined = result[fti].combined_map();

//  QMultiMap<u2, u2> inverse;


  for(u4 i = 0; i < tierbox_width * tierbox_width; ++i)
  {
//   n8 pixel = *start;
//   qDebug() << "pixel = " << *start;
//   qDebug() << "pixel1 = " << ((u4) pixel);
//   qDebug() << "pixel1 = " << ((u2) (pixel >> 32));

   u2 code = (u2) ( (*start) >> 32 );
   u2 c = ++rgb555_counts[code];
//   if(rgb_counts_max < c)
//     rgb_counts_max = c;

//   u1 hue = rgb555_to_hsv(code)[0];
//   ++hue_counts[hue];

   ++start;
  }

//  u2 sz = counts.size();
//  QMapIterator<u2, u2> it (counts);
//  while(it.hasNext())
//  {
//   it.next();
//   u2 k = it.key();
//   u2 v = it.value();
//  }

#ifdef HIDE
  u2 sz = hue_counts.size();

  QImage hue_summary(sz * 10, 800, QImage::Format_RGB32);
  QPainter painter(&hue_summary);

  painter.fillRect(hue_summary.rect(), Qt::white);

  u2 h = 0;
  for(u2 hue = 0; hue <= 255; ++hue)
  {
   auto it = hue_counts.find(hue);
   if(it == hue_counts.end())
    continue;

   QColor color;
   color.setHsv(hue, 200, 200);

   QBrush qbr(color);
   painter.setBrush(qbr);
   painter.drawRect(h, 790 - it.value(), 9, it.value());
   h += 10;

//   break;
  }
#endif //def HIDE

  u2 rgb_counts_max = std::max_element(rgb555_counts.begin(), rgb555_counts.end()).value();

  result[fti].set_largest_bin(rgb_counts_max);

  u2 sz = rgb555_counts.size();


  QMapIterator<u2, u2> r_it(rgb555_counts);

  while(r_it.hasNext())
  {
   r_it.next();

   s2 hue = rgb555_to_hsv(r_it.key())[0];
   hue_counts[hue] += r_it.value();

//   combined[hue].push_back({r_it.key(), r_it.value()});
   combined[hue].counts.push_back(pr2().from_key_value_iterator(r_it));

  }

  u2 hue_counts_max = std::max_element(hue_counts.begin(), hue_counts.end()).value();
  result[fti].set_largest_group_total(hue_counts_max);

  for(s2 hue = 0, go_on = 1; go_on; ++hue)
  {
   if(hue == 360)
   {
    hue = -1;
    go_on = 0;
   }

   auto it = combined.find(hue);
   if(it == combined.end())
     continue;
   it.value().max = std::max_element(it.value().counts.begin(), it.value().counts.end(),
     UNARY_COMPARE_2(pr2))->first;
   it.value().total = hue_counts[hue];
  }
#ifdef HIDE
  QMapIterator<u2, u2> r_it(rgb555_counts);

  while(r_it.hasNext())
  {
   r_it.next();

   s2 hue = rgb555_to_hsv(r_it.key())[0];
   hue_counts[hue] += r_it.value();

//   combined[hue].push_back({r_it.key(), r_it.value()});
   combined[hue].counts.push_back(pr2().from_key_value_iterator(r_it));

  }

  u2 hue_counts_max = std::max_element(hue_counts.begin(), hue_counts.end()).value();
  result[fti].set_largest_group_total(hue_counts_max);



  for(s2 hue = 0, go_on = 1; go_on; ++hue)
  {
   if(hue == 360)
   {
    hue = -1;
    go_on = 0;
   }

   auto it = combined.find(hue);
   if(it == combined.end())
     continue;

//  }

//  //QMapIterator<u2, QVector<pr2>> it(combined);
//  //while(it.hasNext())
//  {
   //it.next();

   {
    it.value().max = std::max_element(it.value().counts.begin(), it.value().counts.end(),
      UNARY_COMPARE_2(pr2))->first;

    QColor color = rgb555_to_qcolor(it.value().max);


//    qDebug() << "color = " << color;


    u2 height = (((r8) hue_counts[hue]) / hue_counts_max) * (max_hue_height - min_hue_height);

//    qDebug() << "v = " << v << ", height = " << height;

    QRect rect(h, bin_base, ((bin_width + 1) * it.value().counts.size()) - 1, min_hue_height + height);
//    qDebug() << "rect = " << rect;

    QBrush qbr(color);
    painter.setBrush(qbr);
    painter.drawRect(rect);

   }
   for(pr2 pr : it.value().counts)
   {
//    u2 v = pr.second;

    QColor color = rgb555_to_qcolor(pr.first);

//    qDebug() << "color = " << color;


    u2 height = (((r8) pr.second) / rgb_counts_max) * (max_bin_height - min_bin_height);

//    qDebug() << "v = " << v << ", height = " << height;

    QRect rect(h, bin_base, bin_width, -(min_bin_height + height));
//    qDebug() << "rect = " << rect;


    QBrush qbr(color);
    painter.setBrush(qbr);
    painter.drawRect(rect);

    if(hue < 10)
      painter.drawText(rect.bottomLeft() - QPoint{-2, 2}, QString::number(hue));
    else if(hue < 100)
    {
     painter.drawText(rect.bottomLeft() - QPoint{-2, 2}, QString::number(hue % 10));
     painter.drawText(rect.bottomLeft() - QPoint{-2, 10},
       QString::number( (hue / 10) %  10) );
    }
    else
    {
     painter.drawText(rect.bottomLeft() - QPoint{-2, 2}, QString::number(hue % 10));
     painter.drawText(rect.bottomLeft() - QPoint{-2, 10},
       QString::number( (hue / 10) %  10) );
     painter.drawText(rect.bottomLeft() - QPoint{-2, 18},
       QString::number( (hue / 100) %  10) );
    }

    it.value().total = hue_counts[hue];


    h += 10;



   }

//   break;
  }

  rgb555_summary.save(path_template.arg(rc.r).arg(rc.c));
#endif

 });




//  QImage ti(tierbox_width, tierbox_width, QImage::Format_ARGB32);

//  XCSD_Image_Geometry::MCH_Info mchi;
//  //pr2s mch;

//  u4 data_index;

//  n8* data_start;

//  tierbox_to_qimage(gtb, ti, ienv, &data_index, &data_start, &mchi, info_folder);
}
#endif // HIDE

u4 XCSD_Image::data_tierbox_to_sdi_pixel_map(u4 tierbox_index,
  std::map<s1, std::pair<u2, std::vector<n8>>>& result)
{
 static u2 box_area = tierbox_width * tierbox_width;
 u4 threshold = tierbox_index * box_area;

 u1 b, a = 0;
 u2 threshold_offset = 0;
 for(u1 ar = 0; ar < 3; ++ar)
 {
  for(u1 ac = 0; ac < 3; ++ac)
  {
   ++a; b = 0;
   for(u1 br = 0; br < 3; ++br)
   {
    for(u1 bc = 0; bc < 3; ++bc)
    {
     ++b;

     std::vector<n8> pixels;
     data_.get_pixel_run(threshold + threshold_offset, 9, pixels);
     result[(ab1{a,b}).to_base(10)] = {threshold_offset, pixels};

     threshold_offset += 9;
     // data to std vec ... starting at threshold + tl ...

    }
   }
  }
 }

 return threshold;
}


//xy1 rows {br, ar};
//xy1 cols {bc, ac};
//xy1 tl = {cols.times({3, 9}).inner_sum(), rows.times({3, 9}).inner_sum()};

//u1 inner_index = 0;

//for(u1 y = 0; y < 3; ++y)
//{
// const QRgb* scan; // = (const QRgb*) ci.scanLine(tl.y + y);
// scan += tl.x;
// for(u1 x = 0; x < 3; ++x)
// {
//  const QRgb& qpixel = *(scan + x);
//  n8 pixel = 0;

//  // //  the (n8) casts here are strictly speaking unnecessary
//  //    but could become necessary with something other
//  //    than 1-byte rgba ...
//  pixel |= (n8)qRed(qpixel);
//  pixel |= (n8)qGreen(qpixel) << 8;
//  pixel |= (n8)qBlue(qpixel) << 16;
//  pixel |= (n8)qAlpha(qpixel) << 24;

//  result[{a,b}].push_back(pixel);
// }
//}



void XCSD_Image::calculate_pixel_averages_1byte(u1 start, u1 end, n8* reset)
{
 geometry_.for_each_full_tierbox([this, start, end, reset](XCSD_Image_Geometry::Grid_TierBox& gtb)
 {
  rc2 rc  = gtb.loc.rc()._to_unsigned();

//  if(rc == rc2{0, 1})
//    qDebug() << rc;

// rc2 rc  = {0, 21};

  XCSD_TierBox* tbox = data_.get_full_tierbox_at_position(rc);

  tbox->check_calculate_pixel_averages_1byte(start, end, this, reset);

 });
}


XCSD_TierBox* XCSD_Image::get_tierbox_from_grid_tierbox(const XCSD_Image_Geometry::Grid_TierBox& gtb)
{
 rc2s rc = gtb.loc.rc();
 return data_.get_full_tierbox_at_position(rc._to_raw_unsigned());
}

void XCSD_Image::tierbox_to_qimage(XCSD_Image_Geometry::Grid_TierBox& gtb,
  QImage& target, Save_Mode save_mode,
  XCSD_Image_Geometry::Iteration_Environment ienv,
  u4* data_index, n8** data_start, //pr2s* mch,
  XCSD_Image_Geometry::MCH_Info* mchi,  QString info_folder)
{
 //static u2 box_area = tierbox_width * tierbox_width;

 u1 tier_blur_level = 0;

 if(u1 code = save_mode & Tier_Blur_27)
 {
  save_mode = (Save_Mode) (save_mode - code);
  tier_blur_level = code >> 6;
 }

 u4 fti = geometry_.get_tierbox_index(gtb, ienv.size_even_odd_info, mchi);

 std::map<s1, std::pair<u2, std::vector<n8>>> sdi;

 u4 di = data_tierbox_to_sdi_pixel_map(fti, sdi);

 XCSD_TierBox* tbox = get_tierbox_from_grid_tierbox(gtb);

// if(tier_blur_level > 0)
//   tbox->check_calculate_pixel_averages_1byte_level1(7, 8, this);

 if(data_index)
 {
  *data_index = di;
  if((di != (u4) -1) && data_start)
    *data_start = data_.get_pixel_data_start(di);
 }



// static u4 deflt;
// (data_index? *data_index : deflt) =
//   data_tierbox_to_sdi_pixel_map(index, sdi);


 QString info_path;
 QString info_string;

 if(!info_folder.isEmpty())
 {
  info_path = QString("%1/%2-%3-%4.txt").arg(info_folder).arg(gtb.loc.r()).arg(gtb.loc.c()).arg(di);
  info_string = QString("Full tierbox %1 %2 (%3)\n\n\n").arg(gtb.loc.r()).arg(gtb.loc.c()).arg(fti);
 }

 for(auto const& [ab_s1, thr_vec]: sdi)
 {
  ab1 ab = {(u1)((u1)ab_s1 / 10), (u1)((u1)ab_s1 % 10)};

  if(!info_string.isEmpty())
    info_string += QString("SDI location %1\n").arg(ab_s1);

  abg1 abg{ab.a, ab.b, 0};

  ab = ab.double_minus(1);


  // // rc here is 0 - 3
  rc1 arc = {(u1)(ab.a / 3), (u1)(ab.a % 3)};
  rc1 brc = {(u1)(ab.b / 3), (u1)(ab.b % 3)};

  u1 tl_scan_row = arc.r * 9 + brc.r * 3;

  u1 tl_scan_column = arc.c * 9 + brc.c * 3;

  u4 offset = thr_vec.first;

  n8 _avg = 0;
  n8* blur_avg;

  if(tier_blur_level == 0)
    blur_avg = nullptr;
  else
  {
   blur_avg = &_avg;
   if(tier_blur_level == 1)
     _avg = tbox->get_3x3_box(ab_s1)->color_average;
   else if(tier_blur_level == 2)
     _avg = tbox->get_9x9_box(abg.a)->color_average;
   else
     _avg = tbox->color_average();
  }

  u1 vi = 0; // vector index
  for(u1 y = 0; y < 3; ++y)
  {
   QRgb* img_pixels = (QRgb*) target.scanLine(tl_scan_row + y);

   img_pixels += tl_scan_column;
   for(u1 x = 0; x < 3; ++x)
   {
    ++abg.g;
    xy1 xy = XCSD_TierBox::get_local_ground_location_sdi(abg.to_base(10));

    n8 pixel = blur_avg? *blur_avg : thr_vec.second[vi];
    // qDebug() << "pixel = " << (pixel & 0x00FFFFFF);

    if(save_mode == Save_QRgb)
      *img_pixels = pixel_number_to_qrgba(pixel);

//      qRgba(
//         (u1)(pixel & 255), (u1)((pixel >> 8) & 255),
//         (u1)((pixel >> 16) & 255),
//         (u1)(255 - ((pixel >> 24) & 255))
//      );

    else if(save_mode >= Save_FB)
     *img_pixels = pixel_number_fb_to_qrgb(pixel, save_mode);

//        qRgba(
//        (u1)((pixel >> 40) & 255), 0,
//        (u1)((pixel >> 48) & 255),
//        255)

    else if(save_mode == Save_Palette)
      ;//?


    ++img_pixels;

    if(!info_string.isEmpty())
      info_string += QString(" %1-%2:%3").arg(xy.to_qstring(2))
        .arg(offset, 3, 10, QChar('0')).arg(thr_vec.second[vi], 16, 16, QChar('0'));

    ++offset;

    ++vi;
   }
   if(!info_string.isEmpty())
     info_string += "\n";

//    qDebug() << "vi = " << vi;
  }
  if(!info_string.isEmpty())
    info_string += "\n";
 }

 if(!info_path.isEmpty())
   save_file(info_path, info_string);
}

   //xy2 tl = gtb.top_left();


QColor XCSD_Image::pixel_number_to_qcolor(n8 pixel)
{
 return QColor(pixel & 255, (pixel >> 8) & 255, (pixel >> 16) & 255,
   255 - ((pixel >> 24) & 255));
}

//Fade_To_White
QColor XCSD_Image::pixel_number_fb_to_qcolor(n8 pixel, Save_Mode save_mode)
{
 u1 b_distance = ((pixel >> 56) & 255);
 u1 f_distance = ((pixel >> 48) & 255);

 switch (save_mode)
 {
 case Save_FB:
  return QColor(f_distance, 0, b_distance);
 case Save_BG:
  return QColor(0, 0, b_distance);
 case Save_FG:
  return QColor(f_distance, 0, 0);

 case Save_FB_One_Channel:
  {
   u1 avg = (u1) (((u2)f_distance + 255 - b_distance) / 2);
   return QColor(avg, avg, avg);
  }

 case Save_BG | Fade_To_White:
  return QColor(255 - b_distance, 255 - b_distance, 255);
 case Save_FG | Fade_To_White:
  return QColor(255, 255 - f_distance, 255 - f_distance);

 default: return QColor();
 }

// return QColor((pixel >> 40) & 255, (pixel >> 40) & 255,
//   (pixel >> 40) & 255);

}

QColor XCSD_Image::pixel_number_palette_to_qcolor(n8 pixel)
{
 // //?
 return QColor();
}

QRgb XCSD_Image::pixel_number_to_qrgb(n8 pixel)
{
 return pixel_number_to_qcolor(pixel).rgb();
}

QRgb XCSD_Image::pixel_number_to_qrgba(n8 pixel)
{
 return pixel_number_to_qcolor(pixel).rgba();
}


QRgb XCSD_Image::pixel_number_fb_to_qrgb(n8 pixel, Save_Mode save_mode)
{
 return pixel_number_fb_to_qcolor(pixel, save_mode).rgb();
}


QRgb XCSD_Image::pixel_number_palette_to_qrgb(n8 pixel)
{
 return pixel_number_palette_to_qcolor(pixel).rgb();
}


SDI_Position XCSD_Image::get_sdi_at_ground_position(u2 x, u2 y)
{
 SDI_Position result{ {0,0}, {0,0}, {0,0}, {0,0} };

 s1 x_offset = -1, y_offset = -1;

 if(geometry_.horizontal_outer_sizes().left > 0)
 {
  if(x < geometry_.horizontal_outer_sizes().left)
  {
   result.tier.r = 0;
   x_offset = x;
  }
  else
  {
   result.tier.r = 1;
   x -= geometry_.horizontal_outer_sizes().left;
  }
 }
 if(x_offset == -1)
   x_offset = x % 27;
 result.full_ground.x = x_offset;

 x /= 27;
 result.tier.r += x;

 if(geometry_.vertical_outer_sizes().top > 0)
 {
  if(y < geometry_.vertical_outer_sizes().top)
  {
   result.tier.c = 0;
   y_offset = y;
  }
  else
  {
   result.tier.c = 1;
   y -= geometry_.vertical_outer_sizes().top;
  }
 }
 if(y_offset == -1)
   y_offset = y % 27;
 result.full_ground.y = y_offset;

 y /= 27;
 result.tier.c += y;

 result.init_mid();

 return result;
}


rc2 XCSD_Image::get_tierbox_at_ground_position_RC2(u2 x, u2 y)
{
 rc2 result {0,0};

 if(geometry_.horizontal_outer_sizes().left > 0)
 {
  if(x <= geometry_.horizontal_outer_sizes().left)
    result.r = 0;
  else
  {
   result.r = 1;
   x -= geometry_.horizontal_outer_sizes().left;
  }
 }
 x /= 27;
 result.r += x;

 if(geometry_.vertical_outer_sizes().top > 0)
 {
  if(y <= geometry_.vertical_outer_sizes().top)
    result.c = 0;
  else
  {
   result.c = 1;
   y -= geometry_.vertical_outer_sizes().top;
  }
 }
 y /= 27;
 result.c += y;
 return result;
}


void XCSD_Image::init_outer_ring_info()
{
 outer_ring_info_ = new QVector<XCSD_Outer_Ring_Info>;
 //, QVector<XCSD_Outer_Ring_Info>* outer_ring_info
// geometry_.for_each_outer_ring_area([this, outer_ring_info](u1 index,
//   XCSD_Image_Geometry::Outer_Ring_Area_Flags area_flags)
// {

// });

}

u4 XCSD_Image::tierbox_index_to_full_tier_index(rc2 rc)
{
 XCSD_TierBox* tbox = data_.get_full_tierbox_at_position(rc);
 //return tbl.

 return tbox->full_tier_index();
}


void XCSD_Image::draw_tierboxes_to_folder(QString path,
  Mat2d<Vec1d<QString>>* paths)
{
 if(paths)
 {
  paths->resize(geometry_.full_tier_counts()._transposed_to<pr2>());
  //paths->set_dimensions(geometry_.full_tier_counts()._transposed_to<pr2>());

  paths->fill_with_default(QString());
 }

 geometry_.for_each_full_tierbox([this, &path, paths](XCSD_Image_Geometry::Grid_TierBox& gtb)
 {
  rc2 rc  = gtb.loc.rc()._to_unsigned();
  XCSD_TierBox* tbox = data_.get_full_tierbox_at_position(rc);

  u4 index= tbox->full_tier_index();

  std::map<s1, std::pair<u2, std::vector<n8>>> sdi;
  u4 di = data_tierbox_to_sdi_pixel_map(index, sdi);
  u4 tbox_offset = tbox->pixel_data_ground_offset();

  if(tbox_offset != di)
    qDebug() << " ! " << tbox_offset << " " << di;

  QString info_string = QString("Full tierbox %1 %2 (%3)\n\n").arg(rc.r).arg(rc.c).arg(index);


  QImage image(27, 27, QImage::Format_ARGB32);

#ifdef HIDE

  for(u1 a = 1; a <= 9; ++a)
  {
   for(u1 b = 1; b <= 9; ++b)
   {
    ab1 ab{a,b};
    std::vector<n8> vec = sdi[ab.to_base(10)].second;

    info_string += QString("\nSDI location %1\n").arg(ab1{a,b}.to_base(10));

    n8 pixel0, pixel1;
    u4 offset0, offset1;
    xy1 xy_0, xy_1;

    for(u1 g = 1; g <= 9; ++g)
    {
     abg1 abg {a, b, g};

     s2 abgi = abg.to_base(10);

     if(abgi == 256)
       qDebug() << abgi;

     xy1 xy = tbox->get_local_ground_location_sdi(abgi);

     s2 sdii = geometry_.ground_offset_coords_to_sdi3(xy._to<go_xy1>());
     u4 offset = (u4) tbox->get_ground_offset_sdi(sdii);

     u4 toffset = offset + tbox_offset;

     n8 pixel = data_.get_single_pixel(toffset);
     //n8 pixel = vec[g - 1];

     QRgb* scanline = (QRgb*) image.scanLine(xy.y);
     scanline[xy.x] = pixel_number_to_qrgb(pixel);

     if(g % 3 == 1)
     {
       pixel0 = pixel;
       offset0 = offset;
       xy_0 = xy;
     }
     else if(g % 3 == 2)
     {
       pixel1 = pixel;
       offset1 = offset;
       xy_1 = xy;
     }
     else
     {
      info_string += QString(" %1-%2:%3 %4-%5:%6 %7-%8:%9\n")
        .arg(xy_0.to_qstring(2))
        .arg(offset0, 3, 10, QChar('0'))
        .arg(pixel0, 16, 16, QChar('0'))
        .arg(xy_1.to_qstring(2))
        .arg(offset1, 3, 10, QChar('0'))
        .arg(pixel1, 16, 16, QChar('0'))
        .arg(xy.to_qstring(2))
        .arg(offset, 3, 10, QChar('0'))
        .arg(pixel, 16, 16, QChar('0'));
     }

    }
   }

  }

 #endif //def HIDE

// #ifdef HIDE

  n8 pixel0, pixel1;
  u4 offset0, offset1;
  xy1 xy_0, xy_1;

  for(u1 y = 0; y < 27; ++y)
  {
   QRgb* scanline = (QRgb*) image.scanLine(y);

   for(u1 x = 0; x < 27; ++x)
   {
    go_xy1 go_xy {x, y};
    s2 sdi = geometry_.ground_offset_coords_to_sdi3(go_xy);
    u4 offset = (u4) tbox->get_ground_offset_sdi(sdi);

    u4 toffset = offset + tbox_offset;
    n8 pixel = data_.get_single_pixel(toffset);
    scanline[x] = pixel_number_to_qrgb(pixel);

    if(x % 3 == 0)
    {
     xy_0 = go_xy._to<xy1>();
     offset0 = offset;
     pixel0 = pixel;
    }
    else if(x % 3 == 1)
    {
     xy_1 = go_xy._to<xy1>();
     offset1 = offset;
     pixel1 = pixel;
    }
    else
    {
     if(x % 9 == 2)
       info_string += "\n";

//     info_string += QString(" %1 %2 %3\n").arg(pixel0, 16, 16, QChar('0'))
//       .arg(pixel1, 16, 16, QChar('0')).arg(pixel, 16, 16, QChar('0'));

     info_string += QString(" %1-%2:%3 %4-%5:%6 %7-%8:%9\n")
       .arg(xy_0.to_qstring(2))
       .arg(offset0, 3, 10, QChar('0'))
       .arg(pixel0, 16, 16, QChar('0'))
       .arg(xy_1.to_qstring(2))
       .arg(offset1, 3, 10, QChar('0'))
       .arg(pixel1, 16, 16, QChar('0'))
       .arg(go_xy.to_qstring(2))
       .arg(offset, 3, 10, QChar('0'))
       .arg(pixel, 16, 16, QChar('0'));

    }
   }
  }
 // #endif

  QString local_path = QString("%1/%2-%3.png").arg(path).arg(tbox->grid_position_string()).arg(tbox_offset);
  image.save(local_path);

  if(paths)
  {
   rc2 pos = tbox->matrix_position();
   (*paths)[pos.r][pos.c] = local_path;// new QString(local_path);
  }

  QString local_info_path = QString("%1/%2-%3.txt").arg(path).arg(tbox->grid_position_string()).arg(tbox_offset);
  save_file(local_info_path, info_string);

 });

}


void XCSD_Image::init_tierboxes()
{
 data_.init_tierboxes(&geometry_);

// for(u2 r = 0; r < geometry_.full_tier_counts().height; ++r)
// {
//  for(u2 c = 0; c < geometry_.full_tier_counts().width; ++c)
//  {
//   rc2 rc {r, c};
//   XCSD_TierBox* box = data_.get_full_tierbox_at_position(rc);
//   qDebug() << box->position();
//  }
// }

 XCSD_Image_Geometry::Iteration_Environment ienv = geometry_.formulate_iteration_environment();

 static n8 calc_reset = 0;

 geometry_.for_each_full_tierbox([this, &ienv](XCSD_Image_Geometry::Grid_TierBox& gtb)
 {
//  rc2 rc  = gtb.loc.rc()._to_unsigned();
//  XCSD_TierBox* tbox = data_.get_full_tierbox_at_position(rc);

  XCSD_TierBox* tbox = get_tierbox_from_grid_tierbox(gtb);

  //tbox->check_calculate_pixel_averages_1byte_level1(1, 4, this);


  tbox->set_mch_code(gtb.loc.get_mch_code());

  XCSD_Image_Geometry::MCH_Info mchi;

  u4 index = geometry_.get_tierbox_index(gtb, ienv.size_even_odd_info, &mchi);

  tbox->set_pixel_data_ground_offset(index * tierbox_width * tierbox_width);

  tbox->set_full_tier_index(index);

  tbox->set_tier_ring(mchi.tier_ring);
  tbox->set_inner_pushout(mchi.inner_pushout);
  tbox->set_compressed_clock_index(mchi.compressed_clock_index);
  tbox->set_full_clock_index(mchi.full_clock_index);
  tbox->set_intra_tier_ring_index(mchi.intra_tier_ring_index);

  u2 offset = tbox->get_ground_offset_for_tierbox_center(
    geometry_.full_tier_counts().width, tierbox_width);

  n8 pixel = data_.get_single_pixel(offset);

  tbox->set_reference_color(pixel);

  xy4 xy = geometry_.get_tierbox_scanline_top_left(gtb);
  tbox->set_global_top_left(xy);

  tbox->check_calculate_pixel_averages_1byte(1, 4, this, &calc_reset);

//  QColor qc = pixel_number_to_qcolor(pixel);
//  qDebug() << tbox->matrix_position();
//  qDebug() << tbox->get_matrix_index_position();
//  qDebug() << tbox->get_grid_position();
//  qDebug() << "offset = " << offset;
//  qDebug() << "color = " << stringify_qcolor(qc);
//  qDebug() << "pixel = " << pixel;
//  qDebug() << "global = " << tbox->get_image_ground_location_for_tierbox_center();

 });



// if(index > 0)
//   return-1;

// for(s1 inner_index = 10; inner_index < 100; ++inner_index)
// {
//  XCSD_TierBox::_inner_box _ibox = tbox->get_inner_box(inner_index);

//  if(inner_index % 10)
//  {
//   XCSD_TierBox::_inner_box_3x3* ibox = _ibox._3x3;

//   u2 soffset = tbox->get_scanline_offset_for_inner_center(inner_index);
//   u2 goffset = tbox->get_ground_offset_for_inner_center(inner_index);
//   xy1 xy = tbox->get_ground_location_for_inner_center(inner_index);

//   qDebug()<< "\nindex: " << inner_index <<
//              ", soffset: " << soffset <<
//              ", goffset: " << goffset << ", xy: " << xy;

//   u2 soffset1 = tbox->get_scanline_offset_sdi(inner_index * 10 + 5);
//   u2 goffset1 = tbox->get_ground_offset_sdi(inner_index * 10 + 5);
//   xy1 xy1 = tbox->get_ground_location_sdi(inner_index * 10 + 5);

//   qDebug()<< "index + 5: " << inner_index * 10 + 5 <<
//              ", soffset1: " << soffset1 <<
//              ", goffset1: " << goffset1 << ", xy1: " << xy1;

//  }



// tierboxes_ = new Vec1d<XCSD_TierBox*>({tierbox_count_});
// u4 total_count = 0;

// u1 non_full_h = 0, non_full_v = 0;
// for(u2 r = 0; r < tier_counts_.width; ++r)
// {
//  if(r == 0)
//    non_full_h = horizontal_outer_sizes_.left;
//  else if(r == tier_counts_.width - 1)
//    non_full_h = horizontal_outer_sizes_.right;

//  for(u2 c = 0; c < tier_counts_.height; ++c)
//  {
//   XCSD_TierBox* trb = new XCSD_TierBox;
//   if(non_full_h > 0)
//   {
//    trb->set_non_full_h(non_full_h);
//    if(r == 0)
//      trb->set_non_full_left();
//   }
//   if(c == 0)
//   {
//    non_full_v = vertical_outer_sizes_.top;
//    if(non_full_v > 0)
//    {
//     trb->set_non_full_v(non_full_v);
//     trb->set_non_full_up();
//    }
//   }
//   else if(c == tier_counts_.height - 1)
//   {
//    non_full_v = vertical_outer_sizes_.bottom;
//    if(non_full_v > 0)
//      trb->set_non_full_v(non_full_v);
//   }
//   trb->init_boxes();
//   tierboxes_->get_at(total_count) = trb;
//   ++total_count;
//  }
//  non_full_h = 0; non_full_v = 0;
// }
}

void XCSD_Image::init_tier_counts(XCSD_Image_Geometry::TierGrid_Preferances pref)
{
 geometry_.init_tier_counts(pref);

// u2 w = image_.width();
// u2 h = image_.height();

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


//void XCSD_Image::init_tierbox_counts()
//{

//}


void XCSD_Image::get_255_palette(QVector<QColor>& vec)
{
 vec.resize(255);

 //QImage i16 = image_.convertToFormat(QImage::Format_RGB16);
 QImage i444 = image_.convertToFormat(QImage::Format_RGB444);

 QVector<u2> colors(65536);

 QMap<QRgb, u4> counts;

 u4 w = i444.width();
 u4 h = i444.height();

 for(u4 x = 0; x < w; ++x)
 {
  for(u4 y = 0; y < h; ++y)
  {
   QRgb rgb = i444.pixel(x, y);
   ++counts[rgb];
//   u1 i = i255.pixelIndex(x, y);
//   ++indices[i].second;
  }
 }

 QVector<QRgb> counts_keys = counts.keys().toVector();

 std::sort(counts_keys.begin(),
   counts_keys.end(),
   [&counts](QRgb lhs, QRgb rhs)
 {
  return counts[lhs] > counts[rhs];
 });

// qDebug() << "counts: " << counts_keys;

 if(counts_keys.size() > 255)
   counts_keys.resize(255);

 u1 i = 0;

 for(QRgb k : counts_keys)
 {
  QColor c = QColor(k);
  qDebug() << i << " color: " << c << " count: " << counts[k];
  ++i;
 }

 std::transform(counts_keys.begin(), counts_keys.end(), vec.begin(),
   [](QRgb rgb)
 {
  return QColor(rgb);
 });

// for(u4 y = 0; y < h; ++y)
// {
//  const u1* sl = i444.constScanLine(y);
//  for(u4 x = 0; x < w; ++x)
//  {

//  }
// }

}

QSize XCSD_Image::show_255_palette(QString path,
  QString sorted_path,
  u1 box_width,
  u1 padline_width)
{

 QVector<QColor> vec; //(255);

 get_255_palette(vec);

 u2 xoffset = 3; //box_width * 15 + 20;


 QPixmap pixmap(box_width * 17 + xoffset * 2, box_width * 15);

 QPixmap pixmap1(box_width * 17 + xoffset * 2, box_width * 15);

 QPainter painter(&pixmap);
 QPainter painter1(&pixmap1);


 u1 index = 0;

 bool needs_padline = false;

 painter.setPen(Qt::NoPen);

 QMap<QRgb, u1> positions;

 QMap<QRgb, QPoint> left_positions;

 painter.setBrush(QColor(255, 255, 255));
 painter.drawRect(0, 0, pixmap.width(), pixmap.height());

 painter1.setBrush(QColor(255, 255, 255));
 painter1.drawRect(0, 0, pixmap1.width(), pixmap1.height());


 for(u1 y = 0; y < 15; ++y)
 {
  u2 top = y * box_width;

  for(u1 x = 0; x < 17; ++x)
  {
   QColor c = vec[index];

   positions[c.rgb()] = index;

   if(y > 0)
   {
    if(y % 2)
      needs_padline = (x < 14);
    else
      needs_padline = (x > 0);
   }

   painter.setBrush(c);


   u2 left = x * box_width + xoffset;

   QRect full_rect(left, top, box_width, box_width);
   left_positions[c.rgb()] = full_rect.center();

   if(needs_padline)
   {
    painter.drawRect(left, top + padline_width, box_width, box_width - padline_width);
//    painter.setBrush(QColor(255, 255, 255));
//    painter.drawRect(left, top, box_width, padline_width);
   }
   else
     painter.drawRect(left, top, box_width, box_width);

   ++index;
  }
 }

// pixmap.save(path);

 QVector<QColor> vec1 = vec;

 std::sort(vec1.begin(), vec1.end(), [](QColor lhs, QColor rhs)
 {
  return lhs.value() < rhs.value();
 });

// QPixmap pixmap1(box_width * 15, box_width * 17);
// QPainter painter1(&pixmap1);

 index = 0;


 //bool needs_padline = false;

 //QMap<QColor, u1> positions;

 for(u1 y = 0; y < 15; ++y)
 {
  u2 top = y * box_width;

  for(u1 x = 0; x < 17; ++x)
  {
   QColor c = vec1[index];


   painter1.setBrush(c);

   u2 left = x * box_width + xoffset;

//   if(needs_padline)
//   {
//    painter.drawRect(left, top + padline_width, box_width, box_width);
//    painter.setBrush(QColor(255, 255, 255));
//    painter.drawRect(left, top, box_width, padline_width);
//   }
//   else

   QRect full_rect(left, top, box_width, box_width);

   painter1.setPen(Qt::NoPen);

   painter1.drawRect(full_rect);

   QRgb rgb = c.rgb();
   QPoint qp = left_positions[rgb];

   u1 left_index = positions[rgb];

   left_index /= 17;

   QPen circle_pen = QPen(QColor(0, 20, 50, 90));
   circle_pen.setWidth(1);

   painter1.setBrush(QColor(255, 255, 255));

   if(left_index < 9)
   {
    painter1.setPen(circle_pen);

    QPoint p1 = full_rect.center() + QPoint{left_index, left_index};
    QPoint p2 = full_rect.center() + QPoint{left_index, -left_index};
    QPoint p3 = full_rect.center() + QPoint{-left_index, -left_index};
    QPoint p4 = full_rect.center() + QPoint{-left_index, left_index};

//    u1 cut = 7;

    QVector<QPoint> points({p1, p2, p3, p4});
    QPolygon poly(points);

    painter1.drawPolygon(points);
   }
   else
   {
    painter1.setPen(Qt::NoPen);

    QPoint p1 = full_rect.center() + QPoint{left_index, left_index};
    QPoint p2 = full_rect.center() + QPoint{left_index, -left_index};
    QPoint p3 = full_rect.center() + QPoint{-left_index, -left_index};
    QPoint p4 = full_rect.center() + QPoint{-left_index, left_index};

    u1 cut = 5;

    QVector<QPoint> points({p1 + QPoint{-cut, 0}, p1 + QPoint{0, -cut},
      p2 + QPoint{0, cut}, p2 + QPoint{-cut, 0},
      p3 + QPoint{cut, 0}, p3 + QPoint{0, cut},
      p4 + QPoint{0, -cut}, p4 + QPoint{cut, 0}
      });
    QPolygon poly(points);

    painter1.drawPolygon(points);
   }


//   QPainterPath path;
//   path.moveTo(full_rect.center() + QPoint{0, left_index});
//   path.lineTo(full_rect.topLeft());
//   path.lineTo(full_rect.topRight());
//   path.lineTo(rect.left() + (rect.width() / 2), rect.top());


   //painter1.drawEllipse(full_rect.center(), left_index, left_index);

   ++index;
  }
 }

 pixmap1.save(sorted_path);
 pixmap.save(path);

 return pixmap1.size();

}


// QImage i255 = image_.convertToFormat(QImage::Format_Indexed8, Qt::ColorOnly);

// QVector<QPair<u1, u4>> indices(256);

// //QVector<QPair<u1, u4>> indices_sorted(256);
// QVector<s2> indices_sorted(256);

// for(u2 i = 0; i < 256; ++i)
//   indices[i].first = i;

// u4 w = i255.width();
// u4 h = i255.height();

// for(u4 x = 0; x < w; ++x)
// {
//  for(u4 y = 0; y < h; ++y)
//  {
//   u1 i = i255.pixelIndex(x, y);
//   ++indices[i].second;
//  }
// }

// std::sort(indices.begin(), indices.end(), [](auto pr1, auto pr2)
// {
//  return pr1.second < pr2.second;
// });

// std::transform(indices.rbegin(), indices.rend(), indices_sorted.begin(), [](auto pr)
// {
//  if(pr.second == 0)
//    return (s2) -1;
//  return (s2) pr.first;
// });

// qDebug() << "indices: " << indices_sorted;

// indices_sorted.removeLast();

// u1 i = 0;
// for(s2 color_index: indices_sorted)
// {
//  if(color_index == -1)
//    break;
//  vec[i] = i255.color(color_index);
//  ++i;
// }

// qDebug() << "vec: " << vec;

//}
//// u1 tw = image_.width();

// u2 start_Top_Left_Corner = 0;
// u2 end_Top_Left_Corner = geometry_.get_outer_ring_position_end(
//   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Left_Corner);


// u2 start_Top_Left_Top = geometry_.get_outer_ring_position_start(
//   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Left_Top);
// u2 end_Top_Left_Top = geometry_.get_outer_ring_position_end(
//   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Left_Top);
// u2 start_Top_Center = geometry_.get_outer_ring_position_start(
//   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Center);
// u2 end_Top_Center = geometry_.get_outer_ring_position_end(
//   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Center);
// u2 start_Top_Right_Top = geometry_.get_outer_ring_position_start(
//   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Right_Top);
// u2 end_Top_Right_Top = geometry_.get_outer_ring_position_end(
//   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Right_Top);

//  // note start at the end here
// u2 start_Top_Right_Corner = geometry_.get_outer_ring_position_end(
//   XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Right_Corner);
// u2 end_Top_Right_Corner = image_.width();

//// for(u1 x = start_Top_Left_Corner; x < end_Top_Left_Corner; ++x)
//// {
////  QRgb* data = (QRgb*) image_.constScanLine(y);
////  QRgb pixel = data[x];
//// }


// u4 mark_offset = 0;

// u1 index = 13;
//   _init_outer_ring_pixel_data(offset, (XCSD_Image_Geometry::Outer_Ring_Positions::Landscape) index,
//    geometry_.outer_ring_positions().index_pairs[index], {height_from_bottom, bottom});

// _init_outer_ring_pixel_data(offset, XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Left_Corner,
//   {start_Top_Left_Corner, end_Top_Left_Corner}, {0, (u1)(height - 1)});


// _init_outer_ring_pixel_data(offset, XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Left_Top,
//   {start_Top_Left_Top, end_Top_Left_Top}, {0, (u1)(height - 1)});

// _init_outer_ring_pixel_data(offset, XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Center,
//   {start_Top_Center, end_Top_Center}, {0, (u1)(height - 1)});

// _init_outer_ring_pixel_data(offset, XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Right_Top,
//   {start_Top_Right_Top, end_Top_Right_Top}, {0, (u1)(height - 1)});



// _init_outer_ring_pixel_data(offset, XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Left_Corner,
//   {start_Top_Left_Corner, end_Top_Left_Corner}, {0, (u1)(height - 1)});

// _init_outer_ring_pixel_data(offset, XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Left_Top,
//   {start_Top_Left_Top, end_Top_Left_Top}, {0, (u1)(height - 1)});

// _init_outer_ring_pixel_data(offset, XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Center,
//   {start_Top_Center, end_Top_Center}, {0, (u1)(height - 1)});

// _init_outer_ring_pixel_data(offset, XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Right_Top,
//   {start_Top_Right_Top, end_Top_Right_Top}, {0, (u1)(height - 1)});




 //for(u2 y = 0; y < height; ++y)
// for(u2 y = 0; y < height; ++y)
// {
//  QRgb* scanline = (QRgb*) image_.constScanLine(y);

//    mark_offset = geometry_.outer_ring_positions().offset_for(
//      XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Left_Corner)
//      + y * (end_Top_Left_Corner - start_Top_Left_Corner + 1);
//    for(u2 x = start_Top_Left_Corner; x <= end_Top_Left_Corner; ++x)
//    {
//     QRgb qpixel = scanline[x];
//     n8 pixel = qrgb_to_pixel_number(qpixel);
//     data_.init_single_pixel(offset + mark_offset, pixel);

//     qDebug() << "x = " << x << "y = " << y << " index = " << offset + mark_offset << " pixel = " << pixel;

//     ++mark_offset;
//    }


//  mark_offset = geometry_.outer_ring_positions().offset_for(
//    XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Left_Top);
//  for(u2 x = start_Top_Left_Top; x < end_Top_Left_Top; ++x)
//  {
//   QRgb qpixel = scanline[x];
//   n8 pixel = qrgb_to_pixel_number(qpixel);
//   data_.init_single_pixel(offset + mark_offset, pixel);
//   ++mark_offset;
//  }

#ifdef HIDE
  mark_offset = geometry_.outer_ring_positions().offset_for(
    XCSD_Image_Geometry::Outer_Ring_Positions::Landscape::Top_Center)
    + y * (end_Top_Center - start_Top_Center);
  for(u2 x = start_Top_Center; x <= end_Top_Center; ++x) //x < end_Top_Center; ++x)
  {
   QRgb qpixel = scanline[x];

//   n8 ntest00 = data_.get_single_pixel(949352);
//   qDebug() << "ntest00 = " << ntest00;

   n8 pixel = qrgb_to_pixel_number(qpixel);

//   if(x < start_Top_Center + 50)
//   {
    qDebug() << "x = " << x << "y = " << y << " index = " << offset + mark_offset << " pixel = " << pixel;

    data_.init_single_pixel(offset + mark_offset, pixel);
//   }

//   n8 ntest01 = data_.get_single_pixel(949352);
//   qDebug() << "ntest01 = " << ntest01;

   ++mark_offset;
  }
#endif

// }

