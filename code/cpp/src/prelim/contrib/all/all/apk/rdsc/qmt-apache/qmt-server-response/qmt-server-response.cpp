
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "qmt-server-response.h"

#include "raw-file/qmt-raw-file-server-response.h"

//?#include "qmt-global-types.h"
#include "global-types.h"

#include "qmt-resource-info.h"

#include <QDebug>

#include <QFile>

#include <QDateTime>

#include <syslog.h>


QMT_Server_Response::QMT_Server_Response(QString log_file)
  :  log_file_(log_file), binary_content_(nullptr)
{

}


void QMT_Server_Response::init_resource_info_content(const QMT_Resource_Info& qri)
{
 QByteArray qba;
 qri.supply_data(qba);
 init_binary_content(qba);
}


void QMT_Server_Response::log_or_debug(QString text)
{
 if(log_file_.isEmpty())
 {
  if(text.endsWith('\n'))
    text.chop(1);
  qDebug() << text;
 }
 else
 {
  static int line_count = 0;
  log_to_logfile(text, ++line_count);
 }
}


void QMT_Server_Response::log_to_logfile(QString text, int line_count)
{
 QFile outfile(log_file_);

 int ok = outfile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
 if(!ok)
 {
  QString errMsg = outfile.errorString();
  syslog(LOG_INFO, "Could not open qmt log file: %s", errMsg.toStdString().c_str());
  return;
 }

 QString qmsg = "(%1) %2. %3"_qt
   .arg(QDateTime::currentDateTime().toString()).arg(line_count).arg(text);
 outfile.write(qmsg.toLatin1());

 outfile.flush();

//#endif //def HIDE
}

QMap<QString, QString*>* QMT_Server_Response::get_field_map()
{
 QMap<QString, QString*>* result = new QMap<QString, QString*>
 {
  {"content-type", &content_type_},
  {"character-set", &character_set_},
  {"content-text", &content_text_},
  {"content-file", &content_file_}
 };

 if(!full_content_type_.isEmpty())
   result->insert("full-content-type", &full_content_type_);
 return result;
}

void QMT_Server_Response::init_binary_content(const QByteArray& qba)
{
 binary_content_ = new QByteArray(qba);
}

QString QMT_Server_Response::get_default_full_content_type()
{
 if(full_content_type().isEmpty())
 {
  return "%1;charset=%2"_qt.arg(content_type_)
    .arg(character_set_);
 }
 return full_content_type_;
}

void QMT_Server_Response::handle_request_from_uri(QString uri)
{
 if(uri.length() > 2)
 {
  if(uri[3] == '~')
  {
   if(uri[1] == 'r' || uri[1] == 'R')
   {
    u4 index = uri.indexOf('/', 3);
    QString format, after;

    if(index == (u4) -1)
      format = uri.mid(3);
    else
    {
     format = uri.mid(4, index - 4); after = uri.mid(index);
    }

    Response_Modes rm = parse_response_mode(uri[2]);

    //if(uri[1].isUpper())

    QMT_Raw_File_Server_Response rr(this, format, after, (s1) rm);
    rr.proceed();
    return;
   }
  }
 }
// content_type_ = "text/html";
// character_set_ = "UTF8";
 log_or_debug("Simply returning the uri ...\n");
 text_html_utf8("Request url: %1"_qt.arg(uri));
}

void QMT_Server_Response::text_html_utf8()
{
 content_type_ = "text/html";
 character_set_ = "UTF8";
}

void QMT_Server_Response::text_html_utf8(QString text)
{
 text_html_utf8();
 content_text_ = text;
}

void QMT_Server_Response::text_html_utf8_error(QString* get_default_message)
{
 static QString default_message = "Unknown/Unavailable resource, or an error occured.";
 if(get_default_message)
 {
  *get_default_message = default_message;
  return;
 }
 text_html_utf8(default_message);
}

void QMT_Server_Response::text_html_utf8_error(QString text, QString log_text)
{
 if(text.isEmpty())
   text_html_utf8_error(&text);

 if(log_text.isEmpty())
   log_or_debug(text);
 else
   log_or_debug(log_text);

 text_html_utf8(text);
}

void QMT_Server_Response::init_content_file_with_type(QString file_type,
  QString file_path)
{
 content_file_ = file_path;
 content_type_ = file_type;
}

