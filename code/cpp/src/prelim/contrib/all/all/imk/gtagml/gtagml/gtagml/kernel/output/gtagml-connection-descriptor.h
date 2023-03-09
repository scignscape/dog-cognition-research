
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_CONNECTION_DESCRIPTOR__H
#define GTAGML_CONNECTION_DESCRIPTOR__H

#include <QString>


#include "kans.h"


KANS_(GTagML)

class GTagML_Connection_Descriptor
{
public:

 enum Descriptors {
   N_A, Tag_Command_Entry, Tag_Command_Main_Tile,
   Closed_Tag_Command_Main_Tile, Tag_Command_Attribute_Tile,
   Tag_Command_Cross, Tag_Command_Cross_From_Blank,
   Tag_Command_Continue, Tag_Command_Continue_From_Blank, Tile_Sequence
 };

private:
  Descriptors descriptor_;

public:

 operator Descriptors() const
 {
  return descriptor_;
 }

 GTagML_Connection_Descriptor(Descriptors descriptor = N_A);
 QString to_string(QString left = QString(), QString right = QString());

};

_KANS(GTagML)


#endif
