
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef QUEUE_DEMO_CLASS__H
#define QUEUE_DEMO_CLASS__H 

#include "accessors.h"

#include "global-types.h"

#include "dgdb-white/dw-stage-value.h"

#include <QString>
#include <QByteArray>

#include "kans.h"
USING_KANS(DGDB)

KANS_CLASS_DECLARE(DGDB ,DW_Stage_Value)
KANS_CLASS_DECLARE(DGDB ,DW_Stage_Queue)

class Queue_Demo_Class
{
 QString title_;
 QString author_;
 u2 num_;
 QDate publication_date_;
 QTime test_time_;
 
public:

 Queue_Demo_Class();

 ACCESSORS(QString ,title)
 ACCESSORS(QString ,author)

 ACCESSORS(u2 ,num)

 ACCESSORS(QDate ,publication_date)
 ACCESSORS(QTime ,test_time)

 void encode_stage_values(QByteArray& qba,
   DW_Stage_Value::Callback_type cb);

 void read_stage_queue(QQueue<void*>& vals);
 
 static void init_stage_queue(const QByteArray& qba, 
   QMap<u4, DW_Stage_Value>& qm, DW_Stage_Queue& sq); 

};



#endif // QUEUE_DEMO_CLASS__H 
