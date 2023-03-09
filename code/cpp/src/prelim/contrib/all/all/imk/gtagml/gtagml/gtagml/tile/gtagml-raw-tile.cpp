
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-raw-tile.h"

#include "kans.h"

USING_KANS(GTagML)


GTagML_Raw_Tile::GTagML_Raw_Tile(QString format, QString text)
 : format_(format), text_(text)
{

}


QString GTagML_Raw_Tile::thumbnail()
{
 return format_ + "<raw>";
}


