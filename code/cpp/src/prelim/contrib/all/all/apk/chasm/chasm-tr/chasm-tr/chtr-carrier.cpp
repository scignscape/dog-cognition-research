

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#include "chtr-carrier.h"


USING_AQNS(Chasm_TR)


ChTR_Carrier::ChTR_Carrier(QString symbol)
  :  symbol_(symbol)
{

}


void ChTR_Carrier::check_literal()
{
 if(literal_info.tbd())
   parse_literal_info();
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
  s4 ind = symbol_.indexOf('.', start);
  if(ind == -1)
  {
   if(start == 0)
   {
    if(symbol_[0] == '.')
      return literal_info.flags.unsigned_decimal = true;
    return check_number_form(symbol_);
   }
   // // if start is non-zero here then we've seen a + or -
   return check_number_form(symbol_.midRef(1));
  }
  //if(ind == )

 }
}

