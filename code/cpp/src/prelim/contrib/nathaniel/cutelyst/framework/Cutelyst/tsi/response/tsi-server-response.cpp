
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "tsi-server-response.h"

#include "raw-file/tsi-raw-file-server-response.h"

#include "../tsi-global-types.h"

#include "../tsi-resource-info.h"

#include <QDebug>

#include <QFile>

#include <QDateTime>

#include <syslog.h>


TSI_Server_Response::TSI_Server_Response(QString log_file)
  :  log_file_(log_file), binary_content_(nullptr), raw_file_response_(nullptr)
{

}

TSI_Server_Response::~TSI_Server_Response()
{
 if(raw_file_response_)
   delete raw_file_response_;
}


void TSI_Server_Response::init_resource_info_content(const TSI_Resource_Info& qri)
{
 QByteArray qba;
 qri.supply_data(qba);
 init_binary_content(qba);
}


void TSI_Server_Response::log_or_debug(QString text)
{
 if(log_file_.isEmpty())
 {
  if(text.endsWith(QChar::fromLatin1('\n')))
    text.chop(1);
  qDebug() << text;
 }
 else
 {
  static int line_count = 0;
  log_to_logfile(text, ++line_count);
 }
}


void TSI_Server_Response::log_to_logfile(QString text, int line_count)
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

QMap<QString, QString*>* TSI_Server_Response::get_field_map()
{
 QMap<QString, QString*>* result = new QMap<QString, QString*>
 {
  {"content-type"_qt, &content_type_},
  {"character-set"_qt, &character_set_},
  {"content-text"_qt, &content_text_},
  {"content-file"_qt, &content_file_}
 };

 if(!full_content_type_.isEmpty())
   result->insert("full-content-type"_qt, &full_content_type_);
 return result;
}

void TSI_Server_Response::init_binary_content(const QByteArray& qba)
{
 binary_content_ = new QByteArray(qba);
}

QString TSI_Server_Response::get_default_full_content_type()
{
 if(full_content_type().isEmpty())
 {
  return "%1;charset=%2"_qt.arg(content_type_)
    .arg(character_set_);
 }
 return full_content_type_;
}



QString TSI_Server_Response::init_from_request_path(QString request_path)
{
 s4 index1 = request_path.indexOf("/tsi="_qt);

 if(index1 == -1)
   return {};

 s4 index2 = request_path.indexOf(QChar::fromLatin1(';'), index1);
 if(index2 == -1)
   return {};

 resource_code_ = request_path.mid(index1 + 1, index2 - index1 - 1);

 request_path.remove(index1 + 1, index2 - index1);

 return request_path;

}

TSI_Raw_File_Server_Response* TSI_Server_Response::parse_resource_code(QString controller_key)
{
 s4 index1 = resource_code_.indexOf(QChar::fromLatin1('='));
 if(index1 == -1)
   return nullptr;

 s4 index2 = resource_code_.indexOf(QChar::fromLatin1('~'), index1 + 1);

 if(index2 == -1)
   return nullptr;

 s4 index3 = index1 + 1;

 if(index2 == index3)
   return nullptr;

 QString format_plus = resource_code_.mid(index2 + 1);

 Response_Modes rm = Response_Modes::N_A;

 if(!(resource_code_[index3] == QChar::fromLatin1('r') || resource_code_[index3] == QChar::fromLatin1('R')))
    return nullptr;

 if(index2 > index3 + 1)
 {
  rm = parse_response_mode(resource_code_[index3 + 1]);
 }

 QString format, after;
 format = format_plus;

 TSI_Raw_File_Server_Response* result = new TSI_Raw_File_Server_Response(this, format, after, (s1) rm);

 return result;

}

void TSI_Server_Response::handle_request_from_uri(QString uri)
{
 if(uri.length() > 2)
 {
  if(uri[3] == QChar::fromLatin1('~'))
  {
   if(uri[1] == QChar::fromLatin1('r') || uri[1] == QChar::fromLatin1('R'))
   {
    u4 index = uri.indexOf(QChar::fromLatin1('/'), 3);
    QString format, after;

    if(index == (u4) -1)
      format = uri.mid(3);
    else
    {
     format = uri.mid(4, index - 4); after = uri.mid(index);
    }

    Response_Modes rm = parse_response_mode(uri[2]);

    //if(uri[1].isUpper())

    TSI_Raw_File_Server_Response rr(this, format, after, (s1) rm);
    rr.proceed();
    return;
   }
  }
 }
// content_type_ = "text/html";
// character_set_ = "UTF8";
 log_or_debug("Simply returning the uri ...\n"_qt);
 text_html_utf8("Request url: %1"_qt.arg(uri));
}

void TSI_Server_Response::text_html_utf8()
{
 content_type_ = "text/html"_qt;
 character_set_ = "UTF8"_qt;
}

void TSI_Server_Response::text_html_utf8(QString text)
{
 text_html_utf8();
 content_text_ = text;
}

void TSI_Server_Response::text_html_utf8_error(QString* get_default_message)
{
 static QString default_message = "Unknown/Unavailable resource, or an error occured."_qt;
 if(get_default_message)
 {
  *get_default_message = default_message;
  return;
 }
 text_html_utf8(default_message);
}

void TSI_Server_Response::text_html_utf8_error(QString text, QString log_text)
{
 if(text.isEmpty())
   text_html_utf8_error(&text);

 if(log_text.isEmpty())
   log_or_debug(text);
 else
   log_or_debug(log_text);

 text_html_utf8(text);
}

void TSI_Server_Response::init_content_file_with_type(QString file_type,
  QString file_path)
{
 content_file_ = file_path;
 content_type_ = file_type;
}

