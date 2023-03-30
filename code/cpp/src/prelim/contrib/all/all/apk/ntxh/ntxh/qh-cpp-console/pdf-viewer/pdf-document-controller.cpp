
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


//#include <QtGui>

#include "pdf-document-controller.h"

//#include "pleneviews/page-and-search-frame.h"
//#include "aforms/multiline-rubber-band.h"
//#include "aforms/rotateable-arrow-annotation.h"
//#include "aforms/measurement-annotation.h"
//#include "aforms/skew-rhombus-annotation.h"
//#include "aforms/simple/simple-rectangle-annotation.h"
//#include "aforms/simple/simple-ellipse-annotation.h"

#include "pdf-document-info.h"

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

#include <QUrl>


PDF_Document_Controller::PDF_Document_Controller()
 : document_(nullptr)//, page_and_search_frame_(nullptr)
  // context_menu_rubber_band_(nullptr),
  // current_multistep_annotation_(nullptr)
{

}


void PDF_Document_Controller::load_page(QPair<u4, u4> physical_dpis)
{
 u4 current_page = state_.current_page();
 if(current_page > 0)
   load_page(current_page, state_.current_scale_factor(), physical_dpis);
}


void PDF_Document_Controller::switch_to_page(u4 page)
{
 state_.set_current_page(page);
 load_page(page, state_.current_scale_factor(), state_.current_physical_dpis());
}


void PDF_Document_Controller::load_page(u4 page, r8 scale_factor, QPair<u4, u4> physical_dpis)
{
 //image_ = document_->page(page);

 Poppler::Page* pg = document_->page(page);

 if(!pg)
   return;

 state_.set_current_physical_dpis(physical_dpis);

 image_ = pg->renderToImage(scale_factor * physical_dpis.first, scale_factor * physical_dpis.second);

 //images_[scene] = image;

 set_pixmap(QPixmap::fromImage(image_));
// QGraphicsItem* gi = scene->addPixmap(pixmap_);
// gi->setZValue(-1);
// gi->setFlag(QGraphicsItem::ItemIsMovable);
// scenes_[currentPage] = scene;


}


void PDF_Document_Controller::load_document(QString file_path)
{

 //setPixmap(QPixmap::fromImage(image))

 Poppler::Document* doc = Poppler::Document::load(file_path);
 if (doc)
 {
  state_.reset_pages();

  Poppler::Document* former = document_;
  if(former)
  {
   prior_info_.push_back(info_);
   delete former;
  }

  document_ = doc;

  info_ = new PDF_Document_Info;
  info_->set_file_path(file_path);

  u4 np = doc->numPages();
  //?page_and_search_frame_->reset_page_count(np);

  //scenes_.clear();
  for(int i = 0; i < doc->numPages(); i++)
  {
   Poppler::Page *p = doc->page(i);
   for(Poppler::Link *li : p->links())
   {
    if(li->linkType() == Poppler::Link::Browse)
    {
     Poppler::LinkBrowse* link = static_cast<Poppler::LinkBrowse*>(li);
     info_->add_url(link->url());
     //url_list_.append(QUrl(link->url()));
    }
   }
  }

  doc->setRenderHint(Poppler::Document::Antialiasing);
  doc->setRenderHint(Poppler::Document::TextAntialiasing);

 }
}


