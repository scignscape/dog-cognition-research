
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QtGui>

#include "pdf-document-state.h"


PDF_Document_State::PDF_Document_State()
  : current_page_(0), current_print_page_(0), current_scale_factor_(1)
{

}

void PDF_Document_State::reset_pages()
{
 current_page_ = 1;
 current_print_page_ = 1;
 current_print_page_string_.clear();
}


