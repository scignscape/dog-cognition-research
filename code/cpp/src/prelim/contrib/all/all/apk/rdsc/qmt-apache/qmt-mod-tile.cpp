

//?
#include <QFile>
#include <QDateTime>

#include "httpd.h"
#include "http_config.h"

#include "gen_tile.h"


#include "mod_tile.h"

#include "qmt-utils/qmt-utils.h"
#include "qmt-utils/qmt-utils.hpp"


#ifdef HIDE
#include <syslog.h>


extern "C" void log_comments(const char* msg)
{
 syslog(LOG_INFO, "c++/qt/ff: %s", msg);


//#ifdef HIDE
 static int count = 0;

 QFile outfile("/quasihome/nlevisrael/osm/mod-tile/qt-pro/qmt/msg.txt");

 int ok = outfile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
 if(!ok)
 {
  QString errMsg = outfile.errorString();
  syslog(LOG_INFO, "?: %s", errMsg.toStdString().c_str());
  return;
 }

 if(count == 0)
 {
  //outfile.resize(0);
 }

 ++count;

 QString qmsg = QString("(%1) %2. %3")
   .arg(QDateTime::currentDateTime().toString()).arg(count).arg(QString::fromLatin1(msg));
 outfile.write(qmsg.toLatin1());

 outfile.flush();

//#endif //def HIDE
}

extern "C" void log_comments_with_value(const char* msg, int i)
{
 QString qmsg = QString::fromLatin1(msg);
 qmsg.replace('@', QString("%1").arg(i));
 log_comments(qmsg.toLatin1());
}


extern "C"
void log_comments_kv(const char* k, const char* v)
{
 QString qsprdata = QString("%1 %2\n").arg(QString::fromLatin1(k)).arg((QString::fromLatin1(v)));

 log_comments(qsprdata.toLatin1());

}

extern "C"
void log_pointer_raw_value(const char* name, void* v)
{
// char sprdata[10];
// sprintf(sprdata, "rdata: %lu\n", (size_t) rdata);

// log_comments(sprdata);

 QString qsprdata = QString("%1 %2\n").arg(QString::fromLatin1(name)).arg((size_t) v);

 log_comments(qsprdata.toLatin1());

}


#endif //def HIDE

static int qmt_request_tile(request_rec* r, protocol* cmd, int renderImmediately)
{

}


// http://localhost:1251/tiles/renderd-example/9/297/191.png




typedef int (*message_callback_type)(request_rec *r, const char *format, ...);

extern "C" int qmt_tile_handler_dirty(request_rec *r, module* tile_module,
  message_callback_type message_callback)
{
 log_comments("tile", "qmt_tile_handler_dirty\n");

 const char* url = r->the_request;

 read_request_url("tile", QString::fromLatin1(url));

 ap_conf_vector_t* sconf;
 tile_server_conf* scfg;
 struct tile_request_data * rdata;
 struct protocol * cmd;



 // syslog(LOG_INFO,  "setting r->handler from %s", r->handler);

#ifdef HIDE
 r->handler = "tile_dirty";

 if (strcmp(r->handler, "tile_dirty"))
 {

  log_comments("tile_handler_dirty not\n");
  // syslog(LOG_INFO, "\ntile_handler_dirty not");

  // syslog(LOG_INFO,  "r->handler %s", r->handler);

  return DECLINED;
 }


#endif //def HIDE

 log_comments("tile", "tile_handler_dirty continued\n");
 // syslog(LOG_INFO, "\ntile_handler_dirty continued");

 rdata = (tile_request_data*) ap_get_module_config(r->request_config,
            tile_module);

 log_pointer_raw_value("tile", "rdata: ", rdata);

 cmd = rdata->cmd;

 if (cmd == NULL)
 {
  log_comments("tile", "cmd null\n");
  return DECLINED;
 }

 log_comments("tile", "tile_handler_dirty cmd ok\n");
 // syslog(LOG_INFO, "\ntile_handler_dirty cmd ok");

 sconf = r->server->module_config;
 scfg = (tile_server_conf*) ap_get_module_config(sconf, tile_module);

 if (scfg->bulkMode) {
  return OK;
 }

 log_comments("tile", "tile_handler_dirty request_tile\n");
 // syslog(LOG_INFO, "\ntile_handler_dirty request_tile");

  qmt_request_tile(r, cmd, 0);

// return error_message(r, "Tile submitted for rendering\n");

 return message_callback(r, "Tile submitted for rendering\n");
}



