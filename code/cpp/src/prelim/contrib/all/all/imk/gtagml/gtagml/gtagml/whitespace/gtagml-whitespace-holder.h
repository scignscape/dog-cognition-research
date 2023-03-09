
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_WHITESPACE_HOLDER__H
#define GTAGML_WHITESPACE_HOLDER__H

#include <QString>

#include "accessors.h"

#include "gtagml-whitespace.h"

#include "kans.h"

KANS_(GTagML)

class GTagML_Whitespace_Holder
{
 GTagML_Whitespace ws_;

 GTagML_Whitespace_Holder* inherited_;

public:

 GTagML_Whitespace_Holder();

 ACCESSORS(GTagML_Whitespace ,ws)
 ACCESSORS(GTagML_Whitespace_Holder* ,inherited)

 QString get_block_whitespace();
 QString get_right_block_whitespace();

 void attach_whitespace(QString whitespace);

 void inherit_whitespace(GTagML_Whitespace_Holder* wsh);

 void get_whitespace_counts_as_inherited(u1* result);

 template<typename T>
 void write_whitespace(T& t)
 {
  t << ws_.to_string();
 }

 template<typename T>
 void write_inherited_whitespace(T& t)
 {
  if(inherited_)
    inherited_->write_whitespace(t);
 }

};

_KANS(GTagML)

#endif
