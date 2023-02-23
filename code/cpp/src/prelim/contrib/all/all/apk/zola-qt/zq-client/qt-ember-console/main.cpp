
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "qh-web-view-dialog.h"


#include <QTcpServer>
#include <QMessageBox>



int main(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

 QH_Web_View_Dialog dlg(nullptr);

#ifdef HIDE

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
//?
#endif


 dlg.set_url_changed_callback([&dlg](QUrl url)
 {
  qDebug() << "url = " << url;
 });

 dlg.set_qh_link_request_callback([&dlg](const
   QUrl& url, const QPoint pos, const QSize window_size,
   QString path, QWebEnginePage::NavigationType navtype)
 {
  QString navtype_string;

  switch(navtype)
  {
#define TEMP_MACRO(x) \
  case QWebEnginePage::NavigationType##x: \
    navtype_string = "(QWebEnginePage::NavigationType)" #x; break; \

  TEMP_MACRO(LinkClicked)
  TEMP_MACRO(Typed)
  TEMP_MACRO(FormSubmitted)
  TEMP_MACRO(BackForward)
  TEMP_MACRO(Reload)
  TEMP_MACRO(Redirect)
  TEMP_MACRO(Other)

#undef TEMP_MACRO
  }



  QMessageBox* mbox = new QMessageBox(QMessageBox::Information,
    "Embedded Ember Monitor",
    "Received Navigation Request: %1                                                      \n"
    "Click \"details\" for all available data."_qt
      .arg(path));
  mbox->setDetailedText(R"(Url: %1
Fragment: %2
Query: %3
Navigation Type: %4
Window Position: %5, %6
Window Size: %7, %8)"_qt
  .arg(url.toString())
  .arg(url.fragment())
  .arg(url.query(QUrl::FullyDecoded))
  .arg(navtype_string)
  .arg(pos.x()).arg(pos.y())
  .arg(window_size.width()).arg(window_size.height())
 );

  mbox->exec();
  mbox->deleteLater();

  //qDebug() << "url = " << url;
 });





// dlg.connect(&dlg, &qh_Web_View_Dialog::zoom_or_coordinates_changed, [&w](r8 z, r8 lat, r8 lon)
// {
//  qDebug() << "z = " << z << "lat = " << lat << " long = " << lon;

//  w.center_on(lon, lat, (u1) z + 2);
// });

 dlg.show();



 return qapp.exec();
}
