
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "local-histogram-data.h"

#include "xcsd-image.h"


Local_Histogram_Data::Local_Histogram_Data()
  :  largest_group_total_(0), largest_bin_(0), largest_group_hue_(-2)
{

}

QColor Local_Histogram_Data::get_ref_color() const
{
 return XCSD_Image::rgb555_to_qcolor(largest_group_hue_ref_color_);

 //if(largest_group_hue_ref_color_ )
// Histogram_Group_Summary hgs = combined_map_.value(largest_group_hue_);
// u2 most = hgs.max;
 //return largest_group_hue_ref_color();
 //u2
}
