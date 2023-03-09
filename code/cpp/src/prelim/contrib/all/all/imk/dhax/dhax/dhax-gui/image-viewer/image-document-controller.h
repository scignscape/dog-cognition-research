
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef IMAGE_DOCUMENT_CONTROLLER__H
#define IMAGE_DOCUMENT_CONTROLLER__H

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

//?#include "pdf-document-state.h"

#include "image-viewer/dhax-drawn-shape.h"

#include "image-viewer/dhax-mouse-interaction-data.h"

#include "xcsd-2d/local-histogram-data.h"

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

class DHAX_Mouse_Interaction_Data;

class Image_Document_Controller //: public QGraphicsView //QLabel
{
// QPixmap pixmap_;
// QImage image_;

 MultiStep_Annotation_Base* current_multistep_annotation_; // current_arrow_annotation_;

 DHAX_Mouse_Interaction_Data mouse_interaction_data_;

 QString current_file_path_;

 QVector<Local_Histogram_Data>* local_histogram_data_;

 u2 marked_foreground_pole_;
 u2 marked_background_pole_;

public:

 Image_Document_Controller();

 ACCESSORS__RGET(DHAX_Mouse_Interaction_Data ,mouse_interaction_data)

 ACCESSORS(QString ,current_file_path)
 ACCESSORS(QVector<Local_Histogram_Data>* ,local_histogram_data)


 ACCESSORS(u2 ,marked_foreground_pole)
 ACCESSORS(u2 ,marked_background_pole)

 ACCESSORS(MultiStep_Annotation_Base* ,current_multistep_annotation) // current_arrow_annotation_;)

 QString current_file_path_with_presuffix(QString pres);

 MultiStep_Annotation_Base* init_multistep_annotation(QWidget* parent,
   const QPointF posf, DHAX_Annotation_Instance::Compact_Shape_Kind_Summary shape_kind);

#ifdef USE_XCSD
 QPair<QColor, QColor> get_fb_poles();
#endif//def USE_XCSD
};

#endif
