
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "xcsd-image-data.h"

#include "xcsd-image-geometry.h"

#include "mat2d.templates.h"

#include "xcsd-tierbox.h"

USING_XCNS(XCSD)

XCSD_Image_Data::XCSD_Image_Data()
  :  tierboxes_(nullptr), pixel_data_(nullptr),
     image_geometry_(nullptr)
{

}

void XCSD_Image_Data::init_pixels(wh2 total_ground_size)
{
 u4 area = total_ground_size.area();
 pixel_data_ = new Arr1d<n8, index_types<s4>>({(s4)area});
}

void XCSD_Image_Data::get_pixel_run(u4 start_index, u4 length, std::vector<n8>& result)
{
 if(result.size() < length)
   result.resize(length);
 pixel_data_->fetch_raw_data(start_index, length, result.data());
}

u4 XCSD_Image_Data::get_pixel_data_length()
{
 return pixel_data_->size();
}


n8* XCSD_Image_Data::get_pixel_data_start(u4 start_index)
{
 return pixel_data_->get(start_index);
}

void XCSD_Image_Data::init_pixel_run(u4 start_index, u4 length, n8 const* source)
{
 pixel_data_->init_raw_data(start_index, length, source);
}

void XCSD_Image_Data::init_single_pixel(u4 index, n8 pixel_number)
{
 n8* pos = pixel_data_->get(index);
 if(pos)
   *pos = pixel_number;
}

n8 XCSD_Image_Data::get_single_pixel(u4 index)
{
 n8* result = get_pixel_data_start(index);
 if(result)
   return *result;
 return 0;
}



void XCSD_Image_Data::copy_pixels(u4 start_index, const std::vector<n8>& vec)
{
 init_pixel_run(start_index, vec.size(), vec.data());
}


XCSD_TierBox* XCSD_Image_Data::get_full_tierbox_at_position(rc2 rc)
{
 return (*tierboxes_)[rc.r + 2](rc.c + 2);
}


void XCSD_Image_Data::init_tierboxes(XCSD_Image_Geometry* image_geometry)
{
 image_geometry_ = image_geometry;
 wh2 counts = image_geometry_->full_tier_counts() + 2;

 rc2 counts_outliers = counts._transposed_to<rc2>().double_minus(1);

 tierboxes_ = new Mat2d< Vec1d<XCSD_TierBox*> >(counts.height, counts.width);


 for(u2 r = 0; r < counts.height; ++r)
 {
  for(u2 c = 0; c < counts.width; ++c)
  {
   rc2 rc {r, c};

   if(rc.outlies(counts_outliers)) //r == 0 || c == 0 || r == counts.height - 1 || c == counts.width - 1)
   {
    rc.double_add(1);
    (*tierboxes_)[rc.r][rc.c] = nullptr;
    continue;
   }


   // // rc is now +1 to work with Mat2d's 1-based indexing
    //   while frc is -1 to exclude the outer ring
   rc2 frc = rc.double_minus_then_add(1);
   XCSD_TierBox* tbx = new XCSD_TierBox(frc);
   (*tierboxes_)[rc.r][rc.c] = tbx;
  }
 }
}

