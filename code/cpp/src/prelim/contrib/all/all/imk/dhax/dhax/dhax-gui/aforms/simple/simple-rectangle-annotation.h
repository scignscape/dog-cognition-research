
#ifndef SIMPLE_RECTANGLE_ANNOTATION__H
#define SIMPLE_RECTANGLE_ANNOTATION__H


#include <QRubberBand>

#include "global-types.h"

#include "accessors.h"

#include "../simple-annotation-base.h"


class Simple_Rectangle_Annotation : public Simple_Annotation_Base
{
 Q_OBJECT

public:

// u2 left_margin, top_left_margin, top_margin, top_right_margin,
//   right_margin, bottom_right_margin, bottom_margin, bottom_left_margin;
// r8 left_margin_against_image, top_left_margin_against_image, top_margin_against_image,
//   top_right_margin_against_image,
//   right_margin_against_image, bottom_right_margin_against_image,
//   bottom_margin_against_image, bottom_left_margin_against_image;

 enum Parameters {
   u2_width = 0, u2_height = 1, u2_perimeter = 2,
   u2_image_width = 3, u2_image_height = 4,
   u2_image_perimeter = 5, u4_area = 6, u4_image_area = 7,
   r8_wh_ratio = 8, r8_hw_ratio = 9, r8_image_wh_ratio = 10,
   r8_image_hw_ratio = 11, r8_width_against_image = 12,
   r8_height_against_image = 13, r8_perimeter_against_image = 14,
   r8_area_against_image = 15,
   u2_left_margin = 16, u2_top_left_margin = 17,
   u2_top_margin = 18, u2_top_right_margin = 19,
   u2_right_margin = 20, u2_bottom_right_margin = 21,
   u2_bottom_margin = 22, u2_bottom_left_margin = 23,
   r8_left_margin_against_image = 24, r8_top_left_margin_against_image = 25,
   r8_top_margin_against_image = 26, r8_top_right_margin_against_image = 27,
   r8_right_margin_against_image = 28, r8_bottom_right_margin_against_image = 29,
   r8_bottom_margin_against_image = 30, r8_bottom_left_margin_against_image = 31,
   max = 31, count = 32
 };

 enum Directions {
   Left = 0, left = 0, Top_Left = 1, top_left = 1, Top = 2, top = 2,
   Top_Right = 3, top_right = 3, Right = 4, right = 4,
   Bottom_Right = 5, bottom_right = 5, Bottom = 6, bottom = 6,
   Bottom_Left = 7, bottom_left = 7
 };


 struct Measurements {
   u2 width, height, perimeter, image_width, image_height, image_perimeter;
   u4 area, image_area;
   r8 wh_ratio, hw_ratio, image_wh_ratio, image_hw_ratio,
   width_against_image, height_against_image,
   perimeter_against_image, area_against_image;
   u2 margins [8];
   r8 margins_against_image [8];
 };

private:

 Measurements* measurements_;

public:

 Simple_Rectangle_Annotation(DHAX_Mouse_Interaction_Data& mouse_interaction_data, const QPointF& sc, QWidget* p = nullptr);

 Measurements& get_measurements();

 QColor get_occurant_color_mean(u1 number_of_iterations = 10, u1 rounding_factor = 1);
 QColor get_occurant_color_mean(QVector<u4> rgb[3], u1 number_of_iterations, u1 rounding_factor);
 QRectF against_image_coords();

 void get_occurants_vectors(QVector<u4> (&result) [3]);

 QColor get_additive_color_mean(QVector<u4> rgb[3]);

 QString kind_name() Q_DECL_OVERRIDE
 {
  return "Simple-Rectangle";
 }

protected:


Q_SIGNALS:

protected:

// void paintEvent(QPaintEvent *event) ;


public Q_SLOTS:

};

#endif // SIMPLE_RECTANGLE_ANNOTATION__H
