
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef WCM_HYPONODE__H
#define WCM_HYPONODE__H

#include "accessors.h"

#include <QString>
#include <QList>
#include <QDate>

#include "whitedb/_whitedb.h"

#include "wcm/wcm-database.h"

class WCM_Hyponode;
class WCM_Type;


class WCM_Hyponode
{
 wg_enc wgdb_encoding_;
 QVariant qt_encoding_;
 quint64 raw_data_;

public:

 ACCESSORS__SDECLARE(wg_enc ,wgdb_encoding)
 ACCESSORS__GET(wg_enc ,wgdb_encoding)

 ACCESSORS__GET(quint64 ,raw_data)
 void set_raw_data(quint64 raw_data, quint32 size);

 ACCESSORS(QVariant ,qt_encoding)

 //quint64 defers_to_wg() const;
 WCM_Encoding_Package::Tuple get_encoding_tuple() const;

 template<typename STREAM_Type>
 friend STREAM_Type& operator <<(STREAM_Type& lhs, const WCM_Hyponode& rhs)
 {
  WCM_Encoding_Package::Tuple tpl = rhs.get_encoding_tuple();
  switch(tpl.kind)
  {
  case 0: lhs << tpl.kind << rhs.qt_encoding_; break;
  case 1: lhs << tpl.kind << (quint64) rhs.wgdb_encoding_.data; break;
  case 2: lhs << tpl.kind << tpl.blob_size;
    lhs.writeRawData((const char*) rhs.raw_data_, tpl.blob_size); break;

  // //  This is by default but it's expected that someone
   //    using tpl.raw option will re-implement this case.
  case 3: lhs << tpl.kind << tpl.raw <<
    (quint64) rhs.wgdb_encoding_.data << rhs.raw_data_; break;
  }
 }

 template<typename STREAM_Type>
 friend STREAM_Type& operator >>(STREAM_Type& lhs, WCM_Hyponode& rhs)
 {
  quint8 tpl_kind_code;
  lhs >> tpl_kind_code;
  switch(tpl_kind_code)
  {
  case 0: lhs >> rhs.qt_encoding_; break;
  case 1:
   {
    quint64 val;
    lhs >> val;
    rhs.wgdb_encoding_.data = (wg_int) val;
   }
   break;
  case 2:
   {
    quint32 sz;
    lhs >> sz;
    void* pv = malloc(sz);
    lhs.readRawData((char*) pv, sz);
    rhs.set_raw_data( (quint64) pv, sz);
   }
   break;

  // //  This is by default but it's expected that someone
   //    using tpl.raw option will re-implement this case.
  case 3:
   {
    quint64 rd;
    lhs >> rd;
    rhs.set_raw_data(rd, 0);
   }
   break;
  }
 }


 WCM_Hyponode();
};

#endif
