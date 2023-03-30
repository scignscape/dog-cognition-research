
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PDF_DOCUMENT_STATE__H
#define PDF_DOCUMENT_STATE__H

#include <QLabel>
#include <QRectF>


#include <QMenu>
#include <QAction>
#include <QRubberBand>

#include <QPixmap>

#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "accessors.h"

#include "global-types.h"

class PDF_Document_State
{
 u4 current_page_;
 u4 current_print_page_;
 QString current_print_page_string_;

 r8 current_scale_factor_;

 QPair<u4, u4> current_physical_dpis_;


public:

 PDF_Document_State();

 ACCESSORS(u4 ,current_page)
 ACCESSORS(r8 ,current_scale_factor)
 ACCESSORS(MACRO_PASTE(QPair<u4, u4>) ,current_physical_dpis)

 void reset_pages();


};

#endif
