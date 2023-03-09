
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_UDP_CONTROLLER__H
#define DHAX_UDP_CONTROLLER__H

#include <QUdpSocket>

#include <QTcpSocket>
#include <QTcpServer>

//#include <QHttpServer>

#include "accessors.h"

#include "global-types.h"

#include <QLocalServer>


class DHAX_Signal_Generator;

class DHAX_UDP_Controller
{
 QLocalServer socket_server_;
 //socketServer.setSocketOptions(QLocalServer::UserAccessOption);

 QUdpSocket* udp_outgoing_socket_;
 QUdpSocket udp_incoming_socket_;

 QTcpSocket tcp_incoming_socket_;
 QTcpServer tcp_server_;

 DHAX_Signal_Generator* signal_generator_;

public:

 DHAX_UDP_Controller();

 ACCESSORS__CONST_RGET(QUdpSocket ,udp_incoming_socket)
 ACCESSORS__GET(QUdpSocket* ,udp_outgoing_socket)

 ACCESSORS(DHAX_Signal_Generator* ,signal_generator)

 static void wrap_udp(QByteArray& qba, u1 msg_flags = 1);

 void check_init_outgoing_socket();
 void send_datagram(const QByteArray& qba);
 void wrap_and_send_datagram(QByteArray& qba, u1 msg_flags = 1);

};

#endif //  DHAX_UDP_CONTROLLER__H




