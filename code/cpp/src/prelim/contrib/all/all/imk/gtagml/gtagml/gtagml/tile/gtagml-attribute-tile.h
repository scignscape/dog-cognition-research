
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_ATTRIBUTE_TILE__H
#define GTAGML_ATTRIBUTE_TILE__H

#include <QString>

#include "accessors.h"
#include "flags.h"

#include "whitespace/gtagml-whitespace-holder.h"

#include "kans.h"

KANS_(GTagML)

class GTagML_Attribute_Tile : public GTagML_Whitespace_Holder
{
 QString key_;
 QString value_;

public:

 ACCESSORS(QString ,key)
 ACCESSORS(QString ,value)

 GTagML_Attribute_Tile(QString key, QString value);

 template<typename T>
 void write_html(T& t)
 {
  //?
  value_.replace('"', '\\"');
  t << ' ' << key_ << "=\"" << value_ << '\"';
 }

 template<typename T>
 void write_khif(T& t)
 {
  t << " +[@] " << key_ << ' ' << value_ << ' ';
 }

 QString thumbnail();

};

_KANS(GTagML)

#endif
