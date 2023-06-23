
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

#include "case-map/case-map-entry-dialog.h"

// //  MapGraphics
#include "CircleObject.h"
#include "PolygonObject.h"
#include "qmt-gis/qmt-geospatial-marker.h"

#include <QDebug>
#include <QGeoCoordinate>


Lanternfly_Frame::Lanternfly_Frame(Lanternfly_Main_Window* mw) : QFrame(mw)
{
 main_layout_ = new QVBoxLayout;

 scene_ = new MapGraphicsScene;
 view_ = new MapGraphicsView;

 QObject::connect(view_, &MapGraphicsView::preview_dialogs_requested,
    [this](QString which)
 {
  QDialog* dlg = nullptr;

  static QMap<QString, void(*)(QDialog*&)> options {

#define TEMP_MACRO(x) \
   { #x, [](QDialog*& result) \
     {result = new x();} }, \

   TEMP_MACRO(Lanternfly_Sighting_Dialog)
   TEMP_MACRO(Lanternfly_Configuration_Dialog)
   TEMP_MACRO(Lanternfly_Sighting_Filter_Dialog)

   TEMP_MACRO(Case_Map_Entry_Dialog)

#undef TEMP_MACRO
  };

  auto it = options.find(which);
  if(it != options.end())
  {
   (*it)(dlg);
   if(dlg)
   {
    connect(dlg, SIGNAL(location_marker_requested(QGeoLocation)), //this,
      SLOT(handle_location_marker_request(QGeoLocation)));
    dlg->show();
   }
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


//?#ifdef HIDE
// {
//? static QColor transit_color = QColor(155, 90, 40, 255);
// static r8 scale_factor = .000125;

// QTransform trans;
// trans = trans.scale(scale_factor, scale_factor);
// *qpf = trans.map(*qpf);

// QPolygonF* qpf1 = new QPolygonF;
// (*qpf1) << QPointF(40.8782, -74.1096).transposed();
// (*qpf1) << QPointF(40.8782, -74.1196).transposed();
// (*qpf1) << QPointF(40.8882, -74.1196).transposed();
// (*qpf1) << QPointF(40.8882, -74.1096).transposed();

// QTransform trans1;
// trans1 = trans1.fromTranslate(loc.coordinate().longitude(), loc.coordinate().latitude());
// *qpf = trans1.map(*qpf);

// qDebug() << "qpf = " << *qpf;

// PolygonObject* poly  = new PolygonObject(view_, *qpf1, transit_color);

// poly->setLatitude(loc.coordinate().latitude());
// poly->setLongitude(loc.coordinate().longitude());
// scene_->addObject(poly);

// poly->set_index_code(++count);

// view_->zoomIn();
// view_->centerOn(loc.coordinate().longitude(), loc.coordinate().latitude());
// view_->zoomOut();
//? }
//#endif

//#ifdef HIDE
//   QPolygonF* qpf = new QPolygonF;
//   (*qpf) << QPointF(-80, 180);
//   (*qpf) << QPointF(0, 150);
//   (*qpf) << QPointF(80, 180);
//   (*qpf) << QPointF(0, 0);
//   static r8 scale_factor = .0025;

//   QTransform trans;
//   trans = trans.scale(scale_factor, scale_factor);
//   *qpf = trans.map(*qpf);


//   CircleObject*    circle1 = nullptr;
//// CircleObject*    circle1 = new CircleObject(view_, 125, false, transit_color);
////   circle1->sup.set_ref(qpf);

//    circle = new CircleObject(view_, 125, false, transit_color);
//     circle->sup.set_ref(qpf);

//   if(circle1)
//   {
//    circle1->set_index_code(++count);
//    circle1->setFlags(MapGraphicsObject::ObjectIsSelectable);
//    circle1->setLatitude(loc.coordinate().latitude());
//    circle1->setLongitude(loc.coordinate().longitude());
//    //?circle->set_outline_code(s.presentation_code);

//    circle1->sup.set_outline_code(12);
//   }

//   poly = new PolygonObject(view_, QPolygonF({QPointF(loc.coordinate().longitude(),
//     loc.coordinate().latitude())}));




void Lanternfly_Frame::handle_location_marker_request(QGeoLocation loc)
{
 qDebug() << "loc lat: " << loc.coordinate().latitude();
 qDebug() << "loc lon: " << loc.coordinate().longitude();

 static u2 count = 0;

 QPolygonF* qpf = new QPolygonF;
//  (*qpf) << QPointF(80, 80);
//  (*qpf) << QPointF(80, -80);
//  (*qpf) << QPointF(-80, -80);
//  (*qpf) << QPointF(-80, 80);

 (*qpf) << QPointF(-80, 180);
 (*qpf) << QPointF(0, 150);
 (*qpf) << QPointF(80, 180);
 (*qpf) << QPointF(0, 0);

// (*qpf) << QPointF(0, 0);
// (*qpf) << QPointF(80, 180);
// (*qpf) << QPointF(0, 210);
// (*qpf) << QPointF(-80, 180);

// *qpf = qpf->in

 CircleObject* circle = nullptr;
 PolygonObject* poly = nullptr;

 void* ref = nullptr;
 static QColor passive_color = QColor(55, 90, 130, 255);
 static QColor active_color = QColor(155, 190, 30, 255);


   poly = new PolygonObject(view_, {} //*qpf1
                            );

   poly->set_index_code(++count);
   poly->setFillColor(passive_color);
   poly->init_ref_marker(*qpf, passive_color, active_color);
   poly->ref_marker()->set_scale(0.2);

//   poly->sup.check_ref();
//

 if(circle)
 {
  circle->set_index_code(++count);
//?  circle->setFlags(MapGraphicsObject::ObjectIsSelectable);
  circle->setLatitude(loc.coordinate().latitude());
  circle->setLongitude(loc.coordinate().longitude());
  //?circle->set_outline_code(s.presentation_code);

  circle->sup.set_outline_code(12);

  scene_->addObject(circle);
  if(ref)
    circle->sup.set_ref(ref);
  //?stash.push_back(circle);

  view_->zoomIn();
  view_->centerOn(loc.coordinate().longitude(), loc.coordinate().latitude());
  view_->zoomOut();

  //marked_locations_.push_back(loc);
  view_->add_marked_location(loc, circle);
  update();
  repaint();

 }

 if(poly)
 {
  poly->set_index_code(++count);
//?  poly->setFlags(MapGraphicsObject::ObjectIsSelectable);
  poly->setLatitude(loc.coordinate().latitude());
  poly->setLongitude(loc.coordinate().longitude());
  //?circle->set_outline_code(s.presentation_code);

//  if(poly->ref_marker())
//    poly->ref_marker()->set_outline_code(12);

  scene_->addObject(poly);
//  if(ref)
//    circle->set_ref(ref);
  //?stash.push_back(circle);

  view_->zoomIn();
  view_->centerOn(loc.coordinate().longitude(), loc.coordinate().latitude());
  view_->zoomOut();

  //marked_locations_.push_back(loc);
  view_->add_marked_location(loc, poly);
  update();
  repaint();

 }

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


void Lanternfly_Frame::set_view_zoom_level(quint8 level)
{
 view_->setZoomLevel(level);
}


void Lanternfly_Frame::center_on(qreal longitude, qreal latitude)
{
 view_->centerOn(longitude, latitude);
}


void Lanternfly_Frame::set_tile_source(QSharedPointer<MapTileSource> src)
{
 view_->setTileSource(src);
}
