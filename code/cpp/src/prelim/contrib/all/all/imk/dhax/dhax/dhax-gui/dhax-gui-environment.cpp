
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-gui-environment.h"

#include "main-window/dhax-main-window.h"
#include "dhax-graphics-view.h"
#include "main-window/dhax-main-window-frame.h"
#include "main-window/dhax-main-window-controller.h"
#include "main-window/dhax-main-window-receiver.h"
#include "dhax-graphics-frame.h"
#include "dhax-graphics-scene.h"

#include "dhax-signal-generator.h"

#include "dhax-data/ann/dhax-annotation-environment.h"
#include "dhax-data/ann/dhax-annotation-instance.h"

#include "dhax-gui/image-viewer/dhax-image-viewer.h"

#include "dhax-gui/image-viewer/dhax-display-image-data.h"

#include "network/dhax-udp-controller.h"

#include "virtual-packages/graphics-scene-demo.h"

#include "main-window/dhax-menu-system.h"

#include "application/dhax-application-controller.h"

#include "main-window/dhax-main-window-data.h"

#include "application/dhax-application-receiver.h"
#include "application/dhax-external-application-controller.h"


#include <QBoxLayout>
#include <QLabel>

#include <QDebug>

#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QSlider>
#include <QButtonGroup>
#include "subwindows/range-slider.h"

#include <type_traits>

#include "stash-signals.h"
#include "stash-signals-alt-base.h"

#include "application/dhax-application-state.h"

DHAX_GUI_Environment::DHAX_GUI_Environment()
  :  main_window_(nullptr),
     main_window_controller_(nullptr),
     application_controller_(nullptr),
     external_application_controller_(nullptr),
     menu_system_(nullptr),
     graphics_view_(nullptr),
     main_window_frame_(nullptr),
     graphics_scene_(nullptr),
     graphics_frame_(nullptr),
     image_viewer_(nullptr),
     udp_controller_(nullptr),
     last_loaded_vpo_(nullptr)
{
}

void DHAX_GUI_Environment::init_stashed_signals()
{
 #include "stash-signals-list.h"

// stash_signal(QPushButton::clicked);
// stash_signal(QCheckBox::stateChanged);
// stash_signal(QCheckBox::clicked);
// stash_signal(QComboBox::currentTextChanged);
// stash_signal(ctkRangeSlider::minimumValueChanged);
// stash_signal(ctkRangeSlider::maximumValueChanged);
// stash_signal(ctkRangeSlider::valueChanged);
// stash_signal(QSlider::valueChanged);
// stash_signal(QAbstractSlider::valueChanged);
// stash_signal(QButtonGroup::idClicked);
}

void DHAX_GUI_Environment::init_application_state()
{
 application_state_ = new DHAX_Application_State;
 application_state_->set_application_colors(new QMap<QString, QColor>
 {
  {"image-background-center-rectangle-color", Qt::darkCyan},
  {"scene-background-color", Qt::lightGray},
  {"scene-margins-color", Qt::white},
  {"image-pen-color", Qt::darkMagenta},

 });
}

DHAX_Annotation_Environment*
 DHAX_GUI_Environment::init_annotation_environment()
{
 annotation_environment_ = new DHAX_Annotation_Environment;
 return annotation_environment_;
}


void DHAX_GUI_Environment::init_main_window()
{
 main_window_ = new DHAX_Main_Window;
}


void DHAX_GUI_Environment::init_integration_controllers()
{
 application_controller_->init_integration_controllers();
}


void DHAX_GUI_Environment::init_udp_controller()
{
 udp_controller_ = new DHAX_UDP_Controller;
 udp_controller_->set_signal_generator(main_window_->signal_generator());

 main_window_->signal_generator()->connect(main_window_->signal_generator(),
   &DHAX_Signal_Generator::received_datagram,
   [this](QByteArray qba)
 {
  application_controller_->dispatch_datagram(qba);
 });
}

void DHAX_GUI_Environment::init_menu_system()
{
 menu_system_ = new DHAX_Menu_System;
 menu_system_->set_main_window(main_window_);
 menu_system_->init_menus();

}


void DHAX_GUI_Environment::init_main_window_data()
{
 main_window_->set_main_window_data(new DHAX_Main_Window_Data);
}

void DHAX_GUI_Environment::init_external_application_controller()
{
 external_application_controller_ = new DHAX_External_Application_Controller;
 application_receiver_->set_external_application_controller(external_application_controller_);
 external_application_controller_->set_application_controller(application_controller_);
 external_application_controller_->set_application_main_window(main_window_);
}

void DHAX_GUI_Environment::init_application_controller()
{
 application_controller_ = new DHAX_Application_Controller;
 application_controller_->set_application_state(application_state_);
 application_controller_->set_menu_system(menu_system_);
 application_controller_->set_graphics_frame(graphics_frame_);
 application_controller_->set_udp_controller(udp_controller_);
 application_controller_->init_udp_controller();
 application_controller_->set_application_main_window(main_window_);
 application_controller_->set_application_receiver(application_receiver_);
 application_receiver_->set_application_controller(application_controller_);
 application_receiver_->set_application_main_window(main_window_);

 _self_connect_(graphics_frame_ ,save_requested)
    _to_bind_0_(application_controller_ ,handle_save_requested);

 _self_connect_(graphics_frame_ ,image_path_show_folder_requested)
    _to_bind_0_(application_controller_ ,handle_image_path_show_folder);

 _self_connect_(graphics_frame_ ,change_image_border_color_requested)
    _to_bind_0_(application_controller_ ,handle_change_image_border_color);

 _self_connect_(graphics_frame_ ,change_scene_background_color_requested)
    _to_bind_0_(application_controller_ ,handle_change_scene_background_color);

 _self_connect_(graphics_frame_ ,change_scene_margins_color_requested)
    _to_bind_0_(application_controller_ ,handle_change_scene_margins_color);

 _self_connect_(graphics_frame_ ,set_border_visible_requested)
    _to_bind_0_(application_controller_ ,handle_set_border_visible);

 _self_connect_(graphics_frame_ ,unset_border_visible_requested)
    _to_bind_0_(application_controller_ ,handle_unset_border_visible);

 _self_connect_(graphics_frame_ ,set_image_pen_visible_requested)
    _to_bind_0_(application_controller_ ,handle_set_image_pen_visible);

 _self_connect_(graphics_frame_ ,unset_image_pen_visible_requested)
    _to_bind_0_(application_controller_ ,handle_unset_image_pen_visible);

#ifdef USE_Image_Edit
 _self_connect_(graphics_frame_ ,set_edit_transform_open_automatically_requested)
    _to_bind_0_(application_controller_ ,handle_set_edit_transform_open_automatically);

 _self_connect_(graphics_frame_ ,unset_edit_transform_open_automatically_requested)
    _to_bind_0_(application_controller_ ,handle_unset_edit_transform_open_automatically);
#endif//def USE_Image_Edit


 _self_connect_(graphics_frame_ ,expand_window_requested)
    _to_bind_0_(application_controller_ ,handle_expand_window);

 _self_connect_(graphics_frame_ ,unexpand_window_requested)
    _to_bind_0_(application_controller_ ,handle_unexpand_window);

 _self_connect_(graphics_frame_ ,unset_image_pen_visible_requested)
    _to_bind_0_(application_controller_ ,handle_unset_image_pen_visible);


 _self_connect_(graphics_frame_ ,change_image_margins_requested)
    _to_bind_2_(application_controller_ ,handle_change_image_margins);

}

void DHAX_GUI_Environment::init_main_window_controller()
{
 main_window_controller_ = new DHAX_Main_Window_Controller;
 main_window_controller_->set_application_main_window(main_window_);
 main_window_controller_->set_zoom_frame(graphics_frame_->zoom_frame());
 main_window_controller_->set_page_and_search_frame(graphics_frame_->page_and_search_frame());
 main_window_controller_->set_shape_select_frame(graphics_frame_->shape_select_frame());
 main_window_controller_->set_display_image_data(graphics_frame_->display_image_data());
 main_window_controller_->set_image_viewer(image_viewer_);
 main_window_controller_->set_main_window_receiver(main_window_receiver_);
 main_window_controller_->set_application_controller(application_controller_);
 main_window_receiver_->set_main_window_controller(main_window_controller_);
 application_controller_->set_main_window_controller(main_window_controller_);

 // //  here?

#ifdef USE_XCSD
 _self_connect_(graphics_scene_ ,DHAX_Graphics_Scene::show_tierbox_local_color_histogram_requested)
   _to_bind_1_(main_window_receiver_ ,handle_show_local_histogram);
#endif//def USE_XCSD

// QObject::connect(graphics_scene_,
//   &DHAX_Graphics_Scene::show_tierbox_local_color_histogram_requested,
//   main_window_receiver_,
//   &DHAX_Main_Window_Receiver::handle_show_local_histogram);

}

void DHAX_GUI_Environment::init_main_window_receiver()
{
 main_window_receiver_ = new DHAX_Main_Window_Receiver;
 main_window_receiver_->set_application_main_window(main_window_);
}

void DHAX_GUI_Environment::init_application_receiver()
{
 application_receiver_ = new DHAX_Application_Receiver;
 //application_receiver_->set_application_main_window(main_window_);
}

//#define self_connect(x) x->connect(x,

void DHAX_GUI_Environment::init_main_window_signal_generator()
{
 main_window_->init_signal_generator();

// _self_connect_(main_window_->signal_generator() ,take_screenshot_requested)
//    _to_bind_0_(main_window_receiver_ ,handle_take_screenshot);

 #define self_connect_sender  main_window_->signal_generator()
 #define self_connect_receiver  main_window_receiver_

 minimal_self_connect (1, with_callstamp) (take_screenshot);
 minimal_self_connect (_with_callstamp_) (load_image);
 minimal_self_connect (_with_callstamp_) (load_bookmarked_image);

#ifdef USE_XCSD
 minimal_self_connect (_with_callstamp_) (show_xcsd_scene);
 minimal_self_connect (_with_callstamp_) (calculate_local_color_histograms);
 minimal_self_connect (_with_callstamp_) (save_local_color_histograms); 
 minimal_self_connect (1, with_callstamp) (show_fb_gradient_trimap);
#endif


 minimal_self_connect (_with_callstamp_) (load_pdf);

 #undef self_connect_receiver
 #define self_connect_receiver  application_receiver_

 minimal_self_connect (_with_callstamp_) (load_notes);
 minimal_self_connect (_with_callstamp_) (view_contours);
 minimal_self_connect (_with_callstamp_) (view_3d);
 minimal_self_connect (_with_callstamp_) (view_360);
 minimal_self_connect (_with_callstamp_) (prepare_video_recorder);
 minimal_self_connect (_with_callstamp_) (test_ssr_datagram);

//?
 minimal_self_connect (1, with_callstamp) (play_video);
 //?minimal_self_connect (_with_callstamp_) (play_video);

 //  _self_connect_(main_window_->signal_generator() ,play_video_requested)
//     _to_bind_2_(application_receiver_ ,handle_play_video);


 minimal_self_connect (_with_callstamp_) (view_cad);

#ifdef USE_FORGE
 minimal_self_connect (_with_callstamp_) (run_forge_workflow);
#endif//def USE_FORGE

 minimal_self_connect (_with_callstamp_) (launch_edge_detection_dialog);

#ifdef USE_XCSD
 minimal_self_connect (_with_callstamp_) (calculate_fb_gaussian);
 minimal_self_connect (_with_callstamp_) (test_pixel_local_aggregate_color_distance);
 minimal_self_connect (_with_callstamp_) (show_pixel_local_aggregate_color_distance);
 minimal_self_connect (_with_callstamp_) (toroid_run_stats);
 minimal_self_connect (1, with_callstamp) (combined_test_stats);
 minimal_self_connect (1, with_callstamp) (register_test_image);
#endif//def USE_XCSD

 _self_connect_(main_window_->signal_generator() ,quit_requested)
   to_lambda[this]()
 {
  main_window_->close();
 };

#ifdef USE_IFC
 main_window_->signal_generator()->self_connect(SIGNAL(ifc_convert_requested(call_Stamp_u2)),
  application_receiver_, SLOT(handle_ifc_convert(call_Stamp_u2)));
#endif

}

void DHAX_GUI_Environment::load_new_virtual_package_object(QString class_name)
{
 // // temp hard-coded
 if(class_name == "Graphics_Scene_Demo")
 {
  Graphics_Scene_Demo* vpo = new Graphics_Scene_Demo;
  loaded_vpos_["Graphics_Scene_Demo"] = vpo;
  last_loaded_vpo_ = vpo;
  vpo->set_scene(graphics_scene_);
  vpo->set_image_display_scene_item(image_viewer_->image_scene_item());
 }
}


void DHAX_GUI_Environment::init_graphics_view()
{
 graphics_view_ = new DHAX_Graphics_View;
 graphics_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
 graphics_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void DHAX_GUI_Environment::init_graphics_frame_layout(QBoxLayout::Direction qbd,
  QBoxLayout::Direction secqbd)
{
 if(graphics_view_)
   graphics_frame_->set_graphics_view(graphics_view_);

 if(graphics_scene_)
 {
  graphics_frame_->set_graphics_scene(graphics_scene_);
  graphics_scene_->set_containing_graphics_frame(graphics_frame_);
 }

 if(image_viewer_)
 {
  graphics_frame_->set_image_viewer(image_viewer_);
  graphics_frame_->set_display_image_data(image_viewer_->display_image_data());
 }
 graphics_frame_->init_layout(qbd, secqbd);
 if(graphics_scene_)
   graphics_view_->setScene(graphics_scene_);

 QObject::connect(graphics_frame_, &DHAX_Graphics_Frame::close_requested,
    [this](bool)
 {
  main_window_->close();
 });
}

void DHAX_GUI_Environment::init_main_window_frame_layout(QBoxLayout::Direction qbd)
{
 QBoxLayout* qbl = new QBoxLayout(qbd);

 qbl->setContentsMargins(0,0,0,0);
 qbl->setMargin(0);
 qbl->setSpacing(0);

 main_window_frame_->setFrameShape(QFrame::NoFrame);
 main_window_frame_->setLineWidth(0);

 if(graphics_frame_)
   qbl->addWidget(graphics_frame_);
 main_window_frame_->setLayout(qbl);


}


void DHAX_GUI_Environment::show_annotation_on_current_image(
  DHAX_Annotation_Instance* dai)
{
 bool fl = dai->float_dimensions();
 if(dai->fits<QGraphicsRectItem>())
 {
  if(fl)
  {
   QRectF qrf;
   dai->init_as(qrf);
   QGraphicsRectItem* qgri = graphics_scene_->addRect(qrf);
  }
  else
  {
   QRect qr;
   dai->init_as(qr);
   QGraphicsRectItem* qgri = graphics_scene_->addRect(qr);
  }
 }
}

//void DHAX_GUI_Environment::show_image(QString path)
//{
// image_viewer_->load_image(path);
//// QPixmap qpm(path);
//// graphics_scene_->addPixmap(qpm);
//}

void DHAX_GUI_Environment::init_main_window_frame()
{
 main_window_frame_ = new DHAX_Main_Window_Frame;
 main_window_->setCentralWidget(main_window_frame_);
}

void DHAX_GUI_Environment::init_graphics_frame()
{
 graphics_frame_ = new DHAX_Graphics_Frame;
 graphics_frame_->set_application_colors(application_state_->application_colors());
}

void DHAX_GUI_Environment::init_graphics_scene()
{
 graphics_scene_ = new DHAX_Graphics_Scene;
 graphics_scene_->set_background_color(
   application_state_->application_color("scene-background-color"));
// graphics_scene_->set_foreground_color(
//   application_state_->application_color("scene-margins-color"));
}

void DHAX_GUI_Environment::show_main_window()
{
 main_window_->show();
}


void DHAX_GUI_Environment::init_image_viewer()
{
 image_viewer_ = new DHAX_Image_Viewer;
 image_viewer_->set_main_window(main_window_);

 image_viewer_->set_scrolled_image_view(graphics_view_);
 image_viewer_->set_scrolled_image_scene(graphics_scene_);

 image_viewer_->set_application_state(application_state_);
 image_viewer_->display_image_data()->set_application_state(application_state_);

 //QMap<QString, QColor>*


}

