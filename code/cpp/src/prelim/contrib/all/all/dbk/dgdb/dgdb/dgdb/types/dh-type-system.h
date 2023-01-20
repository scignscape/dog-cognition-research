
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef DH_TYPE_SYSTEM__H
#define DH_TYPE_SYSTEM__H

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


 //?KANS_(DgDb)

class DH_Type;
class DH_Type_Builder;

class DH_Type_System
{
 QMap<QString, QString> type_name_resolutions_;
 QMap<QString, DH_Type*> types_by_name_;
 DH_Type_Builder* current_type_builder_;

public:


 DH_Type_System();

 void build_default_types();

 DH_Type* get_type_by_name(QString tn, QString* res = nullptr);
 DH_Type& register_type(QString tn, QString ctn = QString());

 template<typename VERTEX_Type>
 QString register_type_name_resolution(QString desired)
 {
  QString tn = QString::fromStdString(typeid(VERTEX_Type).name());
  type_name_resolutions_[tn] = desired;
  return tn;
 }

 template<typename VERTEX_Type>
 DH_Type& register_type_with_name_resolution(QString desired)
 {
  QString ctn = register_type_name_resolution<VERTEX_Type>(desired);
  return register_type(desired, ctn);
 }

};


 //?_KANS(DgDb)

#endif // DH_TYPE_SYSTEM__H


