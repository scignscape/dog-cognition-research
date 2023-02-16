
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include <QString>

#include <QFile>

#include <QDebug>


void qlog(QString msg)
{
 static int count = 0;

 QFile outfile(ALACARTE_QLOG_FILE);

 int ok = outfile.open(QIODevice::Append | QIODevice::Text);

 if(!ok)
   qDebug() << "Open " << ALACARTE_QLOG_FILE << "failed; " << outfile.errorString();


 if(count == 0)
 {
  outfile.resize(0);
 }

 ++count;

 QString qmsg = QString("%1. %2").arg(count).arg(msg);
 outfile.write(qmsg.toLatin1());
 outfile.flush();

}
