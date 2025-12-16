
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-chvm-line.h"



USING_AQNS(Chasm_TR)


ChTR_CHVM_Line::ChTR_CHVM_Line(u4 line_id, QString text)
  : line_id_(line_id), text_(text)
{
}

void ChTR_CHVM_Line::pre(QStringList p)
{
 preambles_.append(p);
}

void ChTR_CHVM_Line::pre_blank()
{
 pre({"\n"});
}


QString ChTR_CHVM_Line::get_text()
{
 if(preambles_.isEmpty())
   return text_;

 return preambles_.join("") + text_;
}
