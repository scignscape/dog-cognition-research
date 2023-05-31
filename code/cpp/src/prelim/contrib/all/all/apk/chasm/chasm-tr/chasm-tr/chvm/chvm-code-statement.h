
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef CHVM_CODE_STATEMENT__H
#define CHVM_CODE_STATEMENT__H


#include "accessors.h"

#include "aqns.h"

#include "flags.h"

#include <QFile>
#include <QVector>

//?#include "tsl/ordered_map.h"

#include "global-types.h"

AQNS_(Chasm_TR)

class ChTR_Channel_Package;
class ChTR_Graph;

class ChVM_Code_Statement
{
 QString anchor_;
 ChTR_Channel_Package* channel_package_;

 QVector<QString> code_lines_;

public:


 ChVM_Code_Statement();

 ACCESSORS(QString ,anchor)
 ACCESSORS(ChTR_Channel_Package* ,channel_package)

 void add_code_line(QString line)
 {
  code_lines_.push_back(line);
 }

 QString lines_to_chvm();

};

_AQNS(Chasm_TR)


#endif // CHVM_CODE_STATEMENT__H




