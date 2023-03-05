
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_TYPE_SYSTEM__H
#define QH_TYPE_SYSTEM__H

#include <QMap>
#include <QString>

#include "global-types.h"


#include "accessors.h"

#include "kans.h"

KANS_(RdSC)

class Qh_Pack_Builder;


#ifndef REGISTER_TYPE_NAME_RESOLUTION
#define REGISTER_TYPE_NAME_RESOLUTION(tn) \
register_type_name_resolution<tn>(#tn)
#endif

#ifndef REGISTER_TYPE_NAME_RESOLUTION_2_1
#define REGISTER_TYPE_NAME_RESOLUTION_2_1(ho_tname ,tn) \
register_type_name_resolution<ho_tname<tn>>("(" #ho_tname \
  " " #tn ")")
#endif

#ifndef REGISTER_TYPE
#define REGISTER_TYPE(tn) \
register_type_with_name_resolution<tn>(#tn)
#endif

class Qh_Type;

class Qh_Type_System
{
 QMap<QString, QString> type_name_resolutions_;
 QMap<QString, Qh_Type*> types_by_name_;

public:

 Qh_Type_System();

 Qh_Type* get_type_by_name(QString tn, QString* res = nullptr);
 Qh_Type& register_type(QString tn, QString ctn = QString());

 template<typename VERTEX_Type>
 QString register_type_name_resolution(QString desired)
 {
  QString tn = QString::fromStdString(typeid(VERTEX_Type).name());
  type_name_resolutions_[tn] = desired;
  return tn;
 }

 template<typename VERTEX_Type>
 Qh_Type& register_type_with_name_resolution(QString desired)
 {
  QString ctn = register_type_name_resolution<VERTEX_Type>(desired);
  return register_type(desired, ctn);
 }


};

_KANS(RdSC)


#endif // QH_TYPE_SYSTEM__H


