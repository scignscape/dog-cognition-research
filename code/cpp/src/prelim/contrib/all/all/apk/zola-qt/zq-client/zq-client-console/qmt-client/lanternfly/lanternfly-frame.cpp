
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

#include "zq-client/zq-cross-map-coords.h"

#include "CircleObject.h"

#include "textio.h"

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


//struct Cross_Map_Info {

// r8 zola_window_width;
// r8 zola_window_height;
// r8 zola_exact_zoom;
// u2 multiplied_zoom;
// u1 zq_zoom;

// r8 initial_scaling_factor;
// r8 adjusted_scaling_factor;
// QPointF optimal_center;

//};

struct Cross_Map_Info {

 r8 zola_window_width;
 r8 zola_window_height;
 r8 zola_exact_zoom;
 r8 zola_adjusted_zoom;
 u1 zq_zoom;

 r8 zoom_differential;
 r8 scaling_adjustment;
 r8 scaling_factor;
 QPointF optimal_center;

};

//// set_view_zoom_level(11);

// u2 multiplied_zoom = coords.exact_zoom * 100 - 950;
// r8 initial_scaling_factor = 80;

// r8 adjusted_scaling_factor = initial_scaling_factor - multiplied_zoom / 10;


// r8 scale_factor = adjusted_scaling_factor / 100000;

//// r8 scale_factor = .0007;
//// if(coords.exact_zoom >= 10)
////   scale_factor = .0006;

// QPointF ll0 = {291, 278};

// Cross_Map_Info cmi { coords.window_size.width(),
//   coords.window_size.height(),
//   coords.exact_zoom, multiplied_zoom,
//   view_->zoomLevel(), initial_scaling_factor, adjusted_scaling_factor, ll0 };

// QString file = ROOT_FOLDER "/../cross-map-info.txt";
// KA::TextIO::append_to_file(file, "\n",
//R"(ZWW: %1 ZWH: %2 ZEZ: %3 MZ: %4 ZQZ: %5 ISF: %6 ASF: %7 OCX: %8  OCY: %9
//                                        )"_qt
//  .arg(cmi.zola_window_width)
//  .arg(cmi.zola_window_height)
//  .arg(cmi.zola_exact_zoom)
//  .arg(cmi.multiplied_zoom)
//  .arg(cmi.zq_zoom)
//  .arg(cmi.initial_scaling_factor)
//  .arg(cmi.adjusted_scaling_factor)
//  .arg(cmi.optimal_center.x())
//  .arg(cmi.optimal_center.y())
//                            );


//// QPointF ll = view_->mapToScene(pos);  40.9241, Longitude: -74.2653

//// QPointF ll = view_->mapToScene(coords.local_window_coords.toPoint());

//// QPointF lpos {0, 167};
//// QPointF lpos {0, coords.local_window_coords.y()};

void Lanternfly_Frame::mark_coordinates(const ZQ_Cross_Map_Coords& coords)
{
 QPoint ll_tl = {0, 0};
 QPoint ll_br = {view_->width(), view_->height()};

 QPoint ll_center = (ll_tl + ll_br) / 2;;

 QPointF geo_ll_tl = view_->mapToScene({ll_tl.x(), ll_tl.y()});
 QPointF geo_ll_br = view_->mapToScene({ll_br.x(), ll_br.y()});

 r8 xdiff = ll_br.x() - ll_tl.x();
 r8 ydiff = ll_br.y() - ll_tl.y();

 QPointF center1 = (geo_ll_tl + geo_ll_br) / 2;
 QPointF geo_center1 = view_->mapToScene(ll_center);

 QPointF lwc = coords.local_window_coords;
 QPointF lwc_center = {280, 280};

 qDebug() << "lwc = " << coords.local_window_coords;
 QPointF diff = lwc - lwc_center;
 //diff.rx() = -diff.x();
 qDebug() << "diff = " << diff;

 r8 zoom_differential = coords.adjusted_zoom - view_->zoomLevel();

 r8 scaling_adjustment = .9;

 zoom_differential /= view_->zoomLevel();
 zoom_differential *= scaling_adjustment;

 r8 scaling_factor = 1 - zoom_differential;


  Cross_Map_Info cmi { coords.window_size.width(),
    coords.window_size.height(),
    coords.exact_zoom, coords.adjusted_zoom,
    view_->zoomLevel(), zoom_differential, scaling_adjustment, scaling_factor, lwc_center};

   QString file = ROOT_FOLDER "/../cross-map-info.txt";
   KA::TextIO::append_to_file(file, "\n",
  R"(ZWW: %1 ZWH: %2 ZEZ: %3 ZAZ: %4 ZQZ: %5 ZDF: %6 SCF: %7 OCX: %8  OCY: %9
                                          )"_qt
    .arg(cmi.zola_window_width)
    .arg(cmi.zola_window_height)
    .arg(cmi.zola_exact_zoom)
    .arg(cmi.zola_adjusted_zoom)
    .arg(cmi.zq_zoom)
    .arg(cmi.zoom_differential)
    .arg(cmi.scaling_factor)
    .arg(cmi.scaling_adjustment)
    .arg(cmi.optimal_center.x())
    .arg(cmi.optimal_center.y())
                              );

 r8 scale_factor = scaling_factor;
 diff *= scale_factor;

 QPointF ll_center1 = ll_center + diff;
 QPointF geo_center = view_->mapToScene(ll_center1.toPoint());

 qDebug() << "diff = " << diff;

 qDebug() << "center = " << center;

//?
// geo_center += diff;

//  QString file = ROOT_FOLDER "/../cross-map-info.txt";
//  KA::TextIO::append_to_file(file, "\n",
// R"(ZWW: %1 ZWH: %2 ZEZ: %3 MZ: %4 ZQZ: %5 ISF: %6 ASF: %7 OCX: %8  OCY: %9
//                                         )"_qt
//   .arg(cmi.zola_window_width)
//   .arg(cmi.zola_window_height)


//? QPointF ll0 = view_->mapToScene({280, 280});
//? QPointF ll1 = view_->mapToScene(coords.local_window_coords.toPoint());

// r8 xdiff = ll1.x() - ll0.x();
// r8 ydiff = ll1.y() - ll0.y();
 //ydiff /= lpos.y();


// qDebug() << " ll0 = " << ll_tl << " ll1 = " << ll_br;
// qDebug() << " ll0 = " << ll0 << " coords.local_window_coords = " << coords.local_window_coords;

//?
//?
// QPointF pos {coords.latitude + ydiff, coords.longitude + xdiff};
//
// QPointF pos {40.9241, -74.2653};
// QPointF pos {40.91236, -74.04735};

//?
//? QPointF pos {coords.latitude, coords.longitude};
//? QPointF pos {ll0.y(), ll0.x()};
 QPointF pos {geo_center.y(), geo_center.x()};

 QPointF pos1 {geo_center1.y(), geo_center1.x()};

 QString scoords = "Latitude: %1, Longitude: %2"_qt.arg(pos.x()).arg(pos.y());
 QString s1coords = "Latitude: %1, Longitude: %2"_qt.arg(coords.latitude).arg(coords.longitude);

 qDebug() << "scoords = " << scoords;
 qDebug() << "s1coords = " << s1coords;

 static QColor parks_color = QColor(155, 0, 220, 220);

 static QColor alt_color = QColor(55, 200, 220, 220);

 QPolygonF* qpf = new QPolygonF;
 (*qpf) << QPointF(-80, 180);
 (*qpf) << QPointF(0, 150);
 (*qpf) << QPointF(80, 180);
 (*qpf) << QPointF(0, 0);

// (*qpf) << QPointF(-20, 110);
// (*qpf) << QPointF(20, 110);
// (*qpf) << QPointF(110, 20);
// (*qpf) << QPointF(110, -20);
// (*qpf) << QPointF(20, -110);
// (*qpf) << QPointF(-20, -110);
// (*qpf) << QPointF(-110, -20);
// (*qpf) << QPointF(-110, 20);
// (*qpf) << QPointF(4, 0);
// (*qpf) << QPointF(-4, 0);
// (*qpf) << QPointF(0, 4);
// (*qpf) << QPointF(0, -4);

 QTransform qtr;
 qtr.scale(1, -1);
 *qpf = qtr.map(*qpf);

 view_->add_superimposed_marking(pos, qpf, parks_color, .15);

 view_->add_superimposed_marking(pos1, qpf, alt_color, .15);

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
