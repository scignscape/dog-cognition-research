
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_ANNOTATION_GROUP__H
#define DHAX_ANNOTATION_GROUP__H

#include <QString>
#include <QPoint>
#include <QVector>


#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include "location/dhax-location-2d.h"


#include <functional>

#include <QDateTime>

#include "kans.h"


//KANS_(GTagML)

class DHAX_Annotation_Instance;
class DHAX_Environment_Settings;

class DHAX_Annotation_Group
{
 DHAX_Annotation_Group* parent_group_;

 //?DHAX_Environment_Settings* specified_environment_settings_;

 QVector<DHAX_Annotation_Instance*> annotations_;

 n8 target_data_;

 QString target_path_;


public:

 DHAX_Annotation_Group(DHAX_Annotation_Group* parent_group = nullptr);

 ACCESSORS(DHAX_Annotation_Group* ,parent_group)
 ACCESSORS__RGET( QVector<DHAX_Annotation_Instance*> ,annotations)
 //ACCESSORS(DHAX_Environment_Settings* ,specified_environment_settings)
 ACCESSORS(n8 ,target_data)
 ACCESSORS(QString ,target_path)


 template<typename OBJECT_Type>
 OBJECT_Type* target_data_as()
 {
  return (OBJECT_Type*) target_data_;
 }

 template<typename OBJECT_Type>
 void set_target_data_as(OBJECT_Type* ptr)
 {
  target_data_ = (n8) ptr;
 }

 void add_annotation(DHAX_Annotation_Instance* axa);
 DHAX_Annotation_Instance* add_annotation();

};

// _KANS(GTagML)


#endif  //  DHAX_ANNOTATION_GROUP__H
