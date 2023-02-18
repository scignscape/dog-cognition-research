
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "lanternfly-frame.h"


#include "MapGraphicsView.h"
#include "MapGraphicsScene.h"

#include "qmt-client-layer.h"
#include "qmt-client-context-menu-handler.h"
#include "qmt-client-location-focus.h"
#include "qmt-client-data-set.h"

#include "main-window.h"

#include "lanternfly-sighting-dialog.h"
#include "lanternfly-configuration-dialog.h"
#include "lanternfly-sighting-filter-dialog.h"

#include "CircleObject.h"

#include <QDebug>


Lanternfly_Frame::Lanternfly_Frame(Lanternfly_Main_Window* mw) : QFrame(mw)
{
 main_layout_ = new QVBoxLayout;

 scene_ = new MapGraphicsScene;
 view_ = new MapGraphicsView;

 QObject::connect(view_, &MapGraphicsView::preview_dialogs_requested,
    [](QString which)
 {
  QDialog* dlg = nullptr;

  static QMap<QString, void(*)(QDialog*&)> options {

#define TEMP_MACRO(x) \
   { #x, [](QDialog*& result) \
     {result = new x;} }, \

   TEMP_MACRO(Lanternfly_Sighting_Dialog)
   TEMP_MACRO(Lanternfly_Configuration_Dialog)
   TEMP_MACRO(Lanternfly_Sighting_Filter_Dialog)

#undef TEMP_MACRO
  };

  auto it = options.find(which);
  if(it != options.end())
  {
   (*it)(dlg);
   if(dlg)
     dlg->show();
  }
 });

 // Lanternfly_Sighting_Dialog* lsd = new Lanternfly_Sighting_Dialog;
 // lsd->show();

 // Lanternfly_Sighting_Filter_Dialog* lsfd = new Lanternfly_Sighting_Filter_Dialog;
 // lsfd->show();

 // Lanternfly_Configuration_Dialog* lcd = new Lanternfly_Configuration_Dialog;
 // lcd->show();



 client_layer_ = new QMT_Client_Layer(scene_, view_);
 view_->set_qmt_client_layer_base(client_layer_);

 client_context_menu_handler_ = new QMT_Client_Context_Menu_Handler(view_);
 view_->set_qmt_client_context_menu_handler_base(client_context_menu_handler_);

 qmt_client_location_focus_ = new QMT_Client_Location_Focus(this);
 view_->set_qmt_client_location_focus_base(qmt_client_location_focus_);

 qmt_client_data_set_ = new QMT_Client_Data_Set(mw);
 view_->set_qmt_client_data_set_base(qmt_client_data_set_);


 view_->set_coords_notify_callback([this](const QPointF qpf, quint8 zoom)
 {
  coords_line_edit_->setText(QString("%1,%2    (%3)")
    .arg(qpf.y()).arg(qpf.x()).arg(zoom));
 });

 view_->setScene(scene_);

 main_layout_->addWidget(view_);

 coords_line_edit_ = new QLineEdit("0,0");

 main_layout_->addWidget(coords_line_edit_);

 setLayout(main_layout_);
}

void Lanternfly_Frame::adopt_location(QString name)
{
 QString ok = qmt_client_location_focus_->adopt_location(name);
 if(!ok.isEmpty())
 {
  if(view_->coords_notify_callback())
  {
   view_->coords_notify_callback()({
     qmt_client_location_focus_->current_central_longitude(),
     qmt_client_location_focus_->current_central_latitude()},
     view_->zoomLevel());
  }
 }
}

void Lanternfly_Frame::add_marking(QPolygonF* qpf, qreal latitude,
  qreal longitude,
  QColor color, r8 scale, void** check_result)
{
 CircleObject* circle = new CircleObject(view_, scale, false, color);

 if(scale > 0)
 {
  QTransform qtr;
  qtr.scale(scale, scale);
  *qpf = qtr.map(*qpf);
 }

 void* ref = qpf;

 //circle->set_index_code(++count);
 circle->setFlags(MapGraphicsObject::ObjectIsSelectable);
  //circle->set_outline_code(s.presentation_code);

 scene_->addObject(circle);

 scene_->data_layer_objects.insert(circle);

 if(ref)
   circle->set_ref(ref);
 //stash.push_back(circle);

 if(check_result)
   *check_result = circle;

 circle->setLatitude(latitude);
 circle->setLongitude(longitude);

 circle->setZValue(50000);
 //update();
}


void Lanternfly_Frame::show_coordinate_marking(const QPoint& pos)
{

}


void Lanternfly_Frame::mark_coordinates(const QPoint& pos)
{
 QPointF ll = view_->mapToScene(pos);

 QString coords = "Latitude: %1, Longitude: %2"_qt.arg(ll.x()).arg(ll.y());

 qDebug() << "coords = " << coords;

 QPolygonF* qpf1 = new QPolygonF;
 (*qpf1) << QPointF(-80, 180);
 (*qpf1) << QPointF(0, 150);
 (*qpf1) << QPointF(80, 180);
 (*qpf1) << QPointF(0, 0);

 //view_->held_coordinate_marking_ = qpf1;

// QTransform qtr;
// qtr.scale(2, 2);
// *qpf1 = qtr.map(*qpf1);

 //qpf1->

 //static QColor transit_color = ;

// ll.setY(40.7125);
// ll.setX(-73.9022);


// static QColor parks_color = QColor(155, 0, 220, 220);

// QPolygonF* qpf = new QPolygonF;
// (*qpf) << QPointF(-110, -110);
// (*qpf) << QPointF(-110, 110);
// (*qpf) << QPointF(110, -110);
// (*qpf) << QPointF(110, 110);

// add_marking(qpf, ll.x(), ll.y(), parks_color, 200);

 //40.7125  long =  -73.9022

 //view_->mark_coordinates(pos);
// update();
}

void Lanternfly_Frame::set_view_zoom_level(quint8 level)
{
 view_->setZoomLevel(level);
}


void Lanternfly_Frame::center_on(qreal longitude, qreal latitude)
{
 view_->centerOn(longitude, latitude);
}

void Lanternfly_Frame::check_run_coords_notify_callback(r8 lon, r8 lat)
{
 if(view_->coords_notify_callback())
 {
  view_->run_coords_notify_callback(lon, lat);
 }


}


void Lanternfly_Frame::set_tile_source(QSharedPointer<MapTileSource> src)
{
 view_->setTileSource(src);
}
