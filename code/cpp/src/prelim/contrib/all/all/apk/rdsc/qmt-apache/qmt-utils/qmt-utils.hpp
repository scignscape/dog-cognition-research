

#ifndef QMT_UTILS__HPP
#define QMT_UTILS__HPP

#include <QString>

class QMT_Server_Response;

extern void log_comments_qstring(QString file, QString str);

extern void read_request_url(QString file, QString req);

extern QMT_Server_Response* get_qmt_server_response(QString uri, QString log_file);//, QString log_file = QString());


#endif // QMT_UTILS__HPP
