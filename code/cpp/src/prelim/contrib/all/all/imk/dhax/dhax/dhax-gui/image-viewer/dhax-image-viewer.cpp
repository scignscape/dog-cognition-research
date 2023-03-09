
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-image-viewer.h"

#include "dhax-image-scene-item.h"
#include "dhax-display-image-data.h"

#include "dhax-graphics-scene.h"
#include "dhax-graphics-view.h"

#include "application/dhax-application-state.h"

#include "pdf-viewer/pdf-document-controller.h"

#include "image-document-controller.h"


#include <QGraphicsProxyWidget>
#include <QDebug>


DHAX_Image_Viewer::DHAX_Image_Viewer(QWidget* parent)
  :  QWidget(parent), scrolled_image_view_(nullptr),
     scrolled_image_scene_(nullptr),
     scrolled_image_pixmap_item_(nullptr),
     background_rectangle_(nullptr),
     background_center_rectangle_(nullptr),
     background_rectangle_center_x_(0),
     background_rectangle_center_y_(0),
     main_layout_(0),
     image_scene_item_(nullptr),
     display_image_data_(new DHAX_Display_Image_Data),
     main_window_(nullptr),
     pdf_document_controller_(nullptr),
     image_document_controller_(nullptr)
{
}

void DHAX_Image_Viewer::load_pdf_pixmap(PDF_Document_Controller* document_controller)
{
 pdf_document_controller_ = document_controller;
 load_image(document_controller->pixmap());
 scrolled_image_view_->set_pdf_document_controller(document_controller);
}

void DHAX_Image_Viewer::load_image_pixmap(QPixmap pixmap, Image_Document_Controller* document_controller)
{
 scrolled_image_pixmap_ = new QPixmap(pixmap);

 image_document_controller_ = document_controller;
 scrolled_image_view_->set_image_document_controller(document_controller);

 complete_load_image();
}

void DHAX_Image_Viewer::load_image(QString file_path, Image_Document_Controller* document_controller)
{
 scrolled_image_pixmap_ = new QPixmap(file_path);

 image_document_controller_ = document_controller;
 scrolled_image_view_->set_image_document_controller(document_controller);

 complete_load_image();

}


//scrolled_image_view_->set_pdf_document_controller(document_controller);



void DHAX_Image_Viewer::reset_scale(r8 factor)
{
 scrolled_image_view_->resetTransform();
// qDebug() << "factor = " << factor;
 scrolled_image_view_->scale(factor, factor);
 //?
// scrolled_image_pixmap_item_->setScale(factor);
// background_center_rectangle_->setScale(factor);
// background_rectangle_->setScale(factor);
 //?recenter_image();
}


void DHAX_Image_Viewer::mouseMoveEvent(QMouseEvent *mouseEvent)
{
 qDebug() << " ... ";
}

wh2 DHAX_Image_Viewer::dimensions_maxed(u2 y_max)
{
 QSize sz = get_scrolled_image_pixmap_size();
 if(y_max == 0 || sz.height() < y_max)
   return { (u2)sz.width(), (u2) sz.height()};
 return { (u2)sz.width(), y_max};
}

wh2 DHAX_Image_Viewer::dimensions_maxed(wh2 max)
{
 if(max.width == 0)
   return dimensions_maxed(max.width);

 QSize sz = get_scrolled_image_pixmap_size();
 if(max.width < sz.width())
 {
  if(max.height == 0 || sz.height() < max.height)
    return { max.width, (u2) sz.height()};
  return { max.width, max.height};
 }
 if(max.height == 0 || sz.height() < max.height)
   return { (u2)sz.width(), (u2) sz.height()};
 return { (u2)sz.width(), max.height};

}

void DHAX_Image_Viewer::recenter_image()
{
 int w = scrolled_image_pixmap_item_->boundingRect().width() *
   scrolled_image_pixmap_item_->scale();
 int h = scrolled_image_pixmap_item_->boundingRect().height() *
   scrolled_image_pixmap_item_->scale();

 int new_left = background_rectangle_center_x_ - (w/2);
 int new_top = background_rectangle_center_y_ - (h/2);

// qDebug() << "pos = " << scrolled_image_pixmap_item_->pos();
// qDebug() << "new_left = " << new_left << " and new_top = " << new_top;

//?
 scrolled_image_pixmap_item_->setPos(new_left, new_top);
}

DHAX_Graphics_Frame* DHAX_Image_Viewer::get_graphics_frame()
{
 return scrolled_image_scene_->containing_graphics_frame();
}


void DHAX_Image_Viewer::recenter_image_against_margins()
{
// DHAX_Application_State::Image_Margins& im = application_state_->image_margins();
// update_image_margins(im);

 image_scene_item_->reset_background_to_original_position();

 //recenter_image();
}


void DHAX_Image_Viewer::recenter_scroll_center()
{
 if(!image_scene_item_)
   return;

//? image_scene_item_->reset_background_to_original_position();

 scrolled_image_view_->centerOn(background_rectangle_center_x_, background_rectangle_center_y_);
}


void DHAX_Image_Viewer::recenter_scroll_top_left()
{
 if(!image_scene_item_)
   return;

//? image_scene_item_->reset_background_to_original_position();

 qreal width = scrolled_image_view_->viewport()->width();
 qreal height = scrolled_image_view_->viewport()->height();

 QPointF pos = scrolled_image_pixmap_item_->pos();
 pos += {width/2, height/2};

 scrolled_image_view_->centerOn(pos);
}

QSize DHAX_Image_Viewer::get_scrolled_image_pixmap_size()
{
 return scrolled_image_pixmap_->size();
}


void DHAX_Image_Viewer::cancel_notation()
{
 image_scene_item_->cancel_notation();
}


void DHAX_Image_Viewer::draw_circle(const QPointF& center,
  r8 radius, QColor brush_color, QColor pen_color, u1 index)
{
 QBrush qbr(brush_color);
 QPen qpen(pen_color);
 QGraphicsEllipseItem* el = scrolled_image_scene_->addEllipse(center.x() - radius,
   center.y() - radius, radius * 2, radius * 2, qpen, qbr);
 el->setParentItem(scrolled_image_pixmap_item_);
 el->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

 if(index)
   controls_[index] = {el, radius};
}

void DHAX_Image_Viewer::load_image(QPixmap pixmap)
{
 scrolled_image_pixmap_ = new QPixmap(pixmap);
 complete_load_image();
}

void DHAX_Image_Viewer::update_image_margins(const DHAX_Application_State::Image_Margins& im)
{
 if(!scrolled_image_pixmap_)
   return;

 u4 sipw = scrolled_image_pixmap_->width();
 u4 siph = scrolled_image_pixmap_->height();

 u4 background_w, background_h, margin_l, margin_r, margin_t, margin_b,
   margin_with_border_l, margin_with_border_t, image_with_border_w, image_with_border_h;

 if(im.via_percent())
 {
  margin_l = ((r8)im.percent.left / 100) * sipw;
  margin_r = ((r8)im.percent.right / 100) * sipw;
  margin_t = ((r8)im.percent.top / 100) * siph;
  margin_b = ((r8)im.percent.bottom / 100) * siph;
 }

 else
 {
  margin_l = im.left;
  margin_r = im.right;
  margin_t = im.top;
  margin_b = im.bottom;
 }

 if(margin_l < im.border.left)
   margin_l = im.border.left;
 if(margin_r < im.border.right)
   margin_r = im.border.right;
 if(margin_t < im.border.top)
   margin_t = im.border.top;
 if(margin_b < im.border.bottom)
   margin_b = im.border.bottom;

 background_w = sipw + margin_l + margin_r;
 background_h = siph + margin_t + margin_b;
 margin_with_border_l = margin_l - im.border.left;
 margin_with_border_t = margin_t - im.border.top;
 image_with_border_w = sipw + im.border.left + im.border.right;
 image_with_border_h = siph + im.border.top + im.border.bottom;

 background_rectangle_->setRect(0, 0, background_w, background_h);
 background_center_rectangle_->setRect(margin_with_border_l, margin_with_border_t,
   image_with_border_w, image_with_border_h);

 scrolled_image_pixmap_item_->setPos(margin_l, margin_t);
}

void DHAX_Image_Viewer::complete_load_image()
{
 u4 sipw = scrolled_image_pixmap_->width();
 u4 siph = scrolled_image_pixmap_->height();

 const DHAX_Application_State::Image_Margins& im = application_state_->image_margins();

// u4 background_w, background_h, margin_l, margin_r, margin_t, margin_b,
//   margin_with_border_l, margin_with_border_t, image_with_border_w, image_with_border_h;

// if(im.via_percent())
// {
//  margin_l = ((r8)im.percent.left / 100) * sipw;
//  margin_r = ((r8)im.percent.right / 100) * sipw;
//  margin_t = ((r8)im.percent.top / 100) * siph;
//  margin_b = ((r8)im.percent.bottom / 100) * siph;
// }

// else
// {
//  margin_l = im.left;
//  margin_r = im.right;
//  margin_t = im.top;
//  margin_b = im.bottom;
// }

// if(margin_l < im.border.left)
//   margin_l = im.border.left;
// if(margin_r < im.border.right)
//   margin_r = im.border.right;
// if(margin_t < im.border.top)
//   margin_t = im.border.top;
// if(margin_b < im.border.bottom)
//   margin_b = im.border.bottom;

// background_w = sipw + margin_l + margin_r;
// background_h = siph + margin_t + margin_b;
// margin_with_border_l = margin_l - im.border.left;
// margin_with_border_t = margin_t - im.border.top;
// image_with_border_w = sipw + im.border.left + im.border.right;
// image_with_border_h = siph + im.border.top + im.border.bottom;

 background_rectangle_ = scrolled_image_scene_->addRect(0, 0, 0, 0);
 //background_rectangle_ = scrolled_image_scene_->addRect(0, 0, background_w, background_h);

 if(background_center_rectangle_)
   delete background_center_rectangle_;

//?
// if(image_with_border_w % 2)
//   ++image_with_border_w;

// if(image_with_border_h % 2)
//   ++image_with_border_h;

 background_center_rectangle_ = scrolled_image_scene_->addRect(0, 0, 0, 0);

// background_center_rectangle_ = scrolled_image_scene_->addRect(
//   margin_with_border_l, margin_with_border_t,
//   image_with_border_w, image_with_border_h);

 reset_background_rectangle_color();

 background_rectangle_->setPen(Qt::NoPen);

 background_rectangle_center_x_ = background_rectangle_->boundingRect().x() +
   (background_rectangle_->boundingRect().width() / 2);

 background_rectangle_center_y_ = background_rectangle_->boundingRect().y() +
   (background_rectangle_->boundingRect().height() / 2);


 display_image_data_->setView(scrolled_image_pixmap_->toImage());


  // //  always new ?
 image_scene_item_ = new DHAX_Image_Scene_Item;// (this);
 image_scene_item_->set_data(display_image_data_);
 image_scene_item_->set_containing_image_view(scrolled_image_view_);

 if(image_document_controller_)
   image_scene_item_->set_image_file_path(image_document_controller_->current_file_path());

 image_scene_item_->temp = this;

 image_scene_item_->resize(sipw, siph);

 image_scene_item_->setParent(nullptr);
 //image_scene_item_->setParent(background_center_rectangle_);

 //QGraphicsProxyWidget* w =  scrolled_image_scene_->addWidget(image_scene_item_);

 _Proxy_Widget* w = scrolled_image_scene_->add_proxy_widget(image_scene_item_);
// w->setParentItem(background_center_rectangle_);

 //w->setPen(QColor::red);


 //?

 image_scene_item_->set_original_position(background_center_rectangle_->pos());

 background_center_rectangle_->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
 reset_background_center_rectangle_color();

 //
 background_center_rectangle_->setPen(Qt::NoPen); //application_state_->application_color("image-pen-color"));
 //background_center_rectangle_->setPen(QColor("cyan")); //application_state_->application_color("image-pen-color"));

// QGraphicsRectItem* foreground_center_rectangle_ = scrolled_image_scene_->addRect(
//   (sipw/2) - 10, (siph/2) - 10, sipw, siph);
// foreground_center_rectangle_->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
// foreground_center_rectangle_->setVisible(false);
// QBrush qbr;
// qbr.setColor(QColor::fromRgba(qRgba(200, 200, 100, 100)));
// qbr.setStyle(Qt::BrushStyle::SolidPattern);
// foreground_center_rectangle_->setBrush(qbr);

 //foreground_center_rectangle


  w->graphicsItem()->setParentItem(background_center_rectangle_);
  w->graphicsItem()->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

  background_center_rectangle_->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

 image_scene_item_->set_this_proxy_widget(w);
 image_scene_item_->set_background_item(background_center_rectangle_);


 scrolled_image_pixmap_item_ = w;

 update_image_margins(im);

 //QPointF top_left = update_image_margins(im);

 //?w->setPos(sipw/2,siph/2);
 //w->setPos(top_left);

 //?
 recenter_scroll_center();
}

void DHAX_Image_Viewer::reset_background_rectangle_color()
{
 background_rectangle_->setBrush(application_state_->application_colors()->value("scene-margins-color"));
}

void DHAX_Image_Viewer::reset_background_center_rectangle_color()
{
 if(background_center_rectangle_)
 {
  if(application_state_->flags.image_border_visible_fixed | application_state_->flags.image_border_visible_temp)
    background_center_rectangle_->setBrush(application_state_->application_colors()->value("image-background-center-rectangle-color"));
  else
    background_center_rectangle_->setBrush(Qt::NoBrush);
 }
}

