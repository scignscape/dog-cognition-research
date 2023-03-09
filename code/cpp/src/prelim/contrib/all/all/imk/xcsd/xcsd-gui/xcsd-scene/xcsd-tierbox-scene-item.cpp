
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "xcsd-tierbox-scene-item.h"

//?
#include "dhax-graphics-scene.h"


#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>

#include <QMenu>

#include <tuple>


class XCSD_Graphics_Scene : public QGraphicsScene
{
public:

 virtual void handle_tierbox_context_menu_action(XCSD_Tierbox_Scene_Item*, u1) = 0;
 virtual void handle_tierbox_hover_enter(XCSD_Tierbox_Scene_Item*) = 0;

};


XCSD_Tierbox_Scene_Item::XCSD_Tierbox_Scene_Item(
  //?DHAX_Graphics_Scene* containing_scene,
    DHAX_Graphics_Scene* containing_scene,
  QString path, rc2 rc, QGraphicsItem* parent)
  :  QGraphicsPixmapItem(parent),
     containing_scene_(containing_scene), scene_hover_rect_(nullptr),
     row_column_pos_(rc)
{
 QPixmap pixmap;
 pixmap.load(path);
 setPixmap(pixmap);
 setAcceptHoverEvents(true);

 xy_corner_ = (row_column_pos_._transposed() * 27).as_qpoint();

 current_menu_ = nullptr;

}

void XCSD_Tierbox_Scene_Item::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
 QMenu* menu = new QMenu;

 QBrush qbr = scene_hover_rect_->brush();
 QBrush old_qbr = qbr;
 qbr.setColor(QColor(100,50, 70, 100));
 scene_hover_rect_->setBrush(qbr);
 scene_hover_rect_->setVisible(true);
// update();

 QAction* show_histogram_action = menu->addAction("Show Histogram");
 show_histogram_action->setProperty("ActionCode", (u1) Action_Codes::Show_Histogram);

 QAction* show_tierbox_data_action = menu->addAction("Show TierBox Data");
 show_tierbox_data_action->setProperty("ActionCode", (u1) Action_Codes::Show_TierBox_Data);

 current_menu_ = menu;

 QAction* selected_action = menu->exec(event->screenPos() - QPoint(3, 3));

 if(selected_action)
 {
  containing_scene_->handle_tierbox_context_menu_action(this,
    (u1)selected_action->property("ActionCode").toUInt());
 }
 //  qDebug() << "action = " << selected_action->text();

// QAction::connect(selected_action, &QAction::triggered, []
// {
//  qDebug() << "a3";
// });


 current_menu_ = nullptr;
 scene_hover_rect_->setBrush(old_qbr);
 menu->deleteLater();



 // containing_scene_
}


void XCSD_Tierbox_Scene_Item::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
// qDebug() << event->pos();
// containing_scene_->handle_tierbox_hover_enter(this);

// u2 x_corner = row_column_pos_.c * 27;
// u2 y_corner = row_column_pos_.r * 27;

 scene_hover_rect_->setVisible(true);
 scene_hover_rect_->setPos(pos()); //x_corner_, y_corner_);

 containing_scene_->handle_tierbox_hover_enter(this);

}

void XCSD_Tierbox_Scene_Item::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
// qDebug() << event->pos();
 //containing_scene_->handle_tierbox_hover_leave(this);

 if(!current_menu_)
   scene_hover_rect_->setVisible(false);
}

