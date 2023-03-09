
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QtGui>

#include "pdf-document-info.h"


PDF_Document_Info::PDF_Document_Info()
{

}


void PDF_Document_Info::add_url(QUrl url)
{
 url_list_.push_back(url);
}

