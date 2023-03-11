
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chasm-procedure-table.h"

#include "chasm/chasm-runtime.h"
#include "chasm/chasm-call-package.h"


#include <QString>
#include <QVariant>
#include <QByteArray>

#include <QUrl>

#include <QPoint>

#include <QRegularExpression>


Chasm_Procedure_Table::Chasm_Procedure_Table(Chasm_Runtime* csr)
{
 const QVector<Chasm_Type_Object*>& pto = *csr->pretype_type_objects();

 type_object_ref_ = pto[0];
 type_object_u1_ = pto[1];
 type_object_u2_ = pto[2];
 type_object_QString_ = pto[3];
 type_object_u4_ = pto[4];
 type_object_QByteArray_ = pto[5];
 type_object_r8_ = pto[6];
 type_object_QVariant_ = pto[7];
 type_object_n8_ = pto[8];
 type_object_ptr_ = pto[9];

 type_object_qsl_ = csr->type_system().get_type_object_by_name("QStringList&");
}


QString read_fncode(QString& code, QString& lead)
{
 QString result = code;

 QRegularExpression rx("^(\\D+)(0*)");

 QRegularExpressionMatch rxm = rx.match(result);
 if(rxm.hasMatch())
 {
  lead = rxm.captured(1);
  result = code.mid(rxm.capturedEnd());
  if(!rxm.captured(2).isEmpty())
  {
   code = lead + result;
  }
 }
 return result;
}

void Chasm_Procedure_Table::register_procedure_s1(QString name,
  _minimal_fn_s1_type sfn, QString code)
{
 QString lead;
 QString fc = read_fncode(code, lead);
 n8 nn = fc.toULongLong();
 CFC_Pair fncodes = _cfc(nn);
 procedure_name_resolutions_[name] = name + code;
 registered_procedures_[name + code] = {fncodes, _minimal_fn_type {.s1 = sfn}};
}


void Chasm_Procedure_Table::register_procedure_s0(QString name,
  _minimal_fn_s0_type fn, QString code)
{
 QString lead;
 QString fc = read_fncode(code, lead);
 n8 nn = fc.toULongLong();
 CFC_Pair fncode = _cfc(nn);
 procedure_name_resolutions_[name] = name + code;
 registered_procedures_[name + code] = {fncode, {.s0 = fn}};
}

CFC_Pair Chasm_Procedure_Table::find_procedure(QString name,
  _minimal_fn_s0_type& s0, _minimal_fn_s1_type& s1)
{
 {
  auto it = procedure_name_resolutions_.find(name);
  if(it != procedure_name_resolutions_.end())
    name = *it;
 }
 auto it = registered_procedures_.find(name);
 if(it == registered_procedures_.end())
   return Chasm_Function_Code::_invalid_pair();
 const QPair<CFC_Pair, _minimal_fn_type>& pr = *it;
 if(pr.first.first.convention == 0)
   s0 = pr.second.s0;
 else
   s1 = pr.second.s1;
 return pr.first;
}

Chasm_Value_Expression Chasm_Procedure_Table::read_value_expression(QString type_string, QString rep)
{
 Chasm_Value_Expression result;
 Chasm_Value_Expression::Known_Type_Strings k = Chasm_Value_Expression::parse_known_type_string(type_string);

 switch (k)
 {
 default: //parse_other(rep);
    break;
 case Chasm_Value_Expression::Known_Type_Strings::QSL:
   result.parse_qsl(rep, type_object_qsl_); break;
 case Chasm_Value_Expression::Known_Type_Strings::QS:
   result.parse_qs(rep, type_object_QString_); break;

 case Chasm_Value_Expression::Known_Type_Strings::U1: result.parse_u1(rep, type_object_u1_);
   break;

// case Chasm_Value_Expression::Known_Type_Strings::B1: result.parse_b1(rep); break;
// case Chasm_Value_Expression::Known_Type_Strings::U1: result.parse_u1(rep); break;
// case Chasm_Value_Expression::Known_Type_Strings::U2: result.parse_u2(rep); break;
// case Chasm_Value_Expression::Known_Type_Strings::U4: result.parse_u4(rep); break;
// case Chasm_Value_Expression::Known_Type_Strings::S1: result.parse_s1(rep); break;
// case Chasm_Value_Expression::Known_Type_Strings::S2: result.parse_s2(rep); break;
// case Chasm_Value_Expression::Known_Type_Strings::S4: result.parse_s4(rep); break;
// case Chasm_Value_Expression::Known_Type_Strings::N8: result.parse_n8(rep); break;
// case Chasm_Value_Expression::Known_Type_Strings::R4: result.parse_r4(rep); break;
// case Chasm_Value_Expression::Known_Type_Strings::R8: result.parse_r8(rep); break;
 }
  //raw_value_ = rep.toInt();

 return result;
}


Chasm_Value_Expression Chasm_Procedure_Table::read_value_expression(QString rep)
{
 QString type_string;
 if(rep.startsWith("$.."))
   rep.remove(1, 1);
 else if(rep.startsWith("$."))
   rep.remove(0, 1);
 else if(rep.startsWith('.'))
 {
  s4 index = rep.indexOf('/');
  if(index == -1)
  {
   type_string = rep.mid(1);
   rep.clear();
  }
  else
  {
   type_string = rep.mid(1, index - 1);
   rep = rep.mid(index + 1);
  }
 }
 return read_value_expression(type_string, rep);
}

QVector<Chasm_Value_Expression> Chasm_Procedure_Table::parse_expressions(QString reps)
{
 QVector<Chasm_Value_Expression> result;

 QStringList qsl;

 s4 index = 0;
 s4 old_index = 0;
 s4 mid_index = 0;
 while (true)
 {
  index = reps.indexOf(';', mid_index);
  if(index == -1)
    break;
  QChar qc = reps[index];
  s4 gap = index - 1;
  while (gap >= 0)
  {
   QChar qc = reps[gap];
   if(qc != '$')
     break;
   --gap;
  }
  u1 dollars = index - gap - 1;
  if((dollars % 2) == 1)
  {
   mid_index = index + 1;
   continue;
  }
  QString rep = reps.mid(old_index, index - old_index);
  index = old_index = mid_index = index + 1;
  rep.replace("$$", "$");
  rep.replace("$;", ";");

  qsl << rep;
 }

 result.resize(qsl.size());

 std::transform(qsl.begin(), qsl.end(), result.begin(),
   [this](QString qs) { return read_value_expression(qs); });

 return result;

}


