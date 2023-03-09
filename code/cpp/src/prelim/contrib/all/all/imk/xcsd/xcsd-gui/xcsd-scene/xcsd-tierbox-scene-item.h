
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef XCSD_TIERBOX_SCENE_ITEM__H
#define XCSD_TIERBOX_SCENE_ITEM__H

#include <QFrame>
#include <QBoxLayout>
#include <QGraphicsRectItem>
#include <QDebug>

#include "accessors.h"

#include "global-types.h"


#include "self-connect.h"


#include "xcsd-2d/xcsd-sdi-structures.h"

//?class XCSD_Graphics_Scene;

class DHAX_Graphics_Scene;

class XCSD_Tierbox_Scene_Item : public QGraphicsPixmapItem
{
 //Q_OBJECT

private:

 //XCSD_Graphics_Scene* containing_scene_;
 DHAX_Graphics_Scene* containing_scene_;

 QGraphicsRectItem* scene_hover_rect_;

 QString image_file_path_;

 rc2 row_column_pos_;

 QPoint xy_corner_;
 //u2 y_corner_;

 QMenu* current_menu_;

public:

 XCSD_Tierbox_Scene_Item(DHAX_Graphics_Scene* containing_scene,
   QString path, rc2 rc, QGraphicsItem* parent = nullptr);

// USE_SELF_CONNECT(normal)
// USE_SELF_CONNECT(lambda)

 enum class Action_Codes : u1 {
   N_A, Show_Histogram, Show_TierBox_Data
 };


 ACCESSORS(QString ,image_file_path)
 ACCESSORS(rc2 ,row_column_pos)
 ACCESSORS(QGraphicsRectItem* ,scene_hover_rect)

 void hoverEnterEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;

 void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;

 void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) Q_DECL_OVERRIDE;
// {
//     QMenu menu;
//     QAction *removeAction = menu.addAction("Remove");
//     QAction *markAction = menu.addAction("Mark");
//     QAction *selectedAction = menu.exec(event->screenPos());
//     // ...
// }


//Q_SIGNALS:

//protected:

// void paintEvent(QPaintEvent *);
// void mousePressEvent(QMouseEvent* mouseEvent);
// void mouseReleaseEvent(QMouseEvent *mouseEvent);
// void mouseMoveEvent(QMouseEvent *mouseEvent);
// void mouseDoubleClickEvent(QMouseEvent *mouseEvent);


};

#endif //  XCSD_TIERBOX_SCENE_ITEM__H




