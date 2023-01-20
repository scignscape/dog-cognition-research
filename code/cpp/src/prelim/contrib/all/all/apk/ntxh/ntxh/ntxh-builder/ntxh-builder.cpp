
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ntxh-builder.h"


#include <QDebug>
#include <QTextStream>



USING_KANS(HGDMCore)

NTXH_Builder::NTXH_Builder(QTextStream& qts)
  : qts_(qts)
{

}

void NTXH_Builder::enter(QString type_name)
{
 qts_ << "\n!/" << type_name;
}

void NTXH_Builder::leave()
{
 qts_ << "\n/!";
}

void NTXH_Builder::leave_type()
{
 qts_ << ';';
}

void NTXH_Builder::leave_prelude()
{
 qts_ << "\n&/";
}

void NTXH_Builder::enter_coda()
{
 qts_ << "\n/&";
}

void NTXH_Builder::add_replacement(QString key, QString val)
{
 qts_ << "\n%" << key << ": " << val;
}

void NTXH_Builder::el(int i)
{
 for(int j = 0; j < i; ++j)
   qts_ << "\n";
}

void NTXH_Builder::add_array_type_entry(QString type_name, QString codes)
{
 qts_ << "\n&" << type_name << " [" << codes << "] ";
}

void NTXH_Builder::add_structure_type_entry(QString type_name, QString codes)
{
 qts_ << "\n&" << type_name << " {" << codes << "} ";
}

void NTXH_Builder::ssf(QString field_name, QString val)
{
 qts_ << "\n$" << field_name << "# " << val;
}


void NTXH_Builder::sf(QString field_name, QString val)
{
 qts_ << "\n$" << field_name << ": " << val;
}

void NTXH_Builder::msf(QString field_name, QString val)
{
 qts_ << "\n$" << field_name << ". " << val << "\n.";
}

void NTXH_Builder::array_append()
{
 qts_ << "\n<>>";
}

void NTXH_Builder::top_append()
{
 qts_ << "\n<+>";
}

void NTXH_Builder::add_type_fields(QString qs, int start)
{
 QList<QStringList> fs;

 QStringList qsl = qs.split(",", QString::SplitBehavior::SkipEmptyParts);

 for(QString iqs : qsl)
 {
  QStringList iqsl = iqs.simplified().split(' ');
  fs.push_back(iqsl);
 }

 add_type_fields(fs, start);
}

void NTXH_Builder::add_type_fields(QList<QStringList>&& fs, int start)
{
 add_type_fields(fs, start);
}

void NTXH_Builder::add_type_fields(QList<QStringList>& fs, int start)
{
 int i = start;
 for(QStringList& qsl : fs)
 {
  qts_ << "\n ";
  for(QString qs : qsl)
  {
   qts_ << ':' << qs << ':' << i << ' ';
  }
  ++i;
 }
}

void NTXH_Builder::add_prelude_comment(QString qs)
{
 qts_ << "\n- " << qs << "\n.\n";
}

void NTXH_Builder::add_sl_comment(QString qs)
{
 qts_ << ";;- " << qs << '\n';
}

void NTXH_Builder::add_ml_comment(QString qs)
{
 qts_ << "\n;;-- " << qs << "\n --;;";
}



