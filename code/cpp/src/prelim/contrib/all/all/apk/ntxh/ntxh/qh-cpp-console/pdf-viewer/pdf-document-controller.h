
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PDF_DOCUMENT_CONTROLLER__H
#define PDF_DOCUMENT_CONTROLLER__H

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

#include "pdf-document-state.h"


class QScrollArea;


class PDF_Document_Info;


class PDF_Document_Controller //: public QGraphicsView //QLabel
{
// QMap<int, QGraphicsScene*> scenes_;

// QMap<QGraphicsScene*, QImage> images_;

 Poppler::Document* document_;

 PDF_Document_Info* info_;

 PDF_Document_State state_;

 QPixmap pixmap_;
 QImage image_;

 QVector<PDF_Document_Info*> prior_info_;

public:

 PDF_Document_Controller();

 ACCESSORS(Poppler::Document* ,document)
 ACCESSORS(QPixmap ,pixmap)

 QMatrix matrix() const;
 qreal scale() const;

 //   int init_images(QMap<int, QMap<QImage*, QString> >& images);

 int number_of_pages();

 void load_document(QString file_path);

 void switch_to_page(u4 page);
 void load_page(QPair<u4, u4> physical_dpis);
 void load_page(u4 page, r8 scale_factor, QPair<u4, u4> physical_dpis);

 QList<QUrl> url_list_;

};

#endif
