
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "rotateable-arrow-annotation.h"

#include <QPainter>

#include <QTextStream>
#include <QRectF>

#include <QDebug>

#include <QWheelEvent>

#include "global-types.h"

#include "image-viewer/dhax-mouse-interaction-data.h"

static DHAX_Mouse_Interaction_Data _no_data {};


Rotateable_Arrow_Annotation::Rotateable_Arrow_Annotation(const QByteArray& data)
  :  MultiStep_Annotation_Base(_no_data, nullptr),
     xscale_(0), yscale_(0), xtranslate_(0), ytranslate_(0)
{
 QDataStream qds(data);
 qds >> rendered_polygon_ >> shaft_ >> tip_ >> tip_point_width_ >> tip_point_width_delta_
   >> tip_corner_bend_delta_ >> rotation_ >> rotation_landmark_
   >> rotation_center_ >> mapped_rotation_center_
   >> shaft_offset_ >> shaft_offset_delta_
   >> fill_color_ >> xscale_ >> yscale_ >> xtranslate_ >> ytranslate_;

}


Rotateable_Arrow_Annotation::Rotateable_Arrow_Annotation(QString kv_text)
 :  MultiStep_Annotation_Base(_no_data, nullptr),
    xscale_(0), yscale_(0), xtranslate_(0), ytranslate_(0)
{
// kv_text = kv_text.simplified();
// kv_text.replace(": ", ":");
 QStringList lines = kv_text.split('\n', Qt::SkipEmptyParts);
 QMap<QString, QStringList> split_tokens;
 for(QString line : lines)
 {
  line = line.simplified();
  line.replace(": ", " ");
  QStringList tokens = line.split(' ');
  if(tokens.isEmpty())
     continue;
  split_tokens[tokens.takeFirst()] = tokens;
 }

 NTXH_Data nd;
 read_ntxh_data(split_tokens, nd);
 read_from_ntxh_data(nd);
 as_polygon(rendered_polygon_, &nd);

}


Rotateable_Arrow_Annotation::Rotateable_Arrow_Annotation(DHAX_Mouse_Interaction_Data& mouse_interaction_data,
    const QPointF& sc, QWidget* p) :
    MultiStep_Annotation_Base(mouse_interaction_data, p), tip_point_width_(0), tip_point_width_delta_(1),
    tip_corner_bend_(0), tip_corner_bend_delta_(1), rotation_(0), shaft_offset_(0), shaft_offset_delta_(1),
    xscale_(1), yscale_(1), xtranslate_(0), ytranslate_(0)
{
 shaft_.setTopLeft(sc);
 shaft_.setBottomRight(sc);
 if(p)
   setGeometry(p->geometry());
}

void Rotateable_Arrow_Annotation::generate_ntxh(QString& result)
{
// QPolygonF qpf;
// as_polygon(qpf);


 static QStringList fields {"shaft",
   "tip", "tip_point_width", "tip_point_width_delta",
   "tip_corner_bend", "tip_corner_bend_delta",
   "rotation", "rotation_landmark", "rotation_center",
   "mapped_rotation_center", "shaft_offset",
   "shaft_offset_delta"
 };

 QString text;
 QTextStream qts(&text);

//#define _SP_ << ' ' <<
 NTXH_Data nd;
 generate_ntxh_data(nd);

#define fld(x) \
  << #x ": " << nd.x << "\n"

#define fld2(x, y, z) \
  << #x ": " << nd.x.y() << " " << nd.x.z() << "\n" \

#define fld3(x, y, z, n) \
  << #n ": " << nd.y##x << " " \
  << nd.z##x << "\n"


 QString color;
 if(fill_color_.isValid())
   color = "color: %1 %2 %3 %4\n"_qt.arg(fill_color_.red())
   .arg(fill_color_.green()).arg(fill_color_.blue())
   .arg(fill_color_.alpha());
 else
   color = "color: 124.5 124.5 124.5\n";


// qts << shaft_.top() _SP_ shaft_.right() _SP_ shaft_.bottom() _SP_
//   shaft_.left() _SP_ tip_.top() _SP_ tip_.right() _SP_ tip_.bottom() _SP_
//   tip_.left() _SP_ tip_point_width_ _SP_ tip_point_width_delta_ _SP_
//   tip_corner_bend_delta_ _SP_ rotation_ _SP_ mapped_rotation_center_.x() _SP_
//   mapped_rotation_center_.y() _SP_ shaft_offset_ _SP_ shaft_offset_delta_;

 qts << color;

 if( (get_xscale() == 1) && (get_yscale() == 1) )
    qts << "scale: \n";
 else
   qts fld3(scale ,x ,y ,scale);

 qts
   fld3(translate ,x ,y ,tr)
   fld2(shaft_corner ,x ,y)
   fld(shaft_width)
   fld(shaft_length)
   fld(tip_width)
   fld(tip_length)
   fld(tip_point_width)
   fld(tip_corner_bend)
   fld(rotation)
   fld2(rotation_center ,x ,y)
   fld(shaft_offset)
   fld(shaft_offset_delta)
   fld(corner_pair_direction)
   ;

#undef fld
#undef fld2

 text.chop(1); // //  the last newline

 QByteArray qba;
 QDataStream qds(&qba, QIODevice::WriteOnly);
 qds << shaft_ << tip_ << tip_point_width_ << tip_point_width_delta_
   << tip_corner_bend_delta_ << rotation_ << rotation_landmark_
   << rotation_center_ << mapped_rotation_center_
   << shaft_offset_ << shaft_offset_delta_
   << fill_color_ << xscale_ << yscale_ << xtranslate_ << ytranslate_;

 QByteArray qba64 = qba.toBase64();

 static QString result_template =
R"(
!/ Shape_Annotation
$k: Rotateable_Arrow_Annotation
$s#
$t.
%1
.
$d.
%2
.
/!
<+>
 )";

 result = result_template.arg(text).arg(QString::fromLatin1(qba64));
}

void Rotateable_Arrow_Annotation::adjust_geometry(const QPointF& pos)
{
 if(current_corner_pair_direction_ & Corner_Pair_Directions::First_Phase)
 {
  shaft_.setBottomRight(pos);
 }
 else if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
 {
  QLineF rline(rotation_center_, pos);
  rotation_ = rline.angleTo(rotation_landmark_);
 }
 else if(current_corner_pair_direction_ & Corner_Pair_Directions::Second_Phase)
 {
  Corner_Pair_Directions cpd = (Corner_Pair_Directions) (current_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);
  switch (cpd)
  {
  case Corner_Pair_Directions::Down_Right:
   {
    tip_.setBottomRight(pos);
    tip_.setTopLeft(shaft_.topRight() - QPointF(0, tip_.bottom() - shaft_.bottom()));
   }
   break;
  case Corner_Pair_Directions::Up_Right:
   {
    tip_.setTopRight(pos);
    tip_.setBottomLeft(shaft_.bottomRight() - QPointF(0, tip_.top() - shaft_.top()));
   }
   break;
  case Corner_Pair_Directions::Down_Left:
   {
    tip_.setBottomLeft(pos);
    tip_.setTopRight(shaft_.topLeft() - QPointF(0, tip_.bottom() - shaft_.bottom()));
   }
   break;
  case Corner_Pair_Directions::Up_Left:
   {
    tip_.setTopLeft(pos);
    tip_.setBottomRight(shaft_.bottomLeft() - QPointF(0, tip_.top() - shaft_.top()));
   }
   break;
  case Corner_Pair_Directions::Down_Right_Down:
   {
    tip_.setBottomRight(pos);
    tip_.setTopLeft(shaft_.bottomLeft() - QPointF(tip_.right() - shaft_.right(), 0));
   }
   break;
  case Corner_Pair_Directions::Down_Left_Down:
   {
    tip_.setBottomLeft(pos);
    tip_.setTopRight(shaft_.bottomRight() - QPointF(tip_.left() - shaft_.left(), 0));
   }
   break;

  case Corner_Pair_Directions::Up_Right_Up:
   {
    tip_.setTopRight(pos);
    tip_.setBottomLeft(shaft_.topLeft() - QPointF(tip_.right() - shaft_.right(), 0));
   }
   break;
  case Corner_Pair_Directions::Up_Left_Up:
   {
    tip_.setTopLeft(pos);
    tip_.setBottomRight(shaft_.topRight() - QPointF(tip_.left() - shaft_.left(), 0));
   }
   break;


  default:
   return;
  }
 }
// else if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
// {

// }
}

void Rotateable_Arrow_Annotation::reset_geometry(const QPointF& sc)
{
}

void Rotateable_Arrow_Annotation::init_tip_phase(const QPointF& pos)
{
 Corner_Pair_Directions cpd = get_corner_pair_direction(shaft_);

 if(cpd == Corner_Pair_Directions::N_A)
   return;

 shaft_ = shaft_.normalized();

 if(shaft_.width() < shaft_.height())
 {
  // // switch to up or down facing arrow ...
  cpd ^= 1;
 }

 switch (cpd)
 {
 case Corner_Pair_Directions::Down_Right:
  tip_.setTopLeft(shaft_.topRight());
  tip_.setBottomRight(shaft_.bottomRight());
  break;
 case Corner_Pair_Directions::Up_Right:
  tip_.setBottomLeft(shaft_.bottomRight());
  tip_.setTopRight(shaft_.topRight());
  break;
 case Corner_Pair_Directions::Down_Left:
  tip_.setTopRight(shaft_.topLeft());
  tip_.setBottomLeft(shaft_.bottomLeft());
  break;
 case Corner_Pair_Directions::Up_Left:
  tip_.setBottomRight(shaft_.bottomLeft());
  tip_.setTopLeft(shaft_.topLeft());
  break;

 case Corner_Pair_Directions::Down_Right_Down:
  tip_.setTopLeft(shaft_.bottomLeft());
  tip_.setBottomRight(shaft_.bottomRight());
  break;
 case Corner_Pair_Directions::Down_Left_Down:
  tip_.setTopRight(shaft_.bottomRight());
  tip_.setBottomLeft(shaft_.bottomLeft());
  break;

 case Corner_Pair_Directions::Up_Right_Up:
  tip_.setBottomLeft(shaft_.topLeft());
  tip_.setTopRight(shaft_.topRight());
  break;
 case Corner_Pair_Directions::Up_Left_Up:
  tip_.setBottomRight(shaft_.topRight());
  tip_.setTopLeft(shaft_.topLeft());
  break;

 default:
  return;
 }

 current_corner_pair_direction_ = cpd | Corner_Pair_Directions::Second_Phase;
}

void Rotateable_Arrow_Annotation::finish_rotation_phase(const QPointF& pos)
{
 current_corner_pair_direction_ ^= Corner_Pair_Directions::Third_Phase;
 current_corner_pair_direction_ |= Corner_Pair_Directions::Fourth_Phase;

 repaint();
}

void Rotateable_Arrow_Annotation::finish_tip_phase(const QPointF& pos)
{
 Corner_Pair_Directions cpd = (Corner_Pair_Directions) (current_corner_pair_direction_ &
   Corner_Pair_Directions::Direction_Only);

 current_corner_pair_direction_ ^= Corner_Pair_Directions::Second_Phase;
 current_corner_pair_direction_ |= Corner_Pair_Directions::Third_Phase;

 switch (cpd)
 {
 case Corner_Pair_Directions::Down_Right:
 case Corner_Pair_Directions::Up_Right:
  rotation_center_ =
    ((shaft_.topLeft() + shaft_.bottomLeft()) / 2)
    + QPointF(shaft_.height() / 2, 0);
  break;
 case Corner_Pair_Directions::Down_Left:
 case Corner_Pair_Directions::Up_Left:
  rotation_center_ = ((shaft_.topRight() + shaft_.bottomRight()) / 2)
    - QPointF(shaft_.height() / 2, 0);
  break;
 case Corner_Pair_Directions::Down_Right_Down:
 case Corner_Pair_Directions::Down_Left_Down:
  rotation_center_ = ((shaft_.topLeft() + shaft_.topRight()) / 2)
    + QPointF(0, shaft_.width() / 2);
  break;
 case Corner_Pair_Directions::Up_Right_Up:
 case Corner_Pair_Directions::Up_Left_Up:
  rotation_center_ = ((shaft_.bottomLeft() + shaft_.bottomRight()) / 2)
    - QPointF(0, shaft_.width() / 2);
  break;
 }

 rotation_landmark_.setP1(rotation_center_);
 rotation_landmark_.setP2(pos);
 mapped_rotation_center_ = mapFromParent(rotation_center_.toPoint());
}


void Rotateable_Arrow_Annotation::wheelEvent(QWheelEvent* event)
{
 Qt::KeyboardModifiers mods = event->modifiers();

 if(mods & (Qt::ShiftModifier | Qt::ControlModifier))
 {
  if(mods & Qt::ShiftModifier)
  {
   switch (_spaceship(event->angleDelta().y()))
   {
   case 1: if(tip_point_width_ > 0)
    {
     tip_point_width_ -= tip_point_width_delta_;
     repaint();
    }
    break;
   case -1: tip_point_width_ += tip_point_width_delta_; repaint(); break;
   default: return;
   }
  }
  else if(mods & Qt::ControlModifier)
  {
   switch (_spaceship(event->angleDelta().y()))
   {
   case 1: if(tip_corner_bend_ > 0)
    {
     tip_corner_bend_ -= tip_corner_bend_delta_;
     repaint();
    }
    break;
   case -1: tip_corner_bend_ += tip_corner_bend_delta_; repaint(); break;
   default: return;
   }
  }
 }
 else
 {
  switch (_spaceship(event->angleDelta().y()))
  {
  case 1: shaft_offset_ -= shaft_offset_delta_;
    repaint();
   break;
  case -1: shaft_offset_ += shaft_offset_delta_; repaint(); break;
  default: return;
  }
  event->accept();
 }
}


void Rotateable_Arrow_Annotation::set_gradient_center(QConicalGradient& gradient)
{
 gradient.setCenter(shaft_.center());
}

void Rotateable_Arrow_Annotation::read_ntxh_data(QMap<QString, QStringList>& kv_map, NTXH_Data& result)
{
 QStringList color_qsl = kv_map.value("color");

 if(color_qsl.size() == 3)
  result.color = QColor::fromRgbF(color_qsl.value(0).toFloat() / 255,
    color_qsl.value(1).toFloat() / 255, color_qsl.value(2).toFloat() / 255 );
 else
  result.color = QColor::fromRgbF(color_qsl.value(0).toFloat() / 255,
    color_qsl.value(1).toFloat() / 255, color_qsl.value(2).toFloat() / 255,
    color_qsl.value(3).toFloat() / 255);


 QStringList scale_qsl = kv_map.value("scale");
 if(scale_qsl.size() > 1)
 {
  result.xscale = scale_qsl[0].toDouble();
  result.yscale = scale_qsl[1].toDouble();
 }
 else
   result.xscale = result.yscale = scale_qsl.value(0, "1").toDouble();


 QStringList translate_qsl = kv_map.value("tr");
 if(translate_qsl.size() > 1)
 {
  result.xtranslate = translate_qsl[0].toDouble();
  result.ytranslate = translate_qsl[1].toDouble();
 }
 else
   result.xtranslate = result.ytranslate = translate_qsl.value(0).toDouble();


// result.shaft_corner = QPointF(kv_map.value("shaft_corner").value(0).toFloat(),
//   kv_map.value("shaft_corner_y").value(0).toFloat());

#define fld(ty, x) \
 result.x = kv_map.value(#x).value(0).to##ty();

#define fld2_QPointF(x) \
 result.x = QPointF(kv_map.value(#x).value(0).toFloat(), \
  kv_map.value(#x).value(1).toFloat());

#define fld2_QPoint(x) \
 result.x = QPoint(kv_map.value(#x).value(0).toInt(), \
  kv_map.value(#x).value(1).toInt());

 fld2_QPointF(shaft_corner)
 fld2_QPoint(rotation_center)

 fld(Int, corner_pair_direction)
 fld(Double, shaft_width)
 fld(Double, shaft_length)
 fld(Double, tip_width)
 fld(Double, tip_length)
 fld(Double, rotation)
 fld(Double, shaft_offset)
 fld(Double, shaft_offset_delta)
 fld(Double, tip_point_width)
 fld(Double, tip_corner_bend)

#undef fld
#undef fld_QPointF
#undef fld_QPoint

// result.rotation_center = QPoint(kv_map.value("rotation_center_x").value(0).toInt(),
//   kv_map.value("rotation_center_y").value(0).toInt());

//  result.corner_pair_direction = kv_map.value("corner_pair_direction").value(0).toInt();
}

void Rotateable_Arrow_Annotation::read_from_ntxh_data(const NTXH_Data& nd)
{
 fill_color_ = nd.color;
 xscale_ = nd.xscale;
 yscale_ = nd.yscale;
 xtranslate_ = nd.xtranslate;
 ytranslate_ = nd.ytranslate;

 tip_point_width_ = nd.tip_point_width;

 current_corner_pair_direction_ = (Corner_Pair_Directions) nd.corner_pair_direction;
 tip_corner_bend_ = nd.tip_corner_bend;
 rotation_ = nd.rotation;
 mapped_rotation_center_ = nd.rotation_center;
 shaft_offset_ = nd.shaft_offset;
 shaft_offset_delta_ = nd.shaft_offset_delta;

 shaft_.setTopLeft(nd.shaft_corner);
 shaft_.setHeight(nd.shaft_width);
 shaft_.setWidth(nd.shaft_length);

 tip_.setLeft(shaft_.right());
 tip_.setTop(shaft_.center().y() - (nd.tip_width / 2));
 tip_.setHeight(nd.tip_width);
 tip_.setWidth(nd.tip_length);


 //?
 tip_point_width_delta_ = 1;
 tip_corner_bend_delta_ = 1;

}


void Rotateable_Arrow_Annotation::generate_ntxh_data(NTXH_Data& result)
{
 QRect _shaft; map_from_parent(shaft_.normalized(), _shaft);
 QRect _tip; map_from_parent(tip_.normalized(), _tip);

 result.color = fill_color_;
 result.xscale = xscale_;
 result.yscale = yscale_;
 result.corner_pair_direction = (s1) current_corner_pair_direction_;
 result.shaft_corner = _shaft.topLeft();
 result.shaft_width = _shaft.height();
 result.shaft_length = _shaft.width();
 result.tip_width = _tip.height();
 result.tip_length = _tip.width();
 result.tip_corner_bend = tip_corner_bend_;
 result.rotation = rotation_;
 result.rotation_center = mapped_rotation_center_;
 result.shaft_offset = shaft_offset_;
 result.shaft_offset_delta = shaft_offset_delta_;
 result.xtranslate = xtranslate_;
 result.ytranslate = ytranslate_;
 result.color = fill_color_;
}

void Rotateable_Arrow_Annotation::as_polygon(QPolygonF& result, NTXH_Data* nd)
{
 QRect _shaft, _tip;

 r8 xscale = get_xscale();
 r8 yscale = get_yscale();

 if(nd)
 {
  _shaft = shaft_.toRect();
  _tip = tip_.toRect();
 }
 else
 {
  map_from_parent(shaft_.normalized(), _shaft);
  map_from_parent(tip_.normalized(), _tip);
 }

 s1 cpd = (current_corner_pair_direction_ & Corner_Pair_Directions::Direction_Only);

 if(tip_point_width_ > 0)
   cpd = -cpd;

 QPoint bend(tip_corner_bend_, 0);

 if( (cpd & 1) == 0 )
   // //  i.e. a down-right-down or similar
   bend = bend.transposed();

 QVector<QPoint> points;

 switch(cpd)
 {
 case -(s1) Corner_Pair_Directions::Down_Right:
 case -(s1) Corner_Pair_Directions::Up_Right:
  {
   QPoint mid = ((_tip.topRight() + _tip.bottomRight()) / 2);
   points = QVector<QPoint>{
     _shaft.topLeft() - QPoint(0, shaft_offset_), _tip.topLeft() - bend,
     mid - QPoint(0, tip_point_width_),
     mid + QPoint(0, tip_point_width_),
     _tip.bottomLeft() - bend, _shaft.bottomRight(), _shaft.bottomLeft() + QPoint(0, shaft_offset_)
     };
  }
  break;
 case (s1) Corner_Pair_Directions::Down_Right:
 case (s1) Corner_Pair_Directions::Up_Right:
  {
   points = QVector<QPoint>{
     _shaft.topLeft() - QPoint(0, shaft_offset_), _shaft.topRight(), _tip.topLeft() - bend,
     ((_tip.topRight() + _tip.bottomRight()) / 2),
      _tip.bottomLeft() - bend, _shaft.bottomRight(), _shaft.bottomLeft() + QPoint(0, shaft_offset_)
     };
  }
  break;
 case (s1) Corner_Pair_Directions::Down_Right_Down:
  {
   points = QVector<QPoint>{
     _shaft.topRight() + QPoint(shaft_offset_, 0), _shaft.bottomRight(), _tip.topRight() - bend,
     ((_tip.bottomRight() + _tip.bottomLeft()) / 2),
      _tip.topLeft() - bend, _shaft.bottomLeft(), _shaft.topLeft() - QPoint(shaft_offset_, 0)
     };
  }
  break;
 case -(s1) Corner_Pair_Directions::Down_Right_Down:
  {
   QPoint mid = ((_tip.bottomLeft() + _tip.bottomRight()) / 2);
   points = QVector<QPoint>{
     _shaft.topRight() + QPoint(shaft_offset_, 0), _shaft.bottomRight(), _tip.topRight() - bend,
     mid + QPoint(tip_point_width_, 0),
     mid - QPoint(tip_point_width_, 0),
     _tip.topLeft() - bend, _shaft.bottomLeft(), _shaft.topLeft() - QPoint(shaft_offset_, 0)
     };
  }
  break;
 case (s1) Corner_Pair_Directions::Up_Right_Up:
  {
   points = QVector<QPoint>{
     _shaft.bottomRight() + QPoint(shaft_offset_, 0), _shaft.topRight(), _tip.bottomRight() + bend,
     ((_tip.topRight() + _tip.topLeft()) / 2),
      _tip.bottomLeft() + bend, _shaft.topLeft(), _shaft.bottomLeft() - QPoint(shaft_offset_, 0)
     };
  }
  break;
 case -(s1) Corner_Pair_Directions::Up_Right_Up:
  {
   QPoint mid = ((_tip.topLeft() + _tip.topRight()) / 2);
   points = QVector<QPoint>{
     _shaft.bottomRight() + QPoint(shaft_offset_, 0), _shaft.topRight(), _tip.bottomRight() + bend,
     mid + QPoint(tip_point_width_, 0),
     mid - QPoint(tip_point_width_, 0),
     _tip.bottomLeft() + bend, _shaft.topLeft(), _shaft.bottomLeft() - QPoint(shaft_offset_, 0)
     };
  }
  break;
 case (s1) Corner_Pair_Directions::Down_Left_Down:
  {
   points = QVector<QPoint>{
     _shaft.topLeft() - QPoint(shaft_offset_, 0), _shaft.bottomLeft(), _tip.topLeft() - bend,
     ((_tip.bottomLeft() + _tip.bottomRight()) / 2),
      _tip.topRight() - bend, _shaft.bottomRight(), _shaft.topRight() + QPoint(shaft_offset_, 0)
     };
  }
  break;
 case -(s1) Corner_Pair_Directions::Down_Left_Down:
  {
   QPoint mid = ((_tip.bottomLeft() + _tip.bottomRight()) / 2);
   points = QVector<QPoint>{
     _shaft.topLeft() - QPoint(shaft_offset_, 0), _shaft.bottomLeft(), _tip.topLeft() - bend,
     mid - QPoint(tip_point_width_, 0),
     mid + QPoint(tip_point_width_, 0),
     _tip.topRight() - bend, _shaft.bottomRight(), _shaft.topRight() + QPoint(shaft_offset_, 0)
     };
  }
  break;
 case (s1) Corner_Pair_Directions::Up_Left_Up:
  {
   points = QVector<QPoint>{
     _shaft.bottomLeft() - QPoint(shaft_offset_, 0), _shaft.topLeft(), _tip.bottomLeft() + bend,
     ((_tip.topLeft() + _tip.topRight()) / 2),
      _tip.bottomRight() + bend, _shaft.topRight(), _shaft.bottomRight() + QPoint(shaft_offset_, 0)
     };
  }
  break;
 case -(s1) Corner_Pair_Directions::Up_Left_Up:
  {
   QPoint mid = ((_tip.topLeft() + _tip.topRight()) / 2);
   points = QVector<QPoint>{
     _shaft.bottomLeft() - QPoint(shaft_offset_, 0), _shaft.topLeft(), _tip.bottomLeft() + bend,
     mid - QPoint(tip_point_width_, 0),
     mid + QPoint(tip_point_width_, 0),
      _tip.bottomRight() + bend, _shaft.topRight(), _shaft.bottomRight() + QPoint(shaft_offset_, 0)
     };
  }
  break;
 case -(s1) Corner_Pair_Directions::Down_Left:
 case -(s1) Corner_Pair_Directions::Up_Left:
  {
   QPoint mid = ((_tip.topLeft() + _tip.bottomLeft()) / 2);

   points = QVector<QPoint>{
     _shaft.topRight() - QPoint(0, shaft_offset_), _shaft.topLeft(), _tip.topRight() + bend,
     mid - QPoint(0, tip_point_width_),
     mid + QPoint(0, tip_point_width_),
     _tip.bottomRight() + bend, _shaft.bottomLeft(), _shaft.bottomRight() + QPoint(0, shaft_offset_)
     };
  }
  break;
 case (s1) Corner_Pair_Directions::Down_Left:
 case (s1) Corner_Pair_Directions::Up_Left:
  {
   points = QVector<QPoint>{
     _shaft.topRight() - QPoint(0, shaft_offset_), _shaft.topLeft(), _tip.topRight() + bend,
     ((_tip.topLeft() + _tip.bottomLeft()) / 2),
     _tip.bottomRight() + bend, _shaft.bottomLeft(), _shaft.bottomRight() + QPoint(0, shaft_offset_)
     };
  }
  break;
 }
 QPolygonF poly(points);

 if(nd)
 {
  if( (xscale != 1) || (yscale != 1) )
  {
   poly = QTransform().translate(mapped_rotation_center_.x(), mapped_rotation_center_.y())
     .scale(xscale, yscale).translate(-mapped_rotation_center_.x(), -mapped_rotation_center_.y())
     .map(poly);
  }
 }

 if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_or_Fourth_Phase)
 {
  poly = QTransform().translate(mapped_rotation_center_.x(), mapped_rotation_center_.y())
    .rotate(rotation_).translate(-mapped_rotation_center_.x(), -mapped_rotation_center_.y())
    .map(poly);
 }

 if(nd)
 {
  if(xtranslate_  || ytranslate_)
  {
   poly = QTransform().translate(xtranslate_, ytranslate_)
     .map(poly);
  }
 }

 result = poly;
}


void Rotateable_Arrow_Annotation::process_paint_event(QPaintEvent* event, QPainter& painter)
{

 if(current_corner_pair_direction_ & Corner_Pair_Directions::First_Phase)
 {
  QRect _shaft; map_from_parent(shaft_, _shaft);
  painter.drawRect(_shaft);
 }

 else if(current_corner_pair_direction_ &
   Corner_Pair_Directions::Phase_234)
 {
  QPolygonF poly;
  as_polygon(poly);

  painter.drawPolygon(poly);

  if(current_corner_pair_direction_ & Corner_Pair_Directions::Third_Phase)
  {
   painter.setBrush(QColor("orange"));
   painter.drawEllipse(mapped_rotation_center_, 4, 4);
  }

 }
}
