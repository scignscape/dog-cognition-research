
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

#include "image-viewer/dhax-drawn-shape.h"

#include "image-viewer/dhax-mouse-interaction-data.h"

class MultiLine_Rubber_Band;
class Arrow_Annotation;

class MultiStep_Annotation_Base;

class QScrollArea;

//?
//QSNS_CLASS_DECLARE(Cy_Mesh ,dhax_PDF_View_Dialog)
//USING_QSNS(Cy_Mesh)

class DHAX_PDF_View_Dialog;

class PDF_Document_Info;
class Page_and_Search_Frame;


class PDF_Document_Controller //: public QGraphicsView //QLabel
{
// QMap<int, QGraphicsScene*> scenes_;

// QMap<QGraphicsScene*, QImage> images_;

 Poppler::Document* document_;

 PDF_Document_Info* info_;

 PDF_Document_State state_;

 QPixmap pixmap_;
 QImage image_;

// Arrow_Annotation* current_arrow_annotation_;
 MultiStep_Annotation_Base* current_multistep_annotation_; // current_arrow_annotation_;

 QVector<PDF_Document_Info*> prior_info_;

 Page_and_Search_Frame* page_and_search_frame_;

 DHAX_Mouse_Interaction_Data mouse_interaction_data_;

public:

 PDF_Document_Controller();

 ACCESSORS(Poppler::Document* ,document)
 ACCESSORS(QPixmap ,pixmap)
 ACCESSORS(Page_and_Search_Frame* ,page_and_search_frame)

 ACCESSORS__RGET(DHAX_Mouse_Interaction_Data ,mouse_interaction_data)

 QMatrix matrix() const;
 qreal scale() const;

 //   int init_images(QMap<int, QMap<QImage*, QString> >& images);

 int number_of_pages();

 void load_document(QString file_path);

 void switch_to_page(u4 page);
 void load_page(QPair<u4, u4> physical_dpis);
 void load_page(u4 page, r8 scale_factor, QPair<u4, u4> physical_dpis);

 QList<QUrl> url_list_;

 MultiStep_Annotation_Base* init_multistep_annotation(QWidget* parent,
   const QPointF posf, DHAX_Annotation_Instance::Compact_Shape_Kind_Summary shape_kind);

//    int currentPage;
//    QPoint dragPosition;
//    MultiLine_Rubber_Band* rubberBand;

//    QRectF searchLocation;
//    qreal scaleFactor;
};

#endif
