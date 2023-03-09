
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef LOCAL_HISTOGRAM_DATA__H
#define LOCAL_HISTOGRAM_DATA__H


#include "xcsd-1d/_vec1d.h"

#include "xcsd-1d/vec1d.h"
#include "xcsd-1d/arr1d.h"

#include "xcsd-sdi-structures.h"

#include <QImage>

#include "accessors.h"

XCNS_(XCSD)

//class XCSD_XPixel;


struct Histogram_Group_Summary
{
 u2 total;
 u2 max;
 QVector<pr2> counts;
};


class Local_Histogram_Data
{

 QMap<u2, u2> rgb555_map_;
 QMap<s2, u2> hue_map_;

 QMap<s2, Histogram_Group_Summary> combined_map_;

 u2 largest_group_total_;
 u2 largest_bin_;

 s2 largest_group_hue_;
 u2 largest_group_hue_ref_color_;

public:

 Local_Histogram_Data();

 ACCESSORS__RGET(MACRO_PASTE(QMap<u2, u2>) ,rgb555_map)
 ACCESSORS__RGET_CONST(MACRO_PASTE(QMap<u2, u2>) ,rgb555_map)
 ACCESSORS__RGET(MACRO_PASTE(QMap<s2, u2>) ,hue_map)
 ACCESSORS__RGET_CONST(MACRO_PASTE(QMap<s2, u2>) ,hue_map)
 ACCESSORS__RGET(MACRO_PASTE(QMap<s2, Histogram_Group_Summary>) ,combined_map)
 ACCESSORS__RGET_CONST(MACRO_PASTE(QMap<s2, Histogram_Group_Summary>) ,combined_map)

 ACCESSORS(u2 ,largest_group_total)
 ACCESSORS(u2 ,largest_bin)

 ACCESSORS(s2 ,largest_group_hue)
 ACCESSORS(u2 ,largest_group_hue_ref_color)


 QColor get_ref_color() const;


};


_XCNS(XCSD)

#endif // LOCAL_HISTOGRAM_DATA__H
