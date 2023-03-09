
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-tile.h"

#include "gh/gh-prenode.h"

#include "kans.h"

USING_KANS(GTagML)


GTagML_Tile::GTagML_Tile(QString raw_text)
  :  raw_text_(raw_text), whitespace_defer_(nullptr),
     prenode_(nullptr), length_adjustment_(0)
{

}

GH_Prenode* GTagML_Tile::init_prenode(GH_Block_Base* block, u4 enter, u4 leave)
{
 prenode_ = new GH_Prenode(block, enter, leave);
 return prenode_;
}


u4 GTagML_Tile::effective_length()
{
 return raw_text_.size() - length_adjustment_;
}

QString GTagML_Tile::thumbnail(int max_characters)
{
 QString result;
 if(raw_text_.size() > max_characters)
 {
  result += raw_text_.left(max_characters - 3) + "...";
 }
 else
 {
  result += raw_text_;
 }
 return result;
}

QString GTagML_Tile::to_string()
{
 QString result = raw_text_;
 return result;
}


