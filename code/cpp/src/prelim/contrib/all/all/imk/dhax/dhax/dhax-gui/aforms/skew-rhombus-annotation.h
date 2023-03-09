
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef SKEW_RHOMBUS_ANNOTATION__H
#define SKEW_RHOMBUS_ANNOTATION__H


#include <QRubberBand>

#include "global-types.h"

#include "accessors.h"

#include "multistep-annotation-base.h"

class DHAX_Mouse_Interaction_Data;

class Skew_Rhombus_Annotation : public MultiStep_Annotation_Base //, public QRubberBand
{
 Q_OBJECT

 QRectF scaffold_;

 s2 x_offset_;
 s2 expansion_;
 r8 rotation_;

 s2 y_offset_;

public:

 Skew_Rhombus_Annotation(DHAX_Mouse_Interaction_Data& mouse_interaction_data,
   const QPointF& sc, QWidget* p = nullptr);

 ACCESSORS(s2 ,x_offset)
 ACCESSORS(s2 ,expansion)
 ACCESSORS(r8 ,rotation)
 ACCESSORS(s2 ,y_offset)

 QPair<r8, r8> get_offset_angle();

 QString kind_name() Q_DECL_OVERRIDE
 {
  return "Skew/Rhombus";
 }

 virtual void reset_geometry(const QPointF& sc = {}) Q_DECL_OVERRIDE;

 virtual void adjust_geometry(const QPointF& pos) Q_DECL_OVERRIDE;

 virtual void show() Q_DECL_OVERRIDE;

 void init_skew_phase(const QPointF& pos);
 void finish_skew_phase(const QPointF& pos);
 void finish_expansion_phase(const QPointF& pos);

 virtual void init_second_phase(const QPointF &pos) Q_DECL_OVERRIDE
 {
  init_skew_phase(pos);
 }

 virtual void finish_second_phase(const QPointF &pos) Q_DECL_OVERRIDE
 {
  finish_skew_phase(pos);
 }

 virtual void finish_third_phase(const QPointF &pos) Q_DECL_OVERRIDE
 {
  finish_expansion_phase(pos);
 }


 void process_paint_event(QPaintEvent* event, QPainter& painter) Q_DECL_OVERRIDE;
 void set_gradient_center(QConicalGradient& gradient) Q_DECL_OVERRIDE;


Q_SIGNALS:

protected:


public Q_SLOTS:

};

#endif //  SKEW_RHOMBUS_ANNOTATION__H
