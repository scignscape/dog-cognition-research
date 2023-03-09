

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef MEASUREMENT_ANNOTATION__H
#define MEASUREMENT_ANNOTATION__H


#include <QRubberBand>

#include "global-types.h"

#include "accessors.h"

#include "multistep-annotation-base.h"


class Measurement_Annotation //
  : public MultiStep_Annotation_Base
{
 Q_OBJECT


 QRectF inner_;
 QRectF outer_;

 u1 left_line_width_;
 u1 right_line_width_;

 u1 top_line_width_;
 u1 bottom_line_width_;

 s2 horizontal_extension_;
 s2 vertical_extension_;

 void _check_outer_adjust(u1 index, s2 amount);


protected:

 void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;


public:

 Measurement_Annotation(DHAX_Mouse_Interaction_Data& mouse_interaction_data, const QPointF& sc, QWidget* p = nullptr);

 ACCESSORS__RGET(QRectF ,inner)
 ACCESSORS__RGET(QRectF ,outer)

 ACCESSORS(s1 ,horizontal_extension)
 ACCESSORS(s1 ,vertical_extension)


 ACCESSORS(u1 ,left_line_width)
 ACCESSORS(u1 ,right_line_width)

 ACCESSORS(u1 ,top_line_width)
 ACCESSORS(u1 ,bottom_line_width)

 void adjust_geometry(const QPointF& pos) Q_DECL_OVERRIDE;

 void reset_geometry(const QPointF& sc = {}) Q_DECL_OVERRIDE;


 void init_outer_phase(const QPointF& pos);
 void finish_outer_phase(const QPointF& pos);
 void finish_extension_phase(const QPointF& pos);

 virtual void init_second_phase(const QPointF &pos) Q_DECL_OVERRIDE
 {
  init_outer_phase(pos);
 }

 virtual void finish_second_phase(const QPointF &pos) Q_DECL_OVERRIDE
 {
  finish_outer_phase(pos);
 }

 virtual void finish_third_phase(const QPointF &pos) Q_DECL_OVERRIDE
 {
  finish_extension_phase(pos);
 }

protected:

 void process_paint_event(QPaintEvent* event, QPainter& painter) Q_DECL_OVERRIDE;
 void set_gradient_center(QConicalGradient& gradient) Q_DECL_OVERRIDE;


Q_SIGNALS:

protected:

// void paintEvent(QPaintEvent *event) ;


public Q_SLOTS:

};

#endif // MEASUREMENT_ANNOTATION__H
