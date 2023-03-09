
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-attribute-tile.h"

#include "kans.h"

USING_KANS(GTagML)


GTagML_Attribute_Tile::GTagML_Attribute_Tile(QString key, QString value)
 : key_(key), value_(value)
{

}


QString GTagML_Attribute_Tile::thumbnail()
{
 return key_ + "=...";
}


