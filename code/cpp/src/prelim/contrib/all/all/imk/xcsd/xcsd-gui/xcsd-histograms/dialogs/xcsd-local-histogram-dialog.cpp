
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "xcsd-local-histogram-dialog.h"

#include "xcsd-2d/xcsd-image.h"

#include <QGraphicsRectItem>

#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>


XCSD_Local_Histogram_Dialog::Rect_Item::Rect_Item(Window_Rect_Item* parent,
  const QRect& rect, u2 cc, QColor color)
  :  QGraphicsRectItem(rect, parent), //hue(h),
    color_code(cc)
{
 setParentItem(parent);
 QBrush qbr(color);
 setBrush(qbr);
 setAcceptHoverEvents(true);
}

void XCSD_Local_Histogram_Dialog::Rect_Item::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
 QColor color(brush().color());
 int hh = color.hue();
 u1 s = color.hsvSaturation();
 u1 v = color.value();
 //color.setHsv(360 - hh, s, v);
 color.setHsv(360 - hh, 200, 200);

 QPen pen;
 pen.setColor(color);
 pen.setWidth(3);
 setPen(pen);
 update();
}

void XCSD_Local_Histogram_Dialog::Rect_Item::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
 QPen pen;
 pen.setColor(Qt::black);
 pen.setWidth(1);
 setPen(pen);
 update();
}


//void XCSD_Tierbox_Scene_Item::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
void XCSD_Local_Histogram_Dialog::Rect_Item::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
#ifdef USE_XCSD
 get_parent_dialog()->context_menu(this, event);
#endif
}


#ifdef USE_XCSD

XCSD_Local_Histogram_Dialog::XCSD_Local_Histogram_Dialog(QWidget* parent,
  pr2 totals, QColor ref_color, QMap<s2, Histogram_Group_Summary>* data)
  :  QDialog(parent)
{

 image_height_ = 520;
 max_bin_height_  = 200;
 min_bin_height_  = 10;
 bin_base_  = 260;
 bin_width_  = 9;

 max_group_height_  = 200;
 min_group_height_  = 10;


 auto [largest_group_total, largest_bin] = totals;

 graphics_scene_ = new QGraphicsScene(this);

 parent_rect_item_ = new Window_Rect_Item(this);
 graphics_scene_->addItem(parent_rect_item_);

 graphics_view_ = new QGraphicsView(this);

 graphics_view_->setScene(graphics_scene_);

 u2 h = 0;
 for(s2 hue = 0, go_on = 1; go_on; ++hue)
 {
  if(hue == 360)
  {
   hue = -1;
   go_on = 0;
  }
  auto it = data->find(hue);
  if(it == data->end())
    continue;



  {
   Histogram_Group_Summary& hgs = it.value();

   u2 most = hgs.max;

   QColor color = XCSD_Image::rgb555_to_qcolor(most);

   u2 height = (((r8) hgs.total) / largest_group_total) * (max_group_height_ - min_group_height_);

   QRect rect(h, bin_base_,
     ((bin_width_ + 1) * it.value().counts.size()) - 1, min_group_height_ + height);
//    qDebug() << "rect = " << rect;


   Rect_Item* ri = new Rect_Item(parent_rect_item_, rect, most, color);

//?   graphics_scene_->addItem(ri);

//   ri->setBrush(qbr);
//   ri->setFlags(QGraphicsItem::ItemIsSelectable);

//  painter.setBrush(qbr);
//  painter.drawRect(rect);
  }

  for(pr2 pr : it.value().counts)
  {
   u2 v = pr.second;

   QColor color = XCSD_Image::rgb555_to_qcolor(pr.first);

   u2 height = (((r8) pr.second) / largest_bin) * (max_bin_height_ - min_bin_height_);

//    qDebug() << "v = " << v << ", height = " << height;

   QRect rect(h, bin_base_, bin_width_, -(min_bin_height_ + height));
//    qDebug() << "rect = " << rect;

   rect = rect.normalized();

//   QBrush qbr(color);

   Rect_Item* ri = new Rect_Item(parent_rect_item_, rect.normalized(), pr.first, color);

   ri->setZValue(1);

   QFont font;
   font.setPointSize(7);

   u1 text_vertical_offset = 16;

   if(hue < 10)
     graphics_scene_->addText(QString::number(hue), font)->setPos(rect.topLeft() - QPoint{1, 18});
     //painter.drawText(rect.bottomLeft() - QPoint{-2, 2}, QString::number(hue));
   else if(hue < 100)
   {
    graphics_scene_->addText(QString::number(hue % 10), font)->setPos(rect.topLeft() - QPoint{1, 18});
    graphics_scene_->addText(QString::number((hue / 10) % 10),
      font)->setPos(rect.topLeft() - QPoint{1, 26});


    text_vertical_offset += 8;

//    painter.drawText(rect.bottomLeft() - QPoint{-2, 2}, QString::number(hue % 10));
//    painter.drawText(rect.bottomLeft() - QPoint{-2, 10},
//      QString::number( (hue / 10) %  10) );
   }
   else
   {
    graphics_scene_->addText(QString::number(hue % 10), font)->setPos(rect.topLeft() - QPoint{1, 18});
    graphics_scene_->addText(QString::number((hue / 10) % 10),
      font)->setPos(rect.topLeft() - QPoint{1, 26});
    graphics_scene_->addText(QString::number((hue / 100) % 10),
      font)->setPos(rect.topLeft() - QPoint{1, 34});

    text_vertical_offset += 16;
   }

   if(color == ref_color)
   {
    QPen pen;
    pen.setColor(Qt::darkRed);
    pen.setWidth(1);
    pen.setStyle(Qt::PenStyle::DashLine);
    QPoint l1 (rect.left() - 1, rect.top() - text_vertical_offset);
    QPoint l2 = l1 + QPoint(bin_width_ + 4, 0);
    QPoint l3 = l1 + QPoint(0, 22);
    QPoint l4 = l2 + QPoint(0, 22);
    graphics_scene_->addLine(l1.x() - 4, l1.y(), l2.x() + 4, l2.y(), pen);

    pen.setColor(color);
    pen.setWidth(2);
    pen.setStyle(Qt::PenStyle::DotLine);

    graphics_scene_->addLine(l1.x(), l1.y() + 4, l3.x(), l3.y(), pen);
    graphics_scene_->addLine(l2.x(), l2.y() + 4, l4.x(), l4.y(), pen);

    graphics_scene_->addText("ref", font)->setPos(l1 - QPoint{3, 17});
   }


   h += 10;
  }
 }

 main_layout_ = new QVBoxLayout;

 main_layout_->addWidget(graphics_view_);
 setLayout(main_layout_);

}

void XCSD_Local_Histogram_Dialog::context_menu(Rect_Item* ri, QGraphicsSceneContextMenuEvent* event)
{
 qDebug() << "event = " << event->pos();

 QMenu* menu = new QMenu(this);//

 menu->addAction("Mark as global background pole", [this, ri]
 {
  mark_global_background_pole_requested(ri->color_code);
 });

 menu->addAction("Mark as global foreground pole", [this, ri]
 {
  mark_global_foreground_pole_requested(ri->color_code);
 });

 menu->addAction("Mark as local background pole", [this, ri]
 {
  mark_local_background_pole_requested(ri->color_code);
 });

 menu->addAction("Mark as local foreground pole", [this, ri]
 {
  mark_local_foreground_pole_requested(ri->color_code);
 });

 QPoint p = graphics_view_->mapFromScene(event->pos().toPoint());
 p = mapToGlobal(p);

 menu->popup(p);

}
#endif//def USE_XCSD

