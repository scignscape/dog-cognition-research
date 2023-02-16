
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "main-window-controller.h"

#include "MapGraphicsView.h"

#include "dialogs/tile-server-select-dialog.h"

#include "qmt/qmt-client-layer-base.h"

#include "global-types.h"


#include "web-engine/qmt-web-engine-view.h"
#include "web-engine/qmt-web-engine-page.h"
#include "web-engine/qmt-my-page.h"

#include "CircleObject.h"


#include <QMessageBox>

#include <QGeoLocation>
#include <QGeoAddress>

#include <QFileDialog>

#include <QDebug>

Main_Window_Controller::Main_Window_Controller(MapGraphicsView* view)
  :  view_(view), info_files_(_auto_new(info_files_)),
     current_map_style_index_(-1), current_location_spot_(nullptr)
{
 //qmt_client_layer_base_ = view_->qmt_client_layer_base();
}


void Main_Window_Controller::load_incident_reports()
{
 QString path = QFileDialog::getOpenFileName(view_, "Select Incident Reports File",
   EXAMPLE_DATA_FOLDER);
 if(path.isEmpty())
   return;
 set_info_file("incidents", path);
}



void Main_Window_Controller::load_web_engine_view(QPoint pos, QUrl url)
{

 QMT_Web_Engine_View* wev = new QMT_Web_Engine_View(nullptr);

 QMT_Web_Engine_Page* wep = new QMT_Web_Engine_Page(nullptr);

 QObject::connect(wep, &QMT_Web_Engine_Page::urlChanged,[this](const QUrl &url){
  qDebug() << "browse:" << url.toString();
  //? check_url_patterns(url.toString().prepend("urlChanged!"));
 });

 QObject::connect(wep, &QMT_Web_Engine_Page::navRequest,[this](const QUrl &url){
  qDebug() << "request:" << url.toString();
  //? check_url_patterns(url.toString().prepend("navRequest!"));
 });


 QObject::connect(wep, &QMT_Web_Engine_Page::linkHovered,[](const QUrl &url){
  qDebug() << "H:" << url.toString();
 });

 QMT_My_Page* myp = new QMT_My_Page;
 QWebChannel* channel = new QWebChannel(wev);
 channel->registerObject(QStringLiteral("content"), myp);
 wep->setWebChannel(channel);

 wev->setPage(wep);

 wep->load(url);

 wev->move(pos);

 wev->show();

}


void Main_Window_Controller::track_incidents(r8 latitude, r8 longitude, s4 allow_duplicates)
{
 // EVENT_ID_CNTY		EVENT_DATE			EVENT_TYPE		LATITUDE	LONGITUDE TIMESTAMP

 u1 matches_size = 30;

// QVector<QPair<QVector<r8>, QStringList>> info;

 QMT_Client_Data_Set_Base* data_set = active_data_sets_.first()->make_new_unattached_child_data_set();

 u4 count = match_locations_in_info_file("incidents", data_set,
    latitude, longitude, matches_size, 3, 4, ' ', allow_duplicates);

 if(count == 0)
 {
  // //  we don't do anything if there are no matches
   //    (i.e., no matches within sufficient distance)
  delete data_set;
  return;
 }

 active_data_sets_.push(data_set);

// QString path = "/home/nlevisrael/gits/acle/lat-lon.txt";
// match_locations_in_text_file(path,
//    latitude, longitude, matches_size, 3, 4, ' ', info, allow_duplicates);

 if(!qmt_client_layer_base_->adopt_style("incident"))
 {
  qreal diamond_scale = 1.5;
  QPointF diamond_adj{0, 0};

  QPolygonF diamond;// = new QPolygonF;
  diamond << QPointF(-240, 110)*diamond_scale + diamond_adj;
  diamond << QPointF(240, 110)*diamond_scale + diamond_adj;
  diamond << QPointF(110, 240)*diamond_scale + diamond_adj;
  diamond << QPointF(110, -240)*diamond_scale + diamond_adj;
  diamond << QPointF(240, -110)*diamond_scale + diamond_adj;
  diamond << QPointF(-240, -110)*diamond_scale + diamond_adj;
  diamond << QPointF(-110, -240)*diamond_scale + diamond_adj;
  diamond << QPointF(-110, 240)*diamond_scale + diamond_adj;
  qmt_client_layer_base_->define_and_adopt_style("incident",
    "handle_incident_context_menu",
    {QColor(175, 104, 39)}, diamond,
    { {"select-margin", QVariant((r4)300.) }}); // 80, 105, 155
 }

 qmt_client_layer_base_->add_d0_marks(data_set);

}


void Main_Window_Controller::check_clear_data_layers(CircleObject* _spot)
{
 if(_spot)
 {
  active_data_sets_.pop();
  if(QMT_Client_Data_Set_Base* data_set = _spot->client_data_set_base())
  {
   if(data_set->current_bind_vector())
   {
    for(CircleObject* co : *data_set->current_bind_vector())
    {
     if(co)
       view_->scene()->removeObject(co);
     //co->setVisible(false);
    }
   }
   //?
   //?delete data_set;
  }
  _spot->setVisible(false);
  view_->scene()->removeObject(_spot);
  //?delete _spot;
 }

 //_spot

}


CircleObject* Main_Window_Controller::add_spot_location_marking(r8 latitude, r8 longitude)
{
 QPolygonF* qpf1 = new QPolygonF;
 (*qpf1) << QPointF(-20, 110);
 (*qpf1) << QPointF(20, 110);
 (*qpf1) << QPointF(40, 40);
 (*qpf1) << QPointF(110, 20);
 (*qpf1) << QPointF(110, -20);
 (*qpf1) << QPointF(40, -40);
 (*qpf1) << QPointF(20, -110);
 (*qpf1) << QPointF(-20, -110);
 (*qpf1) << QPointF(-40, -40);
 (*qpf1) << QPointF(-110, -20);
 (*qpf1) << QPointF(-110, 20);
 (*qpf1) << QPointF(-40, 40);

 QColor spot_clr = QColor(201, 159, 34);

 // QColor(201, 159, 34)

 CircleObject* result = new CircleObject(view_, 125, false, spot_clr);
 result->setLatitude(latitude);
 result->setLongitude(longitude);
 view_->scene()->addObject(result);
 result->set_ref(qpf1);

 return result;
}

void Main_Window_Controller::find_bus_stops(r8 latitude, r8 longitude, CircleObject* _spot)
{
 qDebug() << "lat = " << latitude;
 qDebug() << "lon = " << longitude;

 check_clear_data_layers(_spot);

 CircleObject* spot = add_spot_location_marking(latitude, longitude);

 current_location_spot_ = spot;

 spot->setFlags(MapGraphicsObject::ObjectIsSelectable);


 QObject::connect(spot, &CircleObject::selectedChanged, [spot]()
 {
  if(spot->isSelected())
    spot->setFlag(MapGraphicsObject::ObjectIsMovable);
  else
    spot->setFlag(MapGraphicsObject::ObjectIsMovable, false);
 });

  QObject::connect(spot, &CircleObject::posChanged, [spot]()
  {
   if(spot->isSelected())
     spot->move_increment();
  });

  QObject::connect(spot, &CircleObject::move_registered, [spot, this](const QPointF& pos)
  {
   qDebug() << "pos = " << pos;
   r8 lat = spot->latitude();
   r8 lon = spot->longitude();
   find_bus_stops(lat, lon, spot);
  });


 //    QString path = main_window_controller_->get_info_file("bus");  //"/home/nlevisrael/gits/acle/bus_data/stops.txt";
 static u1 stops_size = 20;

 //QVector<QPair<QVector<r8>, QStringList>> info;

 QMT_Client_Data_Set_Base* data_set = active_data_sets_.first()->make_new_unattached_child_data_set();
   //new QMT_Data_Set_Base;

 u4 count = match_locations_in_info_file("bus", data_set,
   latitude, longitude, stops_size, 4, 5, ',');

 if(count == 0)
 {
  // //  we don't do anything if there are no matches
   //    (i.e., no matches within sufficient distance)
  delete data_set;
  return;
 }

 data_set->bind_to_spot_location(spot);

 spot->set_client_data_set_base(data_set);


 active_data_sets_.push(data_set);

 if(!qmt_client_layer_base_->adopt_style("bus-stop"))
 {
  qreal diamond_scale = 2;
  QPointF diamond_adj{0, 0};

  QPolygonF diamond;// = new QPolygonF;
  diamond << QPointF(-20, 110)/diamond_scale + diamond_adj;
  diamond << QPointF(20, 110)/diamond_scale + diamond_adj;
  diamond << QPointF(110, 20)/diamond_scale + diamond_adj;
  diamond << QPointF(110, -20)/diamond_scale + diamond_adj;
  diamond << QPointF(20, -110)/diamond_scale + diamond_adj;
  diamond << QPointF(-20, -110)/diamond_scale + diamond_adj;
  diamond << QPointF(-110, -20)/diamond_scale + diamond_adj;
  diamond << QPointF(-110, 20)/diamond_scale + diamond_adj;
  qmt_client_layer_base_->define_and_adopt_style("bus-stop",
    "handle_bus_stop_context_menu",
    {QColor(80, 105, 155)}, diamond); // 80, 105, 155
    //? {QColor(201, 159, 34)}, diamond); // 80, 105, 155
 }
 qmt_client_layer_base_->add_d0_marks(data_set);

 view_->scene()->removeObject(spot);
 view_->scene()->addObject(spot);


}


void Main_Window_Controller::load_bus_data()
{
 QString path = QFileDialog::getOpenFileName(view_, "Select File (it should match \"stops.txt\")",
   EXAMPLE_DATA_FOLDER);
 if(path.isEmpty())
   return;
 set_info_file("bus", path);
}

void Main_Window_Controller::reset_map_style(QPoint qp)
{
 // //  1 is the index for OpenStreetMap in the french style ...
  //    (at least is is in the current Tile_Server_Select_Dialog
  //    setup.  I suppose in more polished code we'd have some
  //    kind of configuration to choose a default style)
 static constexpr int preferred_map_style_index = 1;

 if(current_map_style_index_ == -1)
   current_map_style_index_ = preferred_map_style_index;

 Tile_Server_Select_Dialog* tsd = new Tile_Server_Select_Dialog(current_map_style_index_);
 tsd->move(qp);

 QObject::connect(tsd, &Tile_Server_Select_Dialog::update_requested, [this](QDialog* dlg,
   Tile_Server_Select_Dialog::Summary summary)
 {
  qDebug() << "Host: %1\nUrl: %2\nAPI Key: %3"_qt
    .arg(summary.host)
    .arg(summary.url)
    .arg(summary.api_key);

  current_map_style_index_ = summary.index;

  QSharedPointer<MapTileSource> mts = view_->tileSource();

  mts->set_current_host(summary.host);

  mts->set_current_url(summary.url.replace("@@", summary.api_key));
   // mts->set_current_local_host(summary);

  mts->update_hosts();
  mts->update_host_cache();

  view_->force_reset();

  dlg->close();
 });

 tsd->show();
}


void Main_Window_Controller::deactivate_local_tile_server()
{
 QSharedPointer<MapTileSource> mts = view_->tileSource();
// mts->set_current_local_host({});
// mts->set_current_local_info_host({});
// mts->set_current_local_url({});
// mts->set_current_local_info_url({});
// mts->update_hosts();
 mts->set_current_local_host_status(-1);
 mts->update_local_host_status();
}


void Main_Window_Controller::_activate_local_tile_server(const QString* local_socket_flag)
{
 QSharedPointer<MapTileSource> mts = view_->tileSource();

 QString location = "nyc";
//? QString location = "kherson";

 mts->set_current_local_info_host("http://localhost:6600/qmt%1/rI~png/~tiles/%2/~osm-"_qt
   .arg(local_socket_flag? *local_socket_flag : "").arg(location));
 mts->set_current_local_host("http://localhost:6600/qmt%1/rS~png/~tiles/%2/~osm-"_qt
   .arg(local_socket_flag? *local_socket_flag : "").arg(location));
 mts->set_current_local_info_url("%1-%2-%3");
 mts->set_current_local_url("%1-%2-%3");
 mts->update_hosts();
}

void Main_Window_Controller::toggle_marking_outline_visibility()
{
 u4 count = 0;
 for(QMT_Client_Data_Set_Base* ds : active_data_sets_)
   ds->toggle_marking_outline_visibility(&count);

 if(count)
   view_->force_reset();
}


void Main_Window_Controller::load_single_file_data_set()
{
 QString infile = QFileDialog::getOpenFileName(nullptr, "Select File",
   EXAMPLE_DATA_FOLDER);

 QFileInfo qfi(infile);

 if(qfi.suffix() == "ntxh")
 {
  QMT_Client_Data_Set_Base* ds = active_data_sets_.first()->make_new_unattached_child_data_set();
  ds->load_ntxh_file(infile);
  ds->add_markings();
  if(ds->load_ok())
    active_data_sets_.push(ds);
 }
}

void Main_Window_Controller::show_llcoords(QPoint qp)
{
 QPointF ll = view_->mapToScene(qp);

 QString coords = "Latitude: %1, Longitude: %2"_qt.arg(ll.x()).arg(ll.y());

 QMessageBox* mbox = new QMessageBox(QMessageBox::Information, "Coordinates: ", coords);

 mbox->move(view_->mapToGlobal(qp));
 mbox->exec();

}

void Main_Window_Controller::llcoords_to_street_address(QPoint qp)
{
 QPointF ll = view_->mapToScene(qp);

 QMT_GIS_Utils::Result_Callbacks* cbs = new QMT_GIS_Utils::Result_Callbacks; // {};
 cbs->failure = [](QVariant, QString error_string)
 {
  qDebug() << error_string;
 };

 cbs->success = [ll, this, qp](QVariant qvar)
 {
  QList<QGeoLocation> reply_locations =
    qvar.value<QList<QGeoLocation>>();

  int length = reply_locations.length();
  if(length == 0)
  {
   QMessageBox::information(nullptr, "Geographic Location Lookup Error",
     "The lookup returned with no results.");
   return;
  }
  QGeoLocation loc1 = reply_locations.first();
  QGeoAddress address = loc1.address();
  QString address_string = "Coordinates: %1, %2\nCity: %3\n"
    "State: %4\nStreet: %5\nPostal Code: %6\n\nFull Text:\n\n%7"_qt
    .arg(ll.y()).arg(ll.x()).arg(address.city()).arg(address.state())
    .arg(address.street()).arg(address.postalCode()).arg(address.text());
  if(length == 1)
  {
   qDebug() << "Address length 1: " << address_string;

   QMessageBox* mbox = new QMessageBox(QMessageBox::Information,
     "Geographic Location Lookup Result",
     "The lookup for latitude %1, longitude %2 returned with one result, "
     "in %3, %4."_qt
       .arg(ll.x()).arg(ll.y()).arg(address.city()).arg(address.country()));
   mbox->setDetailedText(address_string);

   mbox->move(view_->mapToGlobal(qp));

   mbox->exec();
   mbox->deleteLater();
  }
  else
  {
   qDebug() << "Address length 2 or greater: " << address_string;

   QMessageBox* mbox = new QMessageBox(QMessageBox::Information,
     "Geographic Location Lookup Result",
     "The lookup for latitude %1, longitude %2 returned with %5 results. "
     "Here is the first, in %3, %4."_qt
       .arg(ll.x()).arg(ll.y()).arg(address.city()).arg(address.country()).arg(length));
   mbox->setDetailedText(address_string);

   mbox->exec();
   mbox->deleteLater();
  }

 };


 gis_utils_.get_street_address_from_ll(ll, *cbs);

}



//if(!infile.atEnd())
//  // // header
//  infile.readLine();

//while(!infile.atEnd())
//{
// QByteArray line = infile.readLine().simplified();
// QList<QByteArray> qbas = line.split(' ');
// if(qbas.length() < 6)
//  continue;
// QString event_id = QString::fromLatin1(qbas[0]);
// QString event_date_string = QString::fromLatin1(qbas[1]);
// //QDate event_date = QDate::fromString(QString::fromLatin1(qbas[1]), Qt::DateFormat::);
// QString event_type = QString::fromLatin1(qbas[2]);
// r8 latitude = qbas[3].toDouble();
// r8 longitude = qbas[4].toDouble();

// QDate event_date = QDate::fromString(event_date_string, "dd-MMMM-yy");

