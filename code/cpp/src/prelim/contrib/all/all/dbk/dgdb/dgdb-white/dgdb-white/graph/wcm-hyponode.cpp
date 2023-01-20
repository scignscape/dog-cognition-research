
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "wcm-hyponode.h"

#include <QDataStream>
#include <QIODevice>
#include <QMetaType>

#include "wcm/wcm-column-set.h"

WCM_Hyponode::WCM_Hyponode()
{

}

WCM_Encoding_Package::Tuple WCM_Hyponode::get_encoding_tuple() const
{
 static int mt = QMetaType::type("WCM_Encoding_Package");
 if(qt_encoding_.userType() == mt)
 {
  WCM_Encoding_Package encp = qt_encoding_.value<WCM_Encoding_Package>();
  return encp.as_tuple();
 }
 return WCM_Encoding_Package::null_tuple();
}

template<>
void WCM_Database::untranslate_data(wg_int data, WCM_Hyponode& who)
{
 who.set_wgdb_encoding({data});
}

//quint64 WCM_Hyponode::defers_to_wg() const
//{
// static int mt = QMetaType::type("WCM_Encoding_Package");
// if(qt_encoding_.userType() == mt)
// {
//  WCM_Encoding_Package qvdbv = qt_encoding_.value<WCM_Encoding_Package>();
//  if(qvdbv.code == 1)
//    return qvdbv.code;
// }
// return 0;
//}

void WCM_Hyponode::set_wgdb_encoding(wg_enc wgdb_encoding)
{
 static WCM_Encoding_Package qvdbv {1};
 wgdb_encoding_ = wgdb_encoding;
 qt_encoding_.setValue(qvdbv);
}

void WCM_Hyponode::set_raw_data(quint64 raw_data, quint32 size)
{
 WCM_Encoding_Package qvdbv = WCM_Encoding_Package::from_raw_size(size);
 raw_data_ = raw_data;
 qt_encoding_.setValue(qvdbv);
}


