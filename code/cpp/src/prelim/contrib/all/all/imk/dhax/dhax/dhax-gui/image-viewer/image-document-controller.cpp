
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QtGui>

#include "image-document-controller.h"

#include "pleneviews/page-and-search-frame.h"

#include "aforms/multiline-rubber-band.h"
#include "aforms/rotateable-arrow-annotation.h"
#include "aforms/measurement-annotation.h"
#include "aforms/skew-rhombus-annotation.h"

#include "aforms/simple/simple-rectangle-annotation.h"
#include "aforms/simple/simple-ellipse-annotation.h"
#include "aforms/simple/simple-polyline-annotation.h"

#include "xcsd-2d/xcsd-image.h"

//#include "pdf-document-info.h"

//#include "multiline-rubber-band.h"

////#include <QRubberBand>

//#include <QAction>
//#include <QMenu>

//#include <QScrollBar>

//#include <QScrollArea>

//#include <QMessageBox>

//#include <poppler-qt5.h>

//#include <QDataStream>

//#include "subwindows/pdf-document-widget.h"

//#include "paraviews/dhax-pdf-view-dialog.h"

//#include "rotateable-arrow-annotation.h"

//#include "multiline-rubber-band.h"


Image_Document_Controller::Image_Document_Controller()
  :  local_histogram_data_(nullptr),
     marked_foreground_pole_(-1), marked_background_pole_(-1)
 //: document_(nullptr) //, page_and_search_frame_(nullptr)
  // context_menu_rubber_band_(nullptr),
  // current_multistep_annotation_(nullptr)
{

}

MultiStep_Annotation_Base* Image_Document_Controller::init_multistep_annotation(
  QWidget* parent, const QPointF posf,
  DHAX_Annotation_Instance::Compact_Shape_Kind_Summary shape_kind)
{
 current_multistep_annotation_ = nullptr;
 switch(shape_kind)
 {
 case DHAX_Annotation_Instance::Compact_Shape_Kind_Summary::Arrow:
  current_multistep_annotation_ = new Rotateable_Arrow_Annotation(mouse_interaction_data_, posf, parent);
  break;

 case DHAX_Annotation_Instance::Compact_Shape_Kind_Summary::Multiline:
  current_multistep_annotation_ = new MultiLine_Rubber_Band(mouse_interaction_data_, QRubberBand::Rectangle, posf, parent);
  break;

 case DHAX_Annotation_Instance::Compact_Shape_Kind_Summary::Measurement:
  current_multistep_annotation_ = new Measurement_Annotation(mouse_interaction_data_, posf, parent);
  break;

 case DHAX_Annotation_Instance::Compact_Shape_Kind_Summary::Rectangle:
  current_multistep_annotation_ = new Simple_Rectangle_Annotation(mouse_interaction_data_, posf, parent);
  break;

 case DHAX_Annotation_Instance::Compact_Shape_Kind_Summary::Ellipse:
  current_multistep_annotation_ = new Simple_Ellipse_Annotation(mouse_interaction_data_, posf, parent);
  break;

 case DHAX_Annotation_Instance::Compact_Shape_Kind_Summary::Non_Regular_Polygon:
  current_multistep_annotation_ = new Simple_Polyline_Annotation(mouse_interaction_data_, posf, parent);
  break;

 case DHAX_Annotation_Instance::Compact_Shape_Kind_Summary::Skew_Rhombus:
  current_multistep_annotation_ = new Skew_Rhombus_Annotation(mouse_interaction_data_, posf, parent);
  break;

 default: break;
 }

 //dragPosition = event->pos();
 //current_multistep_annotation_->show();
 //current_multistep_annotation_->set_image_rectf()
 return current_multistep_annotation_;
}

QString Image_Document_Controller::current_file_path_with_presuffix(QString pres)
{
 QFileInfo qfi(current_file_path_);
 return qfi.absolutePath() + "/" + qfi.completeBaseName() + "." + pres + "." + qfi.suffix();
}

#ifdef USE_XCSD
QPair<QColor, QColor> Image_Document_Controller::get_fb_poles()
{
 QPair<QColor, QColor> result;

 if(marked_foreground_pole_ != (u2) -1)
   result.first = XCSD_Image::rgb555_to_qcolor(marked_foreground_pole_);

 if(marked_background_pole_ != (u2) -1)
   result.second = XCSD_Image::rgb555_to_qcolor(marked_background_pole_);

 return result;
}
#endif
