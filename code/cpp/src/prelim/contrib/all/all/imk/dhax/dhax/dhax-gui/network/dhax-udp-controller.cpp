
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-udp-controller.h"

#include "dhax-signal-generator.h"

#include <QLocalSocket>

#include <QNetworkReply>


DHAX_UDP_Controller::DHAX_UDP_Controller()
  :  udp_outgoing_socket_(nullptr), signal_generator_(nullptr)
{
 //socket_server_.listen("/home/nlevisrael/gits/osm/inner-system/socket-files/qt-test/renderd.sock");

#ifdef HIDE
 socket_server_.listen("/home/nlevisrael/gits/osm/inner-system/run/renderd/renderd.sock");


 socket_server_.connect(&socket_server_, &QLocalServer::newConnection,
     [this]()
 {
//  QString result = QString::fromLatin1(tcp_incoming_socket_.readAll());
//  qDebug() << "Incoming Local " << result;

  qDebug() << "New Local connection ";
  QLocalSocket* clientConnection = socket_server_.nextPendingConnection();
  //?QObject::connect(clientConnection, &QAbstractSocket::disconnected,
  //?  clientConnection, &QObject::deleteLater);
  clientConnection->write("AOK");
  QObject::connect(clientConnection, &QTcpSocket::readyRead, [clientConnection, this]
  {
   QString result = QString::fromLatin1(clientConnection->readAll());
   qDebug() << "Incoming Local " << result;

   clientConnection->write(R"(HTTP/1.1 200 OK
                           Content-Length: 13
                           Content-Type: text/plain; charset=utf-8

                           Hello World!)"
                           );
   clientConnection->flush();
   //?clientConnection->disconnectFromHost();
   clientConnection->close();

//   QByteArray received;
//   while(clientConnection->bytesAvailable())
//   {
//    received.append(clientConnection->readAll());
//   }
  });

 });
#endif


 int tcp_shost = 65432;


 qDebug() << "Incoming server bound to host " << tcp_shost;
 bool ok  = tcp_server_.listen(QHostAddress::LocalHost, tcp_shost);
 if(!ok)
    qDebug() << "listen failed";


 tcp_server_.connect(&tcp_server_, &QTcpServer::newConnection,
     [this]()
 {
  qDebug() << "New connection ";
  QTcpSocket* clientConnection = tcp_server_.nextPendingConnection();
  QObject::connect(clientConnection, &QAbstractSocket::disconnected,
    clientConnection, &QObject::deleteLater);
//  clientConnection->write("AOK");
  QObject::connect(clientConnection, &QTcpSocket::readyRead, [clientConnection, this]
  {
   QString result = QString::fromLatin1(clientConnection->readAll());

   if(result.startsWith("GET "))
   {
    int index = result.indexOf("geojson");
    if(index != -1)
    {
     QString new_url = result.mid(4, index + 3)
       .prepend("http://planninglabs.carto.com"); // geojson = 7; 4 + 7 - 3

//     new_url = "http://glukkazan.github.io/";

     qDebug() << "Incoming URL " << new_url;

     QNetworkRequest req;
     req.setUrl(QUrl(new_url));

     static QNetworkAccessManager* qnam = new QNetworkAccessManager;

     QNetworkReply* reply = qnam->get(req);

     QObject::connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
      [reply](QNetworkReply::NetworkError code)
     {
      qDebug() << "Network error: " << code << "\n";
      reply->deleteLater();
     });

     QObject::connect(reply, &QNetworkReply::finished, [reply, clientConnection]()
     {
      qDebug() << "Finished: ";
      QByteArray qba = reply->readAll();

      qDebug() << "\n\n qba = " << qba << "\n\n";

      reply->deleteLater();

      QList<QNetworkReply::RawHeaderPair> headers = reply->rawHeaderPairs();

      QByteArray hdr;
      hdr.append("HTTP/1.1 200 OK\n");

      for(QNetworkReply::RawHeaderPair pr : headers)
      {
       if(pr.first == "Transfer-Encoding")
         continue;
       hdr.append(pr.first);
       hdr.append(": ");
       hdr.append(pr.second);
       hdr.append("\n");
      }
      hdr.append("\n");

      qba.prepend(hdr);

//      Date: Wed, 15 Feb 2023 14:59:34 GMT\nContent-Type: application/json; charset=utf-8\nTransfer-Encoding: chunked\nConnection: keep-alive\nAccess-Control-Allow-Origin: *\nAccess-Control-Allow-Headers: *\nAccess-Control-Expose-Headers: *\nCarto-User: planninglabs\nCarto-User-Id: 41182a72-28d0-43e5-9a39-aeed81a361ad\nCarto-Rate-Limit-Limit: 81\nCarto-Rate-Limit-Remaining: 80\nCarto-Rate-Limit-Reset: 0\nvary: Accept-Encoding, Authorization\nCache-Control: no-cache,max-age=31536000,must-revalidate,public\nSurrogate-Key: t:6zE4UE\nLast-Modified: Tue, 10 Jan 2023 02:18:13 GMT\nContent-Disposition: attachment; filename=cartodb-query.geojson; modification-date=\"Wed, 15 Feb 2023 14:59:34 GMT\";\nX-Varnish: 24471357\nAge: 0\nX-Cache: MISS\nContent-Encoding: gzip\n\n

//      qba.prepend(R"(HTTP/1.1 200 OK
//Date: Wed, 15 Feb 2023 05:48:18 GMT
//Content-Type: application/json; charset=utf-8
//Connection: keep-alive
//Vary: Accept-Encoding
//Access-Control-Allow-Origin: *
//)");

//      qba.prepend("HTTP/1.1 200 OK\n\n");

//         clientConnection->write(R"(HTTP/1.1 200 OK
//Content-Length: 13
//Content-Type: text/plain; charset=utf-8

//Hello World!)");

//      clientConnection->write(R"(HTTP/1.1 200 OK
//                              Content-Length: %1
//                              Content-Type: text/plain; charset=utf-8)"_qt.arg(qba.size()).toLatin1());

         clientConnection->write(qba);
         clientConnection->flush();
         clientConnection->disconnectFromHost();
         clientConnection->close();

     });

     qDebug() << "Reply processing ... ";



    }
   }

//   qDebug() << "Incoming TCP " << result;

//   clientConnection->write(R"(HTTP/1.1 200 OK
//                           Content-Length: 13
//                           Content-Type: text/plain; charset=utf-8

//                           Hello World=)"
//                           );
//   clientConnection->flush();
//   clientConnection->disconnectFromHost();
//   clientConnection->close();

  });
 });

// https://planninglabs.carto.com/api/v2/sql?q=SELECT%20*%20FROM%20(%20SELECT%20ST_CollectionExtract(ST_Collect(the_geom),3)%20as%20the_geom,%20zonedist,%20zonedist%20as%20id%20FROM%20dcp_zoning_districts%20GROUP%20BY%20zonedist%20)%20a%20WHERE%20id%20=%20%27R2A%27&format=geojson
#ifdef HIDE
 int tcp_shost = 1237;


 qDebug() << "Incoming server bound to host " << tcp_shost;
 bool ok  = tcp_server_.listen(QHostAddress::LocalHost, tcp_shost);
 if(!ok)
    qDebug() << "listen failed";


 tcp_server_.connect(&tcp_server_, &QTcpServer::newConnection,
     [this]()
 {
  qDebug() << "New connection ";
  QTcpSocket* clientConnection = tcp_server_.nextPendingConnection();
  QObject::connect(clientConnection, &QAbstractSocket::disconnected,
    clientConnection, &QObject::deleteLater);
  clientConnection->write("AOK");
  QObject::connect(clientConnection, &QTcpSocket::readyRead, [clientConnection, this]
  {
   QString result = QString::fromLatin1(clientConnection->readAll());
   qDebug() << "Incoming TCP " << result;

   clientConnection->write(R"(HTTP/1.1 200 OK
                           Content-Length: 13
                           Content-Type: text/plain; charset=utf-8

                           Hello World=)"
                           );
   clientConnection->flush();
   clientConnection->disconnectFromHost();
   clientConnection->close();

//   QByteArray received;
//   while(clientConnection->bytesAvailable())
//   {
//    received.append(clientConnection->readAll());
//   }
  });

//    QByteArray qba(512, ' ');
//    tcp_incoming_socket_.read(qba.data(), 512);

//    qDebug() << "Incoming TCP " << qba;

    //signal_generator_->emit_received_datagram(qba);
    //read_udp_socket(qba);
 });



 int tcp_host = 1357;

 qDebug() << "Incoming socket bound to host " << tcp_host;
 bool bok  = tcp_incoming_socket_.bind(QHostAddress::LocalHost, tcp_host);
 if(!bok)
    qDebug() << "bind failed";

 tcp_incoming_socket_.connect(&tcp_incoming_socket_, &QTcpSocket::readyRead,
     [this]()
 {
  QString result = QString::fromLatin1(tcp_incoming_socket_.readAll());
  qDebug() << "Incoming TCP " << result;
//    QByteArray qba(512, ' ');
//    tcp_incoming_socket_.read(qba.data(), 512);

//    qDebug() << "Incoming TCP " << qba;

    //signal_generator_->emit_received_datagram(qba);
    //read_udp_socket(qba);
 });

 int host = 1234;
 qDebug() << "Incoming socket bound to host " << host;
 udp_incoming_socket_.bind(QHostAddress::LocalHost, host);

 udp_incoming_socket_.connect(&udp_incoming_socket_, &QUdpSocket::readyRead,
   [this]()
 {
  QByteArray qba(512, ' ');
  udp_incoming_socket_.readDatagram(qba.data(), 512);

  qDebug() << "Incoming " << qba;

  signal_generator_->emit_received_datagram(qba);
  //read_udp_socket(qba);
 });

#endif
}

void DHAX_UDP_Controller::send_datagram(const QByteArray& qba)
{
 check_init_outgoing_socket();
 udp_outgoing_socket_->writeDatagram(qba, QHostAddress::LocalHost, 1235);
}

void DHAX_UDP_Controller::check_init_outgoing_socket()
{
 if(udp_outgoing_socket_)
  return;

 int host = 1235;
 udp_outgoing_socket_ = new QUdpSocket;
 qDebug() << "Outgoing socket bound to host " << host;
 udp_outgoing_socket_->bind(QHostAddress::LocalHost, host);
}

void DHAX_UDP_Controller::wrap_and_send_datagram(QByteArray& qba, u1 msg_flags)
{
 wrap_udp(qba, msg_flags);
 send_datagram(qba);
}


void DHAX_UDP_Controller::wrap_udp(QByteArray& qba, u1 msg_flags)
{
 u2 sz = qba.size();
 u1 sz0 = sz & 255;
 u1 sz1 = sz >> 8;

 sz1 |= (msg_flags << 2);

 qba.prepend(sz0);
 qba.prepend(sz1);
}
