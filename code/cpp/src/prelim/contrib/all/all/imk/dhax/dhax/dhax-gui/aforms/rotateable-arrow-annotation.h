
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ROTATEABLE_ARROW_ANNOTATION__H
#define ROTATEABLE_ARROW_ANNOTATION__H


#include <QRubberBand>

#include "global-types.h"

#include "accessors.h"

#include "multistep-annotation-base.h"


class Rotateable_Arrow_Annotation //
  : public MultiStep_Annotation_Base
{
 Q_OBJECT

 struct NTXH_Data {
  QColor color;
  r8 xscale;
  r8 yscale;
  r8 xtranslate;
  r8 ytranslate;
  s1 corner_pair_direction;
  QPointF shaft_corner;
  r8 shaft_width;
  r8 shaft_length;
  r8 tip_width;
  r8 tip_length;
  r8 tip_point_width;
  r8 tip_corner_bend;
  r8 rotation;
  QPoint rotation_center;
  r8 shaft_offset;
  r8 shaft_offset_delta;
 };

 //?  r8 shaft_base_extension;

 QRectF shaft_;
 QRectF tip_;

 r8 tip_point_width_;
 r8 tip_point_width_delta_;

 r8 tip_corner_bend_;
 r8 tip_corner_bend_delta_;

 r8 rotation_;

 QLineF rotation_landmark_;
 QPointF rotation_center_;
 QPoint mapped_rotation_center_;

 r8 shaft_offset_;
 r8 shaft_offset_delta_;

 QPolygonF rendered_polygon_;

 QColor fill_color_;
 r8 xscale_, yscale_, xtranslate_, ytranslate_;

 void generate_ntxh_data(NTXH_Data& result);
 void read_from_ntxh_data(const NTXH_Data& nd);
 void read_ntxh_data(QMap<QString, QStringList>& kv_map, NTXH_Data& result);


protected:

 void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;


public:

 Rotateable_Arrow_Annotation(DHAX_Mouse_Interaction_Data& mouse_interaction_data, const QPointF& sc, QWidget* p = nullptr);

 Rotateable_Arrow_Annotation(const QByteArray& data);

 Rotateable_Arrow_Annotation(QString kv_text);

 void as_polygon(QPolygonF& result, NTXH_Data* nd = nullptr);

 ACCESSORS__RGET(QRectF ,shaft)
 ACCESSORS__RGET(QRectF ,tip)
 //ACCESSORS__RGET(QRectF ,tip_point_width)
 ACCESSORS(r8 ,rotation)

 ACCESSORS__CONST_RGET(QPolygonF ,rendered_polygon)
 ACCESSORS(QColor ,fill_color)

 r8 get_xscale()
 {
  if(xscale_ == 0)
    return 1;
  return xscale_;
 }

 r8 get_yscale()
 {
  if(yscale_ == 0)
    return 1;
  return yscale_;
 }

 void adjust_geometry(const QPointF& pos) Q_DECL_OVERRIDE;

 void reset_geometry(const QPointF& sc = {}) Q_DECL_OVERRIDE;

 QString kind_name() Q_DECL_OVERRIDE {return "Arrow"; }
 void generate_ntxh(QString& result) Q_DECL_OVERRIDE;

 void init_tip_phase(const QPointF& pos);
 void finish_tip_phase(const QPointF& pos);
 void finish_rotation_phase(const QPointF& pos);

 virtual void init_second_phase(const QPointF &pos) Q_DECL_OVERRIDE
 {
  init_tip_phase(pos);
 }

 virtual void finish_second_phase(const QPointF &pos) Q_DECL_OVERRIDE
 {
  finish_tip_phase(pos);
 }

 virtual void finish_third_phase(const QPointF &pos) Q_DECL_OVERRIDE
 {
  finish_rotation_phase(pos);
 }

protected:

 void process_paint_event(QPaintEvent* event, QPainter& painter) Q_DECL_OVERRIDE;
 void set_gradient_center(QConicalGradient& gradient) Q_DECL_OVERRIDE;


Q_SIGNALS:

protected:

// void paintEvent(QPaintEvent *event) ;


public Q_SLOTS:

};

#endif // ROTATEABLE_ARROW_ANNOTATION__H
