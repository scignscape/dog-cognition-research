

//?#include <QFile>

#include "httpd.h"

#include <syslog.h>

int qmt_tile_handler_dirty(request_rec *r)
{

}



void log_comments(const char* msg)
{
 syslog(LOG_INFO, "MSG: %s", msg);


#ifdef HIDE
 static int count = 0;

 QFile outfile("/home/nlevisrael/gits/osm/mod-tile/qt-pro/qmt/msg.txt");

 int ok = outfile.open(QIODevice::ReadWrite | QIODevice::Text);
 if(!ok)
   return;

 if(count == 0)
 {
  outfile.resize(0);
 }

 ++count;

 QString qmsg = QString("%1. %2").arg(count).arg(QString::fromLatin1(msg));
 outfile.write(qmsg.toLatin1());

#endif //def HIDE
}
