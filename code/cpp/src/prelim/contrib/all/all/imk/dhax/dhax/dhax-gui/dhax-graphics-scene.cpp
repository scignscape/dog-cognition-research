
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-graphics-scene.h"

#include "xcsd-tierbox-scene-item.h"
#include "xcsd-outer-ring-scene-item.h"

#include "dhax-graphics-frame.h"


DHAX_Graphics_Scene::DHAX_Graphics_Scene()
  :  QGraphicsScene(), hover_rect_(nullptr)
{
// QRadialGradient gradient(50, 50, 800);
//       gradient.setColorAt(0.9, QColor::fromRgb(0, 150,140));
//       gradient.setColorAt(0.6, QColor::fromRgb(255, 0, 0));
//       gradient.setColorAt(0.2, QColor::fromRgb(0, 0, 0));
//       gradient.setColorAt(0, QColor::fromRgb(0, 200, 0));
}

void DHAX_Graphics_Scene::set_background_color(QColor c)
{
 setBackgroundBrush(QBrush(c));
}





void DHAX_Graphics_Scene::add_outer_pixmap(const XCSD_Outer_Ring_Info &xori,
  const QPoint& pos)
{
 XCSD_Outer_Ring_Scene_Item* xorsi = new XCSD_Outer_Ring_Scene_Item(xori);

 qDebug() << "xori rect = " << xori.rect;

 xorsi->setPos(xori.rect.topLeft());

 addItem(xorsi);

 //return;

 QGraphicsPolygonItem* qgpi;

 QPoint tl;

 if(xori.extra.isNull())
 {
  QRect rect(0, 0, xori.rect.width(), xori.rect.height());
  QPolygon poly(rect);
  qgpi = new QGraphicsPolygonItem(poly);
  tl = xori.rect.topLeft();
 }
 else
 {
  QVector<QPoint> points;
  points << xori.rect.topLeft() << xori.rect.topRight()
    << xori.rect.bottomRight() << xori.rect.bottomLeft()
    << xori.extra.topLeft() << xori.extra.topRight()
    << xori.extra.bottomRight() << xori.extra.bottomLeft();

  qDebug() << "\npoints1 = " << points;

  std::sort(points.begin(), points.end(), [](const QPoint& lhs, const QPoint& rhs)
  {
   if(lhs.y() == rhs.y())
     return lhs.x() < rhs.x();
   return lhs.y() < rhs.y();
  });

  qDebug() << "\npoints2 = " << points;

  tl = points.first();
  for(QPoint& qp : points)
    qp -= tl;

  if(points[2].x() == points[4].x()) // left
  {
   points.takeAt(2);
   points.takeAt(3);
   points[3].ry() = points[2].y();

   QPoint p4 = points.takeAt(4);
   points.push_back(p4);
  }
  else // right
  {
   points.takeAt(3);
   points.takeAt(4);
   points[3].ry() = points[2].y();

   // //  swap 2 and 5
   QPoint p2 = points[2];
   points[2] = points[5];
   points[5] = p2;

   // //  swap 3 and 4
   QPoint p3 = points[3];
   points[3] = points[4];
   points[4] = p3;

  }

//  points.takeAt(4);


  QPolygon poly(points);

  qDebug() << "\npoints = " << points;

  qgpi = new QGraphicsPolygonItem(poly);
 }



 QColor clr(200, 100, 150, 100);
 QBrush qbr(clr);
 qgpi->setBrush(qbr);
 QPen qpen;
//  qpen.setStyle(Qt::PenStyle::DashDotDotLine);
// QColor clr1(0, 20, 15, 200);
// qpen.setColor(clr1);
// qpen.setWidthF(1.5);
 qgpi->setPen(Qt::NoPen);
 addItem(qgpi);
 qgpi->setZValue(1);

 qgpi->setPos(tl); // + pos);

 qgpi->setVisible(false);

 xorsi->set_scene_hover_polygon(qgpi);

 // scene_hover_rect_->setVisible(true);


}


void DHAX_Graphics_Scene::add_tierbox_pixmap(QString path, rc2 rc, u2 x_corner, u2 y_corner)
{
// QPixmap pixmap;
// pixmap.load(path);

 if(!hover_rect_)
 {
  hover_rect_ = new QGraphicsRectItem(0, 0, 27, 27);
  QColor clr(100, 200, 150, 100);
  QBrush qbr(clr);
  hover_rect_->setBrush(qbr);
  QPen qpen;
//  qpen.setStyle(Qt::PenStyle::DashDotDotLine);
  QColor clr1(0, 20, 15, 200);
  qpen.setColor(clr1);
  qpen.setWidthF(1.5);
  hover_rect_->setPen(qpen);
  addItem(hover_rect_);
  hover_rect_->setZValue(1);
 }

 hover_rect_->setVisible(false);

 XCSD_Tierbox_Scene_Item* xtsi = new XCSD_Tierbox_Scene_Item(this, path, rc);

 xtsi->set_scene_hover_rect(hover_rect_);

 //xtsi->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
 xtsi->setPos(x_corner, y_corner);

 addItem(xtsi);
}


void DHAX_Graphics_Scene::handle_tierbox_hover_enter(XCSD_Tierbox_Scene_Item* xtsi)
{
 containing_graphics_frame_->show_info(QString("TierBox %1, %2")
   .arg(xtsi->row_column_pos().r).arg(xtsi->row_column_pos().c));
}


void DHAX_Graphics_Scene::handle_tierbox_context_menu_action(XCSD_Tierbox_Scene_Item* xtsi,
  u1 action_code)
{
 rc2 rc = xtsi->row_column_pos();

 //qobject_cast<DHAX_Graphics_Scene*>(this->v)

 switch( (XCSD_Tierbox_Scene_Item::Action_Codes) action_code)
 {
 case XCSD_Tierbox_Scene_Item::Action_Codes::Show_Histogram:
  {
   rc2 rc = xtsi->row_column_pos();
   Q_EMIT show_tierbox_local_color_histogram_requested(rc);
  }
  break;

 default:
   break;
 }

// u2 x_corner = rc.c * 27;
// u2 y_corner = rc.r * 27;

// hover_rect_->setVisible(true);

// hover_rect_->setPos(x_corner, y_corner);

// qDebug() << "xy corner = " << x_corner << ", " << y_corner;
}

//void DHAX_Graphics_Scene::set_foreground_color(QColor c)
//{
// setForegroundBrush(QBrush(c));
//}
