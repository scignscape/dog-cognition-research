
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef QMT_RAW_FILE_SERVER_RESPONSE__H
#define QMT_RAW_FILE_SERVER_RESPONSE__H

#include "accessors.h"
#include "global-types.h"

#include <QString>

class QMT_Server_Response;

class QMT_Raw_File_Server_Response
{ 
 QMT_Server_Response* main_response_;
 QString format_;
 QString url_path_;

 QString folder_branch_;

 QChar non_lowercase_flag_;

 s1 response_mode_;

public:

 QMT_Raw_File_Server_Response(QMT_Server_Response* main_response,
    QString format, QString url_path,
    s1 response_mode, QString folder_branch = {});

 void proceed(QString prepend = {});

 void check_rename(QString& path, QString prepend);

 void check_rewrite_nonexistent_path(QString& path);

 ACCESSORS(QChar ,non_lowercase_flag)

// ACCESSORS(QString ,full_content_type)
// ACCESSORS(QString ,character_set)

// ACCESSORS(QString ,content_text)
// ACCESSORS(QString ,content_file)

// ACCESSORS(QByteArray* ,binary_content)


};



#endif // QMT_SERVER_RESPONSE__H
