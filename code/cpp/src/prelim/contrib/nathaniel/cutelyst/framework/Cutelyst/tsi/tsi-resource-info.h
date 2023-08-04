
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef TSI_RESOURCE_INFO__H
#define TSI_RESOURCE_INFO__H


#include "tsi-accessors.h"
#include "tsi-global-types.h"

#include <QString>

class TSI_Server_Response;

class TSI_Resource_Info
{ 
 QString request_path_;
 QString actual_path_;

 u4 size_;

public:

 TSI_Resource_Info(QString request_path, QString actual_path,
    u4 size);

 TSI_Resource_Info();

 ACCESSORS(QString ,request_path)
 ACCESSORS(QString ,actual_path)
 ACCESSORS(u4 ,size)

 void supply_data(QByteArray& qba) const;
 void absorb_data(const QByteArray& qba);


};



#endif // TSI_RESOURCE_INFO
