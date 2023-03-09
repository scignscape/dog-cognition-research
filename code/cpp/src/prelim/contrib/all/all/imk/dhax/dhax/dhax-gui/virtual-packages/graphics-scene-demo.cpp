
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "graphics-scene-demo.h"

#include "dhax-graphics-scene.h"

#include "image-viewer/dhax-image-scene-item.h"


#include <QGraphicsEllipseItem>

#include <QDebug>


Graphics_Scene_Demo::Graphics_Scene_Demo()
  :  scene_(nullptr), image_display_scene_item_(nullptr)
{

}

void Graphics_Scene_Demo::draw_circle(const QPointF& center,
  r8 radius, QColor brush_color, QColor pen_color, u1 index)
{
 QBrush qbr(brush_color);
 QPen qpen(pen_color);
 QGraphicsEllipseItem* el = scene_->addEllipse(center.x() - radius,
   center.y() - radius, radius * 2, radius * 2, qpen, qbr);
 el->setParentItem(image_display_scene_item_->this_proxy_widget());
 el->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

 controls_[index] = {el, radius};
}

void Graphics_Scene_Demo::add_triple_dots(r8 x1, r8 y1, r8 x2, r8 y2, r8 x3, r8 y3)
{
 QPointF p1(x1, y1);
 QPointF p2(x2, y2);
 QPointF p3(x3, y3);

 r8 radius = 7;
 QColor brush_color = Qt::yellow;
 QColor pen_color = Qt::black;

 QColor mid_brush_color = Qt::red;

 draw_circle(p1, radius, brush_color, pen_color, 1);
 draw_circle(p2, radius, mid_brush_color, pen_color, 2);
 draw_circle(p3, radius, brush_color, pen_color, 3);

 image_display_scene_item_->connect(image_display_scene_item_,
   &DHAX_Image_Scene_Item::draw_cubic_path_requested,
   [this]()
 {
  draw_curve_path("cubic");
 });

 image_display_scene_item_->connect(image_display_scene_item_, &DHAX_Image_Scene_Item::draw_quad_path_requested,
   [this]()
 {
  draw_curve_path("quad");
 });

  // void draw_cubic_path_requested();
  // void draw_quad_path_requested();


// QBrush qbr(brush_color);
// QPen qpen(pen_color);
// QGraphicsEllipseItem* el = scene_->addEllipse(center.x() - radius,
//   center.y() - radius, radius * 2, radius * 2, qpen, qbr);
// el->setParentItem(image_display_scene_item_);
// el->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

}

void Graphics_Scene_Demo::draw_curve_path(QString kind)
{
 QPoint p1 = control_center(1).toPoint();
 QPoint mid = control_center(2).toPoint();
 QPoint p2 = control_center(3).toPoint();

 draw_circle(p1, 2, Qt::cyan, Qt::transparent, 0);
 draw_circle(mid, 2, Qt::cyan, Qt::transparent, 0);
 draw_circle(p2, 2, Qt::cyan, Qt::transparent, 0);

 QPainterPath path;



// display_image_->scrolled_image_pixmap_item()->mapToScene()

 path.moveTo(p1);

 if(kind == "cubic")
   path.cubicTo(mid, mid, p2);
 else if(kind == "quad")
   path.quadTo(mid, p2);
 else
 {
  qDebug() << "Unknown path kind! Falling back on drawing a line.";
  path.lineTo(mid);
  path.moveTo(mid);
  path.lineTo(p2);
 }

 QGraphicsPathItem* ppi = scene_->addPath(path,
   QPen(QColor(25, 79, 106), 1, Qt::SolidLine,
   Qt::FlatCap, Qt::MiterJoin), QBrush(QColor(5, 122, 163, 100)));

 ppi->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
 ppi->setParentItem(image_display_scene_item_->this_proxy_widget());
}

