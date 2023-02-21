
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "zq-client/zq-web-view-dialog.h"

#include "qmt-client/main-window.h"

#include "zq-client/zq-cross-map-coords.h"

#include "qmt-client/lanternfly/lanternfly-frame.h"

#include "qmt-client/ses/e-designation-dialog.h"


#include <QTcpServer>
#include <QMessageBox>



int main(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

 ZQ_Web_View_Dialog dlg(nullptr);

//?#ifdef HIDE

 QTcpServer* tcp_server = new QTcpServer();
 QMap<qintptr, QByteArray>* temps = new QMap<qintptr, QByteArray>();

 int port = 4202;

 QString waiting_message;
 if (!tcp_server->listen(QHostAddress::LocalHost, port))
 {
  QMessageBox::critical(nullptr, "TCP Initialization Failed",
                         QString("Could not use port: %1.")
                         .arg(tcp_server->errorString()));
 }
 else
 {
  waiting_message = QString("Using IP: %1\nport: %2\n\n")
     .arg(tcp_server->serverAddress().toString()).arg(tcp_server->serverPort());

  qDebug() << waiting_message;
//  QMessageBox::information(nullptr, "TCP is Started",
//                            QString(waiting_message));
 }

 Lanternfly_Main_Window w;


 QObject::connect(tcp_server, &QTcpServer::newConnection, [tcp_server, temps, &w]
 {
  QTcpSocket* clientConnection = tcp_server->nextPendingConnection();
  QObject::connect(clientConnection, &QAbstractSocket::disconnected,
    clientConnection, &QObject::deleteLater);
  clientConnection->write("OK");
  QObject::connect(clientConnection, &QTcpSocket::readyRead, [clientConnection, temps, &w]
  {
   qintptr sd = clientConnection->socketDescriptor();
   QByteArray received;
   while(clientConnection->bytesAvailable())
   {
    received.append(clientConnection->readAll());
   }
   qDebug() << "received = " << received;

   if(received.startsWith("GET "))
   {

    received = received.mid(4);
    s4 index = received.indexOf(' ');
    if(index != -1)
    {
     received = received.left(index);
     received.prepend("https://planninglabs.carto.com");
     w.process_api_request(received);
    }
   }


  });
 });
//?#endif

 w.lanternfly_frame()->set_current_url(dlg.initial_url());

 w.show();

// "http://localhost:4201/about?layer-groups=%5B%22building-footprints%22%2C%22commercial-overlays%22%2C"


 dlg.set_info_url_changed_callback([&dlg](QString url_string)
 {
  QUrl url(url_string);
  QString fragment = url.fragment();
  QString query = url.query(QUrl::ComponentFormattingOption::FullyDecoded);
  QString path = url.path();

  qDebug() << " +---- url = " << url;
  qDebug() << " +---- query = " << query;
  qDebug() << " +---- fragment = " << fragment;
  qDebug() << " +---- path = " << path;

  QString cut = "/l/";

  if(path.startsWith(cut))
    path = path.mid(cut.size());

  cut = "e-designation/";

  QString ed_number;
  QString zd_number;

  if(path.startsWith(cut))
    ed_number = path.mid(cut.size());

  else
  {
   cut = "zoning-district/";
   if(path.startsWith(cut))
     zd_number = path.mid(cut.size());
  }

  if(!ed_number.isEmpty())
  {
   E_Designation_Dialog* edd = new E_Designation_Dialog(&dlg, path);
   edd->show();
  }

  if(!zd_number.isEmpty())
  {
   QString urls = url_string;
   urls.replace("http://localhost:4201", "https://planninglabs.carto.com");
   urls.replace(' ', '_');
//   qDebug() << urls;
  }
 });


 dlg.set_zoom_or_coordinates_changed_callback([&w](r8 z, r8 lat, r8 lon, QString url_string)
 {
//  w.lanternfly_frame()->set_current_url("");
//  w.lanternfly_frame()->set_current_url(url + "|||||||||||||||||||||||||||||");

  QUrl url(url_string);
  QString fragment = url.fragment();
  QString query = url.query(QUrl::ComponentFormattingOption::FullyDecoded);

  QString str = url.adjusted(
    QUrl::UrlFormattingOption::RemoveQuery | QUrl::UrlFormattingOption::RemoveFragment).toString();

  str += "?...#" + fragment;

  w.lanternfly_frame()->set_current_url(str);

  qDebug() << "z = " << z << "lat = " << lat << " long = " << lon;
  w.center_on(lon, lat, (u1) z + 2);


 });

 dlg.set_mark_location_callback([&w](const ZQ_Cross_Map_Coords& coords)
 {
  qDebug() << "z = " << coords.zoom << "lat = " << coords.latitude
           << " long = " << coords.longitude
           << " gpos = " << coords.global_window_coords
           << " lpos = " << coords.local_window_coords;

  w.mark_coordinates(coords); //.local_window_coords.toPoint());
 });


// dlg.connect(&dlg, &ZQ_Web_View_Dialog::zoom_or_coordinates_changed, [&w](r8 z, r8 lat, r8 lon)
// {
//  qDebug() << "z = " << z << "lat = " << lat << " long = " << lon;

//  w.center_on(lon, lat, (u1) z + 2);
// });

 dlg.show();



 return qapp.exec();
}
