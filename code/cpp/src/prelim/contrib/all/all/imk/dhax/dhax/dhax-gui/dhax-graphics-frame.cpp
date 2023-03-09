
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dhax-graphics-frame.h"

#include "pleneviews/shape-select-frame.h"
#include "pleneviews/zoom-and-navigate-frame.h"
#include "pleneviews/page-and-search-frame.h"

#include "dhax-graphics-view.h"

#include "image-viewer/dhax-display-image-data.h"
#include "image-viewer/dhax-image-viewer.h"

#include "global-types.h"

#include "self-connect.h"
#include "stash-signals.h"

#include <QDebug>
#include <QMetaObject>

DHAX_Graphics_Frame::DHAX_Graphics_Frame(QWidget* parent)
  :  QFrame(parent), main_layout_(nullptr),
     shape_select_frame_(nullptr), display_image_data_(nullptr),
     zoom_frame_(nullptr), image_viewer_(nullptr),
     graphics_view_(nullptr), graphics_scene_(nullptr), secondary_layout_(nullptr)
{

}

void DHAX_Graphics_Frame::init_layout(QBoxLayout::Direction qbd,
  QBoxLayout::Direction secqbd)
{
 main_layout_ = new QBoxLayout(qbd);
 secondary_layout_ = new QBoxLayout(secqbd);

 page_and_search_frame_ = new Page_and_Search_Frame(this);
 page_and_search_frame_->setFrameShape(QFrame::Box);
 page_and_search_frame_->setLineWidth(1);
 secondary_layout_->addWidget(page_and_search_frame_);


 shape_select_frame_ = new Shape_Select_Frame(this);
 shape_select_frame_->update_border_color_button_color(application_colors_->value("image-background-center-rectangle-color"));
 shape_select_frame_->update_scene_color_button_color(application_colors_->value("scene-background-color"));
 shape_select_frame_->update_back_color_button_color(application_colors_->value("scene-margins-color"));
 shape_select_frame_->update_image_pen_color_button_color(application_colors_->value("image-pen-color"));


 zoom_frame_ = new Zoom_and_Navigate_Frame(this);

 zoom_frame_->setFrameShape(QFrame::NoFrame);
 zoom_frame_->setLineWidth(0);

 secondary_layout_->addWidget(zoom_frame_);
 secondary_layout_->setStretch(1,40);
 zoom_frame_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
 //QSpacerItem* sp = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
 QSpacerItem* sp = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
 secondary_layout_->addItem(sp);
 secondary_layout_->setStretch(1, 1);
 //secondary_layout_->addStretch(1);
 //secondary_layout_->addWidget(shape_select_frame_, Qt::AlignTop);

// //top_layout_->addWidget(shape_select_frame_, Qt::AlignTop);
 QVBoxLayout* shape_select_frame_position_layout = new QVBoxLayout;
 shape_select_frame_position_layout->addWidget(shape_select_frame_);
 shape_select_frame_position_layout->addStretch();
 //shape_select_frame_position_layout->addSpacing(400);
 secondary_layout_->addLayout(shape_select_frame_position_layout);
// // top_layout_->addStretch(1);


 setFrameShape(QFrame::NoFrame);
 setLineWidth(0);
 setContentsMargins(0,0,0,0);
 secondary_layout_->setContentsMargins(0,0,0,0);
 secondary_layout_->setMargin(0);
 secondary_layout_->setSpacing(0);


 main_layout_->addLayout(secondary_layout_);

 if(graphics_view_)
 {
  main_layout_->addWidget(graphics_view_, 1);

  graphics_view_->set_mouse_keyboard_modifiers_callback([this]
    (DHAX_Mouse_Keyboard_Data mkd)
  {
   if(mkd.Unleft())
   {
    if(display_image_data_->temporary_pan_mode())
    {
     zoom_frame_->unindicate_temporary_modes();
     display_image_data_->unset_temporary_pan_mode();
     graphics_view_->deactivate_hand_drag_mode();
    }
    else if(display_image_data_->temporary_pull_mode())
    {
     zoom_frame_->unindicate_temporary_modes();
     display_image_data_->unset_temporary_pull_mode();
    }
   }

   else if(mkd.Ctrl_left() || (mkd.Meta_left() && mkd.Shift_left()))
   {
    zoom_frame_->indicate_temporary_pull_mode();
    display_image_data_->set_temporary_pull_mode();
   }

   else if(mkd.Shift_left() || mkd.Meta_left())
   {
    zoom_frame_->indicate_temporary_pan_mode();
    display_image_data_->set_temporary_pan_mode();
    graphics_view_->activate_hand_drag_mode();
   }

   else if(mkd.Unctrl_left() || (mkd.Unmeta_left() && mkd.Unshift_left()))
   {
    zoom_frame_->unindicate_temporary_pull_mode();
    display_image_data_->unset_temporary_pull_mode();
   }

   else if(mkd.Unshift_left() || mkd.Unmeta_left())
   {
    zoom_frame_->unindicate_temporary_pan_mode();
    display_image_data_->unset_temporary_pan_mode();
    graphics_view_->deactivate_hand_drag_mode();
   }


//   qDebug() << "ks = " << ks;

//   if(qmo == &DHAX_Graphics_View::staticMetaObject)
//   {
//    qDebug() << qmo->className();
//    static const QMetaObject* s = &DHAX_Mouse_Keyboard_Protocol::staticMetaObject;
//    qDebug() << s->className();
//    if(qmo->inherits(s))
//    {
//     qDebug() << "qmo->className();";
//    }
//   }

  });
 }

 info_label_ = new QLabel("No image", this);

 info_label_->setStyleSheet("QLabel{background-color:rgb(234,247,255);"
   "padding: 0px 0px 0px 40px;border-top: 2px ridge orange;"
                            "font-size:7pt;color:rgb(80,60,70);}");

 main_layout_->addWidget(info_label_);

 main_layout_->setContentsMargins(0,0,0,0);
 main_layout_->setMargin(0);
 main_layout_->setSpacing(0);

 this->setFrameShape(QFrame::NoFrame);
 this->setLineWidth(0);

 setLayout(main_layout_);

//? zoom_frame_->self_connect(SIGNAL(zoom_factor_changed(r8)), this, SLOT(handle_zoom_factor_changed(r8)));

// connect(shape_select_frame_, &Shape_Select_Frame::save_requested,
//   this, &DHAX_Graphics_Frame::save_requested);




 _self_connect_(zoom_frame_ ,zoom_factor_changed)
   _to_this_(handle_zoom_factor_changed);


 _self_connect_(shape_select_frame_ ,save_requested)
   _to_this_(save_requested);

 _self_connect_(shape_select_frame_ ,image_path_show_folder_requested)
   to_coemit(bool)(image_path_show_folder_requested);

 _self_connect_(shape_select_frame_ ,change_border_color_requested)
   to_coemit(bool)(change_image_border_color_requested);

 _self_connect_(shape_select_frame_ ,change_scene_color_requested)
   _to_this_(change_scene_background_color_requested);

 _self_connect_(shape_select_frame_ ,change_back_color_requested)
   _to_this_(change_scene_margins_color_requested);

 _self_connect_(shape_select_frame_ ,change_border_visible_state_requested)
   to_lambda[this] (bool state)
 {
  if(state)
    Q_EMIT set_border_visible_requested();
  else
    Q_EMIT unset_border_visible_requested();
 };

 _self_connect_(shape_select_frame_ ,change_image_pen_visible_state_requested)
   to_lambda[this] (bool state)
 {
  if(state)
    Q_EMIT set_image_pen_visible_requested();
  else
    Q_EMIT unset_image_pen_visible_requested();
 };

 _self_connect_(shape_select_frame_ ,edit_transform_open_automatically_requested)
   to_lambda[this] (bool state)
 {
  if(state)
    Q_EMIT set_edit_transform_open_automatically_requested();
  else
    Q_EMIT unset_edit_transform_open_automatically_requested();
 };

// shape_select_frame_->_self_connect(&Shape_Select_Frame::change_scene_color_requested)
//   (this, &DHAX_Graphics_Frame::change_scene_background_color_requested);

//?   to_coemit(bool)(change_scene_background_color_requested);


   // _self_connect_(shape_select_frame_ ,change_scene_color_requested)
   //   to_lambda[this] (bool) coemit(change_scene_background_color_requested);
// _self_connect_(shape_select_frame_ ,change_scene_color_requested)
//   to_lambda_coemit (bool) re(change_scene_background_color_requested());

// {
//  Q_EMIT change_scene_background_color_requested();
// };

 _self_connect_(shape_select_frame_ ,change_border_width_requested)
   to_lambda[this] (u1 width)
 {
  Q_EMIT change_image_margins_requested({width},
     (u1) Change_Image_Margins::Image_Border1);
 };

 _self_connect_(shape_select_frame_ ,change_vertical_margin_percent_requested)
   to_lambda[this] (u1 xy, bool and_sides)
 {
  if(and_sides)
    Q_EMIT change_image_margins_requested({xy},
       (u1) Change_Image_Margins::Vertical_and_Horizontal_Percent);

  else
    Q_EMIT change_image_margins_requested({xy, xy},
       (u1) Change_Image_Margins::Vertical_Percent);

  //Q_EMIT change_image_border_color_requested();
 };

 _self_connect_(shape_select_frame_ ,change_vertical_margin_requested)
   to_lambda[this] (u1 xy, bool and_sides)
 {
  if(and_sides)
    Q_EMIT change_image_margins_requested({xy},
       (u1) Change_Image_Margins::Vertical_and_Horizontal);

  else
    Q_EMIT change_image_margins_requested({xy, xy},
       (u1) Change_Image_Margins::Vertical);

  //Q_EMIT change_image_border_color_requested();
 };

 //change_vertical_margin_percent_requested

 shape_select_frame_->self_connect(SIGNAL(close_requested(bool)), this, SIGNAL(close_requested(bool)));

 _self_connect_(zoom_frame_ ,image_top_left_button_clicked)
   to_coemit(void)(image_viewer_->recenter_scroll_top_left);
//   to_lambda[this](bool)
// {
//  image_viewer_->recenter_scroll_top_left();
// };

 _self_connect_(zoom_frame_ ,center_image_button_clicked)
   to_coemit()(image_viewer_->recenter_scroll_center);

 _self_connect_(zoom_frame_ ,replace_center_image_button_clicked)
   to_coemit()(image_viewer_->recenter_image_against_margins);


 _self_connect_(zoom_frame_ ,expand_window_button_clicked)
   to_coemit()(expand_window_requested);

//   to_lambda[this](bool)
// {
//  Q_EMIT expand_window_requested();
// };

 _self_connect_(zoom_frame_ ,unexpand_window_button_clicked)
   to_coemit()(unexpand_window_requested);

//   to_lambda[this](bool)
// {
//  Q_EMIT unexpand_window_requested();
// };


// {
//  image_viewer_->recenter_scroll_center();
// };

 _self_connect_(zoom_frame_ ,pan_mode_changed)
   to_lambda[this](bool mode)
 {
  if(mode)
  {
   display_image_data_->unset_fixed_pull_mode();
   display_image_data_->set_fixed_pan_mode();
   graphics_view_->activate_hand_drag_mode();
  }
  else
  {
   display_image_data_->unset_fixed_pan_mode();
   graphics_view_->deactivate_hand_drag_mode();
  }

//  if(mode)
//  {
//   display_image_data_->unset_pull_mode();
//   display_image_data_->set_pan_mode();
//   graphics_view_->activate_hand_drag_mode();
//  }
//  else
//  {
//   display_image_data_->unset_pan_mode();
//   graphics_view_->deactivate_hand_drag_mode();
//  }

 };

 _self_connect_(zoom_frame_ ,pull_mode_changed)
   to_lambda[this](bool mode)
 {
  if(mode)
  {
   if(display_image_data_->pan_modes())
   {
    display_image_data_->unset_pan_modes();
    graphics_view_->deactivate_hand_drag_mode();
   }
   display_image_data_->set_fixed_pull_mode();
  }
  else
  {
   display_image_data_->unset_pull_modes();
  }

//  if(mode)
//  {
//   if(display_image_data_->pan_mode())
//   {
//    display_image_data_->unset_pan_mode();
//    graphics_view_->deactivate_hand_drag_mode();
//   }
//   display_image_data_->set_pull_mode();
//  }
//  else
//  {
//   display_image_data_->unset_pull_mode();
//  }

 };

 _self_connect_(zoom_frame_ ,multi_draw_set)
   to_lambda[this]()
 {
  display_image_data_->set_multi_draw();
 };

 _self_connect_(zoom_frame_ ,multi_draw_unset)
   to_lambda[this]()
 {
  display_image_data_->unset_multi_draw();
 };


 // assume a rectangle to begin with ...
 setup_rectangle_shape();

 _self_connect_(shape_select_frame_ ,shape_selection_changed)
   to_lambda[this](QString sel)
 {
  if(sel == "Rectangle")
    setup_rectangle_shape();
  else if(sel == "Polygon")
    setup_polygon_shape();
  else if(sel == "Ellipse")
    setup_ellipse_shape();
  else if(sel == "Multi-Line")
    setup_multiline_shape();
  else if(sel == "Arrow")
    setup_arrow_shape();
  else if(sel == "Measurement")
    setup_measurement_shape();
  else if(sel == "Skew/Rhombus")
    setup_skew_rhombus_shape();

 };
}

//info_label_

void DHAX_Graphics_Frame::show_info(QString text)
{
 info_label_->setText(text);
}

QSize DHAX_Graphics_Frame::get_scrolled_image_pixmap_size()
{
 return image_viewer_->get_scrolled_image_pixmap_size();
}

void DHAX_Graphics_Frame::handle_zoom_factor_changed(r8 factor)
{
// qDebug() << "factor: " << factor;

 image_viewer_->reset_scale(factor);
}


void DHAX_Graphics_Frame::setup_rectangle_shape()
{
 display_image_data_->reset();
 display_image_data_->enable_rectangle_shape();
}

void DHAX_Graphics_Frame::setup_polygon_shape()
{
 display_image_data_->reset();
 display_image_data_->enable_polygon_shape();
}

void DHAX_Graphics_Frame::setup_ellipse_shape()
{
 display_image_data_->reset();
 display_image_data_->enable_ellipse_shape();
}

void DHAX_Graphics_Frame::setup_multiline_shape()
{
 display_image_data_->reset();
 display_image_data_->enable_multiline_shape();
}

void DHAX_Graphics_Frame::setup_arrow_shape()
{
 display_image_data_->reset();
 display_image_data_->enable_arrow_shape();
}

void DHAX_Graphics_Frame::setup_skew_rhombus_shape()
{
 display_image_data_->reset();
 display_image_data_->enable_skew_rhombus_shape();
}

void DHAX_Graphics_Frame::setup_measurement_shape()
{
 display_image_data_->reset();
 display_image_data_->enable_measurement_shape();
}

void DHAX_Graphics_Frame::setup_highlight(bool checked)
{
 display_image_data_->enableHighlight(checked);
}
