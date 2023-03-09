
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "xcsd-outer-ring-scene-item.h"

//#include "dhax-graphics-scene.h"

#include <QGraphicsSceneHoverEvent>


XCSD_Outer_Ring_Scene_Item::XCSD_Outer_Ring_Scene_Item(const XCSD_Outer_Ring_Info& xori,
  //DHAX_Graphics_Scene* containing_scene,
  //QImage image,
  QGraphicsItem* parent)
   :  QGraphicsPixmapItem(parent) //,
     // containing_scene_(containing_scene), scene_hover_rect_(nullptr)
{
 QPixmap pixmap = QPixmap::fromImage(xori.image);
 setPixmap(pixmap);
 setAcceptHoverEvents(true);
 rect_ = xori.rect;

 //xy_corner_ = (row_column_pos_._transposed() * 27).as_qpoint();
}


void XCSD_Outer_Ring_Scene_Item::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
// qDebug() << event->pos();
// containing_scene_->handle_tierbox_hover_enter(this);

// u2 x_corner = row_column_pos_.c * 27;
// u2 y_corner = row_column_pos_.r * 27;

//?
 scene_hover_polygon_->setVisible(true);
 //scene_hover_polygon_->setPos(pos()); //x_corner_, y_corner_);

}

void XCSD_Outer_Ring_Scene_Item::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
// qDebug() << event->pos();
 //containing_scene_->handle_tierbox_hover_leave(this);

 scene_hover_polygon_->setVisible(false);
}


