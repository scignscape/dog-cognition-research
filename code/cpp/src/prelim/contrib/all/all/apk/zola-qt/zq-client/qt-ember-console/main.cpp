
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "qh-web-view-dialog.h"


#include <QTcpServer>
#include <QMessageBox>



#include <QApplication>
#include <QDebug>
#include <QWebEngineView>
#include <QWebChannel>

#include "JsInterface.h"

#include "textio.h"

//QString qWebChannelJs()
//{
// static QString result;

// if(result.isEmpty())
// {
////  QFile apiFile(":/qtwebchannel/qwebchannel.js"); //load the API from the resources


//  QFile apiFile("/quasihome/nlevisrael/ember/qh-demo/public/raw/qwebchannel.js");

//  if(!apiFile.open(QIODevice::ReadOnly))
//      qDebug()<<"Couldn't load Qt's QWebChannel API!";

//  result = QString::fromLatin1(apiFile.readAll());

//  apiFile.close();
// }

////? qDebug() << "result = " << result;

// return result;

////    return R"DELIMITER(
////        // TODO INSERT JS code here
////    )DELIMITER";
//}

//#include "main.moc"

//auto main( int argn, char* argv[] )-> int
//{
//    QApplication app(argn, argv);
//    QWebEngineView browser;
//    browser.resize(QSize(800,600));

//    browser.show();
////    QString url = "http://localhost:%1/qh-link"_qt.arg(6401);
//    QString url = "http://localhost:%1/raw/temp.html"_qt.arg(6401);

//    browser.load(QUrl(url));

//    // .. SETUP HERE
//    QWebChannel channel;
//    JsInterface jsInterface;
//    browser.page()->setWebChannel(&channel);
//    channel.registerObject(QString("JsInterface"), &jsInterface);


//    QObject::connect(&browser, &QWebEngineView::loadFinished, [&browser](bool ok)
//    {
//        qDebug()<<"Load Finished " << ok;

//        // TEST CODE HERE
//        QString code = QStringLiteral(
//        R"DELIM(

//        var links = document.getElementsByTagName('a');
//        for ( var i=0; i<links.length; ++i)
//        {
//            links[i].style.backgroundColor = 'yellow';
//        };

//        )DELIM");
////?        browser.page()->runJavaScript(code, 42);

////?
//        browser.page()->runJavaScript(qWebChannelJs());

////?        QString js = qWebChannelJs();
////?  KA::TextIO::save_file("/quasihome/nlevisrael/ember/qh-demo/public/assets/images/jjs", js);

//        QString code2 = QStringLiteral(
//        R"DELIM(
//        window.webChannel = new QWebChannel(qt.webChannelTransport, function( channel)
//        {
//            var cpp = channel.objects.JsInterface;
//            cpp.log("Hello from JavaScript!");
//        });

//        )DELIM");
//        browser.page()->runJavaScript(code2);
//    });

//    return app.exec();
//}



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

  if(_midcut(".$", path))
  {
   qDebug() << "P = " << path;

   static QRegularExpression rx("(\\w+)\\s*\\(\\s*([\\d.-]+)\\s*,\\s*([\\d.-]+)\\s*\\)");
//   static QRegularExpression rx("(\\w+)\\(([\\d-]+),");

   QRegularExpressionMatch rxm = rx.match(path);

   if(rxm.hasMatch())
   {
    QString arg = rxm.captured(1);
    QString lat = rxm.captured(2);
    QString lon = rxm.captured(3);

    qDebug() << "arg = " << arg;
    qDebug() << "lat = " << lat;
    qDebug() << "lon = " << lon;

    dlg.wev()->page()->runJavaScript("run_popup('%1, %2', %1, %2);"_qt.arg(lat).arg(lon));

   }

   return;
  }

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
