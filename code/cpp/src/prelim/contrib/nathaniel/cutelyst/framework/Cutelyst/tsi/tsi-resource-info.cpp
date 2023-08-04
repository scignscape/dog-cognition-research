
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "tsi-resource-info.h"

#include "tsi-global-types.h"

#include <QDebug>

#include <QFile>
#include <QDir>

#include <QDateTime>

#include <QDataStream>

#include <syslog.h>

#define DEFAULT_FOLDER_BRANCH "public"

TSI_Resource_Info::TSI_Resource_Info(QString request_path, QString actual_path,
   u4 size)
  :  request_path_(request_path), actual_path_(actual_path),
     size_(size)
{

}

TSI_Resource_Info::TSI_Resource_Info()
  :  size_(0)
{

}

void TSI_Resource_Info::supply_data(QByteArray& qba) const
{
 QDataStream qds(&qba, QIODevice::WriteOnly);
 qds << request_path_ << actual_path_ << size_;
}

void TSI_Resource_Info::absorb_data(const QByteArray& qba)
{
 QDataStream qds(qba);
 qds >> request_path_ >> actual_path_ >> size_;
}

