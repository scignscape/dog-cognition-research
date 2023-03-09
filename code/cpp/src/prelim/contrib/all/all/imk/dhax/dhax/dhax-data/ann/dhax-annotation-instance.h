
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_ANNOTATION_INSTANCE__H
#define DHAX_ANNOTATION_INSTANCE__H

#include <QString>
#include <QPoint>
#include <QVector>


#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include "location/dhax-location-2d.h"

#include <functional>

#include <QGraphicsRectItem>

#include "kans.h"


//KANS_(GTagML)

class DHAX_Annotation_Group;

class DHAX_Annotation_Instance
{
 QVector<n8> locations_;

 DHAX_Annotation_Group* group_;
 QString comment_;

 QStringList scoped_identifiers_;
 QString shape_designation_;

 //?QVector<QPoint>* prelim_shape_points_;


 u2 composite_dimension_code_;
 u1 composite_shape_code_;

 u1 internal_codes_;

 static constexpr u1 internal_code_checked_qrect = 128;

 enum class _Internal_Codes { //_init_as_qrectf_internal_codes {
   N_A,
   Error,
   Declared_As_Rectangle_two_corners,
   Declared_As_Rectangle_hside_and_length,
   Declared_As_Rectangle_vside_and_length,
   Declared_As_Rectangle_hside_and_length_center,
   Declared_As_Rectangle_vside_and_length_center,
   Declared_As_Rectangle_corner_and_two_lengths,
   Declared_As_Rectangle_center_and_two_lengths,
   Declared_As_Rectangle_side_and_length,
   Declared_As_Rectangle_side_and_length_center,
   Declared_As_Rectangle_unit_square_at_center,
   Declared_As_Rectangle_unit_square_at_corner,
   Declared_As_Rectangle_square_at_center,
   Declared_As_Rectangle_square_at_corner,
   Declared_As_Rectangle_horizontal_then_vertical,
   Declared_As_Rectangle_horizontal_then_vertical_center,
   Declared_As_Rectangle_vertical_then_horizontal,
   Declared_As_Rectangle_vertical_then_horizontal_center,
   Declared_As_Rectangle_flat_vertical,
   Declared_As_Rectangle_flat_vertical_center,
   Declared_As_Rectangle_flat_horizontal,
   Declared_As_Rectangle_flat_horizontal_center,
   Declared_As_Rectangle_TBD,
 };

 union {
  QVector<u4>* int4;
  QVector<n8>* int8;
  QVector<float>* fl4;
  QVector<double>* dbl8;
  n8 single;
 } shape_lengths_;

public:

 DHAX_Annotation_Instance();

 ACCESSORS(QVector<n8> ,locations)

 ACCESSORS__RGET(QStringList ,scoped_identifiers)

// ACCESSORS(n8 ,opaque_shape_kind_code)
// ACCESSORS(QString ,comment)

 ACCESSORS(DHAX_Annotation_Group* ,group)
 ACCESSORS(QString ,comment)

 QString scoped_identifiers_to_string();
 ACCESSORS(QString ,shape_designation)

//? ACCESSORS(QVector<QPoint>* ,prelim_shape_points)
// void check_init_prelim_shape_points()
// {
//  if(!prelim_shape_points_)
//    prelim_shape_points_ = new QVector<QPoint>;
// }

// void add_prelim_shape_point(const QPoint& qp)
// {
//  prelim_shape_points_->push_back(qp);
// }

 enum class Compact_Shape_Kind_Summary {
   N_A, Non_Regular_Polygon, Rectangle, Arrow,
   Regular_Polygon, Multiline, Polyline, //?Measurement,  //?Diamond, Polyline,
   Ellipse, QPath, Curve, Measurement, Skew_Rhombus,
     Other_Non_Linear,
 };


 enum class Non_Linear_Shape_Kinds {
   Ellipse, QPath, Curve, Other
 };

 enum class Colinear {
   N_A, Horizontal, Vertical, Linear_At_Angle,
   Horizontal_Then_Vertical, Vertical_Then_Horizontal,
   Multiple_Horizontal, Multiple_Vertical, TBD,
   Multiple_Linear_At_Angle, Orthogonal_At_Angle,
 };

 Colinear check_colinear(n8 loc1, n8 loc2);
 Colinear check_colinear_vh(n8 loc1, n8 loc2, n8 loc3);

 void add_scoped_identifier(QString sid)
 {
  scoped_identifiers_.push_back(sid);
 }

 void init_polygon()
 {
  // //
  composite_shape_code_ = 1;
 }

// void init_rectangle()
// {
//  init_polygon(1);
// }


 void init_polygon(u1 sides)
 {
  sides &= 31;
  // //
  composite_shape_code_ = 1 | (sides << 3);
 }

 void init_polyline()
 {
  // //
  composite_shape_code_ = 3;
 }

 void init_polyline(u1 sides)
 {
  sides &= 31;
  // //
  composite_shape_code_ = 3 | (sides << 3);
 }

 void set_open_flag()
 {
  composite_shape_code_ |= 2;
 }

 void set_center_flag()
 {
  composite_shape_code_ |= 4;
 }

 void set_non_linear_shape_kind(Non_Linear_Shape_Kinds sk)
 {
  composite_shape_code_ &= 254; // clear polygon flag
  composite_shape_code_ |= ((u1) sk << 3);
 }

 u1 get_shape_kind_secondary_code()
 {
  return composite_shape_code_ >> 6;
 }

 static u1 get_raw_polygon_side_count(u1 csc)
 {
  return csc >> 3;
 }

 // raw_polygon_sides = 0:  non-regular
 // raw_polygon_sides = 1:  rectangle
 // raw_polygon_sides = 2:  arrow
 // raw_polygon_sides = 31:  diamond
 // raw_polygon_sides >= 3:  regular polygon
 u1 get_raw_polygon_side_count()
 {
  return get_raw_polygon_side_count(composite_shape_code_);
 }



 void init_rectangle()
 {
  init_polygon(1);
 }

 void init_square()
 {
  init_polygon(31);
 }

 void init_diamond()
 {
  init_square();
  // //  for diamonds open flag means
   //    one diagonal may be longer
  set_open_flag();
 }

 void init_ellipse()
 {
  set_non_linear_shape_kind(Non_Linear_Shape_Kinds::Ellipse);
 }

 static Non_Linear_Shape_Kinds get_non_linear_shape_kind(u1 csc)
 {
  u1 sc = csc >> 3;
  sc &= 3;
  return (Non_Linear_Shape_Kinds) sc;
 }

 Non_Linear_Shape_Kinds get_non_linear_shape_kind()
 {
  return get_non_linear_shape_kind(composite_shape_code_);
 }

// bool shape_is_open();
// bool shape_is_closed();
// bool shape_is_regular();

  bool open_shape_flag()
  {
   return composite_shape_code_ & 2;
  }

  bool center_flag()
  {
   return composite_shape_code_ & 4;
  }


 enum class Dimension_Scale {
   Integer, Float, Ratio, Proper_Fraction
 };

 enum class Dimension_Units {
   N_A, Px, Pc, In, Pt, Cm, Mm, QPoint_or_QPointF
 };

 enum class Byte_Lengths {
   Other, Two, Four, Eight
 };

 ACCESSORS__GSDECLARE(Byte_Lengths ,byte_lengths)
 ACCESSORS__GSDECLARE(Dimension_Units ,dimension_units)
 ACCESSORS__GSDECLARE(Dimension_Scale ,dimension_scale)

 ACCESSORS__GSDECLARE(Byte_Lengths ,shape_lengths_byte_lengths)
 ACCESSORS__GSDECLARE(Dimension_Units ,shape_lengths_dimension_units)
 ACCESSORS__GSDECLARE(Dimension_Scale ,shape_lengths_dimension_scale)

 bool is_signed();
 void note_signed();

 void default_dimensions();
 void reuse_dimensions_for_shape_lengths();

 void qpoint_dimensions();
 void qpointf_dimensions();


// QPair<QPoint, QPoint> to_tlbr_points(const QVector<QPoint>& vec);
// QPair<QPointF, QPointF> to_tlbr_points(const QVector<QPointF>& vec);
 static void to_tlbr_points(QVector<QPoint>& vec);
 static void to_tlbr_points(QVector<QPointF>& vec);

 bool float_dimensions()
 {
  return get_dimension_scale() == Dimension_Scale::Float;
 }

 static Compact_Shape_Kind_Summary check_compact_representation(u1 csc, u1* num_sides = nullptr);
 Compact_Shape_Kind_Summary check_compact_representation(u1* num_sides = nullptr)
 {
  return check_compact_representation(composite_shape_code_, num_sides);
 }

 bool single_shape_length();
 void note_single_shape_length();

 void init_shape_lengths();
 void check_init_shape_lengths();
 void set_shape_length(n8 len);
 void set_shape_length(double len);
 void set_shape_length(float len);

 void add_shape_point(s4 c1, s4 c2);
 void add_shape_point(u4 c1, u4 c2);
 void add_shape_point(double c1, double c2);
 void add_shape_point(float c1, float c2);

 void add_shape_length(n8 len);
 void add_shape_length(double len);
 void add_shape_length(float len);

 void from_compact_string(QString cs);


 void add_signed_shape_point(s4 c1, s4 c2);

 u2 get_shape_point_count();
 u2 get_shape_length_count();

// void absorb_shape_point(const QPoint& qp);
 QString to_compact_string();
 void locations_to_qpoints(QVector<QPoint>& result);
 void locations_to_qpoints(QVector<QPointF>& result);

 template<typename T>
 inline bool fits()
 {
  return false;
 }

 void init_as(QRectF& qrf);
 void init_as(QRect& qr);
};

template<>
inline bool DHAX_Annotation_Instance::fits<QGraphicsRectItem>()
{
 if(open_shape_flag())
   return false;
 internal_codes_ = internal_code_checked_qrect;
 if(composite_shape_code_ & 1) // polygon flag
 {
  u2 point_count = get_shape_point_count();
  u2 length_count = get_shape_length_count();
//  Declared_As_Rectangle'
//   if(center_flag())
//   {

//   }
  if(point_count == 0)
    return false;
  u1 side_count = get_raw_polygon_side_count();
  if(side_count == 1) // rectangle, non-regular
  {
   if(point_count == 2)    // //   one side or two corners?
   {
    if(length_count == 0) // two corners
    {
     // //  always considered to define QRectF (even if on same
      //    vertical or horizontal line)
     internal_codes_ |= (u1) _Internal_Codes::Declared_As_Rectangle_two_corners;
     return true;
    }
    else //  first length is width or height
    {
     Colinear co = check_colinear(locations_[0], locations_[1]);
     switch (co)
     {
     case Colinear::Horizontal:
      internal_codes_ |= center_flag()?
         (u1) _Internal_Codes::Declared_As_Rectangle_hside_and_length_center :
         (u1) _Internal_Codes::Declared_As_Rectangle_hside_and_length;
      return true;
     case Colinear::Vertical:
      internal_codes_ |= center_flag()?
        (u1) _Internal_Codes::Declared_As_Rectangle_vside_and_length_center :
        (u1) _Internal_Codes::Declared_As_Rectangle_vside_and_length;
      return true;
     case Colinear::Linear_At_Angle:
      internal_codes_ |= center_flag()?
        (u1) _Internal_Codes::Declared_As_Rectangle_side_and_length_center :
        (u1) _Internal_Codes::Declared_As_Rectangle_side_and_length;
      return false;
     default: return false; // should never happen with just two points
     }
    }
   }
   else if(point_count == 1)
   {
    if(length_count == 0) //  unit square horiztonal/vertical aligned
    {
     internal_codes_ |= center_flag()?
        (u1) _Internal_Codes::Declared_As_Rectangle_unit_square_at_center :
        (u1) _Internal_Codes::Declared_As_Rectangle_unit_square_at_corner;
     return true;
    }
    else if(length_count == 1)
    {
     internal_codes_ |= center_flag()?
       (u1) _Internal_Codes::Declared_As_Rectangle_unit_square_at_center :
       (u1) _Internal_Codes::Declared_As_Rectangle_unit_square_at_corner;
     return true;
    }
    else
    {
     internal_codes_ |= center_flag()?
       (u1) _Internal_Codes::Declared_As_Rectangle_center_and_two_lengths :
       (u1) _Internal_Codes::Declared_As_Rectangle_corner_and_two_lengths;
     return true;
    }
   }
   else if(point_count == 3)
   {
    Colinear co = check_colinear_vh(locations_[0], locations_[1], locations_[2]);
    if(co == Colinear::Horizontal_Then_Vertical)
    {
     internal_codes_ |= center_flag()?
       (u1) _Internal_Codes::Declared_As_Rectangle_horizontal_then_vertical_center :
       (u1) _Internal_Codes::Declared_As_Rectangle_horizontal_then_vertical;
     return true;
    }
    if(co == Colinear::Vertical_Then_Horizontal)
    {
     internal_codes_ |= center_flag()?
       (u1) _Internal_Codes::Declared_As_Rectangle_vertical_then_horizontal_center :
       (u1) _Internal_Codes::Declared_As_Rectangle_vertical_then_horizontal;
     return true;
    }
    if(co == Colinear::Multiple_Horizontal)
    {
     internal_codes_ |= center_flag()?
       (u1) _Internal_Codes::Declared_As_Rectangle_flat_horizontal_center :
       (u1) _Internal_Codes::Declared_As_Rectangle_flat_horizontal;
     return true;
    }
    if(co == Colinear::Multiple_Vertical)
    {
     internal_codes_ |= center_flag()?
       (u1) _Internal_Codes::Declared_As_Rectangle_flat_vertical_center :
       (u1) _Internal_Codes::Declared_As_Rectangle_flat_vertical;
     return true;
    }
    if(co == Colinear::TBD)
    {
     internal_codes_ |= (u1) _Internal_Codes::Declared_As_Rectangle_TBD;
     return false;
    }
    // //  will we ever get here?
    internal_codes_ |= (u1) _Internal_Codes::Error;
    return false;
   }
  }
  if(side_count == 31) // diamond
  {
//    if(points == )
  }
  else if(side_count == 4)
  {
   return true;
  }
 }
 return false;
}

// _KANS(GTagML)


#endif  //  DHAX_ANNOTATION_INSTANCE__H
