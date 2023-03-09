#ifndef PDF_RUBBER_BAND__H
#define PDF_RUBBER_BAND__H


#include <QRubberBand>

#include "global-types.h"

#include "accessors.h"


class PDF_Rubber_Band : public QRubberBand
{
 Q_OBJECT

//? QPointF starting_corner_;

 QPointF inner_starting_corner_;
 QPointF outer_starting_corner_;
//? QPointF double_top_corner_;


 QPointF inner_end_corner_;
 QPointF outer_end_corner_;
//? QPointF double_bottom_corner_;

// QPointF double_start_;
// QPointF double_end_;

 enum class Corner_Pair_Directions {
  N_A, Up, Up_Right, Right, Down_Right,
  Down, Down_Left, Left, Up_Left,
  Direction_Only = 15,
  Pre_Double = 16, Double = 32, Post_Double = 64,
  Triple_Set = 128
 };

 ENUM_FLAGS_OP_MACROS(Corner_Pair_Directions)

 Corner_Pair_Directions get_corner_pair_direction(const QPointF& landmark,
   const QPointF& trajector);

 Corner_Pair_Directions active_corner_pair_direction_;

 QPoint _map_start_outside_corner(QRect& rect);
 QPoint _map_start_cross_corner(QRect& rect);
 QPoint _map_start_double_corner(QRect& rect);
 QPoint _map_end_double_corner(QRect& rect);

 void init_active_corner_pair_direction(Corner_Pair_Directions cpd, const QPointF& pos);
 void reset_active_corner_pair_direction(Corner_Pair_Directions cpd, const QPointF& pos);

public:

 PDF_Rubber_Band (Shape s, const QPointF& sc, QWidget* p = nullptr);

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

 void reset_geometry(const QPointF& sc = {});

 void adjust_geometry(const QPointF& pos);

 void init_double_band(const QPointF& pos);
 void finish_double_band(const QPointF& pos);

 void complete_band(const QPointF& pos);

Q_SIGNALS:

protected:

 void paintEvent(QPaintEvent *event);


public Q_SLOTS:

};

#endif // PDF_RUBBER_BAND__H
