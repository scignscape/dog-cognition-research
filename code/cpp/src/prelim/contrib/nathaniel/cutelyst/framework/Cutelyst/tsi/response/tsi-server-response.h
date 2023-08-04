
#ifndef TSI_SERVER_RESPONSE__H
#define TSI_SERVER_RESPONSE__H

#include "../tsi-accessors.h"

#include "../tsi-global-types.h"

#include "../chasm-macros.h"

#include <QString>

#include <QStringList>

class TSI_Resource_Info;

class TSI_Raw_File_Server_Response;

class TSI_IMPORT TSI_Server_Response
{
 QString log_file_;

 QString content_type_;
 QString full_content_type_;
 QString character_set_;

 QString content_text_;
 QString content_file_;

 QByteArray* binary_content_;

 QString resource_code_;

 TSI_Raw_File_Server_Response* raw_file_response_;

 QStringList path_components_;


 void log_to_logfile(QString text, int line_count);

public:
 enum class Response_Modes : s1 {
  N_A, Show, Checked_Show, Info, Qt_Serialized_Info
 };

private:
 Response_Modes parse_response_mode(QChar c)
 {
  if(c == QChar::fromLatin1('i'))
    return Response_Modes::Info;

  if(c == QChar::fromLatin1('I'))
    return Response_Modes::Qt_Serialized_Info;

  if(c == QChar::fromLatin1('s'))
    return Response_Modes::Show;

  if(c == QChar::fromLatin1('S'))
    return Response_Modes::Checked_Show;

  return Response_Modes::N_A;
 }

public:

 TSI_Server_Response(QString log_file = QString());

 ~TSI_Server_Response();

 ACCESSORS(QString ,content_type)
 ACCESSORS(QString ,full_content_type)
 ACCESSORS(QString ,character_set)

 ACCESSORS(QString ,content_text)
 ACCESSORS(QString ,content_file)

 ACCESSORS(QByteArray* ,binary_content)

 ACCESSORS(QString ,resource_code)

 ACCESSORS(TSI_Raw_File_Server_Response* ,raw_file_response)

 ACCESSORS(QStringList ,path_components)



 TSI_Raw_File_Server_Response* parse_resource_code(QString controller_key);


 void handle_request_from_uri(QString uri);

 QString get_default_full_content_type();
 QMap<QString, QString*>* get_field_map();

 void init_binary_content(const QByteArray& qba);
 void text_html_utf8();
 void text_html_utf8(QString text);

 void text_html_utf8_error(QString* get_default_message = nullptr);
 void text_html_utf8_error(QString text, QString log_text = {});

 void init_content_file_with_type(QString file_type, QString file_path);

 void init_resource_info_content(const TSI_Resource_Info& qri);

 QString init_from_request_path(QString request_path);

 void log_or_debug(QString text);

 template<typename T>
 friend T& operator << (T& lhs, const TSI_Server_Response& rhs)
 {
  lhs << (rhs.binary_content_? *rhs.binary_content_: QByteArray())
    << rhs.content_type_ << rhs.character_set_
    << rhs.full_content_type_ << rhs.content_file_
    << rhs.content_text_;
 }

 template<typename T>
 friend T& operator >> (T& lhs, TSI_Server_Response& rhs)
 {
  QByteArray qba;
  lhs >> qba
    >> rhs.content_type_ >> rhs.character_set_
    >> rhs.full_content_type_ >> rhs.content_file_
    >> rhs.content_text_;

  if(!qba.isEmpty())
  {
   rhs.init_binary_content(qba);
  }

 }


};



#endif // TSI_SERVER_RESPONSE__H
