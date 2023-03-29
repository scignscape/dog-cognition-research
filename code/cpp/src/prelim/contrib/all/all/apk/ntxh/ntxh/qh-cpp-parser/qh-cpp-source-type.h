
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_CPP_SOURCE_TYPE__H
#define QH_CPP_SOURCE_TYPE__H


#include "accessors.h"

#include "kans.h"

#include "flags.h"

#include <QFile>
#include <QTextStream>

#include "global-types.h"

KANS_(Qh)



class Qh_CPP_Source_Type
{
public:

 flags_(2)
  bool is_enum:1;
  bool is_class:1;
  bool is_struct:1;

 _flags

 struct Field_Info : std::array<QString, 4> {
  QString& name() { return (*this)[0]; }
  QString& type() { return (*this)[1]; }
  QString& minimum() { return (*this)[2]; }
  QString& fixed_value() { return (*this)[2]; }
  QString& maximum() { return (*this)[3]; }
  QString& derived_value() { return (*this)[3]; }

  Field_Info(QString n) { name() = n; }
 };

private:

 QString full_name_;
 QString single_name_;
 QString main_source_file_;

 u2 ref_line_number_;

 QVector<QString> base_types_;

 QVector<Field_Info> fields_;


public:


 Qh_CPP_Source_Type();

 ACCESSORS(QString ,full_name)
 ACCESSORS(QString ,single_name)
 ACCESSORS(QString ,main_source_file)
 ACCESSORS(u2 ,ref_line_number)
 ACCESSORS__RGET(QVector<QString> ,base_types)

 void note_enum_field(QString label, QString value);

};

_KANS(Qh)


#endif // QH_CPP_SOURCE_TYPE__H

