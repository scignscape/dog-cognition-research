
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ChTR_CHVM_LINE__H
#define ChTR_CHVM_LINE__H

#include "global-types.h"

#include "aqns.h"
AQNS_(Chasm_TR)


class ChTR_CHVM_Line
{
 u4 line_id_;

 QStringList preambles_;

 QString text_;

public:

 ChTR_CHVM_Line(u4 line_id, QString text);

 void pre(QStringList p);
 void pre_blank();

 QString get_text();

};


_AQNS(Chasm_TR)

#endif //  ChTR_CHVM_LINE

