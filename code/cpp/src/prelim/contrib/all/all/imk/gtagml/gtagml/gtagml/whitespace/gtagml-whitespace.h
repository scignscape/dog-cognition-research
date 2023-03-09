
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_WHITESPACE__H
#define GTAGML_WHITESPACE__H

#include "accessors.h"
#include "flags.h"
#include "relae-graph/relae-caon-ptr.h"

#include "global-types.h"


#include <QString>

#include "kans.h"

KANS_(GTagML)

class GTagML_Whitespace
{

 caon_ptr<QString> raw_text_;

public:

 enum class Left_Right_Codes
 {
  N_A = 0, Tile = 1, Enter = 2, Leave = 3, Document = 4, Other = 5
 };

 enum class Space_Codes
 {
  N_A = 0, Space = 1, Line = 2, Comment = 3,
  Comment_Pad = 4, Tab = 5, CR = 6, Other = 7
 };


 GTagML_Whitespace();

 void set_left_code(Left_Right_Codes c);
 void set_right_code(Left_Right_Codes c);
 void set_lr_code(Left_Right_Codes c, u1 shift);

 Left_Right_Codes get_left_code();
 Left_Right_Codes get_right_code();

 explicit GTagML_Whitespace(QString raw_text);

 u1 get_length();

 QString to_string();
 void parse(QString raw_text);

 void get_counts(u1* result);
 void get_counts_as_inherited(u1* result);
};

_KANS(GTagML)

#endif
