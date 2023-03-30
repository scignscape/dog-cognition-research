
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PDF_DOCUMENT_INFO__H
#define PDF_DOCUMENT_INFO__H

#include <QLabel>
#include <QRectF>


//?
#include "poppler/qt5/poppler-qt5.h"

#include <QMenu>
#include <QAction>
#include <QRubberBand>

#include <QPixmap>

#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "accessors.h"

#include "qsns.h"

class MultiLine_Rubber_Band;
class Arrow_Annotation;

class MultiStep_Annotation_Base;

class QScrollArea;

//?
//QSNS_CLASS_DECLARE(Cy_Mesh ,dhax_PDF_View_Dialog)
//USING_QSNS(Cy_Mesh)

class DHAX_PDF_View_Dialog;


class PDF_Document_Info //: public QGraphicsView //QLabel
{
 QString file_path_;
 QList<QUrl> url_list_;


public:

 PDF_Document_Info();

 ACCESSORS(QString ,file_path)
 ACCESSORS__CONST_RGET(QList<QUrl> ,url_list)

 void add_url(QUrl url);

};

#endif
