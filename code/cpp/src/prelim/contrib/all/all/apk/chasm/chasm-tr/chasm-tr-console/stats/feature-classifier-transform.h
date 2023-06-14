
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef FEATURE_CLASSIFIER_TRANSFORM__H
#define FEATURE_CLASSIFIER_TRANSFORM__H

#include <QString>

#include "accessors.h"

#include "global-types.h"

//?#include "xcsd-2d/xcsd-sdi-structures.h"


#include <QColor>

typedef QPair<u1, u1> wh1;

class Feature_Classifier_Transform
{ 
 r8 rotation_;
 r8 horizontal_skew_;
 r8 horizontal_shear_;
 r8 horizontal_shear_centered_;
 r8 vertical_skew_;
 r8 vertical_shear_;
 r8 vertical_shear_centered_;

 QColor foreground_color_;
 wh1 box_sizes_;

 QString color_distance_model_;
 u1 color_distance_threshold_;
 u2 lightness_adjustment_;


public:

 Feature_Classifier_Transform();

 ACCESSORS(r8 ,rotation)
 ACCESSORS(r8 ,horizontal_skew)
 ACCESSORS(r8 ,horizontal_shear)
 ACCESSORS(r8 ,horizontal_shear_centered)
 ACCESSORS(r8 ,vertical_skew)
 ACCESSORS(r8 ,vertical_shear)
 ACCESSORS(r8 ,vertical_shear_centered)

 ACCESSORS(QColor ,foreground_color)
 ACCESSORS(wh1 ,box_sizes)

 ACCESSORS(QString ,color_distance_model)
 ACCESSORS(u1 ,color_distance_threshold)
 ACCESSORS(u2 ,lightness_adjustment)

 QColor adjusted_foreground_color();


 void init_from_ntxh(QString ntxh_file);
 void init_from_kv_text(QString kv_text);




};

#endif // STAT_TEST_IMAGE__H
