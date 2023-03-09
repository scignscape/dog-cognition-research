
#include <QString>

//#include <QLocalSocket>

#include <QMap>

#include <QLocalSocket>
#include <QDataStream>
#include <QEventLoop>

#include <QImage>

//?
#include <QFile>
#include <QDateTime>

#include <QDataStream>

#include "httpd.h"
#include "http_config.h"

//?
//#include "gen_tile.h"
//#include "mod_tile.h"

#include <syslog.h>

#include "qmt-server-response/qmt-server-response.h"

#include "global-types.h"


extern "C" void log_comments(const char* file, const char* msg)
{
 static int count = 0;

 QString logfile = QString("%1/%2.txt").arg(PREFERRED_LOG_FOLDER).arg(file);
 QFile outfile(logfile);

 int ok = outfile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
 if(!ok)
 {
  QString errMsg = outfile.errorString();
  syslog(LOG_INFO, "Could not open qmt log file: %s", errMsg.toStdString().c_str());
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

extern "C" void log_comments_with_value(const char* file, const char* msg, int i)
{
 QString qmsg = QString::fromLatin1(msg);
 qmsg.replace('@', QString("%1").arg(i));
 log_comments(file, qmsg.toLatin1());
}

extern "C"
void log_comments_kv(const char* file, const char* k, const char* v)
{
 QString qsprdata = QString("%1 %2\n").arg(QString::fromLatin1(k)).arg((QString::fromLatin1(v)));

 log_comments(file, qsprdata.toLatin1());

}

extern "C"
void log_pointer_raw_value(const char* file, const char* name, void* v)
{
// char sprdata[10];
// sprintf(sprdata, "rdata: %lu\n", (size_t) rdata);

// log_comments(sprdata);

 QString qsprdata = QString("%1 %2\n").arg(QString::fromLatin1(name)).arg((size_t) v);

 log_comments(file, qsprdata.toLatin1());

}

void log_comments_qstring(QString file, QString str)
{
 log_comments(file.toLatin1(), str.toLatin1());
}


void read_request_url(QString file, QString req)
{
 log_comments_qstring(file, req.prepend("the req:") + "\n");
}


void parse_url_via_start(const QString& log_file, const QString& url,
  const QString& required_start,
  void*& details, int** result)
{
 QString f = QString("%1/%2").arg(PREFERRED_LOG_FOLDER).arg(log_file);
 log_comments_qstring(log_file, "URL: %1\n"_qt.arg(url));

 if(url.startsWith(required_start))
 {
  details = (void*) new QString(url.mid(required_start.length()));
  **result = ((QString*)details)->length();
  log_comments_qstring(log_file, "Match: (%1)%2\n"_qt.arg(required_start).arg(*(QString*)details));
 }
 else
 {
  *result = 0;
 }
}

extern "C"
int _parse_url_via_start(const char* log_file, const char* url, const char* required_start,
  int* positive_response, int suggested_negative_response,
  void** details)
{
 QString _url = QString::fromLatin1(url);
 QString _required_start = QString::fromLatin1(required_start);
 int result = 0;
 int* _result = &result;
 parse_url_via_start(log_file, _url, _required_start,
   *details, &_result);
 if(_result)
   *positive_response = result;
 else
   result = suggested_negative_response;
 return result;
}

//extern "C"
//void* get_qmt_response(void* url)
//{

//}



QMT_Server_Response* get_qmt_server_response_l(QString uri)
{
 log_comments_qstring("-qmt-server-response", "Trying local socket: %1\n"_qt.arg(LOCAL_SOCKET_PATH));

 QLocalSocket qls;

 QMT_Server_Response* result = nullptr;

 qls.setServerName(LOCAL_SOCKET_PATH);

 QObject::connect(&qls, &QLocalSocket::connected, [&qls, &uri]()
 {
  log_comments_qstring("-qmt-server-response", "Writing URI: %1\n"_qt.arg(uri));
  qls.write(uri.toLatin1());
 });

 QObject::connect(&qls, &QLocalSocket::readyRead, [&qls, &result]()
 {
  result = new QMT_Server_Response;

  QByteArray qba = qls.readAll();
  QDataStream qds(qba);

  log_comments_qstring("-qmt-server-response", "reading: %1\n"_qt.arg(qba.length()));

//  QString qs = QString::fromLatin1(qba);
//  log_comments_qstring("-tilec", qs + "\n");

  qds >> *result;

//  log_comments_qstring("-tileb", QString("result len: %1").arg(result.length()));
 });

 qls.connectToServer();

 qls.waitForReadyRead();

 if(!result)
 {
  log_comments("-qmt-server-response", "Missing response; trying loop\n");
  while (!result)
    ;
 }

 return result;

}


QMT_Server_Response* get_qmt_server_response(QString uri, QString log_file) //, QString log_file = QString())
{
 if(uri.startsWith("-l"))
 {
  return get_qmt_server_response_l(uri.mid(2));
 }

 //QMT_Server_Response* result = new QMT_Server_Response(log_file);
 QMT_Server_Response* result = new QMT_Server_Response(log_file);

 result->handle_request_from_uri(uri);
 return result;
}

extern "C"
int get_response_array(void* uri, char*** response, const char* log_file)
{

 //?
 QString logfile = QString("%1/%2.txt").arg(PREFERRED_LOG_FOLDER).arg(log_file);

 QMT_Server_Response* qsr = get_qmt_server_response(*(QString*)uri, logfile);
 QMap<QString, QString*>* field_map = qsr->get_field_map();

 QString full_content_type;// = nullptr; // qsr->get_full_content_type();
 QString*& fct = (*field_map)["full-content-type"];
 if(!fct)
 {
  full_content_type = qsr->get_default_full_content_type();
  fct = &full_content_type;
 }

 static QStringList field_list {{"content-text", "full-content-type"}};

 char** fields = (char**) malloc(sizeof(char*) * field_list.size());

 int field_number = 0;

 QByteArray* raw = qsr->binary_content();
 int result = raw? raw->length() : 0;

 bool raw_needs_delete = false;

 log_comments_qstring("-qmt-response-array",
   "qsr->content_file() %1 \n"_qt.arg(qsr->content_file()));

 if(result == 0 && !(raw || qsr->content_file().isEmpty()))
 {
  log_comments_qstring("-qmt-response-array",
    "infile ...");

  QFile infile(qsr->content_file());
  if(infile.open(QIODevice::ReadOnly))
  {
   raw_needs_delete = true;
   raw = new QByteArray;
   *raw = infile.readAll();

//   log_comments_qstring("-qmt-response-array",
//     "\nraw: %1"_qt.arg(QString::fromLatin1(*raw)));

   infile.close();

   result = raw->length();
  }
  else
  {
   log_comments_qstring("-qmt-response-array",
     "infile error ... %1"_qt.arg(infile.errorString()));

  }
 }

 if(result)
 {
  log_comments_qstring("-qmt-response-array", "Passing along raw binary\n");

  char* cs = (char*) malloc(raw->length());
  memcpy(cs, raw->data(), raw->length());
  fields[0] = cs;

  if(raw_needs_delete)
    delete raw;
 }
 else //raw is empty
   fields[0] = 0;

 ++field_number;

 for(QString field : field_list)
 {
  QByteArray fqba = field_map->value(field)->toLatin1();
  char* cs = (char*) malloc(fqba.length() + 1);
  memcpy(cs, fqba.data(), fqba.length());
  cs[fqba.length()] = 0;
  fields[field_number] = cs;
  ++field_number;
 }

 *response = fields;
 return result;
}



#ifdef HIDE

#include "mod-tile.h"


QMap<QString, QString>* get_external_response_qmap_socket(QString msg, QByteArray& result)
{
 QLocalSocket qls;

 QMap<QString, QString>* data = nullptr;

 qls.setServerName("/quasihome/nlevisrael/osm/mod-tile/qt-pro/mod_tile/-qt_/run-logs/test.sock");

 QObject::connect(&qls, &QLocalSocket::connected, [&qls, &msg]()
 {
  log_comments_qstring("-tilex", QString("writing MSG: %1").arg(msg));
  qls.write(msg.toLatin1());
 });

 QObject::connect(&qls, &QLocalSocket::readyRead, [&qls, &data, &result]()
 {
  data = new QMap<QString, QString>;


  QByteArray qba = qls.readAll();
  QDataStream qds(qba);

  log_comments_qstring("-tilex", QString("reading: %1").arg(qba.length()));

  QString qs = QString::fromLatin1(qba);
  log_comments_qstring("-tilec", qs + "\n");

  qds >> result >> *data;

  log_comments_qstring("-tileb", QString("result len: %1").arg(result.length()));
 });

 qls.connectToServer();

 qls.waitForReadyRead();

 if(!data)
 {
  log_comments("-tile", "Unexpected missing data; trying loop\n");
  while (!data)
    ;
 }

 return data;
}

QMap<QString, QString>* get_external_response_qmap(QString msg, QByteArray& result)
{
// return get_external_response_qmap_socket(msg, result);

 QMap<QString, QString>* qmap = new QMap<QString, QString>;
 // QByteArray qba;
 get_qmt_response(msg, *qmap, result);
 return qmap;

 //Reply_Mode rm = tile_handler_serve(const QString& uri, QString& content, QByteArray& qba) //request_rec *r)
}

extern "C"
int get_external_response(void* uri, char*** response)
{
 log_comments_qstring("-tileu", QString("Request uri: ").arg(*((QString*)uri)));

 QByteArray qba;

 QMap<QString, QString>* response_map =  get_external_response_qmap(*((QString*) uri), qba);
 QString& ct = (*response_map)["full-content-type"];

 if(ct.isEmpty())
 {
  ct = QString("%1;charset=%2").arg(response_map->value("content-type"))
    .arg(response_map->value("charset"));
 }

 static QStringList field_list {{"raw-content", "content", "full-content-type"}};

 char** fields = (char**) malloc(sizeof(char*) * field_list.size());

 int field_number = 0;

 int result = qba.length();

 if(result)
 {
  char* cs = (char*) malloc(qba.length());
  memcpy(cs, qba.data(), qba.length());
  fields[0] = cs;
  result = qba.length();
 }
 else //qba is empty
   fields[0] = 0;

 ++field_number;

 for(QString field : field_list)
 {
  QByteArray fqba = response_map->value(field).toLatin1();
  char* cs = (char*) malloc(fqba.length() + 1);
  memcpy(cs, fqba.data(), fqba.length());
  cs[fqba.length()] = 0;
  fields[field_number] = cs;
  ++field_number;
 }

 *response = fields;

 return result;
}

extern "C"
int get_canned_response(void* url, char** response)
{
 QString* qurl = (QString*) url;

 log_comments_qstring("-tile", QString("qurl: %1\n").arg(*qurl));

 QString file = "/quasihome/nlevisrael/osm/apache/install/htdocs/example-map/mapnik.xml";

 log_comments_qstring("-tile", QString("opening: %1\n").arg(file));

 QFile infile(file);
 if(infile.open(QIODevice::ReadOnly))
 {

  QString contents = infile.readAll();
  QByteArray qba = contents.toLatin1();

  log_comments_qstring("-tile", QString("contents: %1\n").arg(contents));

  log_comments_qstring("-tile", QString("contents len: %1\n").arg(qba.length()));

  char* cs = (char*) malloc(qba.length() + 1);

  memcpy(cs, qba.data(), qba.length());

  log_pointer_raw_value("-tile", "cs: ", cs);

  cs[qba.length()] = 0;
  *response = cs;

  log_comments("-tile", *response);

  return qba.length();
 }

 else
 {
  log_comments_qstring("-tile", QString("error: %1\n").arg(infile.errorString()));

 }


 return 0;
}

#endif // HIDE
