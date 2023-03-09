

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gh-prenode.h"

#include "gh-block-base.h"


USING_KANS(GTagML)


GH_Prenode::GH_Prenode()
 : range_({0, 0}), raw_text_(nullptr)
{

}

GH_Prenode::GH_Prenode(QString text)
 : range_({1, 1}), raw_text_(new QString(text))
{

}

QString GH_Prenode::get_summary()
{
 static QPair<u4, u4> signal = {1,1};
 QString result;
 if(range_ == signal)
 {
  result = *raw_text_;
  result.prepend('?');
 }
 else
 {
  result = block_->layer_summary();
  result.append(QString(" %1 %2").arg(range_.first).arg(range_.second));
 }
 return result;
}

GH_Block_Base* GH_Prenode::get_block()
{
 static QPair<u4, u4> signal = {1,1};
 if(range_ != signal)
   return block_;
}

QString GH_Prenode::get_string_content()
{
 return *raw_text_;
}


GH_Prenode::GH_Prenode(GH_Block_Base* block, u4 enter, u4 leave)
 : range_({enter, leave}), block_(block)
{

}

