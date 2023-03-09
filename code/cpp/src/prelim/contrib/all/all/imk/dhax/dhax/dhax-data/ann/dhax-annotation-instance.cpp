
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-annotation-instance.h"

#include "location/dhax-location-2d.h"
#include "location/dhax-signed-location-2d.h"
#include "location/dhax-float-location-2d.h"
#include "location/dhax-double-location-2d.h"

#include <QDebug>

DHAX_Annotation_Instance::DHAX_Annotation_Instance()
  :  shape_lengths_({.int4=nullptr}),
     composite_shape_code_(0),
     composite_dimension_code_(0)//, prelim_shape_points_(nullptr)
{

}

QString DHAX_Annotation_Instance::scoped_identifiers_to_string()
{
 return scoped_identifiers_.join(':');
}

u2 DHAX_Annotation_Instance::get_shape_point_count()
{
 return locations_.size();
}

u2 DHAX_Annotation_Instance::get_shape_length_count()
{
 if(single_shape_length())
   return 1;

 if(!shape_lengths_.int4)
   return 0;

 if(get_shape_lengths_dimension_scale() == Dimension_Scale::Float)
 {
  if(get_shape_lengths_byte_lengths() == Byte_Lengths::Eight)
    return shape_lengths_.dbl8->size();
  else
    return shape_lengths_.fl4->size();
 }
 else
 {
  if(get_shape_lengths_byte_lengths() == Byte_Lengths::Eight)
    return shape_lengths_.int8->size();
  else
    return shape_lengths_.int4->size();
 }
}


void DHAX_Annotation_Instance::check_init_shape_lengths()
{
 if(!shape_lengths_.int4)
   init_shape_lengths();
}

void DHAX_Annotation_Instance::init_shape_lengths()
{
 if(single_shape_length())
   return; // nothing to do ...

 if(get_shape_lengths_dimension_scale() == Dimension_Scale::Float)
 {
  if(get_shape_lengths_byte_lengths() == Byte_Lengths::Eight)
    shape_lengths_.dbl8 = new QVector<double>;
  else
    shape_lengths_.fl4 = new QVector<float>;
 }
 else
 {
  if(get_shape_lengths_byte_lengths() == Byte_Lengths::Eight)
    shape_lengths_.int8 = new QVector<n8>;
  else
    shape_lengths_.int4 = new QVector<u4>;
 }
}

void DHAX_Annotation_Instance::set_shape_length(double len)
{
 check_init_shape_lengths();
 if(get_shape_lengths_dimension_scale() == Dimension_Scale::Float)
 {
  if(get_shape_lengths_byte_lengths() == Byte_Lengths::Eight)
    *shape_lengths_.dbl8 = {len};
  else
    *shape_lengths_.fl4 = {(float)len};
 }
 else
 {
  qDebug() << "Warning: converting double to integer for shape length";
  if(get_shape_lengths_byte_lengths() == Byte_Lengths::Eight)
    *shape_lengths_.int8 = {(n8)len};
  else
    *shape_lengths_.int4 = {(u4)len};
 }
}

void DHAX_Annotation_Instance::set_shape_length(float len)
{
 // //  just reuse the double implementation; probably OK
 set_shape_length((double) len);
}


void DHAX_Annotation_Instance::set_shape_length(n8 len)
{
 if(!single_shape_length())
   qDebug() << "Warning: setting a single length for an annotation expecting a length vector";

 if(get_shape_lengths_byte_lengths() == Byte_Lengths::Eight)
   shape_lengths_.single = len;

 else
 {
  u4 len4 = len;
  if(len4 != len)
    qDebug() << "Warning: length truncated to fit 4 byte integer";
  shape_lengths_.single = len4;
 }
}

DHAX_Annotation_Instance::Colinear
  DHAX_Annotation_Instance::check_colinear(n8 loc1, n8 loc2)
{
 //DHAX_Location_2d* loc = (DHAX_Location_2d*) nn;
 QPointF p1 = ((DHAX_Location_2d*) loc1)->to_qpoint();
 QPointF p2 = ((DHAX_Location_2d*) loc2)->to_qpoint();
 if(p1.x() == p2.x())
   return Colinear::Horizontal;
 if(p1.y() == p2.y())
   return Colinear::Vertical;
 return  Colinear::Linear_At_Angle;
}


DHAX_Annotation_Instance::Colinear
  DHAX_Annotation_Instance::check_colinear_vh(n8 loc1,
  n8 loc2, n8 loc3)
{
 Colinear co1 = check_colinear(loc1, loc2);
 Colinear co2 = check_colinear(loc2, loc3);

 if(co1 == Colinear::Horizontal)
 {
  if(co2 == Colinear::Horizontal)
    return Colinear::Multiple_Horizontal;
  if(co2 == Colinear::Vertical)
    return Colinear::Horizontal_Then_Vertical;
  return Colinear::N_A;
 }

 if(co2 == Colinear::Vertical)
 {
  if(co2 == Colinear::Horizontal)
    return Colinear::Horizontal_Then_Vertical;
  if(co2 == Colinear::Vertical)
    return Colinear::Multiple_Vertical;
  return Colinear::N_A;
 }

 return Colinear::TBD;

// //DHAX_Location_2d* loc = (DHAX_Location_2d*) nn;
// QPointF p1 = ((DHAX_Location_2d*) loc1)->to_qpoint();
// QPointF p2 = ((DHAX_Location_2d*) loc2)->to_qpoint();
// if(p1.x() == p2.x())
//   return Colinear::Horizontal;
// if(p1.y() == p2.y())
//   return Colinear::Vertical;
// return  Colinear::Linear_At_Angle;
}



void DHAX_Annotation_Instance::locations_to_qpoints(QVector<QPoint>& result)
{
 for(n8 nn : locations_)
 {
  DHAX_Location_2d* loc = (DHAX_Location_2d*) nn;
  QPoint qp = loc->to_qpoint();
  result.push_back(qp);
 }
}

template <typename T>
void _to_tlbr_points(QVector<T>& vec)
{
 vec.resize(2);
 T p1 = vec[0];
 T p2 = vec[1];
 vec[0] = T(qMin(p1.x(), p2.x()), qMin(p1.y(), p2.y()));
 vec[1] = T(qMax(p1.x(), p2.x()), qMax(p1.y(), p2.y()));
}


void DHAX_Annotation_Instance::to_tlbr_points(QVector<QPoint>& vec)
{
 _to_tlbr_points(vec);
// vec.resize(2);
// QPoint p1 = vec[0];
// QPoint p2 = vec[1];
// vec[0] = QPoint(qMin(p1.x(), p2.x()), qMin(p1.y(), p2.y()));
// vec[1] = QPoint(qMax(p1.x(), p2.x()), qMax(p1.y(), p2.y()));
}

void DHAX_Annotation_Instance::to_tlbr_points(QVector<QPointF>& vec)
{
 _to_tlbr_points(vec);
}

void DHAX_Annotation_Instance::locations_to_qpoints(QVector<QPointF>& result)
{
 for(n8 nn : locations_)
 {
  DHAX_Location_2d* loc = (DHAX_Location_2d*) nn;
  QPointF qp = loc->to_qpointf();
  result.push_back(qp);
 }
}

void DHAX_Annotation_Instance::default_dimensions()
{
 static u2 code = 0;
 if(code)
   composite_dimension_code_ = code;
 else
 {
  // //  init for this object and keep the result for others
  set_dimension_units(Dimension_Units::Px);
  set_dimension_scale(Dimension_Scale::Integer);
  set_byte_lengths(Byte_Lengths::Four);
  reuse_dimensions_for_shape_lengths();
  code = composite_dimension_code_;
 }
}

void DHAX_Annotation_Instance::qpoint_dimensions()
{
 static u2 code = 0;
 if(code)
   composite_dimension_code_ = code;
 else
 {
  // //  init for this object and keep the result for others
  set_dimension_units(Dimension_Units::QPoint_or_QPointF);
  set_dimension_scale(Dimension_Scale::Integer);
  set_byte_lengths(Byte_Lengths::Four);
  reuse_dimensions_for_shape_lengths();
  code = composite_dimension_code_;
 }
}

void DHAX_Annotation_Instance::qpointf_dimensions()
{
 static u2 code = 0;
 if(code)
   composite_dimension_code_ = code;
 else
 {
  // //  init for this object and keep the result for others
  set_dimension_units(Dimension_Units::QPoint_or_QPointF);
  set_dimension_scale(Dimension_Scale::Float);
  set_byte_lengths(Byte_Lengths::Four);
  reuse_dimensions_for_shape_lengths();
  code = composite_dimension_code_;
 }
}


void DHAX_Annotation_Instance::reuse_dimensions_for_shape_lengths()
{
 u2 composite = composite_dimension_code_ & 127; // ignore signed flag
 composite_dimension_code_ &= 0b1000'0000'1111'1111;
 composite_dimension_code_ |= (composite << 9);
}

bool DHAX_Annotation_Instance::single_shape_length()
{
 return composite_dimension_code_ & 0x8000; // high bit of second byte ...
}

void DHAX_Annotation_Instance::note_single_shape_length()
{
 composite_dimension_code_ |= 0x8000; // high bit of second byte ...
}


bool DHAX_Annotation_Instance::is_signed()
{
 return composite_dimension_code_ & 128; // high bit of first byte...
}

void DHAX_Annotation_Instance::note_signed()
{
 composite_dimension_code_ |= 128;
}

void DHAX_Annotation_Instance::set_byte_lengths
  (Byte_Lengths byte_lengths)
{
 composite_dimension_code_ &= 0b1111'1111'1111'0011;
 composite_dimension_code_ |= ((u1) byte_lengths << 3);
}

DHAX_Annotation_Instance::Byte_Lengths
  DHAX_Annotation_Instance::get_byte_lengths() const
{
 return (Byte_Lengths) ((composite_dimension_code_ >> 3) & 3);
}

void DHAX_Annotation_Instance::set_shape_lengths_byte_lengths
  (Byte_Lengths byte_lengths)
{
 composite_dimension_code_ &= 0b1111'0011'1111'1111;
 composite_dimension_code_ |= ((u2) byte_lengths << 11);
}

DHAX_Annotation_Instance::Byte_Lengths
  DHAX_Annotation_Instance::get_shape_lengths_byte_lengths() const
{
 return (Byte_Lengths) ((composite_dimension_code_ >> 11) & 3);
}


void DHAX_Annotation_Instance::set_dimension_units
  (Dimension_Units dimension_units)
{
 composite_dimension_code_ &= 0b1111'1111'1000'1111;
 composite_dimension_code_ |= ((u1) dimension_units << 5);
}

DHAX_Annotation_Instance::Dimension_Units
  DHAX_Annotation_Instance::get_dimension_units()  const
{
 return (Dimension_Units) ((composite_dimension_code_ >> 5) & 7);
}

void DHAX_Annotation_Instance::set_shape_lengths_dimension_units
  (Dimension_Units dimension_units)
{
 composite_dimension_code_ &= 0b1000'1111'1111'1111;
 composite_dimension_code_ |= ((u2) dimension_units << 13);
}

DHAX_Annotation_Instance::Dimension_Units
  DHAX_Annotation_Instance::get_shape_lengths_dimension_units()  const
{
 return (Dimension_Units) ((composite_dimension_code_ >> 13) & 7);
}


void DHAX_Annotation_Instance::set_dimension_scale
  (Dimension_Scale dimension_scale)
{
 composite_dimension_code_ &= 0b1111'1100;
 composite_dimension_code_ |= (u1) dimension_scale;
}

DHAX_Annotation_Instance::Dimension_Scale
  DHAX_Annotation_Instance::get_dimension_scale()  const
{
 return (Dimension_Scale) (composite_dimension_code_ & 3);
}


void DHAX_Annotation_Instance::set_shape_lengths_dimension_scale
  (Dimension_Scale dimension_scale)
{
 composite_dimension_code_ &= 0b1111'1100'1111'1111;
 composite_dimension_code_ |= ((u2) dimension_scale << 9);
}

DHAX_Annotation_Instance::Dimension_Scale
  DHAX_Annotation_Instance::get_shape_lengths_dimension_scale()  const
{
 return (Dimension_Scale) ((composite_dimension_code_ >> 9) & 3);
}
//ACCESSORS__DECLARE(Byte_Lengths ,byte_lengths)
//ACCESSORS__DECLARE(Dimension_Units ,dimension_units)
//ACCESSORS__DECLARE(Dimension_Scale ,dimension_scale)


//void DHAX_Annotation_Instance::absorb_shape_point(const QPoint& qp)
//{
// DHAX_Location_2d* loc = new DHAX_Location_2d(qp.x(), qp.y());
// locations_.push_back( (n8) loc );
//}

void DHAX_Annotation_Instance::add_shape_point(u4 c1, u4 c2)
{
 DHAX_Location_2d* loc = new DHAX_Location_2d(c1, c2);
 locations_.push_back( (n8) loc );
}

void DHAX_Annotation_Instance::add_shape_point(s4 c1, s4 c2)
{
 // // note: this is not intended for signed arguments
  //   (unlike "add_signed_shape_point")
  //   but rather for unsigned literals that are
  //   interpreted as signed integers.
  //   In this scenario we know they are within proper bounds ...
 add_shape_point((u4) c1, (u4) c2);
}


void DHAX_Annotation_Instance::add_shape_length(n8 len)
{
 if(single_shape_length())
 {
  qDebug() << "Warning: adding shape length to single length may overwrite old value";
  set_shape_length(len);
  return;
 }

 if(get_shape_lengths_dimension_scale() == Dimension_Scale::Float)
 {
  if(get_byte_lengths() == Byte_Lengths::Eight)
    shape_lengths_.dbl8->push_back(len);
  else
    shape_lengths_.fl4->push_back(len);
 }
 else if(get_shape_lengths_byte_lengths() == Byte_Lengths::Eight)
   shape_lengths_.int8->push_back(len);
 else
 {
  u4 len4 = len;
  if(len4 != len)
    qDebug() << "Warning: length truncated to fit 4 byte integer";
  shape_lengths_.int4->push_back(len4);
 }
}

void DHAX_Annotation_Instance::add_shape_length(double len)
{
 if(single_shape_length())
 {
  qDebug() << "Warning: adding shape length to single length may overwrite old value";
  set_shape_length(len);
  return;
 }

 if(get_shape_lengths_dimension_scale() == Dimension_Scale::Float)
 {
  if(get_byte_lengths() == Byte_Lengths::Eight)
    shape_lengths_.dbl8->push_back(len);
  else
    shape_lengths_.fl4->push_back(len);
 }
 else
 {
  qDebug() << "Warning: converting double to integer for shape length";
  if(get_shape_lengths_byte_lengths() == Byte_Lengths::Eight)
    shape_lengths_.int8->push_back(len);
  else
    shape_lengths_.int4->push_back(len);
 }
}

void DHAX_Annotation_Instance::add_shape_length(float len)
{
 if(single_shape_length())
 {
  qDebug() << "Warning: adding shape length to single length may overwrite old value";
  set_shape_length(len);
  return;
 }

 if(get_shape_lengths_dimension_scale() == Dimension_Scale::Float)
 {
  if(get_shape_lengths_byte_lengths() == Byte_Lengths::Eight)
    shape_lengths_.dbl8->push_back(len);
  else
    shape_lengths_.fl4->push_back(len);
 }
 else
 {
  qDebug() << "Warning: converting float to integer for shape length";
  if(get_shape_lengths_byte_lengths() == Byte_Lengths::Eight)
    shape_lengths_.int8->push_back(len);
  else
    shape_lengths_.int4->push_back(len);
 }
}



void DHAX_Annotation_Instance::add_signed_shape_point(s4 c1, s4 c2)
{
 n8 location;
 if(is_signed())
 {
  DHAX_Signed_Location_2d* loc = new DHAX_Signed_Location_2d(c1, c2);
  location = (n8) loc;
 }
 else if(get_dimension_scale() == Dimension_Scale::Float)
 {
  if(get_byte_lengths() == Byte_Lengths::Four)
  {
   DHAX_Float_Location_2d* loc = new DHAX_Float_Location_2d(c1, c2);
   location = (n8) loc;
  }
  else
  {
   DHAX_Double_Location_2d* loc = new DHAX_Double_Location_2d(c1, c2);
   location = (n8) loc;
  }
 }
 else // //  todo: currently ignoring ratios ...
 {
  if( (c1 < 0) || (c2 < 0) )
    qDebug() << "Warning: signed integers passed to anntoation expecting unsigned ...";
  DHAX_Location_2d* loc = new DHAX_Location_2d((u4)c1, (u4)c2);
  location = (n8) loc;
 }
 locations_.push_back(location);
}

void DHAX_Annotation_Instance::add_shape_point(double c1, double c2)
{
 n8 location;
 if(get_byte_lengths() == Byte_Lengths::Four)
 {
  if(get_dimension_scale() == Dimension_Scale::Float)
  {
   qDebug() << "Warning: double-precision values passed to anntoation expecting single-precision floats ...";
   DHAX_Float_Location_2d* loc = new DHAX_Float_Location_2d( (float) c1, (float) c2);
   location = (n8) loc;
  }
  else if(is_signed())
  {
   qDebug() << "Warning: double-precision values truncated to 4-byte signed integer for anntoation ...";
   DHAX_Signed_Location_2d* loc = new DHAX_Signed_Location_2d( (s4) c1, (s4) c2);
   location = (n8) loc;
  }
  else
  {
   qDebug() << "Warning: double-precision values truncated to 4-byte unsigned integer for anntoation ...";
   DHAX_Location_2d* loc = new DHAX_Location_2d( (u4) c1, (u4) c2);
   location = (n8) loc;
  }
 }
 else // //  todo: ignoring shorts and ratios for now ...
 {
  if(get_dimension_scale() == Dimension_Scale::Float)
  {
   DHAX_Double_Location_2d* loc = new DHAX_Double_Location_2d(c1, c2);
   location = (n8) loc;
  }
  else
  {
   qDebug() << "Use of double incompatible with annotation format.";
  }
 }
}


void DHAX_Annotation_Instance::add_shape_point(float c1, float c2)
{
 n8 location;

 if(get_dimension_scale() == Dimension_Scale::Float)
 {
  if(get_byte_lengths() == Byte_Lengths::Four)
  {
   DHAX_Float_Location_2d* loc = new DHAX_Float_Location_2d(c1, c2);
   location = (n8) loc;
  }
  else if(get_byte_lengths() == Byte_Lengths::Eight)
  {
   DHAX_Double_Location_2d* loc = new DHAX_Double_Location_2d(c1, c2);
   location = (n8) loc;
  }
  else // //  todo maybe convert for a ratio or half-precision?
  {
   qDebug() << "Use of double incompatible with annotation format.";
  }
 }
 else if(get_byte_lengths() == Byte_Lengths::Four)
 {
  if(is_signed())
  {
   qDebug() << "Warning: floating-point values converted to 4-byte signed integer for anntoation ...";
   DHAX_Signed_Location_2d* loc = new DHAX_Signed_Location_2d( (s4) c1, (s4) c2);
   location = (n8) loc;
  }
  else
  {
   qDebug() << "Warning: floating-point values converted to 4-byte unsigned integer for anntoation ...";
   DHAX_Location_2d* loc = new DHAX_Location_2d( (u4) c1, (u4) c2);
   location = (n8) loc;
  }
 }
 else // //  todo: ignoring shorts and ratios for now ...
 {
  qDebug() << "Use of float incompatible with annotation format.";
 }
}


DHAX_Annotation_Instance::Compact_Shape_Kind_Summary
  DHAX_Annotation_Instance::check_compact_representation(u1 csc, u1* num_sides)
{
 if(csc & 1)
 {
  if(csc & 2)
    // //  polyline ("open" flag is set)
    return Compact_Shape_Kind_Summary::Polyline;

  // //  most polygons
  u1 psc = get_raw_polygon_side_count(csc);
  switch(psc)
  {
  case 0: return Compact_Shape_Kind_Summary::Non_Regular_Polygon; // qDebug() << "PSC: Non-Regular"; break;
  case 1: return Compact_Shape_Kind_Summary::Rectangle; // qDebug() << "PSC: Rectangle"; break;
  case 2: return Compact_Shape_Kind_Summary::Arrow; // qDebug() << "PSC: Arrow"; break;
  //?case 31: return Compact_Shape_Kind_Summary::Diamond; // qDebug() << "PSC: Diamond"; break;
  default: if(num_sides) *num_sides = psc; return Compact_Shape_Kind_Summary::Regular_Polygon;//qDebug() << "PSC: Regular Polygon with " << psc << " sides"; break;
    // raw_polygon_sides >= 3:  regular polygon
  }
 }
 else
 {
  // //  most polygons
  Non_Linear_Shape_Kinds nsc = get_non_linear_shape_kind(csc);
  switch(nsc)
  {
  case Non_Linear_Shape_Kinds::Curve: return Compact_Shape_Kind_Summary::Curve; //qDebug() << "NSC: Curve"; break;
  case Non_Linear_Shape_Kinds::Ellipse: return Compact_Shape_Kind_Summary::Ellipse; //qDebug() << "NSC: Ellipse"; break;
  case Non_Linear_Shape_Kinds::QPath: return Compact_Shape_Kind_Summary::QPath; // qDebug() << "NSC: QPath"; break;
  case Non_Linear_Shape_Kinds::Other: return Compact_Shape_Kind_Summary::Other_Non_Linear; // qDebug() << "NSC: Other"; break;
  }
 }
}


#define LINE_DIVIDER_STR "|"
#define LINE_SUBDIVIDER_STR "^"

void DHAX_Annotation_Instance::from_compact_string(QString cs)
{
 QStringList parts = cs.split(LINE_DIVIDER_STR);

 if(parts.isEmpty())
   return;

 QString ids = parts.takeFirst();
 scoped_identifiers_ = ids.split(LINE_SUBDIVIDER_STR);

 if(parts.isEmpty())
   return;

 shape_designation_ = parts.takeFirst();

 if(parts.isEmpty())
   return;

// opaque_shape_kind_code_ = parts.takeFirst().toLongLong();

// if(parts.isEmpty())
//   return;

 composite_dimension_code_ = parts.takeFirst().toUInt();
 if(parts.isEmpty())
   return;

 composite_shape_code_ = parts.takeFirst().toUInt();
 if(parts.isEmpty())
   return;

 internal_codes_ = parts.takeFirst().toUInt();
 if(parts.isEmpty())
   return;

 //check_compact_representation();

 QString locs = parts.takeFirst();

 // // prelim or locations?
 if(!locs.isEmpty())
 {
//?  check_init_prelim_shape_points();
  QStringList prelim_points = locs.split(';');
  for(QString prelim_point : prelim_points)
  {
   QStringList ps = prelim_point.split(',');
   add_shape_point(ps.value(0).toInt(), ps.value(1).toInt());
   //prelim_shape_points_->push_back(QPoint(ps.value(0).toInt(), ps.value(1).toInt()));
  }
 }

// QString locs = parts.takeFirst();
// AXFI_Location_2d::read_string(locs, locations_);
}

QString DHAX_Annotation_Instance::to_compact_string()
{
 QString result = scoped_identifiers_.join(LINE_SUBDIVIDER_STR);
 result += QString("|%1|%2|%3|%4|").arg(shape_designation_)
   .arg(composite_dimension_code_)
   .arg(composite_shape_code_).arg(internal_codes_);

  for(n8 nn : locations_)
  {
   DHAX_Location_2d* loc = (DHAX_Location_2d*) nn;
   result += loc->to_string() + ";";
  }
  result.chop(1);


// if(prelim_shape_points_ && !prelim_shape_points_->isEmpty())
// {
//  for(QPoint qp : *prelim_shape_points_)
//  {
//   result += QString("%1,%2:").arg(qp.x()).arg(qp.y());
//  }
//  result.chop(1);
// }

// for(n8 nn : locations_)
// {
//  AXFI_Location_2d* loc = (AXFI_Location_2d*) nn;
//  result += loc->to_string() + ":";
// }
 return result;

}
