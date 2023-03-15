
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "rdsc-qh/qh-web-view-dialog.h"

#include "game/game-board.h"

#include "rdsc-2d/mat2d.templates.h"
#include "rdsc-1d/vec1d.h"

#include "kans.h"


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

 Game_Board board;
//#define folder "/home/nlevisrael/gits/dcr-wip/qmt/server-files/public"
////? board.debug_board("/home/nlevisrael/gits/dcr-wip/game/" "test.txt");
// board.to_svg(folder "/board-svg", folder "/board.svg");

// return 0;
 QApplication qapp(argc, argv);
 QH_Web_View_Dialog dlg("http://localhost:6600/test.html");

 dlg.set_js_callback([&board](QH_Web_View_Dialog* _dlg, QString key, const QJsonValue& msg)
 {
  QString pos_id = msg.toString();

  Game_Position* gp = board.get_game_position_by_label_code(pos_id);

  if(gp)
  {
   u2 r = gp->position_row();
   u2 c = gp->position_column();

   u1 x = c * 100, y = r * 100;
   QString id = "token-s4";

   //runJavaScript("position_token('%1', %2, %3);"_qt.arg(id).arg(x).arg(y));

  _dlg->run_js_in_current_web_page("position_token('%1', %2, %3);"_qt.arg(id).arg(x).arg(y));

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


