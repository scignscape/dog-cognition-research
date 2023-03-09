
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-whitespace-holder.h"

#include "kans.h"

USING_KANS(GTagML)

GTagML_Whitespace_Holder::GTagML_Whitespace_Holder()
  : inherited_(nullptr)
{

}

QString GTagML_Whitespace_Holder::get_right_block_whitespace()
{
 GTagML_Whitespace::Left_Right_Codes lrc = ws_.get_right_code();
 if(lrc == GTagML_Whitespace::Left_Right_Codes::Leave)
   return get_block_whitespace();
 return {};
}

QString GTagML_Whitespace_Holder::get_block_whitespace()
{
 // //  basically just a single space character if one should go into a block ...
 if(ws_.get_length() == 0)
   return {};
 return " ";
}


void GTagML_Whitespace_Holder::get_whitespace_counts_as_inherited(u1* result)
{
 if(inherited_)
   inherited_->ws().get_counts_as_inherited(result);
 else
 {
  result[2] = 0;
  result[3] = 0;
 }
}

void GTagML_Whitespace_Holder::inherit_whitespace(GTagML_Whitespace_Holder* wsh)
{
 inherited_ = wsh;
}


void GTagML_Whitespace_Holder::attach_whitespace(QString whitespace)
{
 ws_ = GTagML_Whitespace(whitespace);
}

