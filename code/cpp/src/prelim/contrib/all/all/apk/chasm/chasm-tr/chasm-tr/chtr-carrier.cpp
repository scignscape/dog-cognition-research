

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "chtr-carrier.h"

#include <QDebug>


USING_AQNS(Chasm_TR)


ChTR_Carrier::ChTR_Carrier(QString symbol)
  :  symbol_(symbol)
{

}


QString ChTR_Carrier::composite_symbol()
{
 if(namespace_.isEmpty())
   return symbol_;
 return "%1:\\%2"_qt.arg(namespace_).arg(symbol_);
}


void ChTR_Carrier::check_literal()
{
 if(literal_info.tbd())
   parse_literal_info();

 QPair<QString, QString> lit = literal_info_string();

 qDebug() << "lit = " << lit;
}

QPair<QString, QString> ChTR_Carrier::literal_info_string()
{
 if(literal_info.flags.known_symbol)
   return {".%1"_qt.arg(namespace_.isEmpty()? "v;" : namespace_),
     symbol_};

 QString result;
 if(literal_info.flags.signed_as_negative)
   result = "n";
 else if(literal_info.flags.signed_as_positive)
   result = "p";
 else if(literal_info.flags.unsigned_integer)
   result = "u";

 if(literal_info.flags.unsigned_decimal)
   result += "d";
 else if(literal_info.flags.signed_decimal)
   return {result + "s", trimmed_symbol()};

 if(literal_info.flags.base_10)
   return {result + QString::number(10), trimmed_symbol()};
 if(literal_info.flags.base_16)
   return {result + QString::number(16), trimmed_symbol()};
 if(literal_info.flags.base_2)
   return {result + QString::number(2), trimmed_symbol()};
 if(literal_info.flags.base_8)
   return {result + QString::number(8), trimmed_symbol()};

 if(literal_info.flags.base_32)
 {
  if(result.isEmpty())
    return {"b32", trimmed_symbol()};
  return {result + QString::number(32), trimmed_symbol()};
 }

 if(literal_info.flags.base_64)
 {
  if(result.isEmpty())
    return {"b64", trimmed_symbol()};
  return {result + QString::number(64), trimmed_symbol()};
 }

 if(result.isEmpty())
   return {"??", symbol_};

 return {result, symbol_};
}

QString ChTR_Carrier::trimmed_symbol()
{
 if(namespace_.startsWith('\\'))
   return symbol_.mid(namespace_.midRef(1).toInt());
 return symbol_;
}


bool ChTR_Carrier::check_number_form(QStringView qsv)
{
 if(qsv.size() == 0)
   return false;

 if(qsv[0] == '0')
 {
  if(qsv.size() == 1)
    return literal_info.note_base_10();

  QChar c1 = qsv[1];
  if(c1 == 'b')
    return literal_info.note_base_2();
  if(c1 == 'x')
    return literal_info.note_base_16();
  if(c1.isDigit())
    return literal_info.note_base_8();

  if(qsv.size() == 2)
  {
   // //  anything special here?
   return false;
  }
  if(qsv[2] == ':')
  {
   if(c1 == 's')
     return literal_info.flags.base_64 = true;
   if(c1 == 'z')
     return literal_info.flags.base_32 = true;
  }
  return false;
 }
 return literal_info.note_base_10();
}

#define _note_base_impl(b) \
inline bool ChTR_Carrier::Literal_Info::note_base_##b() \
{ \
 flags.unsigned_integer = !(flags.signed_as_negative || flags.signed_as_positive); \
 return flags.base_##b = true; \
}

_note_base_impl(10)
_note_base_impl(8)
_note_base_impl(2)
_note_base_impl(16)




bool ChTR_Carrier::parse_literal_info()
{
 // //  assume symbol is not empty

 static auto starts_and_not_ends = [this](char c)
 {
  return symbol_.startsWith(c) && !symbol_.endsWith(c);
 };

 u1 start = 0;

 if(start += starts_and_not_ends('+'))
   literal_info.flags.signed_as_positive = true;
 else if(start += starts_and_not_ends('-'))
   literal_info.flags.signed_as_negative = true;

 QChar qc = symbol_.at(start);
 if(qc.isDigit())
 {
  s4 indx = symbol_.indexOf('.', start);
  if(indx == -1)
  {
   if(start == 0)
     return check_number_form(symbol_);

   // // if start is non-zero here then we've seen a + or -
   namespace_ = QString::number(start).prepend('\\');
   return check_number_form(symbol_.midRef(start));
  }
  //if(ind == )

 }

 if(starts_and_not_ends('.'))
 {
  if(symbol_.at(1).isDigit())
    return literal_info.flags.unsigned_decimal = true;
  return literal_info.flags.known_symbol = true;
 }

 if(qc == '.')
 {
  if(start == 0) // //  this would be .xxx.
    return literal_info.flags.known_symbol = true;

  namespace_ = QString::number(start).prepend('\\');
  return literal_info.flags.signed_decimal = true;
 }

 literal_info.flags.known_symbol = true;

 if(start == 1) // // undo the flags, now spurious
   return literal_info.flags.signed_as_negative =
     literal_info.flags.signed_as_positive = false;

 return false;
}

