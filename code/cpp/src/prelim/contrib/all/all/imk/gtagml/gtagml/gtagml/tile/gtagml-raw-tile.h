
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_RAW_TILE__H
#define GTAGML_RAW_TILE__H

#include <QString>

#include "accessors.h"
#include "flags.h"

#include "whitespace/gtagml-whitespace-holder.h"

#include "kans.h"

KANS_(GTagML)

class GTagML_Raw_Tile : public GTagML_Whitespace_Holder
{
 QString format_;
 QString text_;

public:

 ACCESSORS(QString ,format)
 ACCESSORS(QString ,text)

 GTagML_Raw_Tile(QString format, QString text);


 QString thumbnail();

};

_KANS(GTagML)

#endif // GTAGML_RAW_TILE__H

