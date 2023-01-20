
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NTXH_BUILDER__H
#define NTXH_BUILDER__H


#include "kans.h"
#include "accessors.h"

#include <type_traits>

#include <QVector>
#include <QString>
#include <QStringList>


class QTextStream;


KANS_(HGDMCore)

class NTXH_Builder
{
 QTextStream& qts_;

public:

 NTXH_Builder(QTextStream& qts);

 void enter(QString type_name);
 void leave();

 void leave_type();

 void sf(QString field_name, QString val);
 void msf(QString field_name, QString val);
 void ssf(QString field_name, QString val);

 void add_replacement(QString key, QString val);

 void array_append();
 void top_append();

 template<typename T>
 void nsf(QString field_name, T val)
 {
  sf(field_name, QString::number(val));
 }

 void el(int i = 1);

 template<typename... Ts>
 static QString _join(QString sep, Ts... vals)
 {
  QStringList qsl;
  std::vector<typename std::common_type<Ts...>::type> vec {vals...};
  std::transform(vec.begin(), vec.end(),
    std::back_inserter(qsl),[](typename std::common_type<Ts...>::type val)
  {
   return QString::number(val);
  });
  return qsl.join(sep);
 }

 template<typename... Ts>
 static QString join(const char* sep, Ts... vals)
 {
  return _join(QString(sep), vals...);
 }

 template<typename... Ts>
 static QString join(const QString& sep, Ts... vals)
 {
  return _join(sep, vals...);
 }

 template<typename... Ts>
 static QString join(char sep, Ts... vals)
 {
  return _join(QString(QChar(sep)), vals...);
 }

 template<typename... Ts>
 static QString join(Ts... vals)
 {
  return _join(QString(" "), vals...);
 }

 void add_array_type_entry(QString type_name, QString codes);
 void add_structure_type_entry(QString type_name, QString codes);

 template<typename... Ts>
 void nsf(QString field_name, Ts... vals)
 {
  ssf(field_name, join(vals...));
 }

 template<typename... Ts>
 void enter_array_type(QString type_name, Ts... vals)
 {
  add_array_type_entry(type_name, join(';', vals...));
 }

 template<typename... Ts>
 void enter_structure_type(QString type_name, Ts... vals)
 {
  add_structure_type_entry(type_name, join(';', vals...));
 }

 void leave_prelude();
 void enter_coda();

 void add_prelude_comment(QString qs);
 void add_sl_comment(QString qs);
 void add_ml_comment(QString qs);


 void add_type_fields(QList<QStringList>& fs, int start = 0);
 void add_type_fields(QList<QStringList>&& fs, int start = 0);

 void add_type_fields(QString qs, int start = 0);


};


_KANS(HGDMCore)

#endif // NTXH_BUILDER__H
