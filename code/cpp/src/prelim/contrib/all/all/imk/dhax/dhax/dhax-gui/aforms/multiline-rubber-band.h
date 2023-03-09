
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef MULTILINE_RUBBER_BAND__H
#define MULTILINE_RUBBER_BAND__H


#include <QRubberBand>

#include "global-types.h"

#include "accessors.h"

#include "multistep-annotation-base.h"

class DHAX_Mouse_Interaction_Data;

class MultiLine_Rubber_Band : public MultiStep_Annotation_Base //, public QRubberBand
{
 Q_OBJECT

//? QPointF starting_corner_;

 QPointF inner_starting_corner_;
 QPointF outer_starting_corner_;
//? QPointF double_top_corner_;


 QPointF inner_end_corner_;
 QPointF outer_end_corner_;

 QRect mid_rect_;

//? QPointF double_bottom_corner_;

// QPointF double_start_;
// QPointF double_end_;

// enum class Corner_Pair_Directions {
//  N_A, Up, Up_Right, Right, Down_Right,
//  Down, Down_Left, Left, Up_Left,
//  Direction_Only = 15,
//  Pre_Double = 16, Double = 32, Post_Double = 64,
//  Triple_Set = 128
// };

// ENUM_FLAGS_OP_MACROS(Corner_Pair_Directions)


 QPoint _map_start_outside_corner(QRect& rect);
 QPoint _map_start_cross_corner(QRect& rect);
 QPoint _map_start_double_corner(QRect& rect);
 QPoint _map_end_double_corner(QRect& rect);

 void init_active_corner_pair_direction(Corner_Pair_Directions cpd, const QPointF& pos);
 void reset_active_corner_pair_direction(Corner_Pair_Directions cpd, const QPointF& pos);

public:

 MultiLine_Rubber_Band (DHAX_Mouse_Interaction_Data& mouse_interaction_data, QRubberBand::Shape s, const QPointF& sc, QWidget* p = nullptr);

 ACCESSORS(QPointF ,inner_starting_corner)
 ACCESSORS(QPointF ,outer_starting_corner)
 //?ACCESSORS(QPointF ,double_top_corner)

 ACCESSORS(QPointF ,inner_end_corner)
 ACCESSORS(QPointF ,outer_end_corner)
//? ACCESSORS(QPointF ,double_bottom_corner)

// ACCESSORS(QPointF ,double_start)
// ACCESSORS(QPointF ,double_end)

//? void get_mid_rect_double(QRectF& result);

 void get_mid_rect(QRectF& result);
 void get_mapped_mid_rect(QRect& result);

 void get_mid_rect_post(QRectF& result);
 void get_mapped_mid_rect_post(QRect& result);

 virtual void reset_geometry(const QPointF& sc = {}) Q_DECL_OVERRIDE;

 virtual void adjust_geometry(const QPointF& pos) Q_DECL_OVERRIDE;

 virtual void show() Q_DECL_OVERRIDE;

 void init_double_band(const QPointF& pos);
 void finish_double_band(const QPointF& pos);
 void complete_band(const QPointF& pos);

 void init_second_phase(const QPointF& pos) Q_DECL_OVERRIDE
 {
  init_double_band(pos);
 }

 void finish_second_phase(const QPointF& pos) Q_DECL_OVERRIDE
 {
  finish_double_band(pos);
 }

 void finish_third_phase(const QPointF& pos) Q_DECL_OVERRIDE
 {
  complete_band(pos);
 }

 void process_paint_event(QPaintEvent* event, QPainter& painter) Q_DECL_OVERRIDE;
 void set_gradient_center(QConicalGradient& gradient) Q_DECL_OVERRIDE;


Q_SIGNALS:

protected:


public Q_SLOTS:

};

#endif // MULTILINE_RUBBER_BAND__H
