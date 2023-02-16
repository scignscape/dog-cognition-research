
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef QMT_RESOURCE_INFO__H
#define QMT_RESOURCE_INFO__H

//#include "qmt-accessors.h"
//#include "qmt-global-types.h"


#include "accessors.h"
#include "global-types.h"

#include <QString>

class QMT_Server_Response;

class QMT_Resource_Info
{ 
 QString request_path_;
 QString actual_path_;

 u4 size_;

public:

 QMT_Resource_Info(QString request_path, QString actual_path,
    u4 size);

 QMT_Resource_Info();

 ACCESSORS(QString ,request_path)
 ACCESSORS(QString ,actual_path)
 ACCESSORS(u4 ,size)

 void supply_data(QByteArray& qba) const;
 void absorb_data(const QByteArray& qba);


};



#endif // QMT_RESOURCE_INFO
