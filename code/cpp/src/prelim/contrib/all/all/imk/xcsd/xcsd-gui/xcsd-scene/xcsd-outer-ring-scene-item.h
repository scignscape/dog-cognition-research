
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef XCSD_OUTER_RING_SCENE_ITEM__H
#define XCSD_OUTER_RING_SCENE_ITEM__H

#include <QFrame>
#include <QBoxLayout>
#include <QGraphicsRectItem>
#include <QDebug>

#include "accessors.h"

#include "global-types.h"


#include "self-connect.h"


#include "xcsd-2d/xcsd-sdi-structures.h"

#include "xcsd-2d/xcsd-image.h"

class DHAX_Graphics_Scene;

class XCSD_Outer_Ring_Scene_Item : public QGraphicsPixmapItem
{
 //Q_OBJECT

private:

//? DHAX_Graphics_Scene* containing_scene_;

 QGraphicsPolygonItem* scene_hover_polygon_;

// QString image_file_path_;
// rc2 row_column_pos_;

 QRect rect_;
 //u2 y_corner_;

public:

 XCSD_Outer_Ring_Scene_Item(const XCSD_Outer_Ring_Info& xori,
   //?DHAX_Graphics_Scene* containing_scene,
   //QImage image,
   QGraphicsItem* parent = nullptr);

 USE_SELF_CONNECT(normal)
 USE_SELF_CONNECT(lambda)


 ACCESSORS(QGraphicsPolygonItem* ,scene_hover_polygon)

 void hoverEnterEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;

 void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;

//Q_SIGNALS:

//protected:

// void paintEvent(QPaintEvent *);
// void mousePressEvent(QMouseEvent* mouseEvent);
// void mouseReleaseEvent(QMouseEvent *mouseEvent);
// void mouseMoveEvent(QMouseEvent *mouseEvent);
// void mouseDoubleClickEvent(QMouseEvent *mouseEvent);


};

#endif //  XCSD_OUTER_RING_SCENE_ITEM__H




