
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "rdsc-qh/qh-web-view-dialog.h"

#include "game/game-driver.h"

#include "rdsc-2d/mat2d.templates.h"
#include "rdsc-1d/vec1d.h"

#include "kans.h"

#include <QJsonArray>

#include <QNetworkReply>

USING_KANS(RdSC)

int main1(int argc, char *argv[])
{

// Game_Board board;
//#define folder "/home/nlevisrael/gits/dcr-wip/qmt/server-files/public"
////? board.debug_board("/home/nlevisrael/gits/dcr-wip/game/" "test.txt");
// board.to_svg(folder "/board-svg", folder "/board.svg");

// return 0;
// QApplication qapp(argc, argv);
// QH_Web_View_Dialog dlg("file:///home/nlevisrael/gits/dcr-wip/qmt/server-files/public/test.html");

// dlg.show();

// return qapp.exec();
}


int main(int argc, char *argv[])
{
 Game_Driver driver;

  // // //? board.debug_board("/home/nlevisrael/gits/dcr-wip/game/" "test.txt");
 #define folder "/home/nlevisrael/gits/dcr-wip/qmt/server-files/public"
 driver.board().to_svg(folder "/board-svg", folder "/board.svg");


  // return 0;
 QApplication qapp(argc, argv);
 QH_Web_View_Dialog dlg("http://localhost:6600/test60.html");

 driver.start_game(dlg);

 dlg.set_js_callback([&driver, &dlg](QH_Web_View_Dialog* _dlg, QString key, const QJsonValue& msg)
 {  
  qDebug() << "key = " << key;

  QString el_id;
  if(msg.isArray())
    el_id = msg.toArray().first().toString();
  else
    el_id = msg.toString();

  if(key == "position-clicked")
    driver.handle_position_clicked(*_dlg, el_id);

  else if(key == "token-clicked")
    driver.handle_token_clicked(*_dlg,  el_id);

  else if(key == "position-context-menu")
  {
   QPoint qp(msg.toArray().at(1).toInt(), msg.toArray().at(2).toInt());
   //QPoint qp1(msg.toArray().at(3).toInt(), msg.toArray().at(4).toInt());

   //   u2 x = msg.toArray().at(1).toInt();
//   u2 y = msg.toArray().at(2).toInt();
   qDebug() << "pos id = " <<  el_id << " qp = " << qp << "ey = " << msg.toArray().at(3).toInt()
            << " pY = " << msg.toArray().at(4).toInt() << " == " << qp.y() + msg.toArray().at(4).toInt();

//?   QMenu* menu = new QMenu;
//?   menu->addAction("test1");
//?   menu->addAction("test2");

   QPoint np = dlg.map_point_for_context_menu(qp);
   qDebug() << "np = " << np;
//?   menu->popup(np);
  }

  else if(key == "token-context-menu")
  {
   u2 x = msg.toArray().at(1).toInt();
   u2 y = msg.toArray().at(2).toInt();
   qDebug() << "token id = " <<  el_id << " x = " << x << " y = " << y;
  }

 });

   //"file:///home/nlevisrael/gits/dcr-wip/qmt/server-files/public/test.html");

 dlg.show();

 dlg.resize(1000, 810);

 return qapp.exec();
}



int main2(int argc, char *argv[])
{
QApplication qapp(argc, argv);
  QNetworkRequest qnr;
  qnr.setUrl(QUrl(
    "http://localhost:6600/qmt-l/rs~svg/board"));

  QNetworkAccessManager qnam;

  QEventLoop qel;

  QNetworkReply* reply = qnam.get(qnr);

  QObject::connect(reply, &QNetworkReply::finished, [reply, &qel]()
  {
   QByteArray qba = reply->readAll();
   qDebug() << "qba = " << qba;

   qel.exit();
  });

  qel.exec();

  qapp.exit();
}


