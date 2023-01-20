
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DW_TYPE_SYSTEM__H
#define DW_TYPE_SYSTEM__H

#include <functional>

#include <QMap>
#include <QString>

#include "global-types.h"

//#include "_whitedb/_whitedb.h"

#include "accessors.h"

#include "kans.h"

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


KANS_(DGDB)

class DW_Type;
class DW_Type_Builder;

class DW_Type_System
{
 QMap<QString, QString> type_name_resolutions_;
 QMap<QString, DW_Type*> types_by_name_;
 DW_Type_Builder* current_type_builder_;

public:


 DW_Type_System();

 void build_default_types();

 DW_Type* get_type_by_name(QString tn, QString* res = nullptr);
 DW_Type& register_type(QString tn, QString ctn = QString());

 template<typename VERTEX_Type>
 QString register_type_name_resolution(QString desired)
 {
  QString tn = QString::fromStdString(typeid(VERTEX_Type).name());
  type_name_resolutions_[tn] = desired;
  return tn;
 }

 template<typename VERTEX_Type>
 DW_Type& register_type_with_name_resolution(QString desired)
 {
  QString ctn = register_type_name_resolution<VERTEX_Type>(desired);
  return register_type(desired, ctn);
 }

};


_KANS(DGDB)

#endif // DW_TYPE_SYSTEM__H


