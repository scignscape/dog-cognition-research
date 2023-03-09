
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifdef USE_OpenCV


#include "dhax-application-controller.h"

#include "main-window/dhax-main-window-controller.h"

#include "dhax-graphics-scene.h"
#include "dhax-graphics-frame.h"
#include "image-viewer/dhax-image-scene-item.h"

#include <QGraphicsRectItem>

#include <QMenu>
#include <QAction>

#include <QMessageBox>


struct KeyPoint_Graphics_Item : QGraphicsRectItem
{
 cv::KeyPoint keypoint;

 QBrush hover_brush_;
 QBrush normal_brush_;

 u4 total_keypoint_count_;

 KeyPoint_Graphics_Item(QRect rect, QBrush qbr, QBrush hqbr, cv::KeyPoint& kp,
   u4 total_keypoint_count, QPen pen = Qt::NoPen)
   :  QGraphicsRectItem(rect), keypoint(kp),
      total_keypoint_count_(total_keypoint_count), normal_brush_(qbr), hover_brush_(hqbr)
 {
  setBrush(qbr);
  setPen(pen);

  setAcceptHoverEvents(true);
 }

 void hoverEnterEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;
 void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;
 void contextMenuEvent(QGraphicsSceneContextMenuEvent* event)  Q_DECL_OVERRIDE;

};


void KeyPoint_Graphics_Item::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
 QMenu* menu = new QMenu;
//    menu->addAction("Action 1");
//    menu->addAction("Action 2");

 menu->addAction("Keypoint Info", [this]()
 {
  QString msg = R"(Angle: %1
Size: %2
Response: %3
Octave: %4
 )"_qt.arg(keypoint.angle).arg(keypoint.size)
      .arg(keypoint.response).arg(keypoint.octave);

  QMessageBox* message_box = new QMessageBox();
  message_box->setMinimumWidth(350);

//  message_box->setText("Line Detection Angles (compared to predefined transform)"_qt);
  message_box->setText("KeyPoint Info (one of %1 KeyPoints total)%2"_qt
    .arg(total_keypoint_count_).arg(" "_qt.repeated(30)));

  message_box->setInformativeText(R"(Hit "Show Details" for information about this KeyPoint)");

//  message_box->setText("KeyPoint Info"_qt + " "_qt.repeated(20));
//  message_box->setInformativeText(R"(Hit "Show Details" for information about this KeyPoint)");

  message_box->setDetailedText(msg);
  message_box->show();
 });


 QAction* a = menu->exec(event->screenPos());
}


void KeyPoint_Graphics_Item::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
 setBrush(hover_brush_);
 update();
}

void KeyPoint_Graphics_Item::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
 setBrush(normal_brush_);
 update();
}


void DHAX_Application_Controller::show_keypoints(std::shared_ptr<QMap<QString, std::shared_ptr<DHAX_Stat_Assessment>>>
  transforms_map,
  QString file_path, std::vector<cv::KeyPoint>& keypoints)
{
 load_image(file_path);

 DHAX_Graphics_Scene& scene = *graphics_frame_->graphics_scene();
 DHAX_Image_Scene_Item* dsi = main_window_controller_->image_scene_item();

 dsi->set_current_transforms_map(transforms_map);
 //scene.cur

 QColor color = Qt::cyan;
 QBrush qbr(color);

 QColor hcolor = Qt::white;
 QBrush hqbr(hcolor);


 u1 radius = 3, rx2 = radius * 2;
 for(cv::KeyPoint kp : keypoints)
 {
 // QGraphicsScene*
  u2 x = kp.pt.x, y = kp.pt.y;

  //QGraphicsRectItem*
  //qgri =
  scene.addRect(x - radius, y - radius, rx2, rx2, Qt::NoPen, qbr);

  KeyPoint_Graphics_Item* kpgi = new KeyPoint_Graphics_Item(QRect(x - radius, y - radius,
    rx2, rx2), qbr, hqbr, kp, keypoints.size());

  scene.addItem(kpgi);



 }
}
#endif
