
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qmt-client-context-menu-handler.h"

#include "qmt-client-layer.h"

//#include "MapGraphicsView.h"

#include "global-types.h"

#include <QMessageBox>

#include <QGeoServiceProvider>
#include <QGeoCodingManager>
#include <QGeoCoordinate>

#include <QGeoCodeReply>

#include <QDebug>

#include "MapGraphicsView.h"

#include "CircleObject.h"

#include "qmt/main-window-controller.h"

#include <QMenu>


QMT_Client_Context_Menu_Handler::QMT_Client_Context_Menu_Handler(MapGraphicsView* view)
  :  QMT_Client_Context_Menu_Handler_Base(view)
{
}


QPoint QMT_Client_Context_Menu_Handler::map_event_pos_to_global(
  QGraphicsSceneContextMenuEvent* event, MapGraphicsObject* mgo)
{
 QPoint pos = event->pos().toPoint() + mgo->map_pos_to_view();
 return view_->mapToGlobal(pos);
}


void QMT_Client_Context_Menu_Handler::handle_context_menu_on_mgo
  (QGraphicsSceneContextMenuEvent* event, MapGraphicsObject* mgo)
{
 if(!mgo)
   // // in case it's deleted for some reason before the menu item is selected
   return;


 QVector<QVariant> qvv = mgo->client_data().value<QVector<QVariant>>();

 QStringList qsl;

 if(!qvv.isEmpty())
   qsl = qvv.first().value<QStringList>();

 if(qsl.isEmpty())
 {
  QMenu* menu = new QMenu;
  menu->addAction("code %1"_qt.arg(mgo->index_code()));

  QPoint vpos = event->pos().toPoint() + mgo->map_pos_to_view();
  menu->popup(vpos);

  return;
 }

 QString context_menu_handler = qsl.first();
 if(context_menu_handler.isEmpty())
   context_menu_handler = QMT_Client_Layer::get_context_menu_handler_name(mgo);
 if(context_menu_handler.isEmpty())
 {
  qDebug() << "Unknown context menu handler slot requested (no name provided).";
  qDebug() << " The style name was " << QMT_Client_Layer::get_style_params_name(mgo);
  return;
 }
 bool ok = QMetaObject::invokeMethod(this, context_menu_handler.toLatin1(),
   Qt::DirectConnection,
   Q_ARG(QGraphicsSceneContextMenuEvent* ,event),
   Q_ARG(MapGraphicsObject* ,mgo));
 if(!ok)
   qDebug() << "Unknown context menu handler slot requested: " << context_menu_handler;
}


void QMT_Client_Context_Menu_Handler::handle_incident_context_menu(QGraphicsSceneContextMenuEvent* event,
  MapGraphicsObject* mgo)
{
// QPoint pos = mgo->map_pos_to_view() + event->pos().toPoint();
 QPoint vpos = map_event_pos_to_global(event, mgo); //mgo->map_pos_to_view() + event->pos().toPoint();

 QPointF epos = event->pos();

 QMenu* menu = new QMenu;

 QVector<QVariant> vv = mgo->client_data().value<QVector<QVariant>>();

 QStringList qsl =
   vv.first().value<QStringList>();

 s4 incident_count = (s4) vv.value(2).toDouble();

 qDebug() << "incident count = " << incident_count;

 //QVector<

 QString event_date_string = qsl.value(2);
 QDate event_date = QDate::fromString(event_date_string, "dd-MMMM-yyyy");
 QString incident_category = qsl.value(3);

 menu->addAction("Get Incident Info", [mgo, qsl, event_date, incident_count]
 {
  QString timestamp = qsl.value(4);

  QDateTime qdt = QDateTime::fromSecsSinceEpoch(timestamp.toULong());

  QString incident_count_msg;
  if(incident_count > 1)
    incident_count_msg = QString("\n * The data also reports %1 earlier incidents.\n"_qt.arg(incident_count - 1));
  else if(incident_count < -1)
    incident_count_msg = QString("\n * The data also reports %1 later incidents.\n"_qt.arg(-1 - incident_count));


  QString msg = "ID# %1\n\nUploaded %2\n%3\nLatitude: %4\nLongitude: %5"_qt
    .arg(qsl.value(1)).arg(qdt.toString("dddd, MMMM dd, yyyy (hh:mm:ss)"))
    .arg(incident_count_msg).arg(mgo->latitude()).arg(mgo->longitude());

  QMessageBox* mbox = new QMessageBox(QMessageBox::Information,
    "Incident Info",
    "%1 on %2"_qt
      .arg(qsl.value(3)).arg(event_date.toString("dddd, MMMM dd, yyyy"))); // ll.x()).arg(ll.y()).arg(address.city()).arg(address.country()));
  mbox->setDetailedText(msg);

  mbox->show();

 });

 menu->addAction("Search NPR by incident date (%1)"_qt
   .arg(event_date.toString("M/d/yy")), [this, epos, event_date]
 {
  QString url = "https://www.npr.org/search?query="
   "russia-ukraine-war-what-happened-today-%1-%2"_qt
//    .arg(event_date.year()).arg(event_date.toString("MM"))
//    .arg(event_date.toString("dd"))
    .arg(event_date.toString("MMMM"))
    .arg(event_date.toString("dd"));

  qDebug() << "URL = " << url;

  view_->main_window_controller()->load_web_engine_view(
    view_->mapToGlobal(epos.toPoint()), QUrl(url));
 });

 menu->addAction("Search Google by incident date/category (%1)"_qt
   .arg(incident_category), [this, epos, incident_category, event_date]
 {
  QString url = "https://www.google.com/search?q="
   "\"ukraine\"+\"%1\"+\"%2+%3+%4\""_qt.arg(incident_category)
//    .arg(event_date.year()).arg(event_date.toString("MM"))
//    .arg(event_date.toString("dd"))
    .arg(event_date.toString("MMMM"))
    .arg(event_date.toString("dd"))
    .arg(event_date.year())
    ;

  qDebug() << "URL = " << url;

  view_->main_window_controller()->load_web_engine_view(
    view_->mapToGlobal(epos.toPoint()), QUrl(url));
 });

 menu->popup(vpos);
}



void QMT_Client_Context_Menu_Handler::handle_bus_stop_context_menu(QGraphicsSceneContextMenuEvent* event,
  MapGraphicsObject* mgo)
{
 QPoint pos = mgo->map_pos_to_view() + event->pos().toPoint();

 QMenu* menu = new QMenu;
 menu->addAction("Get Stop Info", [mgo]
 {
  QStringList qsl = mgo->client_data().value<QVector<QVariant>>()
    .first().value<QStringList>();
  qDebug() << "ON: " << qsl;

  QString msg = "Code %1\n\n%2\n\nLatitude: %3\nLongitude: %4"_qt
    .arg(qsl.value(2)).arg(qsl.value(3).replace('"', ""))
    .arg(mgo->latitude()).arg(mgo->longitude());

  QMessageBox* mbox = new QMessageBox(QMessageBox::Information,
    "Bus Stop Info",
    "For Stop #%1"_qt
      .arg(qsl.value(1))); // ll.x()).arg(ll.y()).arg(address.city()).arg(address.country()));
  mbox->setDetailedText(msg);

  mbox->show();

 });

 menu->popup(view_->mapToGlobal(pos));

// pos += event->pos();

// qDebug() << "epos = " << pos;


}

