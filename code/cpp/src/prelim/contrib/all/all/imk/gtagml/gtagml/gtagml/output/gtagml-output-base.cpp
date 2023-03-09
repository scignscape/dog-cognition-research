
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gtagml-output-base.h"

#include "kernel/document/gtagml-document.h"

#include <QFile>
#include <QFileInfo>

#include <QDebug>

#include "kans.h"
USING_KANS(GTagML)


GTagML_Output_Base::GTagML_Output_Base(GTagML_Document& document)
 : document_(document), graph_(*document.graph()), qry_(GTagML_Query::instance())
{

}

GTagML_Output_Base::~GTagML_Output_Base()
{
 //qDebug() << "del GTagML_Output_Base";
}



