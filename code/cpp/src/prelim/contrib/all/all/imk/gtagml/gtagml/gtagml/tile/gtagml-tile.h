
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_TILE__H
#define GTAGML_TILE__H

#include <QString>

#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include "whitespace/gtagml-whitespace-holder.h"

#include "kans.h"

class GH_Block_Base;

KANS_(GTagML)

class GH_Prenode;


class GTagML_Tile : public GTagML_Whitespace_Holder
{
 QString raw_text_;

 u4 length_adjustment_;

 GH_Prenode* prenode_;

 void* whitespace_defer_;

public:

 ACCESSORS(QString ,raw_text)
 ACCESSORS(GH_Prenode* ,prenode)

 ACCESSORS(u4 ,length_adjustment)
 ACCESSORS(void* ,whitespace_defer)

 GTagML_Tile(QString raw_text);

 QString to_string();

 u4 effective_length();

 GH_Prenode* init_prenode(GH_Block_Base* block, u4 enter, u4 leave);

 QString thumbnail(int max_characters = 6);

};

_KANS(GTagML)

#endif
