
#include <QString>

#include <QLocalSocket>
#include <QLocalServer>

#include <QTcpSocket>
#include <QDataStream>

#include <QCoreApplication>

#include <QIODevice>


#include "qmt-server-response/qmt-server-response.h"

#include "qmt-utils/qmt-utils.hpp"


int main(int argc, char* argv[])
{
 QCoreApplication app(argc, argv);

 QLocalServer* qls = new QLocalServer;

 qDebug() << "Trying " << LOCAL_SOCKET_PATH;


 bool ok = qls->listen(LOCAL_SOCKET_PATH);

 if(ok)
   qDebug() << "\nok.  Listening ...\n";

 else
 {
  QAbstractSocket::SocketError se = qls->serverError();

   qDebug() << "not ok ..." << se;


 }

 qls->connect(qls, &QLocalServer::newConnection,
     [qls]()
 {
//  QString result = QString::fromLatin1(tcp_incoming_socket_.readAll());
//  qDebug() << "Incoming Local " << result;

  qDebug() << "New Local connection ";

  QLocalSocket* clientConnection = qls->nextPendingConnection();

//  clientConnection->write("ok");

  QObject::connect(clientConnection, &QTcpSocket::readyRead, [clientConnection]
  {
   qDebug() << "Reading ";

   QString uri = QString::fromLatin1(clientConnection->readAll());

   qDebug() << "uri = " << uri;


   QMT_Server_Response* qsr =  new QMT_Server_Response;
   qsr->handle_request_from_uri(uri);

   QByteArray response; // = result_map["content"].toLatin1();

   QDataStream qds(&response, QIODevice::WriteOnly);

   qds << *qsr;

   //qDebug() << "Incoming Local " << uri;

   qDebug() << "result length: " << response.length();

   clientConnection->write(response);
   clientConnection->flush();
   //?
   clientConnection->disconnectFromServer();
   clientConnection->close();
  });

 });



 return app.exec();
}

